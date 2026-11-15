/* Area m3, file 5: combo counter tick, light colours, attached model matrix. Names inferred. */
#include <stdint.h>

extern int m3_comboCnt3F0B64;
extern int m3_comboMax3F0B68;
extern int m3_comboLockA3F1178;
extern int m3_comboLockB3F0B6C;
extern float m3_tipTimer3F10EC;
extern int m3_tipIdx3F1B40;
extern float m3_tipDelay317CB8;
extern uint8_t g_stats[];
extern uint8_t r2e_stage3F0758[];
void sub_000E8690(int a, int n);
void abc_PlayerD0030(void *s, int id);
void sub_000E5070(void *s);
void sub_00048AF0(int id);

/* 0xE5B70: add n to the combo counter (unless locked), report it, and when it reaches the maximum clamp it and fire the full-combo stat 0x42 and stage event; then when the tip timer has run out play the next of four tips (0x3B4..0x3B7) and restart the timer. */
void m3_ComboTickE5B70(int n) {
    if (n > 0 && m3_comboCnt3F0B64 < m3_comboMax3F0B68) {
        if (m3_comboLockA3F1178 == 0 && m3_comboLockB3F0B6C == 0) {
            m3_comboCnt3F0B64 += n;
            sub_000E8690(2, n);
        }
        if (m3_comboCnt3F0B64 >= m3_comboMax3F0B68) {
            m3_comboCnt3F0B64 = m3_comboMax3F0B68;
            abc_PlayerD0030(g_stats, 0x42);
            sub_000E5070(r2e_stage3F0758);
        }
    }
    if (m3_tipTimer3F10EC <= 0.0f) {
        sub_00048AF0(m3_tipIdx3F1B40 % 4 + 0x3B4);
        m3_tipTimer3F10EC = m3_tipDelay317CB8;
        m3_tipIdx3F1B40++;
    }
}

typedef struct M3Light5 { uint8_t unk00[0xC]; int32_t iC; int32_t i10; uint8_t a[4]; uint8_t b[4]; } M3Light5;
void r2d_StageTrackSet(void *o, int id, float t, float *ca, float *cb);

/* 0xEA930: apply a two-colour light record: both byte colours as floats, the time in milliseconds scaled to seconds, passed with the id to 0xE1570. */
void m3_ApplyLight2EA930(void *o, M3Light5 *l) {
    float cb[4], ca[4];
    if (o == 0 || l == 0) return;
    ca[0] = (float)l->a[0]; ca[1] = (float)l->a[1]; ca[2] = (float)l->a[2]; ca[3] = (float)l->a[3];
    cb[0] = (float)l->b[0]; cb[1] = (float)l->b[1]; cb[2] = (float)l->b[2]; cb[3] = (float)l->b[3];
    r2d_StageTrackSet(o, l->iC, (float)l->i10 * 0.001f, ca, cb);
}

typedef struct M3Body5 { uint8_t unk00[0x20]; float *mtx20; uint8_t unk24[0x3C]; float pos60[3]; float w6C; } M3Body5;
typedef struct M3Att5 { uint8_t unk00[0x18]; float scale18; uint8_t unk1C[0x18]; float pos34[3]; float w40; float rx44, ry48; uint8_t unk4C[0x18]; M3Body5 *body64; } M3Att5;
void a3c_VecCopy(float *dst, const float *src);
void rbj_MatIdentity(float *m);
void rbj_MatRotX(float *d, const float *s, float a);
void rbj_MatRotY(float *d, const float *s, float a);
void rbi_VecScale(float *d, const float *s, float k);
void rbj_MatCopy(float *d, const float *s);

/* 0xC6D50: place the attached body: copy the position, then build its matrix from the X and Y rotations and the uniform scale, translated to that position. */
void m3_AttachPlaceC6D50(M3Att5 *a) {
    float m[16]; float *dst = a->body64->mtx20;
    a3c_VecCopy(a->body64->pos60, a->pos34);
    a->w40 = 1.0f;
    a->body64->w6C = 1.0f;
    rbj_MatIdentity(m);
    rbj_MatRotX(m, m, a->rx44);
    rbj_MatRotY(m, m, a->ry48);
    rbi_VecScale(m, m, a->scale18);
    rbi_VecScale(m + 4, m + 4, a->scale18);
    rbi_VecScale(m + 8, m + 8, a->scale18);
    a3c_VecCopy(m + 12, a->body64->pos60);
    rbj_MatCopy(dst, m);
}

typedef struct M3Spawn5 { uint8_t unk00[0xC]; int8_t slotC, kindD, modeE, typeF; float x10, y14, z18, yaw1C; } M3Spawn5;
typedef struct M3Owner5 { uint8_t unk00[0x330]; void *slots330[1]; } M3Owner5;
void *sub_000EC880(int kind, float *pos, float *rot, int type);
void sub_000E1040(void *o);
void sub_000E1060(void *o, int a, int b, int c);

/* 0xEAEE0: spawn an object from a spawn record (position, yaw as rotation y), start it in its mode and store it in the owner's slot table. */
void m3_SpawnFromRecEAEE0(M3Owner5 *ow, M3Spawn5 *s) {
    float rot[4], pos[4]; void *o;
    if (s == 0 || ow == 0) return;
    pos[3] = 1.0f; rot[3] = 1.0f;
    pos[0] = s->x10; pos[1] = s->y14; pos[2] = s->z18;
    rot[0] = 0.0f; rot[2] = 0.0f; rot[1] = s->yaw1C;
    o = sub_000EC880(s->kindD, pos, rot, s->typeF);
    if (o == 0) return;
    sub_000E1040(o);
    sub_000E1060(o, s->modeE, 0, 0);
    ow->slots330[s->slotC] = o;
}

typedef struct M3Src5 { uint8_t unk00[4]; int32_t i4; float p8[4]; } M3Src5;
typedef struct M3Dst5 { float p[3]; float w; int32_t i10; } M3Dst5;
void rbi_VecNorm(float *d, const float *s);
void rbj_VecTransform(float *d, const float *m, const float *v);
void r4e_VecAdd4(float *d, const float *a, const float *b);

/* 0xEE3B0: transform a point record into a frame: with a matrix, rotate by its normalised axes and add its origin (+0x70); without, copy the point. Sets w = 1 and copies the id. */
void m3_PointToFrameEE3B0(float *m, M3Src5 *s, M3Dst5 *d) {
    float r[16];
    if (s == 0 || d == 0) return;
    if (m) {
        rbi_VecNorm(r, m + 16);
        rbi_VecNorm(r + 4, m + 20);
        rbi_VecNorm(r + 8, m + 24);
        r[12] = 0.0f; r[13] = 0.0f; r[14] = 0.0f; r[15] = 1.0f;
        rbj_VecTransform(d->p, r, s->p8);
        r4e_VecAdd4(d->p, m + 28, d->p);
    } else {
        a3c_VecCopy(d->p, s->p8);
    }
    d->w = 1.0f;
    d->i10 = s->i4;
}
