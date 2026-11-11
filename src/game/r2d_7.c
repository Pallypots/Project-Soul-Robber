/* Area r2d, group 7: effect query, pool allocation and boss scene helpers (0x000E8CA0..0x0012D658). Names inferred. */
#include "r2d.h"
#include <string.h>

/* Zero a block of n bytes the way the original's inlined memset does
   (dwords, then the remaining bytes). The intrinsics are used only for the
   32-bit x86 comparison build; other targets use memset. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <intrin.h>
#define R2D_ZERO(p, n) (__stosd((unsigned long *)(p), 0, (n) >> 2), \
                        __stosb((unsigned char *)(p) + ((n) & ~3u), 0, (n) & 3))
#else
#define R2D_ZERO(p, n) memset((p), 0, (n))
#endif

/* 0x000E8CA0: effect record idx is active in state 3 with its timer within
   60 of 110. */
int r2d_FxNearEnd(unsigned idx)
{
    R2dFx *f;
    if (idx > 0x20)
        for (;;) ;
    f = &r2c_fx3F1B5C[idx];
    if ((f->flags & 1) && f->state04 == 3 && f->t10 + 60.0f >= 110.0f)
        return 1;
    return 0;
}

/* 0x000F5E30: set the mover's two vectors from a and b, both scaled by
   s (0x1ADB60), and clear +0x118. */
void r2d_MoverSet(R2dMover *o, float s, const R2dVec4 *a, const R2dVec4 *b)
{
    if (!o)
        return;
    o->v118 = 0;
    o->vF8 = *a;
    o->v108 = *b;
    sub_001ADB60(&o->vF8, &o->vF8, s);
    sub_001ADB60(&o->v108, &o->v108, s);
}

/* 0x000EED90: allocate and zero the pool of kind 7 (0x118-byte entries).
   Returns 1. */
int r2d_PoolInit7(void)
{
    unsigned n;
    g_acb_3F60F0 = sub_00053AB0(sub_000F30E0(7) * 0x118, 0, 0x176);
    n = sub_000F30E0(7) * 0x118;
    R2D_ZERO(g_acb_3F60F0, n);
    return 1;
}

/* 0x00106350: allocate and zero the pool of kind 0 (0xE8-byte entries). */
void r2d_PoolInit0(void)
{
    unsigned n;
    b10_obj3F6138 = sub_00053AB0(sub_000F30E0(0) * 0xE8, 0, 0xC9);
    n = sub_000F30E0(0) * 0xE8;
    R2D_ZERO(b10_obj3F6138, n);
}

/* 0x00108B10: allocate and zero the pool of kind 2 (0xFC-byte entries). */
void r2d_PoolInit2(void)
{
    unsigned n;
    b10_obj3F6150 = sub_00053AB0(sub_000F30E0(2) * 0xFC, 0, 0x14E);
    n = sub_000F30E0(2) * 0xFC;
    R2D_ZERO(b10_obj3F6150, n);
}

/* 0x00102F40: the boss model (kind 1 or 2) has its +0xD8 value between 15
   and 50 frames' worth. */
int r2d_ScnInWindow(void)
{
    R2dScnModel *m = b10_scr->node8C->m30;
    float t, d;
    if (m->kind08 == 1 || m->kind08 == 2) {
        t = 1.0f / a50_frameUnits;
        d = *(float *)(m->p14 + 0xD8);
        if (d >= t * 15.0f && t * 50.0f >= d)
            return 1;
    }
    return 0;
}

/* 0x00114400: reset the owner's hook record and attach it to row idx of the
   source's model table. */
void r2d_HookAttach(R2dHookSrc *src, R2dHookOwner *o, int idx)
{
    R2dHook *h = &o->hook114;
    sub_001B2150(h);
    h->owner34 = src;
    h->fn04 = sub_00113FB0;
    h->v10 = 0;
    h->v1C = 0;
    h->f14 = 0.0f;
    h->f2C = 0.0f;
    h->f30 = 0.0f;
    sub_001B2160(src->m20->rows + idx * 0x180, h);
}

/* 0x0012D600: apply 0x1208A0(v) to every object of keys (2, 5) and (2, 0xF). */
void r2d_ApplyToKeys(int v)
{
    void *e;
    for (e = r2c_FindKey(2, 5); e; e = r2c_FindKey(-1, -1))
        sub_001208A0(e, v);
    for (e = r2c_FindKey(2, 0xF); e; e = r2c_FindKey(-1, -1))
        sub_001208A0(e, v);
}

/* 0x001153D0: pos is more than 10 units (XZ) from the player and from every
   object of key 2.
   regargs: pos=ESI */
int r2d_PosIsClear(const float *pos)
{
    uint8_t *e;
    if (10.0f >= sub_001B2770(pos, (uint8_t *)g_playerObj + 0x60))
        return 0;
    for (e = r2c_FindKey(2, -1); e; e = r2c_FindKey(-1, -1))
        if (10.0f >= sub_001B2770(e + 0x60, pos))
            return 0;
    return 1;
}
