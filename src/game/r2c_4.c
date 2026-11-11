/* Area r2c, group 4: boss body and helper steps (0x000F4E10..0x000FD416). Names inferred. */
#include "r2c.h"

/* 0x000F4E10: while the boss manager is active, start boss animation anim.
   Calls 0x000F4370 with ESI=anim. */
void r2c_BossAnimIfActive(int anim)
{
    if (g_acb_bossMgr->wA8)
        r2c_BossSetAnim(anim);
}

/* 0x000F7AE0: per-frame step for boss forms 3..5, faster while the
   0x0FE3D0 boss has +0xAA set; 0 otherwise. */
float r2c_BossStepSpeed(const R2cKind *k)
{
    if (k) {
        if (((R2cBossObj *)sub_000FE3D0())->wAA) {
            if (k->kind08 == 3)
                return 42.0f / a50_framesPerSecond;
            if (k->kind08 == 4)
                return 40.5f / a50_framesPerSecond;
            if (k->kind08 == 5)
                return 38.5f / a50_framesPerSecond;
        } else {
            if (k->kind08 == 3)
                return 32.0f / a50_framesPerSecond;
            if (k->kind08 == 4)
                return 30.5f / a50_framesPerSecond;
            if (k->kind08 == 5)
                return 28.5f / a50_framesPerSecond;
        }
    }
    return 0.0f;
}

/* 0x000F7C40: 0x0F7B80(a, b's position, c), or 0 when a or b is missing. */
float r2c_DistTo(void *a, R2cKind *b, float c)
{
    if (!a || !b)
        return 0.0f;
    return sub_000F7B80(a, b->v60, c);
}

/* 0x000F9430: put the form's state to step 0 and copy the helper's position
   and the position of its matching part (form 3: 4, 4: 3, 5: 2) into k. */
void r2c_SnapToHelper(R2cKind *k)
{
    R2cBossObj *e = sub_000F5F80(k);
    R2cKind *t = sub_000FC4B0();
    int part;
    if (k->kind08 == 3)
        part = 4;
    else if (k->kind08 == 4)
        part = 3;
    else if (k->kind08 == 5)
        part = 2;
    sub_000F62F0(e, 0);
    r2c_Vec4Copy(k->v50, t->v50);
    r2c_Vec4Copy(k->v60, (uint32_t *)((char *)sub_0001D0F0(t, part) + 0x70));
}

/* 0x000F9A10: send cue 0x20 to the boss form matching k and clear its step. */
void r2c_FormCue20(const R2cKind *k)
{
    R2cBossObj *e = sub_000F5F80(k);
    if (k->kind08 == 3) {
        sub_000FE330(0x20);
        e->v9C = 0;
        return;
    }
    if (k->kind08 == 4) {
        sub_00100070(0x20);
        e->v9C = 0;
        return;
    }
    if (k->kind08 == 5)
        sub_000FBA50(0x20);
    e->v9C = 0;
}

/* 0x000FA740: two-step sequence: step 0 waits for 0x0F5D00 then sets state
   0x3B; step 1 waits again and raises +0xBC. */
void r2c_StepA(const R2cKind *k)
{
    R2cBossObj *e = sub_000F5F80(k);
    switch (e->v9C) {
    case 0:
        if (sub_000F5D00(k)) {
            sub_000F62F0(e, 0x3B);
            e->v9C++;
        }
        break;
    case 1:
        if (sub_000F5D00(k))
            e->wBC = 1;
        break;
    }
}

/* 0x000FB3E0: like r2c_StepA with state 0x15. */
void r2c_StepB(const R2cKind *k)
{
    R2cBossObj *e = sub_000F5F80(k);
    if (e->v9C == 0) {
        if (sub_000F5D00(k)) {
            sub_000F62F0(e, 0x15);
            e->v9C = 1;
        }
    } else if (sub_000F5D00(k)) {
        e->wBC = 1;
    }
}

/* 0x000FB440: once +0xE4 is set or 0x0F5D00 agrees, kick k's animation
   target, reset the form to step 0 and raise +0xBC. */
void r2c_StepC(const R2cKind *k)
{
    R2cBossObj *e = sub_000F5F80(k);
    if (e->vE4 || sub_000F5D00(k)) {
        sub_001AEED0(k->p30->t14, 2);
        sub_000F62C0(e, 0);
        e->wBC = 1;
    }
}

/* 0x000FB710: restart the form with state 0x16, raise +0xAE and call
   0x0FB580(k, 2). */
void r2c_StepD(const R2cKind *k)
{
    R2cBossObj *e = sub_000F5F80(k);
    sub_000F62F0(e, -1);
    sub_000F62F0(e, 0x16);
    e->wAE = 1;
    sub_000FB580(k, 2);
}

/* 0x000FBA90: force-restart animation anim on both body models; hangs
   without the body or its model. */
void r2c_BodyAnim(int anim)
{
    R2cBossObj *b = afc_body;
    R2cModel *m;
    if (!b)
        for (;;) ;
    m = b->sub8C;
    if (!m)
        for (;;) ;
    m->part30->i08 = -1;
    b->sub90->part30->i08 = -1;
    m = b->sub8C;
    if (!m)
        for (;;) ;
    sub_000832D0(m->part30, anim);
    sub_000832D0(afc_body->sub90->part30, anim);
}

/* 0x000FBCA0: when the body is in phase 2 and its state allows it (not
   0x1C..0x1E, 0x12..0x1B, 2, 3 or 0x0B), the helper is ready and +0xEC is
   clear, send cue 0x1C and clear +0xBC. */
void r2c_BodyCheckRecover(void)
{
    R2cBossObj *b = afc_body;
    int st = afc_bodyState->v6C;
    if (sub_000F3B50(b->sub8C) != 2)
        return;
    if (st >= 0x1C && st <= 0x1E)
        return;
    if (st >= 0x12 && st <= 0x1B)
        return;
    if (st == 2 || st == 3)
        return;
    if (!sub_000FC4D0()->vE8)
        return;
    if (b->wEC || st == 0xB)
        return;
    sub_000FBA00(0x1C);
    b->wBC = 0;
}

/* 0x000FBEA0: start animation 0x21 on both body models, clear the step and
   raise +0xA6. */
void r2c_BodyAnim21(void)
{
    R2cBossObj *b = afc_body;
    if (!b)
        for (;;) ;
    if (!b->sub8C)
        for (;;) ;
    sub_000832D0(b->sub8C->part30, 0x21);
    sub_000832D0(afc_body->sub90->part30, 0x21);
    b->v9C = 0;
    b->wA6 = 1;
}

/* 0x000FC310: start animation 0x24 on both body models, clear the step and
   stop the +0x13C sound. */
void r2c_BodyAnim24(void)
{
    R2cBossObj *b = afc_body;
    if (!b)
        for (;;) ;
    if (!b->sub8C)
        for (;;) ;
    sub_000832D0(b->sub8C->part30, 0x24);
    sub_000832D0(afc_body->sub90->part30, 0x24);
    afc_body->v9C = 0;
    if (b->h13C != -1) {
        sub_00048250(b->h13C);
        b->h13C = -1;
    }
}

/* 0x000FC410: attach model m to the body: reset the body state, register
   its kind-5 and kind-0x0D components on m and start it. Returns m. */
R2cModel *r2c_BodyAttach(R2cModel *m)
{
    R2cBossObj *b;
    if (!m)
        for (;;) ;
    b = afc_body;
    b->sub8C = m;
    sub_000F3AA0(b);
    sub_0001D8B0(b, 5);
    sub_0001D8D0(m, b);
    sub_0001D8B0(b->comp10, 0xD);
    sub_0001D8D0(m, b->comp10);
    sub_0001E9B0(aec_ctx42C8E4, m, m->v14C, 5, 0x11);
    sub_0001EBF0(m, 1);
    sub_000EE270(b->comp10);
    sub_000FBD50();
    return m;
}

/* 0x000FC4E0: detach an active model from the helper: clear the helper,
   deactivate m and remove its kind-5 and kind-0x0D components. 1 when m was
   active. */
int r2c_HelperDetach(R2cModel *m)
{
    R2cHelper *h;
    void *c5, *cd;
    sub_000E3BA0(sub_000E0770());
    if (!(m->flags0C & 1))
        return 0;
    sub_00033B30(m);
    h = afc_helper;
    R2C_ZERO(h, 0x104);
    h->sub8C = 0;
    h->sub90 = 0;
    h->vB4 = 0;
    h->vB8 = 0;
    h->vBC = 0;
    m->flags10 |= 0xD;
    m->flags0C &= ~1u;
    sub_0001EB80(m);
    c5 = sub_0001D960(m, 5);
    cd = sub_0001D960(m, 0xD);
    sub_0001D910(m, c5);
    sub_0001D910(m, cd);
    return 1;
}

/* 0x000FD1C0: put the helper model back to animation 0, clear +0x94 and send
   cue 4 to the three boss forms. */
void r2c_HelperStop(void)
{
    R2cModel *m = afc_helper->sub8C;
    if (!m)
        for (;;) ;
    sub_000832D0(m->part30, 0);
    afc_helper->v94 = 0;
    sub_000FE2E0(4);
    sub_00100020(4);
    sub_000FBA00(4);
}

/* 0x000FD3C0: allocate and clear the helper object. */
void r2c_HelperCreate(void)
{
    R2cHelper *h = (R2cHelper *)sub_00053AB0(sub_000F30E0(0xA) * 0x104, 0, 0x1F6);
    R2C_ZERO(h, 0x104);
    h->sub8C = 0;
    h->sub90 = 0;
    h->vB4 = 0;
    h->vB8 = 0;
    h->vBC = 0;
    afc_helper = h;
}
