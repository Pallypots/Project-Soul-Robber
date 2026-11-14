/* Area m1, file 203: ambient sound helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Fx203 {
    uint32_t flags0; void *p4; uint8_t unk08[0xC]; uint8_t list14[0xC]; struct M1Fx203 *self20; float f24; int32_t bit28;
} M1Fx203;
typedef struct M1FxN203 { struct M1FxN203 *next0; uint8_t unk04[8]; M1Fx203 *fxC; } M1FxN203;
typedef struct M1FxL203 { int32_t unk0; M1FxN203 *first4; } M1FxL203;
typedef struct M1AmN203 { struct M1AmN203 *next0; uint8_t unk04[0xC]; int32_t bit10; uint8_t unk14[0xC]; uint8_t e20[0x20]; } M1AmN203;
typedef struct M1AmO203 { int32_t unk0; M1AmN203 *first4; } M1AmO203;
extern int32_t a5b_g3E6040;
extern M1FxL203 r1e_fxListB3E5AAC;
extern uint8_t r1e_fxPool3E4B70[];
int   r2b_TestBit(int bit);
void *r1c_PoolTake(void *pool, int size);
void  a3c_Clear16(void *l);
void  a5b_RangeInit(M1Fx203 *fx);
void  a4c_ListAppend(void *list, void *node);
void  a5b_PairSet(M1Fx203 *fx, void *e);

/* 0x5C430: start an ambient sound for every active node of o (story bit set or none) that is not already playing. */
void m1_AmbientStart05C430(M1AmO203 *o) {
    M1AmN203 *n; M1FxN203 *a; uint8_t *p; M1Fx203 *fx;
    if (o == 0 || a5b_g3E6040 != 0) return;
    for (n = o->first4; n != 0; n = n->next0) {
        if (n->bit10 != -1 && !r2b_TestBit(n->bit10)) continue;
        for (a = r1e_fxListB3E5AAC.first4; a != 0; a = a->next0)
            if (a->fxC->p4 == (void *)n->e20) goto next;
        p = r1c_PoolTake(r1e_fxPool3E4B70, 0x3C);
        if (p == 0) continue;
        fx = (M1Fx203 *)(p + 0x10);
        if (fx) {
            a3c_Clear16(fx->list14);
            a5b_RangeInit(fx);
            fx->f24 = 1.0f;
            fx->bit28 = -1;
        }
        fx->self20 = fx;
        a4c_ListAppend(&r1e_fxListB3E5AAC, fx->list14);
        { uint8_t *volatile ev = n->e20; uint8_t *e = ev;
          *(uint8_t **)(e + 0xC) = e + 0x10;
          a5b_PairSet(fx, e); }
        fx->flags0 |= 1;
        fx->bit28 = n->bit10;
    next:;
    }
}

typedef struct M1Task203 { int32_t active0; void *owner4; uint8_t unk08[0x10]; uint32_t flags18; uint8_t unk1C[0x84]; } M1Task203;
extern M1Task203 m1_tasks3FE488[8];

/* 0x185540: release every task owned by o: mark it done (flag 8) and clear the owner. */
void m1_TasksRelease185540(void *o) {
#define M1_REL203(i) if (m1_tasks3FE488[i].active0 != 0 && m1_tasks3FE488[i].owner4 == o) { m1_tasks3FE488[i].flags18 |= 8; m1_tasks3FE488[i].owner4 = 0; }
    M1_REL203(0) M1_REL203(1) M1_REL203(2) M1_REL203(3)
    M1_REL203(4) M1_REL203(5) M1_REL203(6) M1_REL203(7)
#undef M1_REL203
}

typedef struct M1Pu203 { uint8_t unk00[0x68]; float f68; uint8_t unk6C[8]; float t74; uint8_t unk78[0x200]; int32_t i278; } M1Pu203;
extern float m1_frameRate42C85C;
void m1_AiGoto113040(void *a, void *e, int st);
void sub_000EEA60(void *o, const float *s);
void m1_AnimScale0EE6D0(void *o, float s);

/* 0x1789E0: pulse while a fuse runs: go to state 3 when it expires; in the last 3 units swell the object and alternate its animation speed in quickening beats. */
void m1_FusePulse1789E0(void *o, M1Pu203 *e) {
    float v[4];
    if (0.0f > e->t74) m1_AiGoto113040(o, e, 3);
    if (3.0f > e->t74) {
        v[1] = 1.0f; v[2] = 1.0f; v[3] = 1.0f;
        v[0] = (3.0f - e->t74) * 0.333333343f + 1.0f;
        sub_000EEA60(o, v);
    }
    { float volatile k = 2.0f; e->f68 -= m1_frameRate42C85C * k; }
    if (0.0f > e->f68 && 3.0f > e->t74) {
        if (e->i278 & 2) { e->i278 = 0; m1_AnimScale0EE6D0(o, 1.0f); }
        else { e->i278 = 2; m1_AnimScale0EE6D0(o, 0.999899983f); }
        e->f68 = e->t74 * 0.125f;
    }
}
