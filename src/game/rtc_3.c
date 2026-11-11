/* Area rtc, group 3: tail-call wrappers in 0x00109600..0x001B7300. Names inferred. */
#include "rtc.h"

/* 0x00109600: call 0x000F3F00 with 0.5 (the second argument is replaced). */
void rtc_F3F00Half(void *o, float unused)
{
    sub_000F3F00(o, 0.5f);
}

/* 0x00109650: clear +0x50 and call 0x000F3F00 with 0.5. */
void rtc_ClearF50Half(RtcObj *o)
{
    o->f50 = 0.0f;
    sub_000F3F00(o, 0.5f);
}

/* 0x00178C00: copy the player's vector at +0x50 into the actor's. */
void rtc_CopyPlayerV50(RtcActor *a)
{
    sub_000F5D40(a->v50, rtc_playerObj->v50);
}

/* 0x00179740: clear +0x0C of b's sub-object and set animation 7 on a. */
void rtc_ClearAndAnim7(RtcActor *a, RtcActor *b)
{
    b->sub278->iC = 0;
    sub_000832D0(a->anim30, 7);
}

/* 0x00192380: set an animation on the object of record i (0..3) of the
   table at 0x00400A88. */
void rtc_RecSetAnim(int i, int anim)
{
    RtcObj *o;
    if (i < 0 || i >= 4)
        return;
    o = r4c_recs400A88[i].obj;
    if (o)
        sub_000832D0(o->anim30, anim);
}

/* 0x0019B5F0: play cue i (0..118) of the table at 0x00330F30; -1 does
   nothing, other out-of-range values hang. */
void rtc_PlayCue(int i)
{
    if (i == -1)
        return;
    if (i <= -1 || i >= 0x77)
        for (;;) ;
    sub_0019A0E0(r4c_cues330F30[i].id);
}

/* 0x0019D710: query the handle stored at 0x00402FF4. */
int rtc_QueryHandle402FF4(int unused)
{
    return sub_001AA520(a19_g402FF4);
}

/* 0x001B2690: call 0x001ADE10 on the matrix at +0x40 of m. */
void rtc_MatrixOp40(float *m, const float *a, const float *b, const float *c, const float *d)
{
    sub_001ADE10(m + 0x10, a, b, c, d);
}

/* 0x001B72C0: emit fog for the sub-object at +0x290 (tail jump); returns the
   advanced command pointer from 0x001B1E10. */
void *rtc_FogEmit290(uint8_t *o, void *a)
{
    return r4_FogEmit(o + 0x290, a);
}

/* 0x001B72E0: call 0x001ADA40 on the sub-object at +0xB0. */
void rtc_ADA40At0B0(uint8_t *o, const void *s)
{
    sub_001ADA40(o + 0xB0, s);
}

/* 0x001B7300: copy a vector into +0x270. */
void rtc_CopyVecTo270(uint8_t *o, const float *s)
{
    sub_000F5D40((float *)(o + 0x270), s);
}

/* 0x0013B960: clear flags on an actor and a body and copy the actor's
   position into the body's vector at +0x88. */
void rtc_ActorSyncBody(RtcActor *a, RtcBody *b)
{
    a->flags10 &= ~0x14u;
    a->flagsC &= ~0x20u;
    b->flags4C &= ~8u;
    sub_000F5D40(b->v88, a->v60);
}

/* 0x00142D60: mark the enemy's parts, then scale its nodes by 2. */
void rtc_EnemyMarkAndScale(void *a, RtcActor *b)
{
    void *n;
    b1b_EnemyMarkParts(a, b);
    n = b->sub278->p20;
    if (n)
        r2d_NodesScale(n, 2.0f);
}

/* 0x00178AD0: add 0.06 * frameUnits^2 to +0x7C, then step 0x00178860. */
void rtc_FallStep(void *a, RtcActor *o)
{
    o->f7C += a50_frameUnits * 0.06f * a50_frameUnits;
    sub_00178860(a, o);
}

/* 0x00178D10: turn +0x50 back by 10 degrees per frame unit, clear flags
   0x18 at +0x128, then step 0x00178860. */
void rtc_TurnStep(RtcActor *o, void *b)
{
    o->v50[0] -= a50_frameUnits * 0.174532935f;
    o->flags128 &= ~0x18u;
    sub_00178860(o, b);
}

/* 0x0017B290: clear the float at +0x10 of b's slot 0 and reset a's
   animation sub-object. */
void rtc_ResetSlot0(RtcActor *a, void *b)
{
    sub_001133E0(b, 0)->f10 = 0.0f;
    sub_001AEDD0(a->anim30->p14, 0);
}

/* 0x0017FBA0: clear b's sub-object timer and set animation 1 on a. */
void rtc_ResetAnim1(RtcActor *a, RtcActor *b)
{
    RtcObj *s = b->sub278;
    s->f10 = 0.0f;
    s->i14 = 0;
    sub_000832D0(a->anim30, 1);
}

/* 0x0017FE80: clear b's sub-object timer and set animation 5 on a. */
void rtc_ResetAnim5(RtcActor *a, RtcActor *b)
{
    RtcObj *s = b->sub278;
    s->f10 = 0.0f;
    s->i14 = 0;
    sub_000832D0(a->anim30, 5);
}

/* 0x00181CA0: set an animation on actor a of the pair with key id (pairs
   whose owner is in state 2 are skipped). */
void rtc_PairAnimA(int id, int anim)
{
    int i;
    for (i = 0; i < 4; i++) {
        RtcPair *p = &rtc_pairs3FE2D8[i];
        if (p->owner->state50 != 2 && p->key == id) {
            sub_000832D0(p->a->anim30, anim);
            return;
        }
    }
}

/* 0x00196A30: apply m to the matrix at +0x70 of obj when obj is one of the
   6 records of the table at *0x00401828. */
void rtc_RecMatrixApply(uint8_t *obj, void *m)
{
    int i;
    if (!obj)
        return;
    for (i = 0; i < 6; i++) {
        if (a19_g401828[i].obj == obj) {
            r6_Mat1ADB40(a19_g401828[i].obj + 0x70, m);
            return;
        }
    }
}

/* 0x0019D7F0: set mode 8/1, apply v, then start sequence 0. */
void rtc_StartSeq0(int v)
{
    a19_g402FE4 = 8;
    a19_g402FE8 = 1;
    sub_000408B0(v);
    sub_000408C0(1);
    sub_0019E810(0);
}

/* 0x0019D830: set mode 8/1, apply v, then start sequence 2. */
void rtc_StartSeq2(int v)
{
    a19_g402FE4 = 8;
    a19_g402FE8 = 1;
    sub_000408B0(v);
    sub_000408C0(1);
    sub_0019E810(2);
}

/* 0x0010AC30: start a mover's timer at 98 frame-seconds, clear its two
   vectors, then call 0x000F3F00 on a with 0. */
void rtc_MoverStart(void *a, RtcMover *m)
{
    m->timeB4 = a50_frameSeconds * 98.0f;
    m->vB8[2] = 0.0f;
    m->vB8[1] = 0.0f;
    m->vB8[0] = 0.0f;
    m->vC4[3] = 0.0f;
    m->vC4[2] = 0.0f;
    m->vC4[1] = 0.0f;
    m->vC4[0] = 0.0f;
    sub_000F3F00(a, 0.0f);
}

/* 0x001598F0: reset b's motion state (speed 0.005 per frame unit, scale
   1), clear flags on a and b and copy a's position into the motion. */
void rtc_MotionReset(RtcActor *a, RtcActor *b)
{
    RtcMotion *m = (RtcMotion *)b->sub278;
    m->v24[2] = 0.0f;
    m->v24[1] = 0.0f;
    m->v24[0] = 0.0f;
    m->scale30 = 1.0f;
    m->f10 = 0.0f;
    m->speedC = a50_frameUnits * 0.005f;
    a->flagsC &= ~0x20u;
    b->flags4C &= ~0x70u;
    m->flags0 |= 2;
    sub_000F5D40(m->v74, a->v60);
}

/* 0x00192910: flag the actor and copy one of two fixed vectors into its
   position depending on b's kind (0/2 or 1/3). */
void rtc_PlaceByKind(RtcActor *a, RtcKindHolder *b)
{
    int kind;
    a->flags10 |= 1;
    kind = b->rec74->kind8;
    if (kind == 0 || kind == 2)
        sub_000F5D40(a->v60, r4c_v27B00C);
    else if (kind == 1 || kind == 3)
        sub_000F5D40(a->v60, r4c_v27B01C);
}

/* 0x001999E0: count down voice i (0..15) once it reports state 7; at zero
   mark it state 5 and stop its sound. */
void rtc_VoiceCountDown(int i, int unused)
{
    RtcVoice *v;
    if (i < 0 || i >= 16)
        return;
    v = &r4c_voices401B30[i];
    if (!v->p0)
        return;
    if (sub_00199850(i) != 7)
        return;
    if (v->count20 != 0 && --v->count20 != 0)
        return;
    v->state10 = 5;
    sub_001AAA00(v->handle14, 0);
}

/* 0x0019B620: pick a stream slot for cue i (0..118; -1 gives 0, other
   out-of-range values hang): slot 9 when the current stream is live,
   otherwise 3, then 4, then 9, stopping at the first that fails. */
int rtc_CuePickSlot(int i)
{
    int r;
    if (i == -1)
        return 0;
    if (i <= -1 || i >= 0x77)
        for (;;) ;
    if (!rtc_flag331748 || r4c_streams401D70[rtc_stream331758].id8 == -1) {
        r = sub_00199DE0(3);
        if (r == -1)
            goto done;
        r = sub_00199DE0(4);
        if (r == -1)
            goto done;
    }
    r = sub_00199DE0(9);
done:
    return sub_0019A1D0(r);
}

/* 0x0010B990: start a mover for a fall: clear it like 0x0010AC30, clear
   +0x50 of o, then set its timer to 9.8 and its vertical speed to -40
   frame-seconds and call 0x000F3F00 on o with 0. */
void rtc_MoverStartFall(RtcObj *o, RtcMover *m)
{
    m->timeB4 = a50_frameSeconds * 98.0f;
    m->vB8[2] = 0.0f;
    m->vB8[1] = 0.0f;
    m->vB8[0] = 0.0f;
    m->vC4[3] = 0.0f;
    m->vC4[2] = 0.0f;
    m->vC4[1] = 0.0f;
    m->vC4[0] = 0.0f;
    o->f50 = 0.0f;
    m->timeB4 = a50_frameSeconds * 9.8f;
    m->vB8[2] = a50_frameSeconds * -40.0f;
    sub_000F3F00(o, 0.0f);
}

/* 0x0010BA40: clear a mover like 0x0010AC30, set +0x50 of o to pi/2 and
   call 0x000F3F00 on o with 0. */
void rtc_MoverStartTurned(RtcObj *o, RtcMover *m)
{
    m->timeB4 = a50_frameSeconds * 98.0f;
    m->vB8[2] = 0.0f;
    m->vB8[1] = 0.0f;
    m->vB8[0] = 0.0f;
    m->vC4[3] = 0.0f;
    m->vC4[2] = 0.0f;
    m->vC4[1] = 0.0f;
    m->vC4[0] = 0.0f;
    o->f50 = 1.57079637f;
    sub_000F3F00(o, 0.0f);
}

/* 0x0013B3F0: hide the actor's node, clear flags 0x78 of b, start reaction
   0x1B and jump its animation to a random frame (0..3, or 3..6). */
void rtc_ReactRandom1B(RtcActor *a, RtcBody *b)
{
    float f;
    RtcAnimPart *p;
    r1_NodeHide((RtcObj *)a);
    b->flags4C &= ~0x78u;
    sub_00113090(a, b, 0x1B);
    f = (float)(sub_001C7EE1() % 4);
    if (sub_001C7EE1() % 2 < 1)
        f += 3.0f;
    p = a->anim30->p14;
    sub_001AEDF0(p, RTC_FTOI(f / p->rateC4));
}

/* 0x0013B480: as 0x0013B3F0 with reaction 0x1C and without hiding. */
void rtc_ReactRandom1C(RtcActor *a, RtcBody *b)
{
    float f;
    RtcAnimPart *p;
    b->flags4C &= ~0x78u;
    sub_00113090(a, b, 0x1C);
    f = (float)(sub_001C7EE1() % 4);
    if (sub_001C7EE1() % 2 < 1)
        f += 3.0f;
    p = a->anim30->p14;
    sub_001AEDF0(p, RTC_FTOI(f / p->rateC4));
}

/* 0x0019A4B0: restart stream i (0..44) when it is set up and ready:
   reset its state to 2 under the stream lock and reload it. */
void rtc_StreamRestart(int i)
{
    RtcStream *s;
    if (i < 0 || i >= 45)
        return;
    s = &r4c_streams401D70[i];
    if (!s->p0)
        return;
    if (!sub_00199E70(i))
        return;
    sub_001AA1E0(r4c_g402778);
    s->i4 = 0;
    s->state10 = 2;
    s->i34 = 0;
    sub_001AAD40(s->id8, s->i14, s->iC, i);
    sub_001AA1F0(r4c_g402778);
}

/* 0x0019C620: run a save step: inside a busy section, if the slot named by
   the request is not already done, select it, run its process until state
   3 and mark the request done (+0x14 = 1); otherwise mark it not done. */
void rtc_SaveStep(RtcSaveReq *r)
{
    sub_001A5380(1);
    sub_00038070(4);
    if (r->p4 && !sub_000512D0(r->slot0 + 0x11D, r->p4)) {
        sub_0004F700(r->slot0 + 0x11D);
        sub_0004F730(1);
        r6e_ProcFinish(r->proc10, r->slot0);
        while (sub_0008CD90(r->proc10) != 3)
            r6b_ProcStep(r->proc10);
        sub_0004F730(0);
        sub_0008CD80(r->proc10);
        r->done14 = 1;
        sub_001A5380(0);
        return;
    }
    r->done14 = 0;
    sub_001A5380(0);
}

/* 0x0011B900: knock out an enemy: update its flags and b's, set its
   reaction list, free its resources and b's part nodes, play motion 0xB
   and effect 0xCE at its model, hide b's record and, for kinds 3/4, renew
   node 9 of the partner (kind 4/3) unless that one is flagged. */
void rtc_EnemyKnockOut(RtcActor *a, RtcActor *b)
{
    int i, k;
    void *e;
    uint8_t *c;
    a->flagsC &= ~0x20u;
    a->flags10 |= 0xD;
    b->flags4C &= 0xFEFFFF87u;
    sub_0013A120(a, 2, b3b_tbl31DBD4);
    r1b_RecFreeRes(a);
    r2d_PListPrune(b);
    r1c_ObjPlayMotion(a, 0xB, 1);
    aab_Effect494D0(0xCE, a->model20 + 0x30, 0);
    for (i = 0; i < 4; i++) {
        if (b->sub278->nodes34[i]) {
            r1d_NodeFree(b->sub278->nodes34[i]);
            b->sub278->nodes34[i] = 0;
        }
    }
    if (b->sub278->p20)
        r1b_RecHideAll(b->sub278->p20);
    switch (a->kind8) {
    case 3:
        k = 4;
        break;
    case 4:
        k = 3;
        break;
    default:
        return;
    }
    e = sub_000EDBE0(2, k);
    if (!e)
        return;
    c = sub_0001D960(e, 4);
    if (!c || (c[0x20] & 1))
        return;
    b1b_NodeRenew(c, 9);
}
