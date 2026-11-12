/* Area m1, file 25: actor reaction after an animation. Names inferred. */
#include <stdint.h>

typedef struct M1Body30 {
    uint8_t unk00[0x30];
    void   *anim30;            /* +0x30 */
} M1Body30;
typedef struct M1Act58 {
    uint8_t unk00[0x58];
    int32_t mode58;            /* +0x58 must be 0x14 here */
} M1Act58;
int  sub_000833E0(void *anim);
int  r2_PlayerOutOfReach(M1Act58 *obj, M1Body30 *self);  /* regargs: obj=EAX self=ESI */
void sub_0011F2B0(void *obj, int k, void *a);             /* regargs: obj=EDI k=EBX */

/* 0x00128240: once the body's animation finished, switches the actor to state
 * 0x11 when the player is out of reach, else 0xF (mode must be 0x14). */
void m1_AfterAnim128240(M1Body30 *body, M1Act58 *act)
{
    if (act->mode58 != 0x14)
        for (;;) ;
    if (sub_000833E0(body->anim30))
        sub_0011F2B0(body, r2_PlayerOutOfReach(act, body) ? 0x11 : 0xF, act);
}

#include "oogie.h"
int sub_000D1E10(void *s, int index, int delta);
int sub_000494D0(int id, const void *pos, int c);

/* 0x000A9A30: adds 2 (or 8 with flag 0x8000000) to Jack's stat 1; when the value
 * changed, shows it (0x23D80) and plays reaction 0x4F (or 0x50); then plays
 * sound 0x18 at Jack and sets flag 0x40000000. */
void m1_StatBumpA9A30(uint32_t *flags)
{
    int anim = 0x4F;
    int amount = 2;
    int before = Stats_Get(&g_stats, 1);
    if (*flags & 0x8000000) {
        anim = 0x50;
        amount = 8;
    }
    if (before != sub_000D1E10(&g_stats, 1, amount)) {
        sub_00023D80(2, amount);
        PlayerObj_D0030(&g_stats, anim);
    }
    sub_000494D0(0x18, (uint8_t *)g_playerObj + 0x60, 0);
    *flags |= 0x40000000;
}

void sub_000A5520(void);
void sub_000A4B80(void);
int  sub_000CF420(void *s, uint32_t flag, int z);
void sub_000CF3F0(void *s, uint32_t flag, int z);

/* 0x000A56C0: runs 0xA5520 and 0xA4B80, then clears Jack's flags 0x800000 and
 * 0x80 where they are set. */
void m1_ClearJackFlagsA56C0(void)
{
    sub_000A5520();
    sub_000A4B80();
    if (sub_000CF420(&g_stats, 0x800000, 0))
        sub_000CF3F0(&g_stats, 0x800000, 0);
    if (sub_000CF420(&g_stats, 0x80, 0))
        sub_000CF3F0(&g_stats, 0x80, 0);
}

int sub_0011EDE0(int id, void *o, void *b);  /* regargs: id=EAX o=EBX b=EDI */

/* 0x00125DE0: once the body's animation finished: player out of reach -> actor
 * state 0x11; else state 0xE if step list 9 runs, otherwise 7. */
void m1_AfterAnim125DE0(M1Body30 *body, M1Act58 *act)
{
    int st;
    if (!sub_000833E0(body->anim30))
        return;
    if (r2_PlayerOutOfReach(act, body)) {
        sub_0011F2B0(body, 0x11, act);
        return;
    }
    st = sub_0011EDE0(9, body, act) ? 0xE : 7;
    sub_0011F2B0(body, st, act);
}


