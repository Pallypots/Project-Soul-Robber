/* Area r3d: game functions in 0x00160000..0x0017FFFF (r3d_2). Names inferred. */
#include "r3d.h"

/* 0x0017FD40: start animation 2 on obj and reset the work timer (mode 6). */
void r3d_Start17FD40(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;

    sub_00036750(obj, 2);
    sub_000832D0(obj->pa30, 2);
    w->f10 = 0.0f;
    w->i14 = 0;
    w->s54 = 6;
}

/* 0x001751D0: remove ref from the three reference slots of a's kind-6 component. */
void r3d_Unref1751D0(R3cObj *a, void *ref)
{
    R3cObj *c;
    R3dRefs *r;
    int i;

    if (!a || !ref)
        return;
    c = sub_0001D960(a, 6);
    if (!c)
        return;
    r = (R3dRefs *)c->work278;
    for (i = 0; i < 3; i++)
        if (r->refs24[i] == ref)
            break;
    if (i == 3)
        for (;;) ;
    r->refs24[i] = 0;
}

/* 0x00171F30: reset the 0x003FD7B0.. counters and both lists of the six 0x003FD2B8 records. */
void r3d_Reset171F30(void)
{
    R3cRecD4 *r;

    r3c_i3FD7B0 = 0;
    r3c_i3FD7B4 = 0;
    r3c_i3FD7B8 = 0;
    r3c_i3FD7BC = 0;
    for (r = r3c_recs3FD2B8; r < r3c_recs3FD2B8 + 6; r++) {
        sub_0001D8B0(r, 8);
        sub_0001D8B0(r->b, 13);
    }
    r3c_i3FD7C0 = 0;
    r3c_obj3FD7C4 = 0;
}

/* 0x0016BDA0: with motion flag 2 (not 0x20) and a height gap to the player outside (C2, C1) pick mode 2;
   otherwise mode 0 once act->f5C goes negative. */
void r3d_Pick16BDA0(R3cObj *obj, R3cObj *act)
{
    uint32_t f = act->p74->flags;
    float d;

    if (f & 2) {
        if (!(f & 0x20)) {
            d = obj->pos60[1] - ((R3cObj *)g_playerObj)->pos60[1];
            if (d > 100.0f || -100.0f > d) {
                sub_001671D0(obj, act, 2);
                return;
            }
        }
    }
    if (0.0f > act->f5C)
        sub_001671D0(obj, act, 0);
}

/* 0x001777A0: remove ref from the reference slots at +0x28 of a's kind-6 component and clear mask bits. */
void r3d_Unref1777A0(R3cObj *a, void *ref, uint32_t mask)
{
    R3cObj *c;
    R3dRefs *r;
    int i;

    if (!a || !ref)
        return;
    c = sub_0001D960(a, 6);
    if (!c)
        return;
    r = (R3dRefs *)c->work278;
    for (i = 0; i < 3; i++)
        if (r->refs28[i] == ref)
            break;
    if (i == 3)
        for (;;) ;
    r->refs28[i] = 0;
    r->flags10 &= ~mask;
}

/* 0x001668D0: reset the task block at 0x003F8400, both lists of the sixteen 0x003F76C0 records,
   then re-initialise the effect pools. */
void r3d_Reset1668D0(void)
{
    R3cRecD4 *r;

    b16_task3F8400 = 0;
    b16_taskId3F8404 = 0;
    r3d_i3F8408 = 0;
    r3d_i3F840C = 0;
    for (r = r3d_recs3F76C0; r < r3d_recs3F76C0 + 16; r++) {
        sub_0001D8B0(r, 9);
        sub_0001D8B0(r->b, 13);
    }
    r3d_i31F024 = 0;
    b16_Buf3F8C98Init();
    b16_Pool20Init();
    b16_Pool60Init();
    b16_Pool18Init();
}

/* 0x0016F7F0: step the sound request at 0x003F9300: in state 0 start sound 0x9F once (-1 when
   no task id), state 1 resets; returns 1 in any other state. */
int r3d_SoundStep16F7F0(void)
{
    switch (r3d_i3F9300) {
    case 0:
        if (!b16_taskId3F92EC)
            return -1;
        if (sub_0004F6D0(0x9F))
            return 0;
        sub_000512D0(0x9F, sub_00053AB0(sub_0004F680(0x9F), 0, 0xE2));
        break;
    case 1:
        break;
    default:
        return 1;
    }
    r3d_i3F9300 = 0;
    return 0;
}

/* 0x00168C60: clear motion flags 0x8C; if a 0xF00000 slot is set, swap its event bits
   (clear 0x1C8+i, set 0x287+i and 0x28B); then finish via 0x000ED780. */
void r3d_Finish168C60(R3cObj *obj, R3cObj *act)
{
    R3cBlk74 *m = act->p74;
    uint32_t f;
    int v, i;

    m->flags &= 0xFFFFFF73;
    f = m->flags;
    if (f & 0xF00000) {
        v = (f >> 20) & 0xF;
        for (i = 0; v && !(v & 1); i++)
            v >>= 1;
        r2b_ClearBit(i + 0x1C8);
        r2b_SetBit(i + 0x287);
        r2b_SetBit(0x28B);
    }
    sub_000ED780(obj);
}

/* 0x0017FEC0: in stage 5, count the start (game mode 1), then after half a second
   enter state 2 and run 0x0017F390; until then advance the work timer. */
void r3d_Stage17FEC0(R3cObj *obj, R3cObj *act)
{
    R3cWork *w;

    if (b7c_stage3FE060 != 5)
        return;
    w = act->work278;
    if (w->i14 == 0) {
        if (((R3cGame *)sub_000E0770())->i324 == 1)
            w->i14++;
        return;
    }
    if (w->f10 > 0.5f) {
        sub_00113040(obj, act, 2);
        sub_0017F390();
        return;
    }
    w->f10 += r3c_frameSeconds;
}

/* 0x0017C2B0: drop act's node 2 (and its record), release handle +0x6C and free block +0x70. */
int r3d_Release17C2B0(R3cObj *obj, R3dAct *act)
{
    R3dNode *n = (R3dNode *)sub_001133E0(act, 2);

    if (n) {
        if (n->i14 >= 0)
            sub_000A7950(n->i14);
        sub_00113370(act, n);
    }
    if (act->h6C >= 0) {
        sub_00048250(act->h6C);
        act->h6C = -1;
    }
    if (act->h70) {
        sub_00033A70(act->h70);
        act->h70 = 0;
    }
    return 1;
}

/* 0x0017CB90: move obj by the work velocity, spin it, add the travelled XZ length to the
   work distance and enter state 8 at 60 units or on contact flags 0xA. */
void r3d_Move17CB90(R3cObj *obj, R3cObj *act)
{
    R3dWork34 *w = (R3dWork34 *)act->work278;

    sub_001ADAF0((float *)obj->pos60, (const float *)obj->pos60, (const float *)w->v34);
    r4c_Spin(obj, r3d_rate32B698);
    w->f44 += r4c_VecLenXZ(w->v34);
    sub_000C56B0(obj);
    if (w->f44 >= 60.0f || (obj->flags128 & 0xA))
        sub_00113040(obj, act, 8);
}

/* 0x0016E1E0: play animation 2, set motion flags 0x200080 and 0x1000, reset the motion vector
   at +0x20 to (0, 3, 0) and copy bank 2's value from the player's model. */
void r3d_Start16E1E0(R3cObj *obj, R3cObj *act)
{
    R3dBlk74 *m = (R3dBlk74 *)act->p74;
    R3dBlk74 *n;

    sub_00167200(obj, act, 2);
    m->flags |= 0x200080;
    n = (R3dBlk74 *)act->p74;
    n->f24 = 0.0f;
    n->f2C = 0.0f;
    n->f20 = 0.0f;
    n->f28 = 3.0f;
    n->flags |= 0x1000;
    m->f40 = ((R3dCtx *)((R3cObj *)g_playerObj)->m20)->banksC4[2].f74;
}

/* 0x0016CF40: play animation 1, set the motion speed (20 per second) and flag 0x400, and snap obj
   to the preset position of slot m->i04 (none for slot 5). */
void r3d_Start16CF40(R3cObj *obj, R3cObj *act)
{
    R3cBlk74 *m = act->p74;
    const float *p;
    int k;

    sub_00167200(obj, act, 1);
    m->v34[0] = r3c_frameSeconds * 20.0f * r3c_frameUnits;
    m->v34[1] = 0.0f;
    m->flags |= 0x400;
    k = m->i04;
    if (k != 5) {
        p = r3d_vecs31F3E0[k];
        obj->pos60[0] = p[0];
        obj->pos60[1] = p[1];
        obj->pos60[2] = p[2];
    }
}

/* 0x00175220: set obj's turn rate: -3 degrees per frame unit while the player is within
   +-90 degrees of its facing, else +3 degrees. */
void r3d_TurnRate175220(R3cObj *obj)
{
    float a = sub_00113290(obj, ((R3cObj *)g_playerObj)->pos60);

    if (a > 1.5707964f || -1.5707964f > a)
        obj->f50 = r3c_frameUnits * 0.05235988f;
    else
        obj->f50 = r3c_frameUnits * -0.05235988f;
}

/* 0x0017E210: reset the work block (word +0x28, timer +0x2C), run 0x00182770(2), fire effect
   0x1D2 at obj and free the four work handles. */
void r3d_Reset17E210(R3cObj *obj, R3cObj *act)
{
    R3dWork *w = (R3dWork *)act->work278;

    w->s28 = 0;
    w->f2C = 0.0f;
    sub_00182770(2);
    sub_000494D0(0x1D2, obj->pos60, 1);
    sub_00033A40(w->p14);
    w->p14 = 0;
    sub_00033A40(w->p10);
    w->p10 = 0;
    sub_00033A40(w->p18);
    w->p18 = 0;
    sub_00033A40(w->p1C);
    w->p1C = 0;
}

/* 0x0016C3D0: store in act's motion block how many of the stage bits 0x12, 0x20.. are set
   in a row (0 without 0x12) and return whether it equals want (12 counts as 5).
   regargs: act=EAX want=stack. */
int r3d_Stage16C3D0(R3cObj *act, int want)
{
    R3cBlk74 *m = act->p74;
    int n, i;

    if (want == 12)
        want = 5;
    if (r2b_TestBit(0x12)) {
        n = 1;
        for (i = 0; i < 5; i++) {
            if (!r2b_TestBit(i + 0x20))
                break;
            n++;
        }
        m->i04 = n;
    } else {
        m->i04 = 0;
    }
    return m->i04 == want;
}

/* 0x00171150: flag obj 0x800 when act's timer runs out; while act->i54 == 1 grow obj's scale
   from 1 at 20 per second until 0.05 s, then settle it at 1. */
void r3d_Grow171150(R3cObj *obj, R3cObj *act)
{
    if ((act->flags4C & 1) && 0.0f >= act->f70)
        obj->flags10 |= 0x800;
    if (act->i54 != 1)
        return;
    if (act->f58 >= 0.05f) {
        sub_000EE850(obj, 1.0f);
        act->i54 = 0;
        return;
    }
    sub_000EE850(obj, act->f58 * 20.0f + 1.0f);
}

/* 0x00172000: step the sound request at 0x003FD7C0: in state 0 start the sound for slot idx
   (0..23) once (-1 when out of range or no task id), state 1 resets; 1 in any other state. */
int r3d_SoundStep172000(int idx)
{
    int id;

    switch (r3c_i3FD7C0) {
    case 0:
        if (!r3c_i3FD7B4 || idx < 0 || idx >= 24)
            return -1;
        id = r3d_ids32B208[idx];
        if (sub_0004F6D0(id))
            return 0;
        sub_000512D0(id, sub_00053AB0(sub_0004F680(id), 0, 0x1A9));
        break;
    case 1:
        break;
    default:
        return 1;
    }
    r3c_i3FD7C0 = 0;
    return 0;
}

/* 0x00175C40: phase 0 arms a 90 s timer (obj flag 1, work flags 0x402); every phase-1 frame
   sets obj->f84 from f70 (x 30 / 90) and finishes (0x000ED780) when the timer runs out. */
void r3d_Timer175C40(R3cObj *obj, R3cObj *act)
{
    R3dAct *a = (R3dAct *)act;
    R3cWork *w = act->work278;

    switch (a->i58) {
    case 0:
        obj->flags10 |= 1;
        act->f74 = r3c_frameSeconds * 90.0f;
        w->flags00 |= 0x402;
        a->i58++;
        /* fall through */
    case 1:
        obj->f84 = obj->f70 * 30.0f * 0.011111111f;
        if (0.0f > act->f74)
            sub_000ED780(obj);
        break;
    }
}

/* 0x00177EC0: as 0x00175C40 with work flag 2 only. */
void r3d_Timer177EC0(R3cObj *obj, R3cObj *act)
{
    R3dAct *a = (R3dAct *)act;
    R3cWork *w = act->work278;

    switch (a->i58) {
    case 0:
        obj->flags10 |= 1;
        act->f74 = r3c_frameSeconds * 90.0f;
        w->flags00 |= 2;
        a->i58++;
        /* fall through */
    case 1:
        obj->f84 = obj->f70 * 30.0f * 0.011111111f;
        if (0.0f > act->f74)
            sub_000ED780(obj);
        break;
    }
}

/* 0x00170910: grow obj's scale from 1 at 20 per second; at 0.05 s settle it at 1, reset
   act's counters and go to state 1 (kind < 10) or 2. */
void r3d_Grow170910(R3cObj *obj, R3cObj *act)
{
    if (act->f58 >= 0.05f) {
        sub_000EE850(obj, 1.0f);
        act->i54 = 0;
        act->f58 = 0.0f;
        act->state50 = (obj->i08 < 10) + 1;
        return;
    }
    sub_000EE850(obj, act->f58 * 20.0f + 1.0f);
}

/* 0x00176400: apply the jump impulse once (work flag 0x100), then when 0x00176150 reports
   landing clear work flags 0x402 and enter state 0. */
void r3d_Land176400(R3cObj *obj, R3cObj *act)
{
    if (!(act->work278->flags00 & 0x100)) {
        obj->pos60[1] += obj->f70 * 30.0f;
        act->work278->flags00 |= 0x100;
    }
    if (sub_00176150(obj, act, &act->work278->i10)) {
        act->work278->flags00 &= 0xFFFFFBFD;
        sub_00113040(obj, act, 0);
    }
}

/* 0x00178C90: steer act's velocity +0x78 toward obj along the unit direction from obj to
   act+0x88 (45 x 4 per second) and reset obj's scale to 1. */
void r3d_Steer178C90(R3cObj *obj, R3cObj *act)
{
    R3dAct *a = (R3dAct *)act;
    float d[4];

    sub_001AD9F0(d, a->v88, obj->pos60);
    sub_001AD7E0(d, d);
    sub_001ADBA0(a->v78, d, r3c_frameSeconds * 45.0f * 4.0f);
    sub_000EE6D0(obj, 1.0f);
}

/* 0x0017E280: sink obj by 8 per frame down to -96, then after one second of the work timer
   send the work owner to state 0. */
void r3d_Sink17E280(R3cObj *obj, R3cObj *act)
{
    R3cWork *w;

    obj->pos60[1] -= 8.000002f / r3c_framesPerSecond;
    w = act->work278;
    if (-96.0f > obj->pos60[1])
        obj->pos60[1] = -96.0f;
    if (w->f2C > 1.0f) {
        sub_00113040(w->obj00, w->act04, 0);
        return;
    }
    w->f2C += r3c_frameSeconds;
}

/* 0x001744C0: hand the pending object at 0x003FD7C4 to its kind-8 component's state machine:
   entry 0 for kinds 16..20, else entry 1 (mode 1); then clear the pending pointer. */
void r3d_Hand1744C0(void)
{
    R3cObj *o = r3c_obj3FD7C4;
    R3cObj *c;
    int k;

    if (!o)
        for (;;)
            ;
    c = sub_0001D960(o, 8);
    if (!c)
        for (;;)
            ;
    k = r3c_obj3FD7C4->i08;
    if (k >= 16 && k <= 20) {
        c->flags4C = 0;
        c->state50 = 0;
        c->f54 = 0.0f;
        r3_fsmEnter32B1B0[0](r3c_obj3FD7C4, c);
    } else {
        c->flags4C = 1;
        c->state50 = 0;
        c->f54 = 0.0f;
        r3_fsmEnter32B1B0[1](r3c_obj3FD7C4, c);
    }
    r3c_obj3FD7C4 = 0;
}

/* 0x00156100: step a blend motion: pos +0x14 = from * (1 - t) + to +0x24 * t, then advance t
   by the speed +0x0C up to 1. */
void r3d_Blend156100(R3dMotion *m)
{
    float a[4], b[4];

    sub_001ADBA0(b, m->v14, 1.0f - m->t10);
    sub_001ADBA0(a, m->v24, m->t10);
    sub_001ADAF0((float *)m->v14, (const float *)b, (const float *)a);
    m->t10 += m->speed0C;
    if (m->t10 > 1.0f)
        m->t10 = 1.0f;
}

/* 0x00175290: ease obj's turn rate +0x50 toward 0 by one degree per frame unit and report
   whether it is now within that step of 0. */
int r3d_EaseTurn175290(R3cObj *obj)
{
    if (obj->f50 > 0.0f)
        obj->f50 += r3c_frameUnits * -0.017453292f;
    else if (0.0f > obj->f50)
        obj->f50 += r3c_frameUnits * 0.017453292f;
    if (r3c_frameUnits * 0.017453292f > obj->f50 && obj->f50 > r3c_frameUnits * -0.017453292f)
        return 1;
    return 0;
}

/* 0x00176970: angle between o's model "back" axis (0, 0, -1) and the direction to the player.
   regargs: o=ESI; float result in st0. */
float r3d_AngleToPlayer176970(R3cObj *o)
{
    float axis[4], d[4];

    axis[0] = 0.0f;
    axis[1] = 0.0f;
    axis[2] = -1.0f;
    axis[3] = 0.0f;
    sub_001AD9F0(d, ((R3cObj *)g_playerObj)->pos60, o->pos60);
    sub_001AD9B0(axis, (const float *)sub_0001D0F0(o, 2), axis);
    sub_001AD9B0(axis, o->m20, axis);
    return sub_001B27C0(axis, d);
}

/* 0x00169E20: once (act->i54 == 0): set motion flag 0x20000 and rate 90 per second, drop
   flags 0x60, light 0x19A at obj when motion flag 0x800 is set, and count the step. */
void r3d_Once169E20(R3cObj *obj, R3cObj *act)
{
    R3cBlk74 *m;
    uint32_t f;

    if (act->i54 != 0)
        return;
    m = act->p74;
    f = m->flags | 0x20000;
    m->f10 = 90.0f / r3c_frameUnits * r3c_frameSeconds;
    m->flags = f;
    if (f & 0x60)
        m->flags = f & ~0x60u;
    if (m->flags & 0x800)
        sub_00049700(0x19A, 0x80, 0x80, 0x80, obj->pos60, 1, 3.4028235e38f, 0);
    act->i54++;
}

/* 0x00176D10: as 0x00175C40 with a 90 frame-unit timer and work flag 0x20. */
void r3d_Timer176D10(R3cObj *obj, R3cObj *act)
{
    R3dAct *a = (R3dAct *)act;
    R3cWork *w = act->work278;

    switch (a->i58) {
    case 0:
        obj->flags10 |= 1;
        act->f74 = 90.0f / r3c_frameUnits * r3c_frameSeconds;
        w->flags00 |= 0x20;
        a->i58++;
        /* fall through */
    case 1:
        obj->f84 = obj->f70 * 30.0f * 0.011111111f;
        if (0.0f > act->f74)
            sub_000ED780(obj);
        break;
    }
}

/* 0x00179E40: release act's sound +0x6C, the work sound +0x28 (unless still playing) and block
   +0x24, clear the 0x003FDC3C block and act's work pointer. */
int r3d_Release179E40(R3cObj *obj, R3cObj *act)
{
    R3dWork *w = (R3dWork *)act->work278;

    if (((R3dAct *)act)->h6C >= 0) {
        sub_00048250(((R3dAct *)act)->h6C);
        ((R3dAct *)act)->h6C = -1;
    }
    if (w->i28 != -1 && !sub_00048100(w->i28)) {
        sub_00048250(w->i28);
        w->i28 = -1;
    }
    if (w->p24) {
        sub_00033A70(w->p24);
        w->p24 = 0;
    }
    R3D_ZERO(r3d_blk3FDC3C, sizeof(r3d_blk3FDC3C));
    act->work278 = 0;
    return 1;
}

/* 0x00166940: step the sound request at 0x0031F024: in state 0 start the sound of slot idx
   (0..3, none for id 0x21D) once (-1 when out of range or no task id), state 1 resets;
   1 in any other state. */
int r3d_SoundStep166940(int idx)
{
    int id;

    switch (r3d_i31F024) {
    case 0:
        if (!b16_taskId3F8404 || idx < 0 || idx >= 4)
            return -1;
        id = b4c_sndTab279924[idx].id;
        if (id == 0x21D || sub_0004F6D0(id))
            return 0;
        sub_000512D0(id, sub_00053AB0(sub_0004F680(id), 0, 0xFF));
        break;
    case 1:
        break;
    default:
        return 1;
    }
    r3d_i31F024 = 0;
    return 0;
}

/* 0x0016AFB0: shrink obj over 90 frame units (act->i54 0 arms act->f5C, 1 scales by the
   remaining fraction) and finish (0x000ED780) when the time runs out. */
void r3d_Shrink16AFB0(R3cObj *obj, R3cObj *act)
{
    switch (act->i54) {
    case 0:
        act->f5C = 90.0f / r3c_frameUnits * r3c_frameSeconds;
        act->i54 = 1;
        /* fall through */
    case 1:
        sub_000EE6D0(obj, act->f5C / (90.0f / r3c_frameUnits * r3c_frameSeconds));
        if (0.0f > act->f5C)
            sub_000ED780(obj);
        break;
    }
}

/* 0x00174C50: step the sound request at 0x003FD7D8: in state 0 start the sound of id slot idx
   (0..39, none for id 0x21D) once (-1 when out of range or no task id), state 1 resets;
   1 in any other state. */
int r3d_SoundStep174C50(int idx)
{
    int id;

    switch (r3d_i3FD7D8) {
    case 0:
        if (!b7c_taskId3FD7CC || idx < 0 || idx >= 40)
            return -1;
        id = r3c_ids279F00[idx].id;
        if (id == 0x21D || sub_0004F6D0(id))
            return 0;
        sub_000512D0(id, sub_00053AB0(sub_0004F680(id), 0, 0xFF));
        break;
    case 1:
        break;
    default:
        return 1;
    }
    r3d_i3FD7D8 = 0;
    return 0;
}

/* 0x00179DC0: for the first entity of list 4 side 5: release its component's sound +0x6C and
   the work sound +0x28 (while still playing) and set the work wait +0x20 to 10. */
void r3d_Quiet179DC0(void)
{
    R3cObj *e = sub_000EDBE0(4, 5);
    R3cObj *c;
    R3dWork *w;

    if (!e)
        return;
    c = sub_0001D960(e, 6);
    if (!c)
        return;
    w = (R3dWork *)c->work278;
    if (!w)
        return;
    if (((R3dAct *)c)->h6C >= 0) {
        sub_00048250(((R3dAct *)c)->h6C);
        ((R3dAct *)c)->h6C = -1;
    }
    if (w->i28 != -1 && sub_00048100(w->i28)) {
        sub_00048250(w->i28);
        w->i28 = -1;
    }
    w->f20 = 10.0f;
}

/* 0x0017F7E0: reset stage state: clear 0x003FE05C/0x003FE060/0x003FE0B8, finish the three
   pending objects at 0x003FE050, set record 0x15 to mode 1 and records 8..13 to mode 5. */
void r3d_ResetStage17F7E0(void)
{
    int i;

    b7c_stage3FE060 = 0;
    r3d_f3FE05C = 0.0f;
    r3d_i3FE0B8 = 0;
    for (i = 0; i < 3; i++) {
        if (r3d_objs3FE050[i]) {
            sub_000ED780(r3d_objs3FE050[i]);
            r3d_objs3FE050[i] = 0;
        }
    }
    sub_000A4290(0x15)->i40 = 1;
    for (i = 0; i < 6; i++)
        sub_000A4290(i + 8)->i40 = 5;
}
