/* Area m3, file 20: boss hit by a record. Names inferred. */
#include <stdint.h>

typedef struct M3HTgt20 { uint8_t unk00[4]; int32_t kind4; uint8_t unk08[4]; uint32_t fC; uint8_t b10; } M3HTgt20;
typedef struct M3HRec20 { uint8_t unk00[0x10]; int32_t kind10; uint8_t unk14[0x10]; float src24[4]; } M3HRec20;
typedef struct M3HBoss20 { uint8_t unk00[0x150]; uint32_t f150; uint8_t unk154[0x554]; int32_t n6A8; } M3HBoss20;
void sub_0009F710(M3HTgt20 *t, float *out);
void r2d_ObjTarget(void *o, float *out);
void a3c_VecCopy(float *dst, const float *src);
int  sub_000C4190(int kind, float *src, float *dir, float *at);
int  sub_000C4590(M3HBoss20 *b, M3HTgt20 *t);
void sub_000C4560(M3HBoss20 *b, M3HTgt20 *t);
void sub_000C44B0(M3HBoss20 *b, M3HTgt20 *t);
void sub_000C45D0(M3HRec20 *r, M3HTgt20 *t);
void sub_000C48A0(float *at, float k, float *src, float *a, float *b);

/* 0xC4EC0: hit the boss with a hit record against target t: unless the boss is guarding (0x2000) or t is inactive/excluded, take t's target point (kind-12 targets use 0x9F710), test the hit from the record's source; if it lands and is new, register it, add a hit mark at the next slot and store the hit point. */
__declspec(noinline) void m3_BossHitC4EC0(M3HBoss20 *b, M3HRec20 *r, M3HTgt20 *t) {
    float at[4], dir[4], src[4], m[6]; uint8_t *e;
    at[0] = 0.0f; at[1] = 0.0f; at[2] = 0.0f; at[3] = 1.0f;
    dir[0] = 0.0f; dir[1] = 0.0f; dir[2] = 0.0f; dir[3] = 1.0f;
    src[0] = 0.0f; src[1] = 0.0f; src[2] = 0.0f; src[3] = 1.0f;
    if (b->f150 & 0x2000) return;
    { volatile uint32_t f = t->fC; if (!(f & 1) || (f & 0x10000) || (t->b10 & 0xC)) return; }
    if (t->kind4 != 0xC) r2d_ObjTarget(t, m);
    else sub_0009F710(t, m);
    a3c_VecCopy(at, m);
    dir[0] = m[4];
    dir[1] = m[5] * -1.0f;
    a3c_VecCopy(src, r->src24);
    if (sub_000C4190(r->kind10, src, dir, at) < 0) return;
    if (sub_000C4590(b, t) >= 0) return;
    sub_000C4560(b, t);
    sub_000C44B0(b, t);
    sub_000C45D0(r, t);
    { uint8_t *volatile ev = (uint8_t *)b + b->n6A8 * 16 + 0x6A8; e = ev; }
    sub_000C48A0(at, m[4], src, (float *)(e + 0x204), (float *)(e + 0x404));
    a3c_VecCopy((float *)((uint8_t *)b + b->n6A8 * 16 + 0x6AC), at);
}

typedef struct M3HRecB20 { uint8_t b0; uint8_t unk01[0xF]; int32_t kind10; uint8_t unk14[0x10]; float src24[4]; } M3HRecB20;

/* 0xC5B30: hit-record entry: area records (flags 6) go to 0xC4EC0; otherwise test the hit against t like 0xC4EC0 but without the repeat check, register it, add a hit mark at the next slot and store the hit point. */
void m3_BossHit2C5B30(M3HBoss20 *b, M3HRecB20 *r, M3HTgt20 *t) {
    float at[4], dir[4], src[4], m[6]; uint8_t *e;
    at[0] = 0.0f; at[1] = 0.0f; at[2] = 0.0f; at[3] = 1.0f;
    dir[0] = 0.0f; dir[1] = 0.0f; dir[2] = 0.0f; dir[3] = 1.0f;
    src[0] = 0.0f; src[1] = 0.0f; src[2] = 0.0f; src[3] = 1.0f;
    if (r->b0 & 6) { m3_BossHitC4EC0(b, (M3HRec20 *)r, t); return; }
    { volatile uint32_t f = t->fC; if (!(f & 1) || (f & 0x10000) || (t->b10 & 0xC)) return; }
    if (t->kind4 != 0xC) r2d_ObjTarget(t, m);
    else sub_0009F710(t, m);
    a3c_VecCopy(at, m);
    dir[0] = m[4];
    dir[1] = m[5] * -1.0f;
    a3c_VecCopy(src, r->src24);
    if (sub_000C4190(r->kind10, src, dir, at) < 0) return;
    sub_000C44B0(b, t);
    sub_000C45D0((M3HRec20 *)r, t);
    { uint8_t *volatile ev = (uint8_t *)b + b->n6A8 * 16 + 0x6A8; e = ev; }
    sub_000C48A0(at, m[4], src, (float *)(e + 0x204), (float *)(e + 0x404));
    a3c_VecCopy((float *)((uint8_t *)b + b->n6A8 * 16 + 0x6AC), at);
}
