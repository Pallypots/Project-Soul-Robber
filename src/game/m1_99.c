/* Area m1, file 99: table resets. Names inferred. */
#include <stdint.h>

typedef struct M1Rec99 { int32_t i00, i04, i08, i0C; int16_t w10; uint8_t pad12[2]; float f14, f18, f1C, f20; } M1Rec99;
extern M1Rec99 b7c_idRecs3FE2D8[4];

/* 0x00182400: clear the four 0x24-byte records at 0x3FE2D8. */
void m1_RecsClear182400(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        b7c_idRecs3FE2D8[i].i00 = 0;
        b7c_idRecs3FE2D8[i].i04 = 0;
        b7c_idRecs3FE2D8[i].i08 = 0;
        b7c_idRecs3FE2D8[i].i0C = 0;
        b7c_idRecs3FE2D8[i].w10 = 0;
        b7c_idRecs3FE2D8[i].f14 = 0.0f;
        b7c_idRecs3FE2D8[i].f18 = 0.0f;
        b7c_idRecs3FE2D8[i].f1C = 0.0f;
        b7c_idRecs3FE2D8[i].f20 = 0.0f;
    }
}

typedef struct M1Rig99 { uint8_t unk00[0x18]; int32_t slot18; uint8_t unk1C[0x26 - 0x1C]; int16_t mode26; uint8_t unk28[0x2C - 0x28]; float size2C; } M1Rig99;
typedef struct M1Step99 { uint8_t unk000[0x50]; int32_t state50; uint8_t unk054[0x5C - 0x54]; float t5C; uint8_t unk060[0x278 - 0x60]; M1Rig99 *rig278; } M1Step99;
typedef struct M1Obj99 { uint8_t unk00[0xA4]; float fA4; uint8_t unkA8[0xB0 - 0xA8]; float fB0; float fB4; uint8_t unkB8[0xE8 - 0xB8]; float fE8; } M1Obj99;
extern float m1_fps42C964;
void sub_000C56B0(void *o);
int  sub_000F6A80(void);
int  sub_000F60C0(void *o, int a, int b);
void *sub_000A4290(int slot);
void sub_000A22C0(void *s, void *o);
int  sub_000ED780(void *o);

/* 0x0017CCD0: grow: copy the rig size into +0xE8/+0xB0/+0xA4 (+0xB4 = -2x), grow it by 8 or 22
 * (states 7/8) over 0.2 s, mode 1 runs 0xC56B0 and mode 0 (unless 0xF6A80) 0xF60C0; after
 * 0.2 s in the state hand the object to slot +0x18 (0xA22C0) and release it. */
void m1_Grow17CCD0(M1Obj99 *o, M1Step99 *h)
{
    M1Rig99 *r = h->rig278;
    float k;
    o->fE8 = r->size2C;
    o->fB0 = r->size2C;
    o->fB4 = r->size2C * -2.0f;
    o->fA4 = r->size2C;
    k = 0.2f;
    if (h->state50 == 7)
        r->size2C = 8.0f / (m1_fps42C964 * k) + r->size2C;
    else if (h->state50 == 8)
        r->size2C = 22.0f / (m1_fps42C964 * k) + r->size2C;
    if (r->mode26 == 1)
        sub_000C56B0(o);
    else if (r->mode26 == 0 && !sub_000F6A80())
        sub_000F60C0(o, 0, 0);
    if (h->t5C > 0.2f && r->slot18 != -1) {
        sub_000A22C0(sub_000A4290(r->slot18), o);
        sub_000ED780(o);
    }
}

typedef struct M1Mov99 {
    uint8_t unk00[0xA8];
    int32_t iA8;               /* +0xA8 */
    uint8_t unkAC[0xB4 - 0xAC];
    float   fB4, fB8, fBC, fC0, fC4;   /* +0xB4..+0xC4 */
    uint8_t unkC8[0xCC - 0xC8];
    float   fCC;               /* +0xCC */
} M1Mov99;
typedef struct M1Obj99B { uint8_t unk00[0x50]; float f50; } M1Obj99B;
extern float m1_frameRate42C85C;
void sub_000F3B00(void *o, int v);
void sub_000F3B30(void *o, int v);
void sub_000F3F00(void *o, int v);

/* 0x001099D0: bounce off as 0x109B10 with a 6 pi spin target. */
void m1_BounceOff1099D0(M1Obj99B *o, M1Mov99 *s)
{
    float a;
    s->fBC = s->fBC * -0.40000001f;
    s->fC0 = s->fC0 * 0.40000001f;
    s->iA8 = 0;
    a = s->fBC;
    s->fB4 = a * -1.0f / (m1_fps42C964 * 0.30000001f);
    s->fB8 = 0.0f;
    if (s->fCC > 0.0f)
        s->fCC = (18.849556f - o->f50) * m1_frameRate42C85C;
    else
        s->fCC = (18.849556f - o->f50) * m1_frameRate42C85C * -1.0f;
    s->fC4 = 0.0f;
    sub_000F3B00(o, 0x44);
    sub_000F3B30(o, 0x20);
    sub_000F3F00(o, 0);
}
