/* Area m1, file 44: simple actor setups (shared template, parameters differ). Names inferred. */
#include <stdint.h>

typedef struct M1ObjS {
    uint8_t  unk00[0x10];
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk14[0x70 - 0x14];
    float    v70[4];           /* +0x70: 1, 1, 1, 0 */
} M1ObjS;
typedef void (*M1CbS)(void);
typedef struct M1ActS {
    uint8_t  unk000[0x20];
    uint32_t flags20;          /* +0x020 */
    uint8_t  unk024[0x27C - 0x24];
    M1CbS    update27C;        /* +0x27C */
    uint8_t  unk280[0x288 - 0x280];
    M1CbS    draw288;          /* +0x288 */
    void    *paramA28C;        /* +0x28C */
    void    *paramB290;        /* +0x290 */
} M1ActS;
void sub_00183C10(void);
void sub_00183200(void);
void sub_0001EBF0(M1ObjS *o, int v);
void sub_0001D610(M1ObjS *o);
void sub_00113040(void *owner, void *obj, int what);

#define M1_SIMPLE_SETUP(name, pa, pb) \
extern uint8_t pa[], pb[]; \
int name(M1ObjS *o, M1ActS *a) \
{ \
    a->paramA28C = pa; \
    a->paramB290 = pb; \
    a->update27C = sub_00183C10; \
    a->draw288 = sub_00183200; \
    o->v70[0] = 1.0f; \
    o->v70[1] = 1.0f; \
    o->v70[2] = 1.0f; \
    o->v70[3] = 0.0f; \
    o->flags10 |= 0xC1; \
    a->flags20 |= 0x80000000; \
    sub_0001EBF0(o, 2); \
    sub_0001D610(o); \
    sub_00113040(o, a, 0); \
    return 1; \
}
/* Each sets up an actor with update 0x183C10, draw 0x183200 and its own parameter
 * pair, scale (1, 1, 1), flags 0xC1 / 0x80000000, mode 2, then event 0. Returns 1. */
M1_SIMPLE_SETUP(m1_Setup179060, m1_p32B39C, m1_p32B3A0)   /* 0x00179060 */
M1_SIMPLE_SETUP(m1_Setup17EBF0, m1_p32B7C8, m1_p32B7CC)   /* 0x0017EBF0 */
M1_SIMPLE_SETUP(m1_Setup17EC80, m1_p32B7D0, m1_p32B7D4)   /* 0x0017EC80 */
M1_SIMPLE_SETUP(m1_Setup17ED70, m1_p32B7D8, m1_p32B7EC)   /* 0x0017ED70 */
M1_SIMPLE_SETUP(m1_Setup17EEA0, m1_p32B800, m1_p32B804)   /* 0x0017EEA0 */
M1_SIMPLE_SETUP(m1_Setup183140, m1_p32B8C8, m1_p32B8CC)   /* 0x00183140 */
M1_SIMPLE_SETUP(m1_Setup183290, m1_p32B8D0, m1_p32B8DC)   /* 0x00183290 */
