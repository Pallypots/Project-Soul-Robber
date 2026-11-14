/* Area m1, file 138: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Obj138 { uint8_t unk00[4]; int32_t kind04; int32_t id08; } M1Obj138;
typedef struct M1Bound138 { float p[4]; float r30; float h34; } M1Bound138;
extern uint8_t m1_stats41FEC0[];
typedef struct M1Slot138 { uint8_t unk00[0x54]; void *obj54; uint8_t unk58[0xE0 - 0x58]; } M1Slot138;
extern M1Slot138 m1_entsE41E2A0[];
int  sub_00171F10(int a, int b);
int  sub_00171AA0(void *s, int k);
void sub_000EDEC0(void *o, M1Bound138 *b);
void sub_0009F710(void *o, M1Bound138 *b);
void sub_000F5D40(float *d, const float *s);
int  sub_000C4C90(int k, int a, float r, int m, float *pos, float *v0, float *v1);

/* 0x000C56B0: lock-on marker: effect kind 10 (11 when 0x171F10 matches) at the middle of the
 * object's bounds (kind 0xC objects use 0x9F710), sized 1.2 times the bound radius; the slot
 * remembers the object. */
void m1_LockMark0C56B0(M1Obj138 *o)
{
    struct { float a[4]; float b[4]; M1Bound138 bd; } l;
    int k, m, r;
    l.a[0] = 0.0f;
    l.a[1] = 0.0f;
    l.a[2] = 0.0f;
    l.a[3] = 1.0f;
    l.b[0] = 0.0f;
    l.b[1] = 0.0f;
    l.b[2] = 0.0f;
    l.b[3] = 1.0f;
    k = (sub_00171F10(o->kind04, o->id08) != 0) + 10;
    m = sub_00171AA0(m1_stats41FEC0, k);
    if (o->kind04 != 0xC)
        sub_000EDEC0(o, &l.bd);
    else
        sub_0009F710(o, &l.bd);
    sub_000F5D40(l.a, l.bd.p);
    l.a[1] = l.bd.h34 * 0.5f + l.a[1];
    l.a[3] = 1.0f;
    r = sub_000C4C90(k, 0, l.bd.r30 * 1.20000005f, m, l.a, l.b, l.b);
    if (r < 0)
        return;
    m1_entsE41E2A0[r].obj54 = o;
}
