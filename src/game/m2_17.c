/* Area m2, file 17: small dispatch helpers. Names inferred. */
#include <stdint.h>

typedef struct M2Curve17 { uint32_t flags0; int32_t kind4; float value8; } M2Curve17;
typedef struct M2LerpOp17 { void *a; float (*eval)(M2Curve17 *c); } M2LerpOp17;
typedef struct M2Track17 { int32_t unk0; int32_t kind4; void *keys8; } M2Track17;
typedef struct M2TrackType17 { void *a, *b; float (*eval)(M2Track17 *t); void *c, *d; } M2TrackType17;
extern M2LerpOp17 a6b_lerpOps[5];
extern M2TrackType17 a6b_trackTypes[5];
void sub_00083520(void *a, void *b, void *c);

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
