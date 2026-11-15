/* Area m3, file 19: hero chase setup. Names inferred. */
#include <stdint.h>

typedef struct M3Hero19 { uint8_t unk00[0x60]; float pos60[4]; uint8_t unk70[0x40]; float radB0; } M3Hero19;
typedef struct M3Scr19 { uint8_t unk00[0x8C]; M3Hero19 *hero8C; uint8_t unk90[0x11C]; float t1AC; uint8_t unk1B0[0x74]; float goal224[4]; int32_t mode234; int32_t fx238; void *att23C; } M3Scr19;
typedef struct M3Ob19 { uint8_t unk00[0x60]; float pos60[4]; } M3Ob19;
extern M3Scr19 *m1_scr3F6130;
extern M3Ob19 *g_playerObj;
extern float b10_frameDelta;
int  aab_Effect494D0(int id, void *pos, int a);
void *aab_Attach36750(void *o, int mode);
float rfl_TurnDelta(void *o, const float *target);
void sub_00101280(int st);
void sub_000F5EA0(float *d, const float *a, const float *b);
float rbj_Distance(const float *a, const float *b);
void rbj_VecScale(float *d, const float *s, float k);
void r4e_VecAdd4(float *d, const float *a, const float *b);
void r4c_VecSub(float *dst, const float *a, const float *b);
void a3c_VecCopy(float *dst, const float *src);

/* 0x1046D0: start the hero's chase of o: play effect 0x1B8 and attach the hero's mode-0 effect once, set the chase time, pick the turn state (0x37 / 0x38 / 0x36) from the turn delta, then aim 50 units past o when the hero is closer than 70 to the player, else 20 units short of the player along the player-to-o direction (or straight at the player in mode 1). */
void m3_ChaseStart1046D0(M3Ob19 *o) {
    M3Scr19 *s = m1_scr3F6130; float d, g, t[4]; M3Hero19 *h;
    if (s->fx238 == -1) s->fx238 = aab_Effect494D0(0x1B8, o->pos60, 1);
    if (s->att23C == 0) s->att23C = aab_Attach36750(s->hero8C, 0);
    s->t1AC = b10_frameDelta + 0.3f;
    d = rfl_TurnDelta(o, g_playerObj->pos60);
    if (d > 0.0f) sub_00101280(0x37);
    else if (0.0f > d) sub_00101280(0x38);
    else sub_00101280(0x36);
    if (s->mode234 == 0) {
        sub_000F5EA0(t, g_playerObj->pos60, o->pos60);
        h = m1_scr3F6130->hero8C;
        g = rbj_Distance(h->pos60, g_playerObj->pos60) - h->radB0;
        if (0.0f > g) g = 0.0f;
        if (70.0f > g) {
            rbj_VecScale(t, t, 50.0f);
            r4e_VecAdd4(s->goal224, o->pos60, t);
            return;
        }
        rbj_VecScale(t, t, 20.0f);
        r4c_VecSub(s->goal224, g_playerObj->pos60, t);
        return;
    }
    a3c_VecCopy(s->goal224, g_playerObj->pos60);
}

typedef struct M3Foe19 { uint8_t unk00[4]; int32_t kind4; int32_t type8; uint8_t unk0C[0x54]; float pos60[4]; } M3Foe19;
typedef struct M3Drop19 { uint32_t f0; uint8_t unk04[0xD8]; } M3Drop19;
extern float m3_dropMeter420C5C;
extern int32_t m3_stat420C24;
extern int32_t m3_stat420C28;
extern int m3_forceKind420090;
extern M3Drop19 aab_recDC[];
int  sub_000EDF10(M3Foe19 *e);
int  b16_ParamI10(int kind, int type, int b);
int  sub_000EDF60(M3Foe19 *e, int a);
int  sub_00171E70(int kind, int type, int big, int b);
int  aab_Rand(void);
int  sub_000A8990(int kind, int a, int b, float *pos, float *dir, float *up);
float sub_00171CF0(void);

/* 0xA8D10: drop a pickup when a foe dies: lower the drop meter by the foe's value; when it runs out pick a pickup kind (a big one less often once the stat ratio is above 1/3, never above 0.8), spawn it 12 units below the foe (kind 0x17 becomes 3 unless forced), mark small drops at a low ratio, then refill the meter (half when nothing spawned). */
void m3_FoeDropA8D10(M3Foe19 *e) {
    int b = 0, kind; volatile int big = 0, r = 0; float p[4], q[4], ratio;
    if (e->kind4 != 0xC && e->kind4 != 3) b = sub_000EDF10(e);
    m3_dropMeter420C5C = m3_dropMeter420C5C - (float)b16_ParamI10(e->kind4, e->type8, b);
    if (!(0.0f >= m3_dropMeter420C5C)) return;
    p[0] = 0.0f; p[1] = 0.0f; p[2] = 0.0f;
    q[0] = 0.0f; q[1] = 0.0f; q[2] = 0.0f;
    p[3] = 1.0f; q[3] = 1.0f;
    ratio = (float)m3_stat420C28 / (float)m3_stat420C24;
    if (e->kind4 != 0xC) {
        if (e->kind4 == 3) big = 1;
        else big = sub_000EDF60(e, 1);
    }
    if (0.8f >= ratio) {
        if (!(ratio > 0.333333f)) big = 0;
        else if (!(aab_Rand() & 1)) { volatile int z; big = 0; z = 0; }
    }
    kind = sub_00171E70(e->kind4, e->type8, big, b);
    a3c_VecCopy(p, e->pos60);
    p[1] = p[1] - 12.0f;
    if (kind > 0) {
        if (kind == 0x17 && m3_forceKind420090 == 0) kind = 3;
        r = sub_000A8990(kind, 2, 0, p, q, q);
        if (big == 0 && 0.333333f >= ratio && r >= 0) aab_recDC[r].f0 |= 0x8000000;
    }
    m3_dropMeter420C5C = sub_00171CF0();
    if (r < 0) m3_dropMeter420C5C = m3_dropMeter420C5C * 0.5f;
}

typedef struct M3MSlot19 { uint8_t unk00[0x48]; int32_t i48; } M3MSlot19;
M3MSlot19 *m1_SlotGet0A4290(int i);
int  r2b_TestBit(int bit);
void sub_000A2D40(int slot, int v);
void sub_000A2CC0(int slot, int v);
void sub_000A2D10(int slot, int v);
void sub_000A2CA0(int slot, int v);
void sub_000A42F0(int i, int v);

/* 0xB16F0: menu step for a 3-int setting with two buttons (slots 0 and 1): 0 clears, 1 sets bit 0 and 10, 3 forces 20; 10 shows both buttons in the look chosen by story bit 0x2C2 and opens them (2 or 0), 11 re-shows them and picks the follow-up states by slot 0's state, 20 clears and returns 0. */
int m3_MenuStepB16F0(int k, int *s) {
    M3MSlot19 *o;
    if (k == 0) { s[0] = 0; s[1] = 0; s[2] = 0; return 1; }
    if (k == 1) { s[0] |= 1; s[2] = 0; s[1] = 10; return 1; }
    if (k == 3) { s[0] = 0; s[1] = 0x14; }
    s[2]++;
    switch (s[1]) {
    case 0x14:
        s[0] = 0; s[1] = 0;
        return 0;
    case 0xB:
        o = m1_SlotGet0A4290(0);
        if (r2b_TestBit(0x2C2)) {
            sub_000A2D10(0, 0x20); sub_000A2D40(1, 0x20);
            sub_000A2CA0(0, 0x10000000); sub_000A2CC0(1, 0x10000000);
            if (o->i48 == 0 || o->i48 == 3 || o->i48 == 5) { sub_000A42F0(0, 1); sub_000A42F0(1, 4); }
            return 1;
        }
        sub_000A2D40(0, 0x20); sub_000A2D40(1, 0x20);
        sub_000A2CC0(0, 0x10000000); sub_000A2CC0(1, 0x10000000);
        if (o->i48 == 1 || o->i48 == 2 || o->i48 == 4) { sub_000A42F0(0, 3); sub_000A42F0(1, 5); }
        return 1;
    case 0xA:
        {
            int v; volatile int z;
            if (r2b_TestBit(0x2C2)) {
                sub_000A2D10(0, 0x20); sub_000A2D40(1, 0x20);
                sub_000A2CA0(0, 0x10000000); sub_000A2CC0(1, 0x10000000);
                sub_000A42F0(0, 2); z = 0;
                v = 2;
            } else {
                sub_000A2D40(0, 0x20); sub_000A2D40(1, 0x20);
                sub_000A2CC0(0, 0x10000000); sub_000A2CC0(1, 0x10000000);
                sub_000A42F0(0, 0);
                v = 0;
            }
            sub_000A42F0(1, v);
        }
        s[1]++;
        return 1;
    }
    return 1;
}

typedef struct M3Gate19 { uint8_t unk00[0x70]; float pos70[4]; uint8_t unk80[0xA0]; uint8_t *body120; uint8_t unk124[0x30]; int32_t snd154; } M3Gate19;
extern int m1_level413178;
extern int32_t m3_gateFx2E50B0[];

void m1_SndStop048250(int h);
void aab_Hide1B3F0(void *o);
int  sub_00049700(int id, int r, int g, int b, void *pos, int a, float range, int c);
float r4_Distance(const float *a, const float *b);
void m1_FxAdd0C4DF0(int a, int kind, float s, int fx, float r1, int b, float r2, float *pos, float *dir, float *up);

/* 0xB03C0: menu step for the gate prop (slot 0x1D): 0 clears, 1 sets bit 0 and 10, 3 clears and returns 0; at 10 without story bit 0xF2 go to 20, without 0xBA stop its hum and hide it, else start the hum (0x2B5) once and, when the player is near, add the sparkle effect for the difficulty level; 20 clears and returns 0. */
int m3_MenuGateB03C0(int k, int *s) {
    M3Gate19 *o = (M3Gate19 *)m1_SlotGet0A4290(0x1D); float p[4], u[4], d[4];
    p[0] = 0.0f; p[1] = 0.0f; p[2] = 0.0f; p[3] = 1.0f;
    d[0] = 0.0f; d[1] = 0.0f; d[2] = 0.0f; d[3] = 1.0f;
    u[0] = 0.0f; u[1] = 0.0f; u[2] = 0.0f; u[3] = 1.0f;
    if (k == 0) { s[0] = 0; s[1] = 0; return 1; }
    if (k == 1) { s[0] |= 1; s[2] = 0; s[1] = 10; return 1; }
    if (k == 3) { s[0] = 0; s[1] = 0; return 0; }
    if (s[1] != 10) {
        if (s[1] != 0x14) return 1;
        s[0] = 0; s[1] = 0;
        return 0;
    }
    if (!r2b_TestBit(0xF2)) { s[1] = 0x14; return 1; }
    if (!r2b_TestBit(0xBA)) {
        m1_SndStop048250(o->snd154);
        o->snd154 = -1;
        aab_Hide1B3F0(o->body120);
        return 1;
    }
    if (o->snd154 == -1) o->snd154 = sub_00049700(0x2B5, 0x80, 0x80, 0x80, o->body120 + 0x60, 1, 90.0f, 0);
    {
        int fx = m3_gateFx2E50B0[m1_level413178];
        a3c_VecCopy(p, o->pos70);
        if (50.0f >= r4_Distance(g_playerObj->pos60, p))
            m1_FxAdd0C4DF0(0, 3, 1.0f, fx, 6.0f, 0, 6.0f, p, d, u);
    }
    return 1;
}
