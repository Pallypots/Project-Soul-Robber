/* Area m1, file 352: enemy spawn setup (handler table, stats and start state). Names inferred. */
#include <stdint.h>

typedef struct M1St352 {
    void *p00; uint8_t unk04[4]; void *p08; uint32_t f0C; uint8_t unk10[0x174 - 0x10];
    int32_t i174; uint8_t unk178[8]; float f180; uint8_t unk184[0x18C - 0x184]; int32_t i18C; int32_t i190; int32_t i194;
} M1St352;
typedef struct M1Ai352 {
    uint8_t unk000[0x24]; int32_t i24; float f28; float f2C; const void *p30; uint8_t unk034[0x4C - 0x34];
    uint32_t f4C; int32_t i50; int32_t i54; uint8_t unk058[0x270 - 0x58]; float f270; float f274; M1St352 *s278;
    void *fn27C; void *fn280; void *fn284; void *fn288; const void *p28C; const void *p290; const void *p294; void *fn298; void *fn29C;
} M1Ai352;
typedef struct M1Ob352 {
    uint8_t unk000[4]; int32_t i04; int32_t i08; uint32_t f0C; uint32_t f10; uint8_t unk014[0x70 - 0x14];
    float f70, f74, f78, f7C; uint8_t unk080[0xD0 - 0x80]; int32_t iD0; uint8_t unk0D4[0xEC - 0xD4];
    int32_t iEC; int32_t iF0; int32_t iF4; uint8_t unk0F8[0x118 - 0xF8]; int32_t i118; int32_t i11C; int32_t i120; int32_t i124;
} M1Ob352;
extern const uint8_t m1_tbl31C298[], m1_tbl31C350[], m1_tbl31C404[], m1_tbl31C264[];
void *sub_00166110(void);
void  a80_SetFlags(void *p, int f);
void  b16_SetFloats(void *p, float a, float b);
void  b16_SetInts(void *p, int a, int b);
void  r2d_HookAttach(void *o, void *e, int k);
int   sub_0001BC40(void *o);
void  rbi_Shapes12DEC0(void);                       /* regargs */
float sub_00171D50(int a, int b, int c);
int   sub_001C7EE1(void);                           /* rand */
void  sub_00025C10(int a, int b);
void  sub_001130F0(void *o, void *e, int k);
void  sub_00131310(int next);                       /* regargs: o=EBX e=EDI */
void  m1_ActorRelease12D670(void);
void  m1_TakeHit1318F0(void);
void  sub_00134FA0(void);
void  r2e_ActorDamp164(void);
void  m1_MoveApply145E10(void);
void  b1b_TargetPlayer(void);

/* 0x135250: set up a spawned enemy: create its effect channel, install the handler table
   and the three move tables, size and gravity, flags, health from its kind, a random
   1..2 x10 idle timer; mode 0 starts it dormant (flag 1, the 0x14 spawn sound, guard 3),
   mode 1 awake (guard 2), any other mode hangs; then enter state 0x2C. */
int m1_EnemySetup135250(M1Ob352 *o, M1Ai352 *e, int mode) {
    M1St352 *s = e->s278;
    void *p;
    s->p00 = o;
    p = sub_00166110();
    s->p08 = p;
    if (!p)
        for (;;);
    a80_SetFlags(p, 6);
    b16_SetFloats(s->p08, 100.0f, 50.0f);
    b16_SetInts(s->p08, 2, 2);
    e->p28C = m1_tbl31C298;
    e->p290 = m1_tbl31C350;
    e->p294 = m1_tbl31C404;
    e->fn27C = (void *)m1_ActorRelease12D670;
    e->fn29C = (void *)m1_TakeHit1318F0;
    e->fn280 = (void *)sub_00134FA0;
    e->fn284 = (void *)r2e_ActorDamp164;
    e->fn288 = (void *)m1_MoveApply145E10;
    e->fn298 = (void *)b1b_TargetPlayer;
    o->f78 = 1.25f;
    o->f74 = 1.25f;
    o->f70 = 1.25f;
    o->f7C = 1.0f;
    r2d_HookAttach(o, e, 0xA);
    e->f28 = -6.25f;
    e->p30 = m1_tbl31C264;
    e->i24 = 2;
    e->f2C = -12.5f;
    o->i124 = 1;
    o->iD0 = sub_0001BC40(o);
    o->iEC = 0;
    o->i118 = 2;
    rbi_Shapes12DEC0();
    o->f0C |= 0x100;
    o->iF0 = 2;
    o->iF4 = 2;
    o->i11C = 1;
    o->i120 = 2;
    o->f10 |= 0x200;
    e->f4C |= 0x200;
    s->f0C |= 0x1000;
    e->i54 = 0;
    e->i50 = 0;
    e->f270 = e->f274 = sub_00171D50(o->i04, o->i08, 0);
    s->f180 = ((float)sub_001C7EE1() * 3.05185094e-05f + 1.0f) * 10.0f;
    s->i174 = 0;
    s->i190 = 0x14;
    s->i194 = 0;
    switch (mode) {
    case 0:
        s->f0C |= 1;
        sub_00025C10(1, 0x14);
        s->i18C = 3;
        break;
    case 1:
        s->f0C &= 0xFFFF7FFEu;
        s->i18C = 2;
        break;
    default:
        for (;;);
    }
    sub_001130F0(o, e, 0);
    sub_00131310(0x2C);
    return 1;
}
