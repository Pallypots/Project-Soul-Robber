/* Area m1, file 20: actor release variant and table value update. Names inferred. */
#include <stdint.h>

typedef struct M1Work278B {
    uint8_t  unk00[4];
    uint8_t  flags04;          /* +0x04 */
    uint8_t  unk05[3];
    void    *fx08;             /* +0x08 */
} M1Work278B;
typedef struct M1Actor278B {
    uint8_t     unk000[0x6C];
    int32_t     snd06C;        /* +0x06C, -1 = none */
    void       *res070;        /* +0x070 */
    uint8_t     unk074[0x278 - 0x74];
    M1Work278B *work278;       /* +0x278 */
} M1Actor278B;
void  sub_00048250(int h);
void  sub_00033A70(void *r);
void  sub_001661B0(void *fx);
void *sub_0001D2B0(void *model, int part);
void  sub_0001EB80(void *o);

/* 0x00114650: like 0x12D670, but the model reset is keyed on flag 0x40 at work+4. Returns 1. */
int m1_ActorRelease114650(void *model, M1Actor278B *a)
{
    M1Work278B *w = a->work278;
    if (a->snd06C != -1) {
        sub_00048250(a->snd06C);
        a->snd06C = -1;
    }
    if (a->res070 != 0) {
        sub_00033A70(a->res070);
        a->res070 = 0;
    }
    sub_001661B0(w->fx08);
    w->fx08 = 0;
    if (w->flags04 & 0x40)
        sub_0001EB80(sub_0001D2B0(model, 2));
    return 1;
}

typedef struct M1Src8 {
    uint8_t unk00[4];
    int32_t a04;               /* +0x04 */
    int32_t b08;               /* +0x08 */
} M1Src8;
typedef struct M1Ent260V {
    uint8_t  unk000[0xC];
    float    val00C;           /* +0x00C */
    uint8_t  unk010[0x110 - 0x10];
    int32_t  ivals110[4];      /* +0x110 */
    M1Src8  *src120;           /* +0x120 */
    uint8_t  unk124[0x260 - 0x124];
} M1Ent260V;
extern M1Ent260V m1_ents4242C0[32];  /* 0x004242C0 */
float sub_00171D50(int a, int b, int c);

/* 0x000A3690: samples entry i's source; stores the float at +0x0C and its
 * integer part in slot j of +0x110. */
void m1_SampleA3690(int i, int j)
{
    M1Ent260V *e = &m1_ents4242C0[i];
    float f;
    if (e->src120 == 0)
        return;
    f = sub_00171D50(e->src120->a04, e->src120->b08, 0);
    e->val00C = f;
    e->ivals110[j] = (int)(unsigned int)f;   /* _ftol2 like the original; assumes f >= 0 (behaviour-test priority) */
}
