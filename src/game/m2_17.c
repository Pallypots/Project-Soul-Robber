/* Area m2, file 17: small dispatch helpers. Names inferred. */
#include <stdint.h>

typedef struct M2Curve17 { uint32_t flags0; int32_t kind4; float value8; } M2Curve17;
typedef struct M2LerpOp17 { void *a; float (*eval)(M2Curve17 *c); } M2LerpOp17;
typedef struct M2Track17 { int32_t unk0; int32_t kind4; void *keys8; } M2Track17;
typedef struct M2TrackType17 { void *a, *b; float (*eval)(M2Track17 *t); void *c, *d; } M2TrackType17;
extern M2LerpOp17 a6b_lerpOps[5];
extern M2TrackType17 a6b_trackTypes[5];
void sub_00083520(void *a, void *b, void *c);
extern int r1e_g41316C, r1e_g413170;

/* 0x1DA90: forwards to 0x83520 (argument count assumed; the jump forwards whatever the caller pushed). */
void m2_Thunk1DA90(void *a, void *b, void *c) {
    sub_00083520(a, b, c);
}

/* 0x7F650: value of curve c: animated curves (flag 2) are evaluated by their kind's operation, others return their constant. */
float m2_CurveValue7F650(M2Curve17 *c) {
    if (c->flags0 & 2) return a6b_lerpOps[c->kind4].eval(c);
    return c->value8;
}

/* 0x7EF00: value of track t, 0 when there is no track or it has no keys; otherwise evaluated by its type. */
float m2_TrackValue7EF00(M2Track17 *t) {
    if (t == 0 || t->keys8 == 0) return 0.0f;
    return a6b_trackTypes[t->kind4].eval(t);
}

typedef struct M2EvAct17 { uint32_t flags0; uint8_t unk04[0xFC]; float t100; } M2EvAct17;

/* 0x9F040: event handler: events 1-3 arm flag 0x400, event 15 arms flag 0x800 with its timer reset, events 34-35 arm flag 0x200 (each clears flag 0x80) and return 1; other events return 0. */
int m2_ActEvent9F040(M2EvAct17 *o, int *ev) {
    switch (*ev) {
    case 1: case 2: case 3:
        o->flags0 = (o->flags0 & ~0x80u) | 0x400;
        return 1;
    case 15:
        o->flags0 = (o->flags0 & ~0x80u) | 0x800;
        o->t100 = 0.0f;
        return 1;
    case 34: case 35:
        o->flags0 = (o->flags0 & ~0x80u) | 0x200;
        return 1;
    }
    return 0;
}

typedef struct M2Act17 { uint32_t flags0; int32_t kind4; uint8_t unk08[0x38]; int32_t state40; uint8_t unk44[0x2C]; float pos70[4]; uint8_t unk80[0xA0]; uint8_t *p120; uint8_t unk124[0x13C]; uint8_t sub260[0x3C]; int32_t i29C; } M2Act17;
void r6e_ActorShow(void *o, int v);
void sub_000A4010(void *o, int v);
int  sub_000833E0(void *a);
void sub_000A41D0(void *o, int v);
M2Act17 *sub_000A42C0(int id);
void sub_000A9340(int a, float *pos);

/* 0x9EEA0: closing actor step: states 0-1 hide it (state 0 also plays close anim 1) and finish (5); states 2-3 play close anim 2 or 4 and wait (4); state 4 finishes once its animation is done. */
void m2_CloseStep9EEA0(M2Act17 *o) {
    int a;
    if (o->p120 == 0) return;
    switch (o->state40) {
    case 0: r6e_ActorShow(o, 0); sub_000A4010(o, 1); o->state40 = 5; break;
    case 1: r6e_ActorShow(o, 0); o->state40 = 5; break;
    case 2: a = 2; goto anim;
    case 3: a = 4;
    anim:
        sub_000A4010(o, a); o->state40 = 4; break;
    case 4: if (sub_000833E0(*(void **)(o->p120 + 0x30))) o->state40 = 5; break;
    }
}

/* 0x94E00: in world 1 area 5, actor id of kind 0x13, 0x15, 0x17 or 0x96 that is not already triggered starts its sub-object and an effect at its position. -1 for no id or no actor, else 1. */
int m2_Trigger94E00(int id) {
    M2Act17 *o;
    if (id == 0) return -1;
    if (r1e_g41316C == 1 && r1e_g413170 == 5) {
        o = sub_000A42C0(id);
        if (o == 0) return -1;
        switch (o->kind4) {
        case 0x13: case 0x15: case 0x17: case 0x96:
            if (o->i29C != 1) {
                sub_000A41D0(o->sub260, 1);
                sub_000A9340(0, o->pos70);
            }
            break;
        }
    }
    return 1;
}
