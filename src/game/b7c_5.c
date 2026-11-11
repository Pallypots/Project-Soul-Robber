/* Area b7c, group 5: boss globals 0x00182750-0x00182E50. Names inferred. */
#include "b7c.h"
#include "shared_decls.h"

extern void *b7c_bossOwner3FE368;       /* 0x003FE368 */
extern void *b7c_bossEnemy3FE36C;       /* 0x003FE36C */
extern int32_t b7c_count3FE374;         /* 0x003FE374 */
extern uint8_t *b7c_bossObj3FE37C;      /* 0x003FE37C */
extern float b7c_mat3FE380;             /* 0x003FE380 rotation angle */
void sub_00181C60(int id, int st);

/* 0x00182750: the boss owner (hangs if not set). */
void *b7c_BossOwner182750(void)
{
    if (b7c_bossOwner3FE368 == 0)
        for (;;) ;
    return b7c_bossOwner3FE368;
}

/* 0x00182760: the boss object (hangs if not set). */
uint8_t *b7c_BossObj182760(void)
{
    if (b7c_bossObj3FE37C == 0)
        for (;;) ;
    return b7c_bossObj3FE37C;
}

/* 0x00182770: switch the boss to a state. */
void b7c_BossSwitch182770(int st)
{
    void *o = b7c_bossOwner3FE368, *e;
    if (o == 0)
        for (;;) ;
    e = b7c_bossEnemy3FE36C;
    if (e == 0)
        for (;;) ;
    sub_00113040(o, e, st);
}

/* 0x00182850: rebuild the boss matrix and copy the position from p. */
void b7c_BossPlace182850(uint8_t *p)
{
    uint8_t *m = b7c_bossObj3FE37C + 0x40;
    sub_001AD940(m);
    sub_001AD8E0(m, m, b7c_mat3FE380);
    b7c_VecCopy(m + 0x30, p + 0x60);
}

/* 0x00182950: reset the counter and switch records 0..3 to state 1. */
void b7c_ResetParts182950(void)
{
    int i;
    b7c_count3FE374 = 0;
    for (i = 0; i < 4; i++)
        sub_00181C60(i, 1);
}

/* 0x00182E40: reset the counter. */
void b7c_ResetCount182E40(void) { b7c_count3FE374 = 0; }
