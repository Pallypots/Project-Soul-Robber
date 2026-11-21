/* Area m1, file 274: object lookups. Names inferred. */
#include <stdint.h>

typedef struct M1Sn274 { uint8_t unk00[0x1E8]; void *p1E8; } M1Sn274;
typedef struct M1Ob274 { uint8_t unk00[0x3C]; void *f3C; } M1Ob274;
extern M1Sn274 *m1_scene42C8E4;
extern void *g_playerObj;
M1Ob274 *sub_0001D080(void *list, int32_t a, int32_t b);
M1Ob274 *sub_0001D080a(void *list, int32_t a, int32_t b);   /* aliases of the same function stop cl merging calls */
M1Ob274 *sub_0001D080c(void *list, int32_t a, int32_t b);
M1Ob274 *sub_0001D080d(void *list, int32_t a, int32_t b);
M1Ob274 *sub_0001D080e(void *list, int32_t a, int32_t b);
M1Ob274 *sub_0001D080f(void *list, int32_t a, int32_t b);
M1Ob274 *sub_0001D080g(void *list, int32_t a, int32_t b);
M1Ob274 *sub_0001D080h(void *list, int32_t a, int32_t b);

/* 0x000E2540: look up a stage object by id 0-10: 0 is the player, 1-9 are entries of the scene's object list,
   10 is the attached object of entry 9. Other ids give 0. */
void *m1_ObjByIdE2540(int32_t unused, int32_t id)
{
    switch (id) {
    case 0: return g_playerObj;
    case 1: return sub_0001D080(m1_scene42C8E4->p1E8, 3, 0);
    case 2: return sub_0001D080a(m1_scene42C8E4->p1E8, 3, 1);
    case 3: return sub_0001D080c(m1_scene42C8E4->p1E8, 3, 3);
    case 4: return sub_0001D080(m1_scene42C8E4->p1E8, 3, 4);
    case 5: return sub_0001D080d(m1_scene42C8E4->p1E8, 3, 5);
    case 6: return sub_0001D080e(m1_scene42C8E4->p1E8, 3, 6);
    case 7: return sub_0001D080(m1_scene42C8E4->p1E8, 3, 7);
    case 8: return sub_0001D080f(m1_scene42C8E4->p1E8, 3, 8);
    case 9: return sub_0001D080g(m1_scene42C8E4->p1E8, 3, 9);
    case 10: return sub_0001D080h(m1_scene42C8E4->p1E8, 3, 9)->f3C;
    }
    return 0;
}

typedef struct M1Ev274 { int32_t kind0; int32_t r4; uint32_t flags8; int32_t zC; float v10[4]; float v20[4]; } M1Ev274;
typedef struct M1Ed274 { uint8_t unk00[8]; int32_t k8; uint8_t unk0C[0xC4]; } M1Ed274;
typedef struct M1Ac274 { uint8_t unk00[0xEC]; uint32_t flagsEC; uint8_t unkF0[0xC8]; uint8_t *p1B8; uint8_t unk1BC[0xD40];
    void *hEFC; uint8_t unkF00[0xD8]; int32_t fFD8; } M1Ac274;
void sub_000C4B70(M1Ed274 *d);
void sub_000C5E70(M1Ac274 *a, void *h, M1Ed274 *d, float *p, float *q);
int32_t sub_000CF790(M1Ac274 *a, uint8_t *p);
void sub_000F5D40(float *d, const float *s);
void sub_0009F6D0(void *h, M1Ev274 *e, int32_t x);

/* 0x000BD570: send action k from actor a to its handler hEFC. Action 14 sends a direct event (kind 14, the
   value read from a's record, a's flag 0x40, zero offsets); any other action builds a default descriptor and
   goes through 0x000C5E70. regargs: a=ESI, k=EDI. */
void m1_SendActionBD570(M1Ac274 *a, int32_t k)
{
    float v[4], s[4];
    M1Ed274 d;
    M1Ev274 e;
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    if (!a->hEFC) return;
    if (k != 14) {
        sub_000C4B70(&d);
        d.k8 = k;
        sub_000C5E70(a, a->hEFC, &d, v, v);
        return;
    }
    s[0] = 0.0f;
    s[1] = 0.0f;
    s[2] = 0.0f;
    s[3] = 1.0f;
    e.kind0 = 14;
    e.zC = 0;
    e.r4 = sub_000CF790(a, a->p1B8 + 4);
    e.flags8 = a->flagsEC & 0x40;
    sub_000F5D40(e.v10, s);
    sub_000F5D40(e.v20, s);
    sub_0009F6D0(a->hEFC, &e, a->fFD8);
}
