/* Area r4f: whole-file load at 0x001AA810 (r4f_12). Names inferred. */
#include "r4f.h"

/* 0x001AA810: read a whole file into a new buffer rounded up to 2 KB sectors (one
   overlapped read). Returns 0 with *outBuf (and *outSize if wanted) set, or an HRESULT
   (bad argument, E_FAIL, out of memory) or the last error code. Stack args (path outBuf
   outSize). Kernel callees are stdcall. */
int r4f_FileLoad(const char *path, void **outBuf, uint32_t *outSize)
{
    R4fOverlapped ov;
    uint32_t size, got;
    void *h, *buf;
    if (!path || !outBuf)
        return 0x80070057;
    *outBuf = 0;
    if (outSize)
        *outSize = 0;
    h = sub_001BCD0D(path, 0x80000000u, 1, 0, 3, 0x20000000, 0);
    if (h == (void *)-1)
        return 0x80004005;
    size = sub_001BCCD2(h, 0);
    if (size == (uint32_t)-1) {
        sub_001BC6FD(h);
        return 0x80004005;
    }
    size = (size + 0x7FF) >> 11 << 11;
    buf = r4f_Alloc1A8630(size);
    if (!buf) {
        sub_001BC6FD(h);
        return 0x8007000E;
    }
    ov.internalHigh = 0;
    ov.offset = 0;
    ov.offsetHigh = 0;
    ov.internal = 0;
    ov.event = 0;
    if ((!sub_001BC813(h, buf, size, 0, &ov) && sub_001BC741() != 0x3E5) ||
        !r4f_GetOverlapped1BC7AE(h, &ov, &got, 1)) {
        sub_001AA1D0(buf);
        sub_001BC6FD(h);
        return sub_001BC741();
    }
    *outBuf = buf;
    if (outSize)
        *outSize = got;
    sub_001BC6FD(h);
    return 0;
}

/* 0x001AAAE0: apply a command to the two cues mapped to id (0 play, 1 stop, 2 pause,
   3 resume, 4 prepare) unless the driver is in a special mode, then remember the pair.
   Stack args (cmd id). XACT callees are stdcall. */
void r4f_MusicCueCmd(int cmd, int id)
{
    R4dDrvMsg m, m2;
    R4fCueMap *e;
    int a, b;
    if (r4d_drvMode40E348 != 0)
        return;
    for (e = r4f_cueMap27B720; e != r4f_cueMap27B720 + 16; e++)
        if (e->id == id)
            break;
    if (e == r4f_cueMap27B720 + 16)
        return;
    a = e->cueA;
    b = e->cueB;
    if (cmd == 0) {
        if (r4f_playA40E5CC) {
            m.x = a;
            m.kind = 4;
            m.f0C = 0;
            m.f08 = r4d_g40E310;
            sub_002226F3(r4f_engines40C868[0], &m, &r4f_playA40E5CC);
        }
        if (r4f_playB40E34C) {
            m.f08 = r4f_g40E314;
            m.x = b;
            m.kind = 4;
            m.f0C = 0;
            sub_002226F3(r4f_engines40C868[r4d_drvMode40E348], &m, &r4f_playB40E34C);
        }
    } else if (cmd == 1) {
        if (r4f_playA40E5CC) {
            sub_00222726(r4f_engines40C868[0], -1, 2, r4f_playA40E5CC);
            r4f_playA40E5CC = 0;
        }
        if (r4f_playB40E34C) {
            sub_00222726(r4f_engines40C868[r4d_drvMode40E348], -1, 2, r4f_playB40E34C);
            r4f_playB40E34C = 0;
        }
    } else if (cmd == 2) {
        if (r4f_playA40E5CC)
            sub_0022275D(r4f_engines40C868[0], r4f_playA40E5CC, 1);
        if (r4f_playB40E34C)
            sub_0022275D(r4f_engines40C868[r4d_drvMode40E348], r4f_playB40E34C, 1);
    } else if (cmd == 3) {
        if (r4f_playA40E5CC)
            sub_0022275D(r4f_engines40C868[0], r4f_playA40E5CC, 0);
        if (r4f_playB40E34C)
            sub_0022275D(r4f_engines40C868[r4d_drvMode40E348], r4f_playB40E34C, 0);
    } else if (cmd == 4) {
        m.x = a;
        m.kind = 8;
        m.f0C = 0;
        m.f08 = 0;
        m2.x = b;
        m2.kind = 8;
        m2.f0C = 0;
        m2.f08 = 0;
        sub_002226C0(r4f_engines40C868[0], &m, &r4f_playA40E5CC);
        sub_002226C0(r4f_engines40C868[r4d_drvMode40E348], &m2, &r4f_playB40E34C);
    }
    r4f_curB40C864 = b;
    r4f_curA40E5D0 = a;
}

/* 0x001AB150: nonzero while a driver voice is still playing; when its status queue shows
   it finished (state 1), release it through 0x001AAD40. Stack arg (v). */
int r4f_DrvVoiceBusy(int v)
{
    R4fDrvVoice *d;
    int busy;
    if (!r4f_voiceH40E5D8[v])
        return 0;
    d = &r4f_voices40CF50[v];
    if (!d->h38)
        return 0;
    busy = 1;
    if (!r4f_DrvStatus1AB0D0((const R4fDrvQuery *)&d->w2C, &d->state48)) {
        do {
            if (d->state48 == 1)
                busy = 0;
        } while (!r4f_DrvStatus1AB0D0((const R4fDrvQuery *)&d->w2C, &d->state48));
        if (!busy)
            sub_001AAD40(busy, d->id00, d->f04, v);
    }
    return busy;
}

/* 0x001AAE20: wait for a playing driver voice to report finished (state 1 without
   flag 8) and release it through 0x001AAD40; gives up when the query fails.
   Stack arg (v). XACT callee is stdcall. */
void r4f_DrvVoicePoll(int v)
{
    R4fDrvVoice *d = &r4f_voices40CF50[v];
    R4fDrvQuery q;
    R4fDrvStatus st;
    if (d->b28 != 1 || !d->f30 || !d->h38)
        return;
    memset(&q, 0, sizeof(q));
    memset(&st, 0, sizeof(st));
    q.h0C = d->h38;
    q.f04 = d->f30;
    q.w02 = 4;
    q.f08 = -1;
    if (sub_00222573(r4d_drvDev40E690, &q, &st))
        return;
    while (st.state00 != 1 || (st.flags02 & 8)) {
        if (sub_00222573(r4d_drvDev40E690, &q, &st))
            return;
    }
    sub_001AAD40(0, d->id00, d->f04, d->f24);
}


/* 0x001AC370: prepare slot i for sound snd, wait (polling with a short delay) until it is
   ready or reports failure, then start it through 0x001AC2E0. Stack args (snd i) with snd
   a 16-bit value. Calls 0x001AD1B0 (with the sound on the stack), 0x001ACF00, 0x001ACF30
   and 0x001ACF20 with ECX=slot; 0x001BD0D6 is stdcall. */
void r4f_DrvStartWait(int snd, int i)
{
    R4eDrvSlot *s = &aac_g40E604[i];
    r4f_SlotPrepare1AD1B0(s, (short)snd);
    if (!sub_001ACF00(s)) {
        do {
            sub_001ACF30(s);
            if (sub_001ACF20(s))
                break;
            sub_001BD0D6(0, 1);
        } while (!sub_001ACF00(s));
    }
    r4f_DrvStart(snd, i);
}
