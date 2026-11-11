/* Area r1e, group 13: link list append, sequence step, sound position, slot add, global reset 0x0001D980..0x000527B0. Names inferred. */
#include "r1e.h"

/* 0x0001D980: allocate a fresh link record and append it to the host's
   list. */
void r1e_LinkAppend(R1eLinkHost *h)
{
    R1eLink48 *n = sub_00053AB0(0x48, 0, 0x4CF);
    R1eLink48 *p;
    n->scale = 1.0f;
    n->d00 = 1;
    n->d04 = 0;
    n->next = 0;
    n->d0C = 1;
    n->d10 = 0;
    n->d14 = 0;
    n->d18 = 0;
    n->d1C = 0;
    n->d20 = 0;
    n->d24 = 0;
    n->d28 = 0;
    n->d2C = 0;
    n->d30 = 0;
    n->f38 = 0.0f;
    n->f3C = 0.0f;
    n->d40 = -1;
    n->d44 = 0;
    if (h->first == 0) {
        h->first = n;
        return;
    }
    for (p = h->first; p->next != 0; p = p->next)
        ;
    p->next = n;
}

/* 0x000330A0: step sequence C: load its timer, then run it down and shift
   the queue when it expires (a timer of -1 never expires). */
void r1e_SeqStepC(void)
{
    switch (r1e_seqStateC381860) {
    case 0:
        r1e_seqTimeC381864 = r1e_seqInitC381868;
        r1e_seqStateC381860++;
        break;
    case 1:
        if (r1e_seqTimeC381864 != -1.0f) {
            sub_000720A0(&r1e_seqTimeC381864, 0);
            if (r1e_seqTimeC381864 <= 0.0f) {
                r1e_seqQC381850[0] = r1e_seqQC381850[1];
                r1e_seqQC381850[1] = r1e_seqQC381850[2];
                r1e_seqQC381850[2] = r1e_seqQC381850[3];
                r1e_seqQC381850[3] = 0;
                r1e_seqStateC381860 = 0;
            }
        }
        break;
    }
}

/* 0x00036C00: place the listener at point idx with the given distance and
   pan mode. */
void r1e_ListenerSet(int mode, int idx, float dist)
{
    float gain;
    r1e_lsFlags3DA098 = (r1e_lsFlags3DA098 & ~6u) | 1;
    r1e_lsMode3DA09C = mode;
    sub_000F5D40(r1e_lsPos3DA0A4, r1e_points2836AC[idx]);
    if (0.0f >= dist)
        gain = 128.0f;
    else
        gain = 128.0f / (r1e_fps42C964 * dist);
    r1e_lsGain3DA0A0 = gain;
    switch (mode) {
    case 0:
        r1e_lsPan3DA0B0 = gain + 128.0f;
        break;
    case 1:
        r1e_lsPan3DA0B0 = 0.0f;
        break;
    }
}

/* 0x00037620: add a channel slot; returns its index, or 1 when all ten
   are taken. */
int r1e_SlotAdd(const R1eQuad *pos, int a, int b, int c, int d, int e, float f, const float *dir)
{
    R1eSlot48 *s;
    int n = r1e_g42CE38;
    if (n == 10)
        return 1;
    s = &r1e_slots42CB20[n];
    s->pos = *pos;
    s->state = a;
    s->d24 = d;
    s->d28 = e;
    s->f2C = f;
    s->d30 = b;
    s->d34 = c;
    s->f38 = 0.0f;
    s->f3C = 0.0f;
    s->f40 = 0.0f;
    s->flags = 0;
    sub_000F5D40(s->dir, dir);
    n = ++r1e_g42CE38;
    r1e_slots42CB20[n].state = 0;
    return n - 1;
}

/* 0x000527B0: clear the scene globals and reset the camera defaults. */
void r1e_SceneGlobalsReset(void)
{
    r1e_scene42C8E4 = 0;
    r1e_g42C8B4 = 0;
    r1e_g42C854 = 0;
    r1e_g42C8E0 = 0;
    r1e_g42C958 = 0;
    r1e_g42C9D4 = 0;
    r1e_g42C8F4 = 0;
    r1e_g42C960 = 0;
    r1e_g42C8E8 = 0;
    r1e_g42C8F8 = 0;
    r1e_g42C8D8 = 0;
    r1e_ctx42C8EC = 0;
    r1e_g42C934 = 0;
    sub_001AD940(r1e_camMat3E1220);
    r1e_camFov3E1260 = 45.0f;
    r1e_g42C95C = 0;
    r1e_g42C954 = 1;
    r1e_g42C8F0 = 0.125f;
}
