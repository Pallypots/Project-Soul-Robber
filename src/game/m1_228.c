/* Area m1, file 228: bone/node helpers (register inputs per docs/verification.md). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Bone228 { float r0[4], r1[4], r2[4], v30[4], v40[4]; uint8_t unk50[0x20]; float v70[3], w7C;
    uint8_t unk80[0x108 - 0x80]; } M1Bone228;
typedef struct M1Mdl228 { uint8_t unk00[0xC0]; int32_t n0C0; M1Bone228 *bones0C4; } M1Mdl228;
typedef struct M1Obj228 { uint8_t unk00[0x20]; M1Mdl228 *mdl20; } M1Obj228;
typedef struct M1Mtx228 { float m[4][4]; } M1Mtx228;
extern float a50_frameUnits;
void sub_000F5D40(void *dst, const void *src);
void sub_001AD7C0(float *out, const float *in, const M1Mtx228 *m);
void sub_001ADAF0(float *out, const float *a, const float *b);

/* 0x001700C0: for every bone after the root, rotate v40 by the bone's 3x3 basis, add v30 into v70 (w=1) and
   advance the v30.y phase by 0.08 per frame unit (regargs: o=EAX). */
void m1_BoneStep1700C0(M1Obj228 *o)
{
    M1Mdl228 *m = o->mdl20;
    int i;
    for (i = 1; i < m->n0C0; i++) {
        M1Bone228 *b = &m->bones0C4[i];
        M1Mtx228 x;
        sub_000F5D40(x.m[0], b->r0);
        sub_000F5D40(x.m[1], b->r1);
        sub_000F5D40(x.m[2], b->r2);
        x.m[3][0] = 0.0f;
        x.m[3][1] = 0.0f;
        x.m[3][2] = 0.0f;
        x.m[3][3] = 1.0f;
        sub_001AD7C0(b->v40, b->v40, &x);
        sub_001ADAF0(b->v70, b->v70, b->v30);
        b->w7C = 1.0f;
        b->v30[1] += a50_frameUnits * 0.08f;
    }
}

typedef struct M1Ent228 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0xC]; M1Mdl228 *mdl20; } M1Ent228;
typedef struct M1Seq228 { uint8_t unk00[0x54]; int32_t st54; float t58; uint8_t unk5C[0x10]; int32_t side6C; } M1Seq228;
void sub_00170400(M1Ent228 *o);                              /* regargs: o=EAX */
void sub_0016FF30(M1Ent228 *o);
void sub_00036750(M1Ent228 *o, int32_t pose);
void sub_00170570(int32_t mode, M1Ent228 *o, M1Seq228 *s);   /* regargs: mode=EAX o=ECX, s on stack */
void sub_000ED780(M1Ent228 *o);

/* 0x001707F0: three-stage break-apart sequence, mode 0: restart, burst, then step bones until t58 > 1 and destroy.
   Calls 0x1700C0 with o in EAX, 0x170400 with o in EAX, 0x170570 with mode=EAX o=ECX. */
void m1_BreakSeq1707F0(M1Ent228 *o, M1Seq228 *s)
{
    switch (s->st54) {
    case 0:
        sub_00170400(o);
        o->flags10 |= 0xD;
        s->st54++;
        return;
    case 1:
        sub_0016FF30(o);
        sub_00036750(o, s->side6C == 1 ? 2 : 0);
        sub_00170570(0, o, s);
        s->st54++;
        return;
    case 2:
        m1_BoneStep1700C0((M1Obj228 *)o);
        if (s->t58 > 1.0f)
            sub_000ED780(o);
        return;
    }
}

/* 0x00170880: same sequence as 0x1707F0 with mode 1. */
void m1_BreakSeq170880(M1Ent228 *o, M1Seq228 *s)
{
    switch (s->st54) {
    case 0:
        sub_00170400(o);
        o->flags10 |= 0xD;
        s->st54++;
        return;
    case 1:
        sub_0016FF30(o);
        sub_00036750(o, s->side6C == 1 ? 2 : 0);
        sub_00170570(1, o, s);
        s->st54++;
        return;
    case 2:
        m1_BoneStep1700C0((M1Obj228 *)o);
        if (s->t58 > 1.0f)
            sub_000ED780(o);
        return;
    }
}

typedef struct M1Slot228 { uint8_t unk00[8]; int32_t kind8; uint8_t unk0C[0x150 - 0xC]; } M1Slot228;
typedef struct M1Act228 { uint8_t unk00[4]; int32_t mode4, sub8; uint32_t flags0C, flags10; uint8_t unk14[0x4C];
    uint8_t pos60[0x10]; } M1Act228;
typedef struct M1Seq2b228 { uint8_t unk00[0x54]; int32_t st54; float t58; uint8_t unk5C[0x10]; int32_t n6C;
    uint8_t unk70[4]; float f74; uint8_t v78[0x10]; } M1Seq2b228;
extern int32_t *b16_task3F92E8;
extern M1Slot228 *b16_taskId3F92EC;
void sub_0016FE00(M1Slot228 *s);
void sub_000A8ED0(int32_t n, void *pos, void *v, int32_t z);

/* 0x00170F60: three-stage sequence: claim the kind-11 slot (hangs if none), set the actor to mode 9 pose 1 and
   spawn (n6C+1)*k effects, k = 1 or (int)-f74 when f74 < 0; then burst; then step bones until t58 > 1 and destroy.
   Calls 0x1700C0 with o in EAX. */
void m1_SpawnSeq170F60(M1Act228 *o, M1Seq2b228 *s)
{
    switch (s->st54) {
    case 0: {
        int n = *b16_task3F92E8;
        M1Slot228 *t = b16_taskId3F92EC;
        int i, k;
        for (i = 0; i < n; i++)
            if (t[i].kind8 == 0xB)
                break;
        if (i >= n)
            for (;;) ;
        sub_0016FE00(&t[i]);
        o->mode4 = 9;
        o->sub8 = 0;
        o->flags0C &= ~0x20u;
        o->flags10 |= 0xC;
        sub_00036750((M1Ent228 *)o, 1);
        if (s->f74 >= 0.0f)
            k = 1;
        else
            k = _mm_cvtt_ss2si(_mm_set_ss(0.0f - s->f74));
        sub_000A8ED0((s->n6C + 1) * k, o->pos60, s->v78, 0);
        s->st54++;
        return;
    }
    case 1:
        sub_0016FF30((M1Ent228 *)o);
        s->st54++;
        return;
    case 2:
        m1_BoneStep1700C0((M1Obj228 *)o);
        if (s->t58 > 1.0f)
            sub_000ED780((M1Ent228 *)o);
        return;
    }
}
