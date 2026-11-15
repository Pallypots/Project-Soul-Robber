/* Area m3, file 10: stage reset, AI warp. Names inferred. */
#include <stdint.h>

typedef struct M3Pair10 { void *a; void *b; int32_t c; } M3Pair10;
typedef struct M3Cue10 { uint8_t unk00[8]; int32_t i8; uint16_t hC, hE; uint8_t data10[1]; } M3Cue10;
typedef struct M3Ent10 { M3Cue10 *cue; uint8_t unk04[0x3C]; } M3Ent10;
typedef struct M3Fx10 { void *p; uint8_t unk04[0x24]; } M3Fx10;
typedef struct M3Stage10 {
    uint8_t unk00[0x5C]; int32_t i5C, i60, i64; void *p68; uint8_t unk6C[0x50]; M3Ent10 ent0BC[1];
    uint8_t unk0FC[0x200]; void *h2FC; uint8_t unk300[0x14]; int32_t cur314; int32_t i318;
    uint8_t unk31C[0x218]; M3Pair10 pair534[8]; uint8_t unk594[0x2D8]; M3Fx10 fx86C[5];
} M3Stage10;
extern uint8_t m1_snd3E1270[];
extern uint8_t g_stats[];
void *sub_0019A950(int size, int a);
void r1b_RecDetachNodes(void *n);
void sub_00019000(void *s, int a);
void sub_000D0200(void *s, int a, int b);
void m1_MenuSlide0E8920(int a, int b);
void sub_000E8A50(int a, int b);
void r1g_ComboRequest(int a, int b);

/* 0xE3390: reset the stage: allocate the 0x214-byte work block, detach and clear the eight node pairs and five effects, play cue 1 on 0x3E1270, reset stats and menus, then load the current entry's cue (id, data, counts) or clear it, and request combo mode 2. */
void m3_StageResetE3390(M3Stage10 *s) {
    int i; M3Cue10 *c;
    s->h2FC = sub_0019A950(0x214, 0);
    for (i = 0; i < 8; i++) {
        if (s->pair534[i].a) r1b_RecDetachNodes(s->pair534[i].a);
        if (s->pair534[i].b) r1b_RecDetachNodes(s->pair534[i].b);
        s->pair534[i].a = 0;
        s->pair534[i].b = 0;
    }
    for (i = 0; i < 5; i++) {
        if (s->fx86C[i].p) r1b_RecDetachNodes(s->fx86C[i].p);
        s->fx86C[i].p = 0;
    }
    sub_00019000(m1_snd3E1270, 1);
    sub_000D0200(g_stats, 0, 0);
    m1_MenuSlide0E8920(0, 0);
    sub_000E8A50(0, 0);
    s->i318 = 0;
    c = s->cur314 >= 0 ? s->ent0BC[s->cur314].cue : 0;
    if (c) {
        s->i5C = c->hE;
        s->i60 = c->i8;
        s->i64 = c->hC;
        s->p68 = c->data10;
        { volatile int z; z = 0; }
        r1g_ComboRequest(2, 0);
        return;
    }
    s->i5C = 0; s->i60 = 0; s->i64 = 0; s->p68 = 0;
    r1g_ComboRequest(2, 0);
}

typedef struct M3St10 { uint8_t unk00[0x34]; void *fx34; } M3St10;
typedef struct M3En10 { uint8_t unk00[0x4C]; uint32_t f4C; uint8_t unk50[8]; int32_t step58; uint8_t unk5C[0x18]; float t74; uint8_t unk78[0x200]; M3St10 *st278; } M3En10;
typedef struct M3Ob10 { uint8_t unk00[0x20]; uint8_t *mdl20; } M3Ob10;
extern float m1_frameTime42C858;
extern float b10_frameDelta;
int  sub_00139FE0(M3Ob10 *a, M3En10 *o);
int  aab_Rand(void);
void m1_AiGoto113040(void *a, void *e, int st);
void r1d_NodeFree(void *n);
void *aab_Attach36750(void *o, int mode);
void aab_Effect494D0(int id, void *pos, int a);

/* 0x11AD10: AI taunt state (when 0x139FE0 allows): step 0 plays effect 0xCB and waits 70 frames; step 1 replaces its attached effect with mode 4; step 2 sets flags 0x38 and goes to state 8 one time in four, else waits 60 frames and goes to state 5. */
void m3_AiTaunt11AD10(M3Ob10 *a, M3En10 *o) {
    if (!sub_00139FE0(a, o)) return;
    switch (o->step58) {
    case 2:
        o->f4C |= 0x38;
        if (aab_Rand() % 4 < 1) { m1_AiGoto113040(a, o, 8); return; }
        o->t74 = 60.0f / m1_frameTime42C858 * b10_frameDelta;
        m1_AiGoto113040(a, o, 5);
        return;
    case 1:
        if (o->st278->fx34) {
            r1d_NodeFree(o->st278->fx34);
            o->st278->fx34 = 0;
        }
        o->st278->fx34 = aab_Attach36750(a, 4);
        o->step58++;
        return;
    case 0:
        aab_Effect494D0(0xCB, a->mdl20 + 0x30, 0);
        o->t74 = 70.0f / m1_frameTime42C858 * b10_frameDelta;
        o->step58++;
        return;
    }
}

typedef struct M3TmRec10 { int32_t start0; uint8_t unk04[8]; int32_t kindC; int32_t len10; int32_t flag14; } M3TmRec10;
typedef struct M3TmSlot10 { int32_t on; int32_t start; int32_t lo; int32_t hi; int32_t col; int32_t text; int32_t flag; } M3TmSlot10;
typedef struct M3Tm10 { uint8_t unk00[0x324]; int32_t mode324; uint8_t unk328[0xF0]; int32_t act418; uint8_t unk41C[0x14]; M3TmSlot10 slot430[8]; } M3Tm10;
extern int m1_level413178;
extern int32_t m3_timerColB318598[];
int m1_HudText0E85D0(int kind, float t);

/* 0xEA3F0: add a timed window from a record: its length in seconds (len * 0.03) gets 3 more seconds on difficulty 0 and 10 percent less on difficulty 2; without a timer object only the HUD text is made; otherwise (unless mode 5) take the first free of the eight slots and fill it like 0xEA060. */
void m3_TimerAddEA3F0(M3Tm10 *o, M3TmRec10 *r) {
    float t; int i, h; M3TmSlot10 *s;
    if (r == 0) return;
    t = (float)r->len10 * 0.03f;
    switch (m1_level413178) {
    case 0: t = t + 3.0f; break;
    case 2: t = t * 0.9f; break;
    }
    if (o == 0) { m1_HudText0E85D0(r->kindC, t); return; }
    if (o->mode324 == 5) return;
    for (i = 0; i < 8; i++)
        if (o->slot430[i].on == 0) break;
    if (i >= 8) return;
    h = m1_HudText0E85D0(r->kindC, t);
    o->act418++;
    s = &o->slot430[i];
    s->on = 1;
    s->start = r->start0;
    s->lo = r->start0 - r->len10 / 2;
    s->hi = r->len10 / 2 + r->start0;
    o->slot430[i].text = h;
    s->col = m3_timerColB318598[r->kindC];
    s->flag = r->flag14;
}

typedef struct M3Xf10 { uint8_t unk00[0x10]; int32_t mode10; uint8_t unk14[0xD8]; } M3Xf10;
extern M3Xf10 m1_slots41D020[20];
void a3c_VecCopy(float *dst, const float *src);
int m1_XfAlloc0C7540(void *o, float a, float b, float *pos, float *dir);

/* 0xC75E0: spawn three stacked transforms at the object (scales 0.2, 0.25 and 0.3; each 2 then 8 more units lower) and set each one that was allocated to mode 8. */
void m3_XfStackC75E0(uint8_t *o) {
    float p[4], d[4]; int r;
    p[0] = 0.0f; p[1] = 0.0f; p[2] = 0.0f; p[3] = 1.0f;
    d[0] = 0.0f; d[1] = 0.0f; d[2] = 0.0f; d[3] = 1.0f;
    a3c_VecCopy(p, (float *)(o + 0x60));
    r = m1_XfAlloc0C7540(o, 1.0f, 0.2f, p, d);
    if (r >= 0) m1_slots41D020[r].mode10 = 8;
    p[1] = p[1] - 2.0f;
    r = m1_XfAlloc0C7540(o, 1.0f, 0.25f, p, d);
    if (r >= 0) m1_slots41D020[r].mode10 = 8;
    p[1] = p[1] - 8.0f;
    r = m1_XfAlloc0C7540(o, 1.0f, 0.3f, p, d);
    if (r >= 0) m1_slots41D020[r].mode10 = 8;
}

extern uint8_t m1_snd3E1270[];
void sub_000DFD40(int *a, int *b);
int  sub_000A4370(int slot);
void sub_000A4340(int slot, int v);
void sub_00019000(void *s, int a);
void sub_0001AB00(void *s, int a, int b, int c, int d);

/* 0xB3B60: menu step for a 2-int setting: 0 clears, 1 sets bit 0 and 10, 3 clears and returns 0; with bit 0 the slot comes from 0xDFD40 (hangs unless it reports 0 and 11), else the mode is the slot; setting 10 opens it with the cue, 11 confirms when ready (then 20), 20 clears and returns 0. */
int m3_MenuStepB3B60(int k, int *s) {
    int l, slot;
    if (k == 0) { s[0] = 0; s[1] = 0; return 1; }
    if (k == 1) { s[0] |= 1; s[1] = 10; return 1; }
    if (k == 3) { s[0] = 0; s[1] = 0; return 0; }
    if (s[0] & 1) {
        sub_000DFD40(&k, &l);
        if (k != 0) for (;;) ;
        if (l != 0xB) for (;;) ;
        slot = 0;
    } else {
        slot = k;
    }
    switch (s[1]) {
    case 0x14:
        s[0] = 0; s[1] = 0;
        return 0;
    case 0xB:
        if (sub_000A4370(slot)) {
            sub_000A4340(slot, 2);
            s[1] = 0x14;
            return 1;
        }
        return 1;
    case 0xA:
        sub_000A4340(slot, 1);
        sub_00019000(m1_snd3E1270, 3);
        sub_0001AB00(m1_snd3E1270, 3, 2, 0, 0);
        s[1]++;
        return 1;
    }
    return 1;
}

typedef struct M3Mv10 { uint8_t unk00[0x34]; uint8_t *base34; uint8_t unk38[0x1C]; float yaw54; uint8_t unk58[8]; float pos60[3]; float w6C; uint8_t unk70[0x10]; float push80[4]; uint8_t unk90[0x98]; uint8_t b128; } M3Mv10;
typedef struct M3Vel10 { uint8_t unk00[0x78]; float v78[3]; } M3Vel10;
extern float m1_frameTime42C858;
void rbj_MatIdentity(float *m);
void rbj_MatRotY(float *d, const float *s, float a);
void rbj_VecTransform(float *d, const float *m, const float *v);
void r4e_VecAdd4(float *d, const float *a, const float *b);

/* 0x113B20: move a jumping object: add its local offset rotated by its yaw, apply gravity (0.06 per frame unit) and 10 percent horizontal drag to the velocity and add it (vertical speed cleared when grounded flags 0x18 are set), then add and clear the one-frame push. */
void m3_JumpMove113B20(M3Mv10 *a, M3Vel10 *v) {
    float m[16], t[4];
    rbj_MatIdentity(m);
    rbj_MatRotY(m, m, a->yaw54);
    rbj_VecTransform(t, m, (float *)(a->base34 + 0x70));
    r4e_VecAdd4(a->pos60, a->pos60, t);
    v->v78[1] = m1_frameTime42C858 * 0.06f + v->v78[1];
    v->v78[0] = (1.0f - m1_frameTime42C858 * 0.1f) * v->v78[0];
    v->v78[2] = (1.0f - m1_frameTime42C858 * 0.1f) * v->v78[2];
    r4e_VecAdd4(a->pos60, a->pos60, v->v78);
    if (a->b128 & 0x18) v->v78[1] = 0.0f;
    r4e_VecAdd4(a->pos60, a->pos60, a->push80);
    a->push80[0] = 0.0f; a->push80[1] = 0.0f; a->push80[2] = 0.0f; a->push80[3] = 1.0f;
    a->w6C = 1.0f;
}

typedef struct M3Cam10 { uint8_t unk00[0xFC]; float yawFC; uint8_t unk100[0x58]; int32_t st158; float t15C; float yaw160; } M3Cam10;
extern uint8_t m1_stickX42CA5E;
float sub_000CCA40(M3Cam10 *c, float yaw);

/* 0xCCB30: free-look camera yaw: state 1 stores the yaw and starts; state 2 turns the yaw while the stick is off centre (direction from 0xCCA40, wrapped to -pi..pi) and after 60 idle frame units adopts it as the new rest yaw. */
void m3_CamYawCCB30(M3Cam10 *c) {
    float t;
    switch (c->st158) {
    case 2:
        if (m1_stickX42CA5E != 0x7F) {
            if (sub_000CCA40(c, c->yaw160) >= 0.0f) {
                t = c->yawFC - m1_frameTime42C858 * 0.012566372f;
                c->yawFC = t;
                if (-3.1415927f > t) c->yawFC = t + 6.2831855f;
            } else {
                t = m1_frameTime42C858 * 0.012566372f + c->yawFC;
                c->yawFC = t;
                if (t > 3.1415927f) c->yawFC = t - 6.2831855f;
            }
            t = 0.0f;
        } else {
            t = c->t15C + m1_frameTime42C858;
        }
        c->t15C = t;
        if (t >= 60.0f) c->yaw160 = c->yawFC;
        return;
    case 1:
        c->yaw160 = c->yawFC;
        c->t15C = 0.0f;
        c->st158 = 2;
        return;
    }
}
