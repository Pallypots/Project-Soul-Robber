/* Area m3, file 14: camera follow target setup. Names inferred. */
#include <stdint.h>

typedef struct M3Tg14 { uint8_t unk00[0x30]; int32_t anim30; uint8_t unk34[0x118]; int32_t list14C; } M3Tg14;
typedef struct M3Cam14 { uint8_t unk00[0x8C]; M3Tg14 *tgt8C; uint8_t unk90[4]; void *fx94; uint8_t unk98[0x10]; int16_t hA8; uint8_t unkAA[6]; int16_t hB0; int16_t hB2; } M3Cam14;
extern M3Cam14 *m1_cam3F610C;
extern void *m1_scene42C8E4;
void sub_000F3AA0(M3Cam14 *c);
void sub_0001D8B0(void *c, int kind);
void r1b_RecAddItem(M3Tg14 *o, void *c);
void r1i_UnitsAttach(void *ctx, void *o, int a, int b, int c);
void sub_0001EBF0(void *o, int a);
void sub_000EE270(void *c);
void sub_000F59F0(void);
int  r2b_TestBit(int bit);
void *aab_Attach36750(void *o, int mode);
void m1_EvRun0E4050(int kind, int key, int a, int b, int c);
void b16_AnimSet(int anim, int a);
void rtc_RecSetAnim(int a, int b);

/* 0xF5BB0: make o the camera's follow target (hangs on null): reset the camera, add its kind 5 and 0xD components to o, attach and enable o, then with story bit 0x57 attach a mode-0 effect and broadcast event 0x16 to group 6, otherwise put the target in anim 0x10 and both records in anim 0x10. Returns o. */
M3Tg14 *m3_CamFollowF5BB0(M3Tg14 *o) {
    M3Cam14 *c; M3Tg14 *t;
    if (o == 0) for (;;) ;
    c = m1_cam3F610C;
    c->tgt8C = o;
    sub_000F3AA0(c);
    sub_0001D8B0(c, 5);
    r1b_RecAddItem(o, c);
    sub_0001D8B0((uint8_t *)c + 0x10, 0xD);
    r1b_RecAddItem(o, (uint8_t *)c + 0x10);
    r1i_UnitsAttach(m1_scene42C8E4, o, o->list14C, 5, 0x11);
    sub_0001EBF0(o, 1);
    sub_000EE270((uint8_t *)c + 0x10);
    sub_000F59F0();
    if (r2b_TestBit(0x57)) {
        c->hA8 = 0;
        c->fx94 = aab_Attach36750(o, 0);
        c->hB0 = 1;
        m1_EvRun0E4050(3, 6, 0x16, -1, 0);
    } else {
        c->hA8 = 2;
        c->fx94 = 0;
        c->hB0 = 0;
        if (m1_cam3F610C == 0) for (;;) ;
        t = m1_cam3F610C->tgt8C;
        if (t == 0) for (;;) ;
        b16_AnimSet(t->anim30, 0x10);
        rtc_RecSetAnim(0, 0x10);
        rtc_RecSetAnim(1, 0x10);
    }
    c->hB2 = 0;
    return o;
}

typedef struct M3Body14 { uint8_t unk00[0x20]; float *mtx20; uint8_t unk24[0x2C]; float rot50[3]; float w5C; float pos60[3]; float w6C; } M3Body14;
typedef struct M3Room14 { uint32_t f0; uint8_t unk04[0xC]; float scale10; uint8_t unk14[0x5C]; float pos70[3]; float w7C; float rot80[3]; float w8C; uint8_t unk90[0x90]; M3Body14 *body120; } M3Room14;
void a3c_VecCopy(float *dst, const float *src);
void rbj_MatIdentity(float *m);
void rbj_MatRotX(float *d, const float *s, float a);
void rbj_MatRotY(float *d, const float *s, float a);
void rbj_MatRotZ(float *d, const float *s, float a);
void rbi_VecScale(float *d, const float *s, float k);
void rbj_MatCopy(float *d, const float *s);
void m1_RoomFloor0A23E0(M3Room14 *r);
void m1_RoomPose0A24C0(M3Room14 *r);

/* 0xA3DB0: place a room object's body: copy position and rotation (w = 1), build the matrix from Z, Y and X rotations and the uniform scale at that position, then update its floor and, when flag 4 is set without flag 8, its pose. */
void m3_RoomPlaceA3DB0(M3Room14 *r) {
    float m[16]; float *dst = r->body120->mtx20;
    a3c_VecCopy(r->body120->pos60, r->pos70);
    r->w7C = 1.0f;
    r->body120->w6C = 1.0f;
    a3c_VecCopy(r->body120->rot50, r->rot80);
    r->w8C = 1.0f;
    r->body120->w5C = 1.0f;
    rbj_MatIdentity(m);
    rbj_MatRotZ(m, m, r->rot80[2]);
    rbj_MatRotY(m, m, r->rot80[1]);
    rbj_MatRotX(m, m, r->rot80[0]);
    rbi_VecScale(m, m, r->scale10);
    rbi_VecScale(m + 4, m + 4, r->scale10);
    rbi_VecScale(m + 8, m + 8, r->scale10);
    a3c_VecCopy(m + 12, r->body120->pos60);
    rbj_MatCopy(dst, m);
    m1_RoomFloor0A23E0(r);
    { volatile uint32_t f = r->f0; if ((f & 4) && !(f & 8)) m1_RoomPose0A24C0(r); }
}

typedef struct M3Pl14 { uint8_t unk00[0x60]; float pos60[4]; } M3Pl14;
extern M3Pl14 *g_playerObj;
int  aab_Rand(void);
void r6c_RotateVec(float *d, const float *rot, const float *v);
void r4e_VecAdd4(float *d, const float *a, const float *b);
void sub_000A8990(int kind, int a, int b, float *pos, float *dir, float *up);

/* 0xA94B0: spawn a random soul pickup (kinds 0x18..0x1B) near the player: 0..110 units behind it, turned by a random angle of up to +-179 degrees, 20 units lower. */
void m3_SoulDropA94B0(void) {
    float p[4], r[4], z[4];
    p[0] = 0.0f; p[1] = 0.0f; p[2] = 0.0f; p[3] = 1.0f;
    r[0] = 0.0f; r[1] = 0.0f; r[2] = 0.0f; r[3] = 1.0f;
    z[0] = 0.0f; z[1] = 0.0f; z[2] = 0.0f; z[3] = 1.0f;
    p[2] = (float)(aab_Rand() % 12) * 10.0f * -1.0f;
    r[1] = (float)(aab_Rand() % 180) * 0.017453292f;
    if (!(aab_Rand() & 1)) r[1] = r[1] * -1.0f;
    r6c_RotateVec(p, r, p);
    r4e_VecAdd4(p, p, g_playerObj->pos60);
    p[1] = p[1] - 20.0f;
    sub_000A8990(aab_Rand() % 4 + 0x18, 9, 0, p, z, z);
}

typedef struct M3Unit14 { uint8_t unk00[8]; int32_t key8; uint32_t fC; uint8_t unk10[0x140]; } M3Unit14;
typedef struct M3Part14 { uint8_t unk00[0xC]; uint32_t fC; } M3Part14;
typedef struct M3Grp14 { uint8_t unk00[0xC8]; void *objC8; uint8_t unkCC[0x1C]; M3Part14 *partE8[5]; } M3Grp14;
typedef struct M3Cmp14 { uint8_t unk00[0x4C]; int32_t i4C; } M3Cmp14;
extern uint8_t m1_snd3E1270[];
extern void *m1_hold3F615C;
extern void *m1_hold3F6158;
void *sub_0001D960(void *o, int kind);
void m1_ListAdd0192B0(void *l, int a);
void sub_00189510(void *h);
void r2d_ObjDestroy(void *o);
int  sub_000F3140(int key);
void r1b_RecDetachNodes(void *n);
void sub_0001D910(void *o, void *c);

/* 0x10F260: tear down a unit group (hangs on null): stop its cue list, release both held handles, destroy the kind 5 component's object, detach every active unit of the group and the five active parts, reset the camera components and remove them. Returns 1. */
int m3_GroupDown10F260(M3Unit14 *u) {
    M3Grp14 *g; M3Cmp14 *c, *d; int i;
    if (u == 0) for (;;) ;
    sub_0001D960(u, 0xD);
    g = sub_0001D960(u, 5);
    m1_ListAdd0192B0(m1_snd3E1270, 0);
    if (m1_hold3F615C) sub_00189510(m1_hold3F615C);
    if (m1_hold3F6158) sub_00189510(m1_hold3F6158);
    m1_hold3F615C = 0;
    m1_hold3F6158 = 0;
    r2d_ObjDestroy(g->objC8);
    for (i = 0; i < sub_000F3140(u->key8); i++) {
        if (u[i].fC & 1) {
            u[i].fC &= ~1u;
            r1b_RecDetachNodes(&u[i]);
        }
    }
    for (i = 0; i < 5; i++) {
        if (g->partE8[i] && (g->partE8[i]->fC & 1)) {
            g->partE8[i]->fC &= ~1u;
            r1b_RecDetachNodes(g->partE8[i]);
        }
    }
    c = sub_0001D960(u, 0xD);
    d = sub_0001D960(u, 5);
    sub_000EE270(c);
    sub_000F3AA0((void *)d);
    d->i4C = 0;
    sub_0001D910(u, d);
    sub_0001D910(u, c);
    return 1;
}
