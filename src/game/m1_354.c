/* Area m1, file 354: second enemy spawn setup (handler table, collision shapes, start state). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1St354 { uint8_t unk00[0x34]; void *p34; uint8_t unk38[4]; void *p3C; uint8_t unk40[0x68 - 0x40]; float f68; } M1St354;
typedef struct M1Ai354 {
    uint8_t unk000[0x24]; int32_t i24; float f28; float f2C; const void *p30; uint8_t unk034[0x4C - 0x34];
    uint32_t f4C; int32_t i50; int32_t i54; uint8_t unk058[0x270 - 0x58]; float f270; float f274; M1St354 *s278;
    void *fn27C; void *fn280; void *fn284; void *fn288; const void *p28C; const void *p290; const void *p294; void *fn298; void *fn29C;
} M1Ai354;
typedef struct M1Anim354 { uint8_t unk00[0xC0]; int32_t iC0; uint8_t *tblC4; } M1Anim354;
typedef struct M1Ob354 {
    uint8_t unk000[4]; int32_t i04; int32_t i08; uint32_t f0C; uint8_t unk010[0x28 - 0x10]; M1Anim354 *p28;
    uint8_t unk02C[0x50 - 0x2C]; float f50, f54, f58, f5C; uint8_t unk060[0x70 - 0x60]; float f70, f74, f78, f7C;
    uint8_t unk080[0xA0 - 0x80]; float fA0, fA4, fA8, fAC, fB0, fB4; uint8_t unk0B8[0xD0 - 0xB8]; int32_t iD0;
    uint8_t unk0D4[0xD8 - 0xD4]; float fD8, fDC, fE0, fE4, fE8; int32_t iEC; int32_t iF0; int32_t iF4;
    float fF8, fFC, f100, f104, f108, f10C, f110, f114; int32_t i118; int32_t i11C; int32_t i120; int32_t i124;
} M1Ob354;
extern const uint8_t m1_tbl31DC78[], m1_tbl31DD38[], m1_tbl31DDF4[], m1_tbl31DC5C[];
extern float m1_frameRate42C85C;
int   sub_000EDAD0(int a, int b);
void *sub_00166110(void);
void  a80_SetFlags(void *p, int f);
void  b16_SetFloats(void *p, float a, float b);
void  b16_SetInts(void *p, int a, int b);
void  r2d_HookAttach(void *o, void *e, int k);
int   sub_0001BC40(void *o);
float sub_00171D50(int a, int b, int c);
void  b4c_MotionSet156180(void *s, int a, int b, int c, int d);
void  m1_AiSway1561D0(void *s, float a, float b);
void  sub_00113190(void *o, void *e, int k);
void  sub_001130F0(void *o, void *e, int k);
void  sub_00147580(void *obj, int32_t st, void *act);   /* regargs: st=EBX act=ESI */
void  b4c_Release1460E0(void);
void  m1_Fn1480E0(void);
void  m1_PathStep1465C0(void);
void  b3b_Update146750(void);
void  m1_MoveApply145E10(void);
void  m1_AiPickTarget146390(void);
void  m1_DropToNode156440(void);

/* 0x154D50: set up the second enemy type unless seven are already active: create its
   effect channel, install the handlers, move tables and the node-drop hook, size and
   gravity, three collision shapes, health from its kind, the rage meter at 100 and the
   down sway; modes 0..3 pick the start (state 0x2D or 0x2E, awake or not), any other
   mode uses whatever was on the stack. Returns 1 when created. */
int m1_EnemySetup154D50(M1Ob354 *o, M1Ai354 *e, int mode) {
    volatile int junk;
    M1St354 *s;
    void *p;
    int k, f;
    if (sub_000EDAD0(2, 7) >= 1)
        return 0;
    s = e->s278;
    s->p34 = o;
    p = sub_00166110();
    s->p3C = p;
    if (!p)
        for (;;);
    a80_SetFlags(p, 6);
    b16_SetFloats(s->p3C, 100.0f, 30.0f);
    b16_SetInts(s->p3C, 2, 2);
    e->p28C = m1_tbl31DC78;
    e->p290 = m1_tbl31DD38;
    e->p294 = m1_tbl31DDF4;
    e->fn27C = (void *)b4c_Release1460E0;
    e->fn29C = (void *)m1_Fn1480E0;
    e->fn280 = (void *)m1_PathStep1465C0;
    e->fn284 = (void *)b3b_Update146750;
    e->fn288 = (void *)m1_MoveApply145E10;
    e->fn298 = (void *)m1_AiPickTarget146390;
    o->f78 = 1.3f;
    o->f74 = 1.3f;
    o->f70 = 1.3f;
    o->f7C = 1.0f;
    *(void **)(o->p28->tblC4 + o->p28->iC0 * 0x108 + 4) = (void *)m1_DropToNode156440;
    r2d_HookAttach(o, e, 0x13);
    e->f28 = -1.3f;
    e->p30 = m1_tbl31DC5C;
    e->i24 = 2;
    e->f2C = -11.7f;
    o->i124 = 1;
    o->iD0 = sub_0001BC40(o);
    o->fB4 = -7.8f;
    o->fB0 = 5.2f;
    o->fA0 = 0.0f;
    o->fA4 = 0.0f;
    o->fA8 = 0.0f;
    o->fAC = 1.0f;
    o->fE8 = 5.2f;
    o->fA4 = 0.0f - -2.6f;
    o->iEC = 0;
    o->fD8 = 0.0f;
    o->fDC = 0.0f;
    o->fE0 = 0.0f;
    o->fE4 = 1.0f;
    o->i118 = 2;
    o->fDC = _mm_cvtss_f32(_mm_sub_ss(_mm_setzero_ps(), _mm_set_ss(5.2f)));
    o->fF8 = 0.0f;
    o->fFC = 0.0f;
    o->f100 = 0.0f;
    o->f104 = 1.0f;
    o->f108 = 0.0f;
    o->f10C = 0.0f;
    o->f110 = 0.0f;
    o->f114 = 1.0f;
    o->fFC = o->fFC - 2.6f;
    o->iF0 = 2;
    o->iF4 = 2;
    o->i11C = 1;
    o->i120 = 2;
    o->f10C = o->f10C + 2.6f;
    e->f4C |= 0x200;
    o->f0C |= 0x100;
    e->i54 = 0;
    e->i50 = 0;
    e->f270 = e->f274 = sub_00171D50(o->i04, o->i08, 0);
    s->f68 = 100.0f;
    b4c_MotionSet156180(s, 0, 0, 0, 0);
    m1_AiSway1561D0(s, -10.0f, m1_frameRate42C85C * 10.0f);
    o->f50 = 0.0f;
    o->f54 = 0.0f;
    o->f58 = 0.0f;
    o->f5C = 1.0f;
    switch (mode) {
    case 0: f = 0; k = 0x2D; break;
    case 1: f = 1; k = 0x2D; break;
    case 2: f = 0; k = 0x2E; break;
    case 3: f = 1; k = 0x2E; break;
    default: f = junk; k = junk; break;
    }
    sub_00113190(o, e, 1);
    sub_001130F0(o, e, f);
    sub_00147580(o, k, e);
    return 1;
}
