/* Area r2c, group 6: script boss and effect-queue helpers (0x00104AF0..0x001090E2). Names inferred. */
#include "r2c.h"

/* 0x00104AF0: stop the script boss's +0x238 sound and +0x23C effect, then
   send cue 0x39 (0x101280). */
void r2c_ScrStop(void)
{
    R2cScr *b = b10_scr;
    int32_t *snd = &b->h238;
    if (*snd != -1) {
        sub_00048250(*snd);
        *snd = -1;
    }
    if (b->h23C) {
        sub_00033A40(b->h23C);
        b->h23C = 0;
    }
    sub_00101280(0x39);
}

/* 0x00105F90: attach model m to the script boss (finishing with 0x105D80).
   Returns m. */
R2cModel *r2c_ScrAttach(R2cModel *m)
{
    R2cScr *b;
    if (!m)
        for (;;) ;
    b = b10_scr;
    b->sub8C = m;
    sub_000F3AA0((R2cBossObj *)b);
    sub_0001D8B0(b, 5);
    sub_0001D8D0(m, b);
    sub_0001D8B0(b->comp10, 0xD);
    sub_0001D8D0(m, b->comp10);
    sub_0001E9B0(aec_ctx42C8E4, m, m->v14C, 5, 0x11);
    sub_0001EBF0(m, 1);
    sub_000EE270(b->comp10);
    sub_00105D80();
    return m;
}

/* 0x00106020: deactivate an active model m (clear flags 1 and 2) and remove
   its kind-5 and kind-0x0D components. 1 when m was active. */
int r2c_ScrDetach(R2cModel *m)
{
    void *c5, *cd;
    sub_000E3BA0(sub_000E0770());
    if (!(m->flags0C & 1))
        return 0;
    sub_00033B30(m);
    m->flags10 |= 0xD;
    m->flags0C &= ~3u;
    sub_0001EB80(m);
    c5 = sub_0001D960(m, 5);
    cd = sub_0001D960(m, 0xD);
    sub_0001D910(m, c5);
    sub_0001D910(m, cd);
    return 1;
}

/* 0x00106170: allocate and clear the 0x90-byte object at 0x3F6134. */
void r2c_Obj90Create(void)
{
    R2cObj90 *o = (R2cObj90 *)sub_00053AB0(sub_000F30E0(9) * 0x90, 0, 0x120);
    R2C_ZERO(o, 0x90);
    b10_obj3F6134 = o;
    o->sub8C = 0;
}

/* 0x001062C0: attach model m to the object at 0x3F6134 (finishing with
   0x1061B0). Returns m. */
R2cModel *r2c_Obj90Attach(R2cModel *m)
{
    R2cObj90 *b;
    if (!m)
        for (;;) ;
    b = b10_obj3F6134;
    if (!b)
        for (;;) ;
    b->sub8C = m;
    sub_000F3AA0((R2cBossObj *)b);
    sub_0001D8B0(b, 5);
    sub_0001D8D0(m, b);
    sub_0001D8B0(b->comp10, 0xD);
    sub_0001D8D0(m, b->comp10);
    sub_0001E9B0(aec_ctx42C8E4, m, m->v14C, 5, 0x11);
    sub_0001EBF0(m, 1);
    sub_000EE270(b->comp10);
    sub_001061B0();
    return m;
}

/* 0x00106550: for a kind-3 key with sub-id 0, release the four children of
   its owner (0x1208A0(child, 5) for active ones) and clear the slots. */
void r2c_ReleaseKids(R2cKeyObj *o)
{
    R2cModel **p;
    int n;
    if (!o)
        for (;;) ;
    if (o->kind04 != 3 || o->v08 != 0)
        return;
    p = ((R2cComp5b *)sub_0001D960(o, 5))->owner64->kids9A8;
    for (n = 4; n; n--, p++) {
        if (*p) {
            if ((*p)->flags0C & 1)
                sub_001208A0(*p, 5);
            *p = 0;
        }
    }
}

/* 0x00109050: queue a new attached effect of the given kind in the 5-entry
   list at 0x3F613C: finished entries are dropped (later ones move up); when
   the queue is full or empty-headed, a still running head is freed and
   replaced. */
void r2c_PushEffect(void *obj, int kind)
{
    int i, n;
    for (i = 0; i < 5; i++) {
        if (!r2c_fx3F613C[i])
            break;
        if (!sub_000336A0(r2c_fx3F613C[i])) {
            for (; i < 4 && r2c_fx3F613C[i + 1]; i++)
                r2c_fx3F613C[i] = r2c_fx3F613C[i + 1];
            break;
        }
    }
    if (i == 5)
        i = 0;
    n = i;
    if (n == 0 && r2c_fx3F613C[0] && sub_000336A0(r2c_fx3F613C[0]))
        sub_00033A70(r2c_fx3F613C[0]);
    r2c_fx3F613C[n] = sub_00036750(obj, kind);
}
