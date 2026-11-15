/* Area m2, file 9. Names inferred. */
#include <stdint.h>


typedef struct M2Act9 { uint32_t flags0; int32_t id4; uint8_t unk08[0x38]; int32_t state40; uint8_t unk44[0x2C]; float pos70[4]; uint8_t unk80[0xA0]; void *p120; uint8_t unk124[0x13C]; uint8_t sub260[0x70]; float home2D0[4]; uint8_t unk2E0[0xA0]; uint8_t *body380; } M2Act9;
extern uint8_t g_stats[];
extern int r1e_g41316C;
extern int r1e_g413170;
void sub_000A41D0(void *o, int v);
void r6e_ActorShow(void *o, int v);
void m1_SlotObj0A42A0(int slot);
void *m1_SlotGet0A4290(int slot);
int  sub_000A2630(void *s, void *p, float *v);
void sub_000CAE20(void *p, float v);
int  r2b_TestBit(int bit);
void a3c_VecCopy(float *d, const float *s);
/* 0x93C50: event actor step. State 0: actor 0x50 or 0xFB in world 2 area 4, once flag 0xBA is set and slot 0x1D accepts it, clears flags 0x810, takes 9999 power, makes its position the home and body position and advances. State 1: releases its sub-object and itself and hides it. */
void m2_ActStep93C50(M2Act9 *o) {
    float v[4];
    void *q = o->p120;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    switch (o->state40) {
    case 0: {
        int ok = 0;
        if ((o->id4 == 0x50 || o->id4 == 0xFB) && r1e_g41316C == 2 && r1e_g413170 == 4 && r2b_TestBit(0xBA)) {
            m1_SlotObj0A42A0(0x1D);
            if (sub_000A2630(m1_SlotGet0A4290(0x1D), q, v)) ok = 1;
            if (ok) {
                o->flags0 &= ~0x810u;
                sub_000CAE20(g_stats, -9999.0f);
                a3c_VecCopy(o->home2D0, o->pos70);
                a3c_VecCopy((float *)(o->body380 + 0x60), o->pos70);
                o->state40++;
            }
        }
        break;
    }
    case 1:
        sub_000A41D0(o->sub260, 1);
        sub_000A41D0(o, -1);
        r6e_ActorShow(o, 0);
        break;
    }
}

extern const char r1b_fmtF[];
extern const char r1b_fmtD[];
char *r1b_NextToken(char **s);
int   r1b_sscanf(const char *s, const char *fmt, ...);
int   r1e_SlotAdd(int *rect, int kind, int a, int b, int c, int n, int d, float *v);

/* 0x7A4F0: script command: read four floats (a rectangle) and an integer from the argument text and add a kind-2 slot with that rectangle (whole units), the integer and a zero vector. Stops quietly when a token is missing. */
void m2_CmdRect7A4F0(char *s) {
    float f[4]; int n; float v[4]; int r[4];
    char *t;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 0.0f;
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &f[0]);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &f[1]);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &f[2]);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &f[3]);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtD, &n);
    r[0] = (int)f[0]; r[1] = (int)f[1]; r[2] = (int)f[2]; r[3] = (int)f[3];
    r1e_SlotAdd(r, 2, 0, 0, 0, n, 0, v);
}
