/* Area m3, batch 40. Names inferred. */
#include <stdint.h>

typedef struct M3FxR40 { uint32_t f0; uint8_t unk04[8]; float tC; uint8_t unk10[0xD0]; } M3FxR40;
typedef struct M3FxP40 { uint8_t unk000[0x150]; uint32_t f150; uint8_t unk154[0x64]; int f1B8; } M3FxP40;
extern M3FxR40 g_ac0_41E2A0[32];
extern float a50_frameUnits;
void sub_000C5340(void);
void sub_000C4420(void *p);
void sub_000C66B0(void *p, M3FxR40 *r);
void sub_000C46B0(void *p, M3FxR40 *r);
void sub_000C6350(void *p, M3FxR40 *r);
void sub_000C4740(void *p, M3FxR40 *r);
void sub_000C4AB0(M3FxR40 *r);
void sub_000C4B70(M3FxR40 *r);
void sub_000C5460(void *p);

/* 0xC6850: per-frame effect pool tick (skipped while paused, flag 0x80000): run each live record's update hooks (or its release hook when its sign bit is set), draw it, count its life down and clear it at zero; then respawn the stage effects when none are active and flag 0x400 is set. */
void m3_FxTickC6850(M3FxP40 *p) {
    M3FxR40 *r;
    if (p->f150 & 0x80000) return;
    sub_000C5340();
    sub_000C4420(p);
    for (r = g_ac0_41E2A0; (int32_t)r < (int32_t)&g_ac0_41E2A0[32]; r++) {
        if (!(r->f0 & 1)) continue;
        if (!(p->f150 & 0x80000)) {
            if ((int32_t)r->f0 >= 0) {
                sub_000C66B0(p, r);
                sub_000C46B0(p, r);
                sub_000C6350(p, r);
            } else {
                sub_000C4740(p, r);
            }
        }
        sub_000C4AB0(r);
        r->tC -= a50_frameUnits;
        if (0.0f > r->tC) sub_000C4B70(r);
    }
    if (!p->f1B8 && (p->f150 & 0x400)) sub_000C5460(p);
}

typedef struct M3FlS40 { int state; int count4; int t8; int dxC; int dy10; uint8_t unk14[0x78]; } M3FlS40;
typedef struct M3FlP40 { uint8_t unk000[0x18C]; int f18C; uint8_t unk190[0x70]; M3FlS40 sl200[1]; } M3FlP40;
extern uint8_t g_ac0_stickX, g_ac0_stickY;
extern uint32_t aa0_flags420010;
extern int m1_gameMode41FF94, m1_btnB41CD04, g_ac0_42CA38;
int  sub_0019BE60(int k);

/* 0xCD070: count stick flicks for slot k: in stick mode wait for a deflection, then for 10 frames count a reversal against it; in button mode count presses of the bound button when not blocked by flags, game modes 2/4/5 or input lock 0x4101. */
void m3_FlickCountCD070(M3FlP40 *p, int k) {
    M3FlS40 *s = &p->sl200[k];
    int x, y;
    switch (s->state) {
    case 1:
        if (s->t8 < 10) {
            x = g_ac0_stickX - 0x7F;
            y = g_ac0_stickY - 0x7F;
            s->t8++;
            if (x == 0 && y == 0) return;
            if (s->dxC * x < 0 || s->dy10 * y < 0) {
                s->dxC = 0;
                s->dy10 = 0;
                s->state = 0;
                s->count4++;
            }
            return;
        }
        s->dxC = 0;
        s->dy10 = 0;
        s->state = 0;
        return;
    case 0:
        if (!p->f18C) {
            x = g_ac0_stickX - 0x7F;
            y = g_ac0_stickY - 0x7F;
            if (x == 0 && y == 0) return;
            s->t8 = 0;
            s->dxC = x;
            s->dy10 = y;
            s->state = 1;
            return;
        }
        if (aa0_flags420010 & 0x82006) return;
        if (m1_gameMode41FF94 == 2 || m1_gameMode41FF94 == 4 || m1_gameMode41FF94 == 5) return;
        if (sub_0019BE60(0x4101)) return;
        if (m1_btnB41CD04 & g_ac0_42CA38) s->count4++;
        return;
    }
}

typedef struct M3IdK40 { uint8_t unk00[8]; int f8; } M3IdK40;
typedef struct M3IdO40 { uint8_t unk00[0x30]; M3IdK40 *p30; } M3IdO40;
typedef struct M3IdA40 { uint8_t unk00[0x60]; float pos60[4]; uint8_t unk70[0x40]; float rB0; } M3IdA40;
typedef struct M3IdB40 { uint8_t unk00[0x8C]; M3IdA40 *p8C; uint8_t unk90[0x118]; int16_t h1A8; uint8_t unk1AA[2]; float t1AC; } M3IdB40;
typedef struct M3IdX40 { uint8_t unk00[0x68]; float f68; } M3IdX40;
extern M3IdB40 *b10_scr;
extern uint8_t *g_playerObj;
extern float a50_frameSeconds;
int  sub_001050B0(float k);
void sub_00104E90(void);
int  afc_NodeActive(void *n);
float sub_001B2770(const float *a, const float *b);
void sub_00101240(int k);

/* 0x1055A0: screen actor idle step: turn (pi/100 per unit) and arm a wait once facing; when armed, idle actors pick a new action after 1.25 s and others when their node fires; once the target rises above 5.5, switch to mode 0xD within 80 units of the player, else 0xB. */
void m3_ScrIdle1055A0(M3IdO40 *o, M3IdX40 *x) {
    float d;
    M3IdB40 *b = b10_scr;
    M3IdA40 *m;
    int r = sub_001050B0(a50_frameUnits * 0.031415928f);
    if (!b->h1A8) {
        if (r) {
            b->t1AC = 0.0f;
            b->h1A8 = 1;
        }
    } else if (o->p30->f8 == 0) {
        if (b->t1AC > 1.25f) goto pick;
        b->t1AC += a50_frameSeconds;
    } else if (afc_NodeActive(o)) {
pick:
        sub_00104E90();
    }
    if (x->f68 > 5.5f) {
        m = b10_scr->p8C;
        d = sub_001B2770(m->pos60, (float *)(g_playerObj + 0x60)) - m->rB0;
        if (0.0f > d) d = 0.0f;
        if (80.0f > d) {
            sub_00101240(0xD);
            return;
        }
        sub_00101240(0xB);
    }
}
