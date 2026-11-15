/* Area m3, file 15: emitter scale, AI form effects. Names inferred. */
#include <stdint.h>

typedef struct M3Em15 { uint8_t unk00[0x84]; struct M3Em15 *p84; struct M3Em15 *p88; int32_t kind8C; uint8_t unk90[0x3C]; float colCC[4]; } M3Em15;
typedef struct M3Own15 { uint8_t unk00[0x28]; M3Em15 *em28; } M3Own15;
typedef struct M3Ctx15 { uint8_t unk00[0x40]; int32_t *rgba40; } M3Ctx15;
extern M3Ctx15 *m1_scene42C8E4;
void sub_000EE980(M3Own15 *o, float *s);
void r4f_EmitBSetPos(M3Em15 *e);
void r4f_EmitASetPos(M3Em15 *e);

/* 0xEEA60: update the owner, then tint its emitter with the scene colour scaled per channel (alpha copied): kind 12 emitters directly, kind 1 through their parent chain. */
void m3_EmitTintEEA60(M3Own15 *o, float *s) {
    M3Em15 *e, *u;
    sub_000EE980(o, s);
    e = o->em28;
    if (e == 0) return;
    switch (e->kind8C) {
    case 12:
        e->colCC[0] = (float)m1_scene42C8E4->rgba40[0] * s[0];
        e->colCC[1] = (float)m1_scene42C8E4->rgba40[1] * s[1];
        e->colCC[2] = (float)m1_scene42C8E4->rgba40[2] * s[2];
        e->colCC[3] = (float)m1_scene42C8E4->rgba40[3];
        r4f_EmitBSetPos(e);
        return;
    case 1:
        u = e->p88->p84->p84;
        u->colCC[0] = (float)m1_scene42C8E4->rgba40[0] * s[0];
        u->colCC[1] = (float)m1_scene42C8E4->rgba40[1] * s[1];
        u->colCC[2] = (float)m1_scene42C8E4->rgba40[2] * s[2];
        u->colCC[3] = (float)m1_scene42C8E4->rgba40[3];
        r4f_EmitASetPos(u);
        return;
    }
}

typedef struct M3St15 { uint8_t unk00[0x20]; void *snd20; uint8_t unk24[0x10]; void *fx34; void *fx38; void *fx3C; void *fx40; } M3St15;
typedef struct M3En15 { uint8_t unk00[0x278]; M3St15 *st278; } M3En15;
typedef struct M3Ob15 { uint8_t unk00[0x14C]; int32_t list14C; } M3Ob15;
void r1b_RecDetachNodes(void *n);
void r1i_UnitsAttach(void *ctx, void *o, int a, int b, int c);
void r1d_NodeFree(void *n);
void *aab_Attach36750(void *o, int mode);
void sub_00189DE0(void *s, int mode);

/* 0x119FF0: switch the AI's form: re-attach the body (list 7 in the alternate form, else its own list) and replace its effects (alternate: modes 7, 8 and 9; normal: mode 4 only, the other two freed), free the fourth effect and pass the form to its sound. */
void m3_AiFormFx119FF0(M3Ob15 *o, M3En15 *e, int alt) {
    M3St15 *st = e->st278;
    r1b_RecDetachNodes(o);
    if (alt) {
        r1i_UnitsAttach(m1_scene42C8E4, o, 7, 5, 0x11);
        if (st->fx34) { r1d_NodeFree(st->fx34); st->fx34 = 0; }
        st->fx34 = aab_Attach36750(o, 7);
        if (st->fx38) { r1d_NodeFree(st->fx38); st->fx38 = 0; }
        st->fx38 = aab_Attach36750(o, 8);
        if (st->fx3C) { r1d_NodeFree(st->fx3C); st->fx3C = 0; }
        st->fx3C = aab_Attach36750(o, 9);
    } else {
        r1i_UnitsAttach(m1_scene42C8E4, o, o->list14C, 5, 0x11);
        if (st->fx34) { r1d_NodeFree(st->fx34); st->fx34 = 0; }
        st->fx34 = aab_Attach36750(o, 4);
        if (st->fx38) { r1d_NodeFree(st->fx38); st->fx38 = 0; }
        if (st->fx3C) { r1d_NodeFree(st->fx3C); st->fx3C = 0; }
    }
    if (st->fx40) { r1d_NodeFree(st->fx40); st->fx40 = 0; }
    if (st->snd20) sub_00189DE0(st->snd20, alt);
}

typedef struct M3Body15 { uint8_t unk00[0x20]; float *mtx20; uint8_t unk24[0x2C]; float rot50[3]; float w5C; float pos60[3]; float w6C; } M3Body15;
typedef struct M3Act15 { uint32_t f0; uint8_t unk04[0xC]; float scale10; uint8_t unk14[0x5C]; float pos70[3]; float w7C; float rot80[3]; float w8C; uint8_t unk90[4]; float f94; uint8_t unk98[0x88]; M3Body15 *body120; } M3Act15;
void a3c_VecCopy(float *dst, const float *src);
void rbj_MatIdentity(float *m);
void rbj_MatRotX(float *d, const float *s, float a);
void rbj_MatRotY(float *d, const float *s, float a);
void rbj_MatRotZ(float *d, const float *s, float a);
void rbi_VecScale(float *d, const float *s, float k);
void rbj_MatCopy(float *d, const float *s);
void m1_RoomFloor0A23E0(M3Act15 *r);
void r6e_ActorSnap(M3Act15 *r);
void r6e_ActorDragLinks(M3Act15 *r);

/* 0xA3EE0: place an actor's body like 0xA3DB0 (position, rotation, Z/Y/X rotation and scale matrix), then update its floor, snap it, clear +0x94 and drag its links. */
void m3_ActorPlaceA3EE0(M3Act15 *r) {
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
    r6e_ActorSnap(r);
    r->f94 = 0.0f;
    r6e_ActorDragLinks(r);
}

void r4i_SetScale(M3Own15 *o, float s);

/* 0xEE850: like 0xEEA60 with one scale for all colour channels: update the owner's scale, then tint its emitter (kind 12 directly, kind 1 through its parent chain), alpha copied. */
void m3_EmitTint1EE850(M3Own15 *o, float s) {
    M3Em15 *e, *u;
    r4i_SetScale(o, s);
    e = o->em28;
    if (e == 0) return;
    switch (e->kind8C) {
    case 12:
        e->colCC[0] = (float)m1_scene42C8E4->rgba40[0] * s;
        e->colCC[1] = (float)m1_scene42C8E4->rgba40[1] * s;
        e->colCC[2] = (float)m1_scene42C8E4->rgba40[2] * s;
        e->colCC[3] = (float)m1_scene42C8E4->rgba40[3];
        r4f_EmitBSetPos(e);
        return;
    case 1:
        u = e->p88->p84->p84;
        u->colCC[0] = (float)m1_scene42C8E4->rgba40[0] * s;
        u->colCC[1] = (float)m1_scene42C8E4->rgba40[1] * s;
        u->colCC[2] = (float)m1_scene42C8E4->rgba40[2] * s;
        u->colCC[3] = (float)m1_scene42C8E4->rgba40[3];
        r4f_EmitASetPos(u);
        return;
    }
}

typedef struct M3MAnim15 { uint8_t unk00[8]; uint8_t b8; uint8_t unk09[3]; int32_t motC; int32_t parts10; uint8_t unk14[4]; int32_t blend18; } M3MAnim15;
typedef struct M3Mot15 { uint8_t unk00[8]; int32_t cur8; uint8_t unk0C[8]; void *player14; } M3Mot15;
typedef struct M3Mdl15 { uint8_t unk00[0x30]; M3Mot15 *mot30; } M3Mdl15;
typedef struct M3Ani15 { uint8_t unk00[0x48]; int32_t anim48; uint8_t unk4C[0xD4]; M3Mdl15 *mdl120; } M3Ani15;
M3MAnim15 *sub_00083120(M3Mot15 *m, int anim);
int  sub_00082FC0(M3MAnim15 *a, int anim);
void r4e_MotionStart(void *p, int mot, int flags, int frames);
void r4d_PartsClearMask(void *p, int m);
void r4d_PartsSetMask(void *p, int m);
void sub_001AEDD0(void *p, int parts);
void sub_00082F90(M3Mot15 *m, M3MAnim15 *a);

/* 0xA4050: play animation anim on an object's model (negative keeps the current one): start its motion over ms milliseconds (converted to 60 fps frames) or its own length, with blend flag 4/8/16/32 from slot (4..7) or the animation, set the part masks and remember the animation. */
void m3_PlayAnimA4050(M3Ani15 *o, int anim, int ms, int slot) {
    int t[4]; M3Mot15 *m; M3MAnim15 *a; int f;
    t[0] = 4; t[1] = 8; t[2] = 0x10; t[3] = 0x20;
    if (o->mdl120 == 0) { o->anim48 = anim; return; }
    m = o->mdl120->mot30;
    if (anim == m->cur8) { o->anim48 = anim; return; }
    if (anim < 0) anim = m->cur8;
    m->cur8 = anim;
    a = sub_00083120(m, anim);
    if (a && a->motC) {
        if (ms) { volatile int k = 60; f = ms * k / 1000; }
        else f = sub_00082FC0(a, m->cur8);
        { volatile int vi = slot ? slot - 4 : a->blend18; r4e_MotionStart(m->player14, a->motC, t[vi] | 2, f); }
        r4d_PartsClearMask(m->player14, 2);
        if (!(a->b8 & 1)) r4d_PartsSetMask(m->player14, 4);
        else r4d_PartsClearMask(m->player14, 4);
        sub_001AEDD0(m->player14, a->parts10);
        sub_00082F90(m, a);
    }
    o->anim48 = anim;
}

typedef struct M3LtNode15 { uint8_t unk00[0xC4]; uint8_t *bonesC4; } M3LtNode15;
typedef struct M3LtObj15 { uint8_t unk00[0x20]; M3LtNode15 *node20; } M3LtObj15;
typedef struct M3LtPair15 { M3LtObj15 *a; M3LtObj15 *b; int32_t c; } M3LtPair15;
typedef struct M3LtFade15 { float t0; float dur; float from[4]; float to[4]; uint8_t unk28[0]; } M3LtFade15;
typedef struct M3LtFadeS15 { float t0; float dur; float from[4]; float to[4]; } M3LtFadeS15;
typedef struct M3Arena15 { uint8_t unk00[0x534]; M3LtPair15 pair534[8]; uint8_t unk594[0]; } M3Arena15;
typedef struct M3ArenaB15 { uint8_t unk00[0x594]; M3LtFadeS15 fade594[8]; } M3ArenaB15;
extern float b10_frameDelta;
void sub_001ADC60(float *d, const float *a, const float *b, float t);

/* 0xE15C0: run the eight arena light fades: while a fade is active and both lights exist, blend each light's colour towards its target by the remaining fraction; when the time runs out snap both to their targets and end the fade (-1). */
void m3_ArenaFadeE15C0(M3Arena15 *o) {
    int i; M3LtObj15 **pb = &o->pair534[0].b; float *pt = ((M3ArenaB15 *)o)->fade594[0].to;
    for (i = 8; i != 0; i--, pb += 3, pt += 10) {
        float d = pt[-5], nd = d - b10_frameDelta, x, k;
        M3LtObj15 *a = pb[-1], *b = pb[0];
        if (a == 0 || b == 0) continue;
        if (!(pt[-6] >= 0.0f)) continue;
        if (d > 0.0f && nd > 0.0f) {
            k = nd / d;
            sub_001ADC60((float *)(a->node20->bonesC4 + 0x1E4), (float *)(a->node20->bonesC4 + 0x1E4), pt - 4, k);
            sub_001ADC60((float *)(b->node20->bonesC4 + 0x1E4), (float *)(b->node20->bonesC4 + 0x1E4), pt, k);
            x = pt[-5] - b10_frameDelta;
        } else {
            a3c_VecCopy((float *)(a->node20->bonesC4 + 0x1E4), pt - 4);
            a3c_VecCopy((float *)(b->node20->bonesC4 + 0x1E4), pt);
            x = -1.0f;
            pt[-6] = -1.0f;
        }
        pt[-5] = x;
    }
}

typedef struct M3HlpT15 { uint8_t unk00[0x54]; float yaw54; uint8_t unk58[8]; float pos60[4]; } M3HlpT15;
typedef struct M3Hlp15 { uint8_t unk00[0x8C]; M3HlpT15 *tgt8C; uint8_t unk90[0x18]; float radA8; uint8_t unkAC[0x14]; int32_t dirC0; float angC4; float spdC8; } M3Hlp15;
typedef struct M3Circ15 { uint8_t unk00[0x60]; float pos60[3]; } M3Circ15;
typedef struct M3PlC15 { uint8_t unk00[0x60]; float pos60[4]; } M3PlC15;
extern M3Hlp15 *m1_helper3F611C;
extern M3PlC15 *g_playerObj;
void m1_AngWrap0F5ED0(float *a);
float sub_001A3EE0(float a);
float sub_001A3ED0(float a);
float rbj_Distance(const float *a, const float *b);
float sub_000FB4A0(const float *p);
void sub_000F3D10(void *t, void *h, int st);

/* 0xFCCA0: circle the helper's target around o: advance the angle by the speed in the current direction (wrapped), move o along the circle of the helper radius, face the helper's target along the tangent, and switch the helper to state 2 when its target's measure is within 90 or o is farther than 40 from the player. */
void m3_HelperCircleFCCA0(M3Circ15 *o) {
    M3Hlp15 *h = m1_helper3F611C; float *a, d, t;
    if (h->dirC0 == 0) h->angC4 = h->spdC8 + h->angC4;
    else if (h->dirC0 == 1) h->angC4 = h->angC4 - h->spdC8;
    a = &h->angC4;
    m1_AngWrap0F5ED0(a);
    o->pos60[0] = sub_001A3EE0(*a) * h->radA8 + o->pos60[0];
    o->pos60[2] = sub_001A3ED0(*a) * h->radA8 + o->pos60[2];
    t = 0.0f - m1_helper3F611C->angC4 - 1.5707964f;
    m1_helper3F611C->tgt8C->yaw54 = t;
    if (-3.1415927f > t) m1_helper3F611C->tgt8C->yaw54 = t + 6.2831855f;
    d = rbj_Distance(o->pos60, g_playerObj->pos60);
    if (!(sub_000FB4A0(m1_helper3F611C->tgt8C->pos60) > 90.0f) || d > 40.0f)
        sub_000F3D10(m1_helper3F611C->tgt8C, m1_helper3F611C, 2);
}
