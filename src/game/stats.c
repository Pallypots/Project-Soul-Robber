/* Player stats and souls. Reference build OOGIE-XBOX-US-RETAIL.
 * Names inferred. Records: docs/functions/stats.md */
#include "oogie.h"
#include <stddef.h>

#define SLOT(s, off, i) (&((int32_t *)((uint8_t *)(s) + (off)))[i])

/* 0x000CF790: read stat `index` (jump table at 0x000CF7DC). */
int Stats_Get(PlayerStats *s, int index)
{
    switch (index) {
    case 0:  return s->maxHealth;
    case 1:  return s->health;
    case 2:  return (int)s->stat2;
    case 3:  return s->stat3;
    case 4: case 5: case 6: case 8: case 9: case 10: case 11:
             return *SLOT(s, 0xD5C, index);
    case 12: return s->soulsWallet;
    default: return *SLOT(s, 0xD74, index);
    }
}

/* 0x000CF810: write stat `index`, returns the value written. Indices 2 and 3
 * are read-only (nothing stored). Index 7 and anything above 12 also set
 * event flag bit (index - 13) when the value is positive. */
int Stats_Set(PlayerStats *s, int index, int value)
{
    int32_t *p = NULL;
    int bit;

    switch (index) {
    case 0:
        p = &s->maxHealth;
        break;
    case 1:
        p = &s->health;
        if ((g_cheatFlags & 1) && value < 1)
            value = 1;
        break;
    case 2: case 3:
        break;
    case 4: case 5: case 6: case 8: case 9: case 10: case 11:
        p = SLOT(s, 0xD5C, index);
        break;
    case 12:
        p = &s->soulsWallet;
        break;
    default:
        p = SLOT(s, 0xD74, index);
        if (value > 0) {
            bit = index - 13;
            g_eventFlagBits[bit / 32] |= 1u << (bit % 32);
        }
        break;
    }
    if (p != NULL)
        *p = value;
    return value;
}

/* 0x000CF910: lifetime soul total, capped at 9,999,999. */
void Souls_AddLifetime(int amount)
{
    if (amount > 0) {
        g_stats.soulsLifetime += amount;
        if (g_stats.soulsLifetime > 9999999)
            g_stats.soulsLifetime = 9999999;
    }
}

/* 0x000D1F40: take `amount` souls from the wallet (kept within 0..99,999).
 * Returns `amount`, or the shortfall-adjusted amount when the wallet holds
 * less (amount - wallet). */
int Souls_Spend(int amount)
{
    int result = amount;
    int w;

    if (g_stats.soulsWallet < amount)
        result = amount - g_stats.soulsWallet;
    amount = -amount;
    sub_00024D30(2, amount);
    w = g_stats.soulsWallet + amount;
    if (w >= 99999)
        w = 99999;
    else if (w <= 0)
        w = 0;
    g_stats.soulsWallet = w;
    return result;
}

/* 0x000CF940 */
int Souls_GetLifetime(void)
{
    return g_stats.soulsLifetime;
}

/* 0x000CF8E0: maximum value for stat `index` (table at 0x002E7AE0). */
int Stats_GetMax(int index)
{
    if (index >= 0x50)
        return 0;
    if (index == 0x17)
        return sub_00171CD0(&g_stats) * 10;
    return g_statMaxTable[index];
}

/* 0x000CF950: Jack takes `damage`. Adds it to the chapter damage tally, never
 * drops below 1 health while cheat flag bit 0 is set, starts the death
 * sequence at 0. Returns 1 alive, -1 dead. */
int Player_TakeDamage(PlayerStats *s, int damage)
{
    Grade_AddDamage(damage);
    if ((g_cheatFlags & 1) && s->health - damage <= 0)
        damage = s->health - 1;
    s->health -= damage;
    sub_00023D80(3, damage);
    if (s->health <= 0) {
        s->health = 0;
        sub_000CEF00();
        return -1;
    }
    return 1;
}

/* 0x000CF9C0 */
int Stats_SetFlag2(PlayerStats *s)
{
    s->timerD94 = 0.0f;
    if (!(s->flags & 2))
        s->flags |= 2;
    return 1;
}

/* 0x000CF9F0: while flag bit 1 is set and timerD94 is below 720, call 0x000CA6C0. */
void Stats_UpdateFlag2(void)
{
    if ((g_stats.flags & 2) && 720.0f > g_stats.timerD94)
        sub_000CA6C0(&g_stats);
}

/* 0x000CFA20 */
int Stats_SetFlag1(PlayerStats *s)
{
    if (s->flags & 1)
        return -1;
    s->flags |= 1;
    s->timerD90 = 0.0f;
    return 1;
}

/* 0x000CFA50 */
uint32_t Stats_TestFlags(PlayerStats *s, uint32_t mask)
{
    return s->flags & mask;
}

/* 0x000CF6A0 */
int Stats_GetD8(void)
{
    return g_stats.unkD8;
}

/* 0x000CF6B0 */
int Stats_Get1B8(void)
{
    return g_stats.unk1B8;
}

/* 0x000CF6C0 */
int Stats_HasEFC(void)
{
    return g_stats.unkEFC != 0 ? 1 : -1;
}
