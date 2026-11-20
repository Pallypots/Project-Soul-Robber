/* Area m1, file 265: AI slot setup. Names inferred. */
#include <stdint.h>

typedef struct M1Ob265 { uint8_t unk00[0xC]; uint32_t flagsC, flags10; uint8_t unk14[0x110]; int32_t f124; } M1Ob265;
typedef struct M1Sl265 { M1Ob265 *o0; void *a4; int32_t f8; uint8_t unkC[4]; int32_t f10; uint8_t unk14[0x30]; int32_t f44, f48; } M1Sl265;  /* 0x4C */
typedef struct M1Ac265 { uint8_t unk00[0x278]; M1Sl265 *s278; void *upd27C; uint8_t unk280[8]; void *msg288; const void *tbl28C;
    const void *tbl290; } M1Ac265;
extern M1Sl265 m1_aiSlots3FE988[4];
extern const uint8_t m1_aiTbl32C3A8[], m1_aiTbl32C3B4[];
void sub_00188CA0(void);
void sub_00188D00(void);
void sub_000F3FD0(M1Ob265 *o);
void m1_AiGoto113040(M1Ob265 *o, M1Ac265 *a, int32_t st);

/* 0x00189020: give actor a (object o) a free AI slot (4 slots): clear and claim it, set o's draw flags, install
   this AI's update/message handlers and tables, then start AI state 0. Returns 1, or 0 when there is no slot. */
int32_t m1_AiAttach189020(M1Ob265 *o, M1Ac265 *a, int32_t arg)
{
    M1Sl265 *e;
    int32_t i;
    if (!o || !a) return 0;
    for (i = 0, e = m1_aiSlots3FE988; (intptr_t)e < (intptr_t)(m1_aiSlots3FE988 + 4); e++, i++)
        if (e->o0 == 0) goto found;
    return 0;
found:
    e = &m1_aiSlots3FE988[i];
    if (e) {
        e->o0 = 0;
        e->a4 = 0;
        e->f44 = 0;
        e->f48 = 0;
    }
    if (i >= 4) return 0;
    e->o0 = o;
    e->a4 = a;
    a->s278 = e;
    o->flagsC = (o->flagsC & ~0xE0u) | 3;
    o->f124 = 0;
    o->flags10 |= 0x44D;
    a->tbl28C = m1_aiTbl32C3A8;
    a->tbl290 = m1_aiTbl32C3B4;
    a->upd27C = (void *)sub_00188CA0;
    a->msg288 = (void *)sub_00188D00;
    e->f8 = arg;
    e->f10 = 0;
    sub_000F3FD0(o);
    m1_AiGoto113040(o, a, 0);
    return 1;
}

typedef struct M1Sc265 { uint8_t unk00[0x50]; float v50[1]; float yaw54; } M1Sc265;
typedef struct M1Bn265 { uint8_t unk00[0x70]; float pos70[4]; } M1Bn265;
typedef struct M1Po265 { uint8_t unk00[8]; int32_t kind8; uint8_t unk0C[0x44]; float v50[4]; float pos60[4]; } M1Po265;
M1Sc265 *sub_000FC4B0(void);
M1Bn265 *sub_0001D0F0(M1Sc265 *s, int32_t bone);
void sub_000F5D40(float *d, const float *s);
void sub_001AD940(float *m);
void sub_001AD8E0(float *out, const float *in, float a);
void sub_001AD9B0(float *out, const float *m, const float *v);
extern const float m1_ofs318E28[4];

/* 0x000F94B0: put o on the scene's bone for its kind (3 -> bone 4, 4 -> 3, 5 -> 2; other kinds use an
   undefined bone in the original, which reads the argument slot) and copy the scene's facing; kind 5 is also
   pushed out by a fixed offset turned to the scene's yaw. */
void m1_PlaceOnBoneF94B0(M1Po265 *o)
{
    M1Sc265 *s = sub_000FC4B0();
    int32_t bone;
    float m[16], v[4];
    if (o->kind8 == 3)
        bone = 4;
    else if (o->kind8 == 4)
        bone = 3;
    else if (o->kind8 == 5)
        bone = 2;
    else
        bone = (int32_t)(intptr_t)o;   /* XBOX32: original reads the uninitialised slot (arg o) */
    sub_000F5D40(o->v50, s->v50);
    sub_000F5D40(o->pos60, sub_0001D0F0(s, bone)->pos70);
    if (o->kind8 == 5) {
        sub_001AD940(m);
        sub_001AD8E0(m, m, s->yaw54);
        sub_001AD9B0(v, m, m1_ofs318E28);
        o->pos60[0] += v[0];
        o->pos60[1] += v[1];
        o->pos60[2] += v[2];
        *(volatile float *)&o->pos60[3] = o->pos60[3];
    }
}
