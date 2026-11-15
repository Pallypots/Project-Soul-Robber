/* Area m2, file 13. Names inferred. */
#include <stdint.h>

typedef struct M2Act13 { uint8_t unk00[0x40]; int32_t state40; uint8_t unk44[0xDC]; uint8_t *p120; } M2Act13;
extern uint8_t *aab_player;
uint8_t *r4i_Joint(uint8_t *q, int idx);
void  a3c_VecCopy(float *d, const float *s);
void  m1_FxAdd0C4DF0(uint8_t *q, int a, float b, int c, float d, int e, float f, float *v0, float *v1, float *v2);
float rbj_Distance(const float *a, const float *b);
void  sub_000A41D0(void *o, int v);
void  r6e_ActorShow(void *o, int v);

/* 0x95350: proximity effect actor. State 0 sparks joints 5..9 and goes to state 1 once the player is 50 units away or more; state 1 goes back to state 0 when the player is within 50; state 10 releases and hides it. */
void m2_SparkStep95350(M2Act13 *o) {
    float a[4], c[4], b[4];
    uint8_t *q = o->p120;
    int i;
    a[0] = 0.0f; a[1] = 0.0f; a[2] = 0.0f; a[3] = 1.0f;
    b[0] = 0.0f; b[1] = 0.0f; b[2] = 0.0f; b[3] = 1.0f;
    c[0] = 0.0f; c[1] = 0.0f; c[2] = 0.0f; c[3] = 1.0f;
    switch (o->state40) {
    case 0:
        for (i = 0; i < 5; i++) {
            uint8_t *j = r4i_Joint(q, i + 5);
            if (j == 0) for (;;) ;
            a3c_VecCopy(a, (float *)(j + 0x70));
            m1_FxAdd0C4DF0(q, 0, 1.0f, 0, 3.0f, 0, 3.0f, a, b, c);
        }
        if (rbj_Distance((float *)(aab_player + 0x60), (float *)(q + 0x60)) >= 50.0f) o->state40++;
        break;
    case 1:
        if (50.0f >= rbj_Distance((float *)(aab_player + 0x60), (float *)(q + 0x60))) o->state40--;
        break;
    case 10:
        sub_000A41D0(o, -1);
        r6e_ActorShow(o, 0);
        break;
    }
}

typedef struct M2Hit13 { int32_t i0; struct M2Hit13 *next4; void *owner8; } M2Hit13;
typedef struct M2Coll13 { struct M2World13 *w0; struct M2Coll13 *next4; M2Hit13 *hits8; uint8_t *nodeC; int32_t v10; int32_t i14; float f18; uint8_t *thing1C; int32_t i20; int32_t i24; } M2Coll13;
typedef struct M2World13 { uint8_t unk00[4]; M2Coll13 *list4; uint8_t unk08[8]; float max10[4]; float min20[4]; } M2World13;
extern uint8_t *r6c_src3ECA7C;
extern uint8_t *r6c_p3ECA38;
extern M2Hit13 *r6c_v3ECA1C;
extern M2Hit13 *r6c_hits3ECA00;
void sub_00083B70(float *outMax, float *outMin, uint8_t *n);
void sub_00080E20(int idx);
void *a5b_AllocCur(int size, int a, int tag);

/* 0x80F90: add model node n to the collision world: widen the world box by the node's box, build the node's hit list (0 when it has none), and link a new collision record (owner thing t, value v, far distance 8388000) at the end of the world's list; every hit points back to it. Returns the record. */
M2Coll13 *m2_CollAdd80F90(M2World13 *w, uint8_t *n, uint8_t *t, int v) {
    float mx[4], mn[4];
    M2Coll13 *e, *p;
    M2Hit13 *h;
    sub_00083B70(mx, mn, n);
    if (mx[0] > w->max10[0]) w->max10[0] = mx[0];
    if (mx[1] > w->max10[1]) w->max10[1] = mx[1];
    if (mx[2] > w->max10[2]) w->max10[2] = mx[2];
    if (w->min20[0] > mn[0]) w->min20[0] = mn[0];
    if (w->min20[1] > mn[1]) w->min20[1] = mn[1];
    if (w->min20[2] > mn[2]) w->min20[2] = mn[2];
    r6c_src3ECA7C = n;
    r6c_p3ECA38 = n + 0x20;
    r6c_v3ECA1C = 0;
    r6c_hits3ECA00 = 0;
    sub_00080E20(*(int *)(n + 0xC));
    if (r6c_hits3ECA00 == 0) return 0;
    e = (M2Coll13 *)a5b_AllocCur(0x28, 0, 0x121);
    e->v10 = v;
    e->w0 = w; e->next4 = 0; e->hits8 = r6c_hits3ECA00; e->i14 = 4; e->nodeC = n; e->thing1C = t;
    e->i20 = t ? *(int32_t *)(t + 0xB4) : 0;
    e->i24 = 0;
    e->f18 = 8388000.0f;
    if (w->list4 != 0) {
        for (p = w->list4; p->next4 != 0; p = p->next4) ;
        p->next4 = e;
    } else {
        w->list4 = e;
    }
    for (h = r6c_hits3ECA00; h != 0; h = h->next4) h->owner8 = e;
    return e;
}

void  rfl_MtxRotateAxis(float *out, const float *a, const float *b, float ang);
void  r4c_Vec4Scale(float *d, const float *a, float s);
void  r4c_VecAdd(float *d, const float *a, const float *b);
float r4_Distance(const float *a, const float *b);

/* 0x954A0: spark ring actor. State 0 sparks 9 points around joint 3 (even steps 0..6 pushed out 12 units along a direction turned by 45 degrees per step, the rest at the joint) and moves to state 1 once the player is 50 units away or more; state 1 returns when the player comes within 50; state 10 releases and hides it. */
void m2_SparkRing954A0(M2Act13 *o) {
    float ang, v[4], p[4], s[4], ray[8];
    uint8_t *q = o->p120;
    uint8_t *j;
    int i;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    switch (o->state40) {
    case 0: {
        float *jp;
        j = r4i_Joint(q, 3);
        if (j == 0) for (;;) ;
        ang = 0.0f;
        jp = (float *)(j + 0x70);
        for (i = 0; i < 9; i++) {
            if (i < 8 && !(i & 1)) {
                rfl_MtxRotateAxis(ray, (float *)(j + 0x40), (float *)(j + 0x60), ang);
                r4c_Vec4Scale(s, ray + 4, 12.0f);
                r4c_VecAdd(p, jp, s);
            } else {
                a3c_VecCopy(p, jp);
            }
            m1_FxAdd0C4DF0(q, 0, 1.0f, 0, 3.0f, 0, 3.0f, p, v, v);
            ang += 0.78539819f;
            while (ang > 3.1415927f) ang -= 6.2831855f;
        }
        if (r4_Distance((float *)(aab_player + 0x60), jp) >= 50.0f) o->state40++;
        break;
    }
    case 1:
        j = r4i_Joint(q, 3);
        if (j == 0) for (;;) ;
        if (50.0f >= r4_Distance((float *)(aab_player + 0x60), (float *)(j + 0x70))) o->state40--;
        break;
    case 10:
        sub_000A41D0(o, -1);
        r6e_ActorShow(o, 0);
        break;
    }
}
