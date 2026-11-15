/* Area m3, file 8: AI target choice. Names inferred. */
#include <stdint.h>

typedef struct M3Tg8 { uint8_t unk00[0xC]; uint8_t bC; uint8_t unkD[0x53]; float pos60[4]; } M3Tg8;
typedef struct M3St8 { uint8_t unk00[4]; uint32_t f4; } M3St8;
typedef struct M3Ai8 { uint8_t unk00[0xF8]; int32_t iF8; uint8_t unkFC[8]; M3Tg8 *tgt104; uint8_t unk108[0x170]; M3St8 *st278; } M3Ai8;
extern M3Tg8 *g_playerObj;
M3Tg8 *sub_000C7130(M3Tg8 *self);
float rbj_Distance(const float *a, const float *b);

/* 0x114930: choose the AI's target: when locked (flag 4) keep a live target or fall back to the player; otherwise pick the decoy from 0xC7130 when it is within 40 units and no farther than the player, else the player. Flag 0x1000 marks a target change. */
void m3_AiPickTarget114930(M3Tg8 *self, M3Ai8 *o) {
    M3St8 *st = o->st278; M3Tg8 *t, *pl, *dc; float dp, dd;
    st->f4 &= ~0x1000u;
    if (st->f4 & 4) {
        if (o->iF8 != 1) return;
        if (o->tgt104 && (o->tgt104->bC & 1)) return;
        t = g_playerObj;
    } else {
        pl = g_playerObj;
        dc = sub_000C7130(self);
        if (pl) dp = rbj_Distance(self->pos60, pl->pos60);
        else dp = 3.4028235e38f;
        t = pl;
        if (dc) {
            dd = rbj_Distance(self->pos60, dc->pos60);
            if (dd <= 40.0f && dd <= dp) t = dc;
        }
        if (o->tgt104 == t && o->iF8 == 1) return;
    }
    o->tgt104 = t;
    o->iF8 = 1;
    st->f4 |= 0x1000;
}

typedef struct M3Voice8 { uint8_t unk00[0xC]; uint16_t idle[2]; uint16_t hurt[4]; uint16_t win[4]; } M3Voice8;
typedef struct M3Talker8 { int32_t i0; uint8_t unk04[0x2F0]; int32_t mode2F4; uint8_t unk2F8[0x1C]; int32_t ch314; uint8_t unk318[0x14]; int32_t busy32C; } M3Talker8;
void *sub_000E23F0(int a, int b);
void *sub_0001D960(void *o, int kind);
int  sub_000F40B0(void);
int  aab_Rand(void);
void sub_000E0A80(M3Talker8 *o, int a, int b, int c, int id);

/* 0xEBF00: play a random voice line from the record: the idle pair in mode 0, else the hurt set or (when 0xF40B0 says so) the win set; empty entries are skipped by counting the non-zero leading entries. */
void m3_VoicePickEBF00(M3Talker8 *o, M3Voice8 *v) {
    int n = 0, id;
    if (o == 0 || v == 0) return;
    sub_0001D960(sub_000E23F0(3, 6), 5);
    o->busy32C = 1;
    if (o->mode2F4 == 0) {
        if (v->idle[0]) n = 1;
        if (v->idle[1]) n++;
        if (n == 0) return;
        id = v->idle[aab_Rand() % n];
    } else if (sub_000F40B0() == 0) {
        if (v->hurt[0]) n = 1;
        if (v->hurt[1]) n++;
        if (v->hurt[2]) n++;
        if (v->hurt[3]) n++;
        if (n == 0) return;
        id = v->hurt[aab_Rand() % n];
    } else {
        if (v->win[0]) n = 1;
        if (v->win[1]) n++;
        if (v->win[2]) n++;
        if (v->win[3]) n++;
        if (n == 0) return;
        id = v->win[aab_Rand() % n];
    }
    if (id) sub_000E0A80(o, 4, o->i0, o->ch314, id);
}

typedef struct M3Turn8 { uint8_t unk00[0x80]; float rot80[4]; uint8_t unk90[0x90]; uint8_t *body120; } M3Turn8;
float sub_00113290(uint8_t *body, void *goal);
float sub_001A3F30(float x);
void a3c_VecCopy(float *dst, const float *src);

/* 0xA3170: turn towards a goal: take the signed angle difference, step by at most |step| (the whole difference when it is smaller), wrap the yaw into -pi..pi and copy the rotation to the body. */
void m3_TurnToA3170(M3Turn8 *o, void *goal, float step) {
    float d = sub_00113290(o->body120, goal), ad, a;
    ad = sub_001A3F30(d);
    if (sub_001A3F30(step) >= ad) a = d + o->rot80[1];
    else if (d > 0.0f) a = step + o->rot80[1];
    else a = o->rot80[1] - step;
    o->rot80[1] = a;
    if (a > 3.1415927f) {
        float x = o->rot80[1];
        do x -= 6.2831855f; while (x > 3.1415927f);
        o->rot80[1] = x;
    }
    if (-3.1415927f > o->rot80[1]) {
        float x = o->rot80[1];
        do x += 6.2831855f; while (-3.1415927f > x);
        o->rot80[1] = x;
    }
    a3c_VecCopy((float *)(o->body120 + 0x50), o->rot80);
}
