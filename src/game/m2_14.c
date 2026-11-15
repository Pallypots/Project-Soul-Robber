/* Area m2, file 14. Names inferred. */
#include <stdint.h>

extern float m2_vecW2C45D8[4];
float rbj_Acos(float c);
float sub_001A3ED0(float a);
void  a3c_VecCopy(float *d, const float *s);

/* 0x3B180: build the rotation matrix about unit axis a for an angle given by its cosine c (s = sin(acos c), t = 1 - c); the translation row is set from the constant vector at 0x2C45D8. */
void m2_AxisRot3B180(float *m, const float *a, float c) {
    float s = sub_001A3ED0(rbj_Acos(c));
    float t = 1.0f - c;
    a3c_VecCopy(m + 12, m2_vecW2C45D8);
    m[3] = 0.0f; m[7] = 0.0f; m[11] = 0.0f;
    m[0] = a[0] * a[0] * t + c;
    m[4] = a[1] * a[0] * t - a[2] * s;
    m[8] = a[2] * a[0] * t + a[1] * s;
    m[1] = a[1] * a[0] * t + a[2] * s;
    m[5] = a[1] * a[1] * t + c;
    m[9] = a[2] * a[1] * t - a[0] * s;
    m[2] = a[2] * a[0] * t - a[1] * s;
    m[6] = a[2] * a[1] * t + a[0] * s;
    m[10] = a[2] * a[2] * t + c;
}

typedef struct M2Spawn14 { uint8_t unk00[4]; int32_t bit4; int8_t a8, b9, cA, nearB; uint8_t unk0C[4]; float pos10[3]; float r1C; uint8_t unk20[0x10]; } M2Spawn14;
typedef struct M2SpList14 { uint8_t unk00[8]; int32_t n8; uint8_t unk0C[4]; M2Spawn14 recs[1]; } M2SpList14;
extern M2SpList14 *m1_residentArg3ED214;
extern M2Spawn14 *r6c_cam3ED218;
extern uint8_t *aab_player;
int   r2b_TestBit(int bit);
int   sub_00086250(int a, int b);
void  rbj_VecSub(float *d, const float *a, const float *b);
float sub_001B27C0(const float *a, const float *b);
void *rbi_Spawn0ED630(int a, int b, float *pos, float *rot, int c);
void  sub_000EDF30(void *o, int k, int v);

/* 0x870B0: spawn every resident entry whose flag is set and whose kind is allowed; near-flagged entries face the player (yaw from 0x1B27C0), others use their stored yaw. The current entry is published at 0x3ED218 during the spawn; a positive bit number also goes to the spawned object. */
void m2_SpawnResidents870B0(void) {
    float rot[4], pos[4], down[4], d[4];
    int32_t *pn = &m1_residentArg3ED214->n8;
    M2Spawn14 *e = m1_residentArg3ED214->recs;
    int i;
    void *o;
    down[0] = 0.0f; down[1] = 0.0f; down[2] = -1.0f; down[3] = 1.0f;
    for (i = 0; i < *pn; i++, e++) {
        if (r2b_TestBit(e->bit4) == 0) continue;
        if (sub_00086250(e->a8, e->b9) == 0) continue;
        pos[0] = e->pos10[0]; pos[1] = e->pos10[1]; pos[2] = e->pos10[2]; pos[3] = 1.0f;
        rot[0] = 0.0f; rot[2] = 0.0f; rot[3] = 0.0f;
        if (e->nearB == 0) {
            rot[1] = e->r1C;
        } else {
            rbj_VecSub(d, (float *)(aab_player + 0x60), pos);
            rot[1] = sub_001B27C0(down, d);
        }
        r6c_cam3ED218 = e;
        o = rbi_Spawn0ED630(e->a8, e->b9, pos, rot, e->cA);
        if (o != 0 && e->bit4 > 0) sub_000EDF30(o, 1, e->bit4);
        r6c_cam3ED218 = 0;
    }
}
