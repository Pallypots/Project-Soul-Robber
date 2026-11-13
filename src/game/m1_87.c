/* Area m1, file 87: facing checks. Names inferred. */
#include <stdint.h>

typedef struct M1Pl87 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl87;
typedef struct M1Obj87 { uint8_t unk00[0x54]; float yaw54; } M1Obj87;
extern M1Pl87 *g_playerObj;
float sub_00113200(void *o, const void *pos);
float sub_001A3F30(float x);
float sub_001B27C0(const float *a, const float *b);
void  sub_001AD940(float *m);
void  sub_001AD8E0(float *d, const float *s, float a);
void  sub_001AD9B0(float *d, const float *m, const float *v);

/* 0x00139E10: facing check: without a direction returns 1 when the player is more than 90
 * degrees off the object's heading; with one returns 1 when the object's back (0,0,-1)
 * turned by its yaw is within 90 degrees of it. */
int m1_Facing139E10(M1Obj87 *o, const float *dir)
{
    float v[4];
    float m[16];
    if (dir == 0) {
        if (sub_001A3F30(sub_00113200(o, g_playerObj->pos60)) > 1.5707964f)
            return 1;
        return 0;
    }
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = -1.0f;
    v[3] = 0.0f;
    sub_001AD940(m);
    sub_001AD8E0(m, m, o->yaw54);
    sub_001AD9B0(v, m, v);
    return 1.5707964f > sub_001A3F30(sub_001B27C0(v, dir)) ? 1 : 0;
}

typedef struct M1Rig87 {
    uint8_t unk00[0xC];
    float   rate0C;            /* +0x0C */
    float   f10;               /* +0x10 */
    uint8_t unk14[0x24 - 0x14];
    float   q24[4];            /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint32_t flags40;          /* +0x40 */
    int32_t i44;               /* +0x44 */
    float   f48;               /* +0x48 */
} M1Rig87;
typedef struct M1Step87 {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x58 - 0x50];
    int32_t phase58;           /* +0x58 */
    uint8_t unk05C[0x6C - 0x5C];
    int32_t snd6C;             /* +0x6C */
    void   *fx70;              /* +0x70 */
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig87 *rig278;           /* +0x278 */
} M1Step87;
typedef struct M1Obj87S { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x58 - 0x14]; float spin58; uint8_t unk5C[0x60 - 0x5C]; float pos60[4]; uint8_t unk70[0x84 - 0x70]; float f84; } M1Obj87S;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
int  sub_001456E0(void *o, void *h, int a, int b);
int  sub_000494D0(int id, const void *pos, int c);
void *sub_00036750(void *o, int b);
int  aab_Rand(void);
void sub_00175310(void *o, const float *p, int v);

/* 0x00157730: enter state 0x14, reset the rig quaternion, rig +0xC = frameTime * 0.005, clear
 * h +0x4C bits 0x70, o flags 0x30, sound 0x12E and effect 5; with rig +0x48 > 0 restart at
 * phase 0, otherwise rig flag 0x200 and a random 4..7 s wait in phase 10. */
void m1_RigDizzy157730(M1Obj87S *o, M1Step87 *h)
{
    M1Rig87 *r = h->rig278;
    sub_001456E0(o, h, 0x14, 0);
    r->q24[2] = 0.0f;
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->q24[3] = 1.0f;
    r->f10 = 0.0f;
    r->rate0C = m1_frameTime42C858 * 0.005f;
    h->flags4C &= ~0x70u;
    o->flags10 |= 0x30;
    h->snd6C = sub_000494D0(0x12E, o->pos60, 0);
    h->fx70 = sub_00036750(o, 5);
    if (r->f48 > 0.0f) {
        r->i44 = 0;
        h->phase58 = 0;
        return;
    }
    r->flags40 |= 0x200;
    h->wait74 = (float)aab_Rand() * 3.0518509e-05f * 3.0f + 4.0f;
    h->phase58 = 0xA;
}

/* 0x00176070: phase 0 starts the spin (0x175310(2), sound 0x20F, o flag 1, spin = 1 degree
 * per frame, wait 90 frames); phase 1 sets +0x84 = p[0] spread over 90 frames, flips the
 * spin each frame and returns 1 (spin cleared) when the wait runs out. */
int m1_Wobble176070(M1Obj87S *o, M1Step87 *h, const float *p)
{
    switch (h->phase58) {
    case 0:
        sub_00175310(o, p, 2);
        sub_000494D0(0x20F, o->pos60, 0);
        o->flags10 |= 1;
        o->spin58 = m1_frameTime42C858 * 0.017453292f;
        h->wait74 = 90.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        h->phase58++;
        break;
    case 1:
        o->f84 = p[0] / (90.0f / m1_frameTime42C858);
        o->spin58 = o->spin58 * -1.0f;
        if (m1_frameRate42C85C > h->wait74) {
            o->spin58 = 0.0f;
            return 1;
        }
        break;
    }
    return 0;
}

typedef struct M1Rig87F { uint32_t unk00; uint32_t flags04; uint8_t unk08[0x18 - 8]; float fade18[2]; int32_t i20; } M1Rig87F;
typedef struct M1Step87F {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021[0x58 - 0x21];
    int32_t phase58;           /* +0x58 */
    uint8_t unk05C[0x74 - 0x5C];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig87F *rig278;          /* +0x278 */
} M1Step87F;
typedef struct M1Obj87F { uint8_t unk00[0x10]; uint32_t flags10; } M1Obj87F;
void sub_00113090(void *o, void *h, int state);
void sub_000414A0(int v);
void sub_00113C60(void *fade, float a, float b);
void sub_00113CB0(float *v, float a, int b);
void sub_00113C90(void *v, int a, int b);

/* 0x0013E9C0: enter state 0x14 (0x414A0(1)), o flag 0x20; rig flag 0x20000000: fade 40 ->
 * 255 and done; otherwise fade timer 20, then with rig flag 0x40000000 shorten the wait by 100
 * (h +0x20 bit 0) and set o flag 4, else restart +0x20 and (bit 0) phase 1 with o flags 6. */
void m1_RigStun13E9C0(M1Obj87F *o, M1Step87F *h)
{
    M1Rig87F *r = h->rig278;
    sub_00113090(o, h, 0x14);
    sub_000414A0(1);
    o->flags10 |= 0x20;
    if (r->flags04 & 0x20000000) {
        r->i20 = 0;
        sub_00113C60(r->fade18, 40.0f, 255.0f);
        return;
    }
    sub_00113CB0(r->fade18, 20.0f, 0);
    if (r->flags04 & 0x40000000) {
        if (h->b20 & 1)
            h->wait74 -= 100.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        o->flags10 |= 4;
        return;
    }
    sub_00113C90(&r->i20, 1, 0);
    if (h->b20 & 1) {
        h->phase58 = 1;
        o->flags10 = (o->flags10 & ~0x20u) | 6;
    }
}

typedef struct M1Scene87 { uint8_t unk00[0x30]; void *anim30; uint8_t unk34[0x60 - 0x34]; float pos60[4]; } M1Scene87;
extern M1Scene87 *m1_sceneObj3FDE68;
extern void *m1_sceneAct3FDE6C;
extern void *m1_resB3FDE74, *m1_resC3FDE78, *m1_resD3FDE7C, *m1_resE3FDE80, *m1_resF3FDE84;
extern const float m1_start27A618[4];
void sub_00113040(void *o, void *h, int state);
void sub_000832D0(void *a, int v);
void sub_000F5D40(float *d, const float *s);
void sub_00033A70(void *r);

#define M1_FREE87(x) if ((x) != 0) { sub_00033A70(x); (x) = 0; }
/* 0x0017D6A0: scene reset: the scene object goes to state 0 with clip 0 at the start position
 * 0x27A618, and the scene resources at 0x3FDE74..0x3FDE84 are released. */
void m1_SceneReset17D6A0(void)
{
    sub_00113040(m1_sceneObj3FDE68, m1_sceneAct3FDE6C, 0);
    sub_000832D0(m1_sceneObj3FDE68->anim30, 0);
    sub_000F5D40(m1_sceneObj3FDE68->pos60, m1_start27A618);
    M1_FREE87(m1_resC3FDE78)
    M1_FREE87(m1_resB3FDE74)
    M1_FREE87(m1_resD3FDE7C)
    M1_FREE87(m1_resC3FDE78)
    M1_FREE87(m1_resE3FDE80)
    M1_FREE87(m1_resF3FDE84)
}
