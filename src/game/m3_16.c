/* Area m3, file 16: stage object teardown. Names inferred. */
#include <stdint.h>

typedef struct M3Cnt16 { int32_t n0; } M3Cnt16;
typedef struct M3Ctx16 { uint8_t unk00[0x1E8]; void *recs1E8; } M3Ctx16;
extern uint8_t *afc_listData;
extern uint8_t *ae0_ptr3F6100;
extern M3Cnt16 *afc_g3F60FC;
extern void *afc_listHead;
extern M3Ctx16 *m1_scene42C8E4;
extern uint8_t m1_snd3E1270[];
void r2d_ObjDestroy(void *o);
void m1_SceneDetach01D030(void *recs, void *t);
void r1b_TableFree(void *t);
void sub_000341A0(void *o);
void r1i_UnitsRelease(void *o);
void m1_ListAdd0192B0(void *l, int a);
void sub_001063A0(void);
void sub_0010CA80(void);
void sub_00108B60(void);
void sub_000FE2B0(void);
void sub_000FFFF0(void);
void sub_000FB9D0(void);
void sub_000F3F50(void);
void sub_000EEDF0(void);
void sub_000FC490(void);
void sub_00101200(void);
void sub_00106090(void);

/* 0xF3680: tear down the stage objects: destroy every active object of the extra table and free it, release the eight 0x150-byte stage units that are in use, stop the cue list, free the list, then run all the stage managers' reset functions. */
void m3_StageTeardownF3680(void) {
    int i, off;
    if (afc_listData == 0) return;
    if (ae0_ptr3F6100) {
        for (i = 0, off = 0; i < afc_g3F60FC->n0; i++, off += 0x150)
            if (ae0_ptr3F6100[off + 0xC] & 1) r2d_ObjDestroy(ae0_ptr3F6100 + off);
        m1_SceneDetach01D030(m1_scene42C8E4->recs1E8, afc_g3F60FC);
        r1b_TableFree(afc_g3F60FC);
        ae0_ptr3F6100 = 0;
        afc_g3F60FC = 0;
    }
    for (off = 0; off < 0xA80; off += 0x150) {
        uint8_t *u = afc_listData + off;
        if (*(int32_t *)(u + 4) != -1 && *(int32_t *)(u + 8) != -1) {
            sub_000341A0(u);
            r1i_UnitsRelease(afc_listData + off);
        }
    }
    m1_ListAdd0192B0(m1_snd3E1270, 0);
    r1b_TableFree(afc_listHead);
    afc_listData = 0;
    afc_listHead = 0;
    sub_001063A0();
    sub_0010CA80();
    sub_00108B60();
    sub_000FE2B0();
    sub_000FFFF0();
    sub_000FB9D0();
    sub_000F3F50();
    sub_000EEDF0();
    sub_000FC490();
    sub_00101200();
    sub_00106090();
}

typedef struct M3BossA16 { uint8_t unk00[0xEF8]; int32_t iEF8; int32_t hEFC; float aim[5][4]; float mF50[16]; float vF90[4]; int32_t iFA0, iFA4, iFA8; float fFAC; } M3BossA16;
void rbj_MatIdentity(float *m);
void rbj_MatCopy(float *d, const float *s);
float sub_00171B40(M3BossA16 *b);
void r2b_Set42C8ECTop(int a);

/* 0xCA400: reset the boss aim state: clear the target and handle, the five aim points and the aim offset to (0,0,0,1), counters to 0, the aim matrix to identity, then recompute +0xFAC and reset the top flag. */
void m3_BossAimResetCA400(M3BossA16 *b) {
    float m[16];
    b->iEF8 = 0; b->hEFC = 0;
    b->aim[0][0] = 0.0f; b->aim[0][1] = 0.0f; b->aim[0][2] = 0.0f; b->aim[0][3] = 1.0f;
    b->aim[1][0] = 0.0f; b->aim[1][1] = 0.0f; b->aim[1][2] = 0.0f; b->aim[1][3] = 1.0f;
    b->aim[2][0] = 0.0f; b->aim[2][1] = 0.0f; b->aim[2][2] = 0.0f; b->aim[2][3] = 1.0f;
    b->aim[3][0] = 0.0f; b->aim[3][1] = 0.0f; b->aim[3][2] = 0.0f; b->aim[3][3] = 1.0f;
    b->aim[4][0] = 0.0f; b->aim[4][1] = 0.0f; b->aim[4][2] = 0.0f; b->aim[4][3] = 1.0f;
    b->vF90[0] = 0.0f; b->vF90[1] = 0.0f; b->vF90[2] = 0.0f; b->vF90[3] = 1.0f;
    b->iFA0 = 0; b->iFA4 = 0; b->iFA8 = 0;
    b->fFAC = 0.0f;
    rbj_MatIdentity(m);
    rbj_MatCopy(b->mF50, m);
    b->fFAC = sub_00171B40(b);
    r2b_Set42C8ECTop(0);
}

typedef struct M3Mot16 { uint8_t unk00[0xC4]; float lenC4; uint8_t unkC8[0x10]; float curD8; } M3Mot16;
typedef struct M3Mdl16 { uint8_t unk00[0x14]; M3Mot16 *mot14; } M3Mdl16;
typedef struct M3TurnO16 { uint8_t unk00[0x30]; M3Mdl16 *mdl30; uint8_t unk34[0x20]; float yaw54; } M3TurnO16;
typedef struct M3TurnE16 { uint8_t unk00[0xA4]; float ang; uint8_t unkA8[0x48]; float vF0[4]; uint8_t unk100[0x10]; int32_t i110, i114; } M3TurnE16;
extern float b10_frameDelta;

/* 0xF21B0: AI turn-around state: stop (velocity rate*0, counters cleared; hangs on null), and during the first 48 frames of the motion turn the yaw by the remaining angle to -pi spread over the remaining time, wrapping the turn angle into -pi..pi. */
void m3_AiTurnF21B0(M3TurnO16 *o, M3TurnE16 *e) {
    float r, x, d, a;
    if (e == 0) for (;;) ;
    e->vF0[0] = b10_frameDelta * 0.0f;
    e->vF0[1] = b10_frameDelta * 0.0f;
    e->vF0[2] = b10_frameDelta * 0.0f;
    e->vF0[3] = b10_frameDelta * 0.0f;
    e->i110 = 0; e->i114 = 0;
    r = o->mdl30->mot14->curD8 / o->mdl30->mot14->lenC4;
    if (!(r >= 0.0f)) return;
    if (!(48.0f > r)) return;
    x = (48.0f - r) * 0.016666668f;
    d = (-3.1415927f - e->ang) * b10_frameDelta / x;
    o->yaw54 = o->yaw54 + d;
    a = d + e->ang;
    e->ang = a;
    if (a > 3.1415927f) {
        float y = e->ang;
        do y -= 6.2831855f; while (y > 3.1415927f);
        e->ang = y;
    }
    if (-3.1415927f > e->ang) {
        float y = e->ang;
        do y += 6.2831855f; while (-3.1415927f > y);
        e->ang = y;
    }
}

typedef struct M3MinT16 { uint8_t unk00[0x30]; int32_t anim30; uint8_t unk34[0x2C]; float pos60[4]; } M3MinT16;
typedef struct M3Min16 { uint8_t unk00[0x8C]; M3MinT16 *a8C; M3MinT16 *b90; uint8_t unk94[0xE4]; float t178; uint8_t unk17C[0xC]; float f188; uint8_t unk18C[0xC]; float y198; uint8_t unk19C[0xC]; M3MinT16 *src1A8; int16_t h1AC; } M3Min16;
typedef struct M3MinO16 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x40]; float yaw54; uint8_t unk58[8]; float pos60[4]; } M3MinO16;
extern M3Min16 *afc_minion;
extern M3MinT16 *g_playerObj;
extern float afc_vec318E18[];
extern float a50_framesPerSecond;
void aab_Show1D610(void *o);
void r4c_VecSub(float *dst, const float *a, const float *b);
void rbi_VecNorm(float *d, const float *s);
float sub_001A3EC0(float x, float z);
void b16_AnimSet(int anim, int a);
void aab_Effect494D0(int id, void *pos, int a);

/* 0xFF5C0: warp an object in for the minion: show it, place it over the minion's source (or the player) at height -85, face it towards the arena centre, set the minion timers, put both minion bodies in anim 0x27 (hangs without them) and play effect 0x148 there. */
void m3_MinionWarpFF5C0(M3MinO16 *o) {
    M3Min16 *h = afc_minion; float d[4], a; M3MinT16 *s;
    aab_Show1D610(o);
    o->f10 &= ~1u;
    if (h->src1A8) {
        o->pos60[0] = h->src1A8->pos60[0];
        o->pos60[2] = h->src1A8->pos60[2];
    } else {
        o->pos60[0] = g_playerObj->pos60[0];
        o->pos60[2] = g_playerObj->pos60[2];
    }
    h->y198 = -85.0f;
    o->pos60[1] = -85.0f;
    r4c_VecSub(d, o->pos60, afc_vec318E18);
    d[3] = 0.0f; d[1] = 0.0f;
    rbi_VecNorm(d, d);
    a = sub_001A3EC0(d[0], d[2]) - 3.1415927f;
    o->yaw54 = a;
    if (-3.1415927f > a) o->yaw54 = a + 6.2831855f;
    h->t178 = 97.0f / a50_framesPerSecond;
    h->f188 = 0.0f;
    h->h1AC = 0;
    if (afc_minion == 0) for (;;) ;
    s = afc_minion->a8C;
    if (s == 0) for (;;) ;
    b16_AnimSet(s->anim30, 0x27);
    b16_AnimSet(afc_minion->b90->anim30, 0x27);
    aab_Effect494D0(0x148, o->pos60, 1);
}

typedef struct M3Fade16 { uint32_t st0; int32_t i4, i8, iC, i10; float t14; uint8_t unk18[0xC]; float f24; uint8_t unk28[0x94]; uint8_t stepA[0x9C]; uint8_t stepB[0x9C]; } M3Fade16;
extern M3Fade16 r2c_fadeD3F4B1C;
void sub_000150B0(void *s, int mode);
void r1b_StepperRun(void *s, int a);

/* 0xE8A50: drive the curtain fade: 0 closes it (from state 1, or from states 3..4 with a reset), 1 opens it (from 0 with the opening steppers 5/6, or from 2 reversing the timer), 2 in states 3..4 runs the closing steppers 9/10 once. */
void m3_CurtainE8A50(int k) {
    switch (k) {
    case 2:
        { volatile uint32_t v = r2c_fadeD3F4B1C.st0; if (v < 3 || v > 4) return; }
        sub_000150B0(r2c_fadeD3F4B1C.stepA, 9);
        sub_000150B0(r2c_fadeD3F4B1C.stepB, 10);
        r1b_StepperRun(r2c_fadeD3F4B1C.stepA, 0);
        r1b_StepperRun(r2c_fadeD3F4B1C.stepB, 0);
        return;
    case 1:
        switch (r2c_fadeD3F4B1C.st0) {
        case 2:
            r2c_fadeD3F4B1C.st0 = 1; r2c_fadeD3F4B1C.i4 = 3; r2c_fadeD3F4B1C.i8 = 2; r2c_fadeD3F4B1C.iC = 0;
            break;
        case 0:
            sub_000150B0(r2c_fadeD3F4B1C.stepA, 5);
            sub_000150B0(r2c_fadeD3F4B1C.stepB, 6);
            r2c_fadeD3F4B1C.iC = 0; r2c_fadeD3F4B1C.i10 = 0; r2c_fadeD3F4B1C.f24 = 0.0f;
            r2c_fadeD3F4B1C.st0 = 1; r2c_fadeD3F4B1C.i4 = 3; r2c_fadeD3F4B1C.i8 = 2;
            return;
        default:
            return;
        }
        break;
    case 0:
        if (r2c_fadeD3F4B1C.st0 == 1) {
            r2c_fadeD3F4B1C.st0 = 2; r2c_fadeD3F4B1C.i4 = 0;
            break;
        }
        { volatile uint32_t v = r2c_fadeD3F4B1C.st0; if (v <= 2 || v > 4) return; }
        r2c_fadeD3F4B1C.i4 = 0; r2c_fadeD3F4B1C.i10 = 0; r2c_fadeD3F4B1C.f24 = 0.0f;
        r2c_fadeD3F4B1C.st0 = 2;
        return;
    default:
        return;
    }
    r2c_fadeD3F4B1C.t14 = 20.0f - r2c_fadeD3F4B1C.t14;
}

typedef struct M3HitRec16 { uint8_t unk00[4]; int32_t i4; int32_t i8; uint8_t unk0C[4]; int32_t i10; uint8_t unk14[8]; int32_t i1C; int32_t i20; float src24[4]; uint8_t unk34[0x20]; void *who54; } M3HitRec16;
typedef struct M3Jack16 { uint8_t unk00[0xFD8]; void *objFD8; } M3Jack16;
void a3c_VecCopy(float *dst, const float *src);
void r2d_ObjTarget(void *o, float *out);
int  sub_000C4190(int kind, float *src, float *dir, float *at);
void rbk_JackHitBy0D3FA0(M3Jack16 *j, void *who, int a, int b, int c, float *dir);
void rbk_JackHurt0D3E10(M3Jack16 *j, float *dir, int a, int b);

/* 0xC4740: hit Jack from a hit record: take his target point, test the hit (0xC4190) from the record's source towards it; on a hit push him along the horizontal direction from the source, by the attacker when the record names one, else as plain damage. */
void m3_JackHitC4740(M3Jack16 *j, M3HitRec16 *r) {
    float d[4], s[4], at[4], v[4], m[6];
    s[0] = 0.0f; s[1] = 0.0f; s[2] = 0.0f; s[3] = 1.0f;
    v[2] = 0.0f; v[3] = 1.0f;
    at[0] = 0.0f; at[1] = 0.0f; at[2] = 0.0f; at[3] = 1.0f;
    d[0] = 0.0f; d[1] = 0.0f; d[2] = 0.0f; d[3] = 1.0f;
    r2d_ObjTarget(j->objFD8, m);
    a3c_VecCopy(at, m);
    v[0] = m[4];
    v[1] = m[5] * -1.0f;
    a3c_VecCopy(s, r->src24);
    if (sub_000C4190(r->i10, s, v, at) < 0) return;
    r4c_VecSub(d, at, s);
    d[1] = 0.0f;
    rbi_VecNorm(d, d);
    if (r->who54) { rbk_JackHitBy0D3FA0(j, r->who54, r->i1C, r->i20, r->i4, d); return; }
    rbk_JackHurt0D3E10(j, d, r->i4, r->i8);
}

typedef struct M3CTg16 { uint8_t unk00[0x30]; int32_t anim30; } M3CTg16;
typedef struct M3Cam16 { uint8_t unk00[0x8C]; M3CTg16 *tgt8C; uint8_t unk90[4]; void *fx94; uint8_t unk98[0x10]; int16_t hA8; uint8_t unkAA[2]; float tAC; uint8_t unkB0[0x58]; int32_t mode108; } M3Cam16;
extern M3Cam16 *m1_cam3F610C;
extern float b10_frameDelta;
void sub_00033A70(void *n);
void r2c_BossDefeat(void);
int  afc_NodeActive(void *n);
void rtc_RecSetAnim(int a, int b);

/* 0xF51D0: camera intro step: in phase 0 count the delay down, then drop the effect and put the target and both records in anim 0x17 (phase 1); in phase 1 finish via 0xF4610 (mode 2, or once the target node is active) and set anim 0x1B or 0x10 if still running. */
void m3_CamIntroF51D0(void) {
    M3Cam16 *c = m1_cam3F610C; int16_t *ph = &c->hA8; M3CTg16 *t;
    if (*ph == 0) {
        if (0.0f > c->tAC) {
            if (c->fx94) { sub_00033A70(c->fx94); c->fx94 = 0; }
            if (m1_cam3F610C == 0) for (;;) ;
            t = m1_cam3F610C->tgt8C;
            if (t == 0) for (;;) ;
            b16_AnimSet(t->anim30, 0x17);
            rtc_RecSetAnim(0, 0x17);
            rtc_RecSetAnim(1, 0x17);
            *ph = 1;
            return;
        }
        c->tAC = c->tAC - b10_frameDelta;
        return;
    }
    if (*ph != 1) return;
    if (c->mode108 == 2) {
        r2c_BossDefeat();
        if (m1_cam3F610C->hA8 == 0) return;
        t = m1_cam3F610C->tgt8C;
        if (t == 0) for (;;) ;
        b16_AnimSet(t->anim30, 0x1B);
        rtc_RecSetAnim(0, 0x1B);
        rtc_RecSetAnim(1, 0x1B);
        return;
    }
    if (!afc_NodeActive(c->tgt8C)) return;
    r2c_BossDefeat();
    if (m1_cam3F610C->hA8 == 0) return;
    t = m1_cam3F610C->tgt8C;
    if (t == 0) for (;;) ;
    b16_AnimSet(t->anim30, 0x10);
    rtc_RecSetAnim(0, 0x10);
    rtc_RecSetAnim(1, 0x10);
}
