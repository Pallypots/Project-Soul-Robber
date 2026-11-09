/* Player character object helpers (0x000CF180-0x000CF4EB). Reference build
 * OOGIE-XBOX-US-RETAIL. Names inferred; the object type is a Hypothesis.
 * Same original source file as stats.c (address order). Records:
 * docs/functions/stats.md */
#include "oogie.h"

/* 0x000CF180: 1 when none of mode bits 0x33 are set, else -1. */
int PlayerObj_ModeSign(PlayerObj *p)
{
    return ((uint8_t)p->modeEC & 0x33) ? -1 : 1;
}

/* 0x000CF1A0 */
int PlayerObj_IsActive(PlayerObj *p)
{
    if (p->unkD4 != 0 || p->modeEC != 0)
        return 1;
    return -1;
}

/* 0x000CF1D0 */
int PlayerObj_IsIdle(PlayerObj *p)
{
    if (p->flags[0] & 0x40000B01)
        return -1;
    return p->modeEC == 0 ? 1 : -1;
}

/* 0x000CF3C0 */
void PlayerObj_SetFlags(PlayerObj *p, uint32_t lo, uint32_t hi)
{
    p->flags[0] |= lo;
    p->flags[1] |= hi;
}

/* 0x000CF3F0 */
void PlayerObj_ClearFlags(PlayerObj *p, uint32_t lo, uint32_t hi)
{
    p->flags[0] &= ~lo;
    p->flags[1] &= ~hi;
}

/* 0x000CF420 */
uint32_t PlayerObj_TestFlags(PlayerObj *p, uint32_t mask, int high)
{
    if (high == 0)
        return p->flags[0] & mask;
    return p->flags[1] & mask;
}

/* 0x000CF450: forwards to 0x000F5D40 with the sub-object at +0xFD8, +0x60
 * (a tail call in the original; any further arguments pass through). */
int PlayerObj_ForwardFD8(PlayerObj *p)
{
    return sub_000F5D40(p->unkFD8 + 0x60);
}

/* 0x000CF470 */
int PlayerObj_Call1ADAF0(int a, int b)
{
    return sub_001ADAF0(a, a, b);
}

/* 0x000CF4E0 */
void PlayerObj_ClearFlags22(PlayerObj *p)
{
    p->flags[0] &= ~0x22u;
}

/* 0x000CF070: 1 (and reset) once timer134 is positive and timer130 has
 * reached it; while timer134 is not positive, asks 0x001AEE50 about the
 * object three links down from +0xFD8 (types not analysed). */
int PlayerObj_TimerDone(PlayerObj *p)
{
    uint8_t *a, *b;

    if (p->timer134 > 0.0f) {
        if (p->timer130 < p->timer134)
            return 0;
        p->timer134 = 0.0f;
        return 1;
    }
    a = *(uint8_t **)(p->unkFD8 + 0x30);
    b = *(uint8_t **)(a + 0x14);
    if (*(int32_t *)(b + 0xC8) != 0)
        return 0;
    return sub_001AEE50(b, 0) & 2;
}

/* 0x000CF0D0 */
void Player_Refresh(void)
{
    uint8_t *o = g_42C8EC;

    sub_0001D610(g_playerObj);
    if (g_stats.unk1B8 == 0 || g_stats.unk1B8 == 1) {
        sub_000CE970();
        sub_000CEF60();
        if (g_stats.unk1B8 == 0)
            sub_0001D610(*(void **)(o + 0x3B0));
    }
}

/* 0x000CF120: angleFC - angle108 wrapped into -pi..pi. */
float PlayerObj_AngleDelta(PlayerObj *p)
{
    float d = p->angleFC - p->angle108;
    if (d > 3.14159274f)
        d -= 6.28318548f;
    if (-3.14159274f > d)
        d += 6.28318548f;
    return d;
}
