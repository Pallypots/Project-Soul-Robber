/* Area r6j: trap room script (r6j_10). Names inferred. */
#include "r6j.h"

/* 0x000BAE80: trap event. Phase 10 waits for any of bits 0x F00 at
   0x00420DAC, then starts camera event 3 and plays sound 0x2A4; 11 takes
   the trap damage for the current level (0x002E5EE0) off the health
   (never below 0) and adds it to the grade; 13 fades out (1 s); 14 waits,
   stops the player (flag 2) and calls 0x000D1D00; 15 calls 0x000DDEF0(0xB,
   4) and 0x000DDF40 and restarts the frame count; 16 after two seconds
   goes on while the player still has health, else releases the player,
   sets player flag 0x80000, calls 0x0019D8B0 and ends (0x14); 17 fades in;
   18 waits; 19 clears the player flags, ends camera event 3 and rearms
   phase 10. Phase 0x14 clears the state and returns 0 (mode 3 forces it).
   Returns 1. */
int r6j_RoomScriptTrap(int mode, R6jStep *st)
{
    int hp;
    int dmg;
    int count;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
        st->count = 0;
        return 1;
    }
    if (mode == 1) {
        st->flags |= 1;
        st->count = 0;
        st->phase = 10;
        return 1;
    }
    if (mode == 3) {
        st->flags = 0;
        st->phase = 0x14;
    }
    count = ++st->count;
    switch (st->phase) {
    case 10:
        if ((r6j_g420DAC & 0xF00) == 0)
            break;
        sub_0019BE90(3);
        sub_00048AF0(0x2A4);
        st->phase++;
        return 1;
    case 11:
        dmg = r6j_trapDamage2E5EE0[r6i_g413178];
        hp = Stats_Get(&g_stats, 1) - dmg;
        if (hp < 0)
            hp = 0;
        Stats_Set(&g_stats, 1, hp);
        Grade_AddDamage(dmg);
        st->phase++;
        break;
    case 12:
        st->phase++;
        break;
    case 13:
        sub_00036C00(1, 0, 1.0f);
        st->phase++;
        return 1;
    case 14:
        if (sub_00036D40() != 0)
            break;
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        st->phase++;
        return 1;
    case 15:
        sub_000DDEF0(0xB, 4);
        sub_000DDF40();
        st->phase++;
        st->count = 0;
        return 1;
    case 16:
        if (!(count > a50_framesPerSecond + a50_framesPerSecond))
            break;
        if (Stats_Get(&g_stats, 1) != 0) {
            st->phase++;
            break;
        }
        sub_000D1930(&g_stats);
        PlayerObj_SetFlags(&g_stats, 0x80000, 0);
        sub_0019D8B0();
        st->phase = 0x14;
        return 1;
    case 17:
        st->phase++;   /* before the fade (0x00036C00 only touches the fade globals) */
        sub_00036C00(0, 0, 1.0f);
        return 1;
    case 18:
        if (sub_00036D40() != 0)
            break;
        st->phase++;
        return 1;
    case 19:
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        st->phase = 10;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000B60A0: second trap event, same as 0x000BAE80 with sound 0x2F7, the
   damage table at 0x002E5910 and 0x000DDEF0(0x14, 4). Phase 10 waits for any of bits 0x F00 at
   0x00420DAC, then starts camera event 3 and plays sound 0x2A4; 11 takes
   the trap damage for the current level (0x002E5EE0) off the health
   (never below 0) and adds it to the grade; 13 fades out (1 s); 14 waits,
   stops the player (flag 2) and calls 0x000D1D00; 15 calls 0x000DDEF0(0xB,
   4) and 0x000DDF40 and restarts the frame count; 16 after two seconds
   goes on while the player still has health, else releases the player,
   sets player flag 0x80000, calls 0x0019D8B0 and ends (0x14); 17 fades in;
   18 waits; 19 clears the player flags, ends camera event 3 and rearms
   phase 10. Phase 0x14 clears the state and returns 0 (mode 3 forces it).
   Returns 1. */
int r6j_RoomScriptTrap2(int mode, R6jStep *st)
{
    int hp;
    int dmg;
    int count;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
        st->count = 0;
        return 1;
    }
    if (mode == 1) {
        st->flags |= 1;
        st->count = 0;
        st->phase = 10;
        return 1;
    }
    if (mode == 3) {
        st->flags = 0;
        st->phase = 0x14;
    }
    count = ++st->count;
    switch (st->phase) {
    case 10:
        if ((r6j_g420DAC & 0xF00) == 0)
            break;
        sub_0019BE90(3);
        sub_00048AF0(0x2F7);
        st->phase++;
        return 1;
    case 11:
        dmg = r6j_trapDamage2E5910[r6i_g413178];
        hp = Stats_Get(&g_stats, 1) - dmg;
        if (hp < 0)
            hp = 0;
        Stats_Set(&g_stats, 1, hp);
        Grade_AddDamage(dmg);
        st->phase++;
        break;
    case 12:
        st->phase++;
        break;
    case 13:
        sub_00036C00(1, 0, 1.0f);
        st->phase++;
        return 1;
    case 14:
        if (sub_00036D40() != 0)
            break;
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        st->phase++;
        return 1;
    case 15:
        sub_000DDEF0(0x14, 4);
        sub_000DDF40();
        st->phase++;
        st->count = 0;
        return 1;
    case 16:
        if (!(count > a50_framesPerSecond + a50_framesPerSecond))
            break;
        if (Stats_Get(&g_stats, 1) != 0) {
            st->phase++;
            break;
        }
        sub_000D1930(&g_stats);
        PlayerObj_SetFlags(&g_stats, 0x80000, 0);
        sub_0019D8B0();
        st->phase = 0x14;
        return 1;
    case 17:
        st->phase++;   /* before the fade (0x00036C00 only touches the fade globals) */
        sub_00036C00(0, 0, 1.0f);
        return 1;
    case 18:
        if (sub_00036D40() != 0)
            break;
        st->phase++;
        return 1;
    case 19:
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        st->phase = 10;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000ADE40: third trap event, same as 0x000BAE80 with sound 0x307, the
   damage table at 0x002E4ECC and 0x000DDEF0(0x1B, 0). Phase 10 waits for any of bits 0x F00 at
   0x00420DAC, then starts camera event 3 and plays sound 0x2A4; 11 takes
   the trap damage for the current level (0x002E5EE0) off the health
   (never below 0) and adds it to the grade; 13 fades out (1 s); 14 waits,
   stops the player (flag 2) and calls 0x000D1D00; 15 calls 0x000DDEF0(0xB,
   4) and 0x000DDF40 and restarts the frame count; 16 after two seconds
   goes on while the player still has health, else releases the player,
   sets player flag 0x80000, calls 0x0019D8B0 and ends (0x14); 17 fades in;
   18 waits; 19 clears the player flags, ends camera event 3 and rearms
   phase 10. Phase 0x14 clears the state and returns 0 (mode 3 forces it).
   Returns 1. */
int r6j_RoomScriptTrap3(int mode, R6jStep *st)
{
    int hp;
    int dmg;
    int count;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
        st->count = 0;
        return 1;
    }
    if (mode == 1) {
        st->flags |= 1;
        st->count = 0;
        st->phase = 10;
        return 1;
    }
    if (mode == 3) {
        st->flags = 0;
        st->phase = 0x14;
    }
    count = ++st->count;
    switch (st->phase) {
    case 10:
        if ((r6j_g420DAC & 0xF00) == 0)
            break;
        sub_0019BE90(3);
        sub_00048AF0(0x307);
        st->phase++;
        return 1;
    case 11:
        dmg = r6j_trapDamage2E4ECC[r6i_g413178];
        hp = Stats_Get(&g_stats, 1) - dmg;
        if (hp < 0)
            hp = 0;
        Stats_Set(&g_stats, 1, hp);
        Grade_AddDamage(dmg);
        st->phase++;
        break;
    case 12:
        st->phase++;
        break;
    case 13:
        sub_00036C00(1, 0, 1.0f);
        st->phase++;
        return 1;
    case 14:
        if (sub_00036D40() != 0)
            break;
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        st->phase++;
        return 1;
    case 15:
        sub_000DDEF0(0x1B, 0);
        sub_000DDF40();
        st->phase++;
        st->count = 0;
        return 1;
    case 16:
        if (!(count > a50_framesPerSecond + a50_framesPerSecond))
            break;
        if (Stats_Get(&g_stats, 1) != 0) {
            st->phase++;
            break;
        }
        sub_000D1930(&g_stats);
        PlayerObj_SetFlags(&g_stats, 0x80000, 0);
        sub_0019D8B0();
        st->phase = 0x14;
        return 1;
    case 17:
        st->phase++;   /* before the fade (0x00036C00 only touches the fade globals) */
        sub_00036C00(0, 0, 1.0f);
        return 1;
    case 18:
        if (sub_00036D40() != 0)
            break;
        st->phase++;
        return 1;
    case 19:
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        st->phase = 10;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000ACCA0: fourth trap event, same as 0x000BAE80 with sound 0x307, the
   damage table at 0x002E4C54 and 0x000DDEF0(0x19, 3 when event flag 0x124
   is set else 0). Phase 10 waits for any of bits 0x F00 at
   0x00420DAC, then starts camera event 3 and plays sound 0x2A4; 11 takes
   the trap damage for the current level (0x002E5EE0) off the health
   (never below 0) and adds it to the grade; 13 fades out (1 s); 14 waits,
   stops the player (flag 2) and calls 0x000D1D00; 15 calls 0x000DDEF0(0xB,
   4) and 0x000DDF40 and restarts the frame count; 16 after two seconds
   goes on while the player still has health, else releases the player,
   sets player flag 0x80000, calls 0x0019D8B0 and ends (0x14); 17 fades in;
   18 waits; 19 clears the player flags, ends camera event 3 and rearms
   phase 10. Phase 0x14 clears the state and returns 0 (mode 3 forces it).
   Returns 1. */
int r6j_RoomScriptTrap4(int mode, R6jStep *st)
{
    int hp;
    int dmg;
    int count;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
        st->count = 0;
        return 1;
    }
    if (mode == 1) {
        st->flags |= 1;
        st->count = 0;
        st->phase = 10;
        return 1;
    }
    if (mode == 3) {
        st->flags = 0;
        st->phase = 0x14;
    }
    count = ++st->count;
    switch (st->phase) {
    case 10:
        if ((r6j_g420DAC & 0xF00) == 0)
            break;
        sub_0019BE90(3);
        sub_00048AF0(0x307);
        st->phase++;
        return 1;
    case 11:
        dmg = r6j_trapDamage2E4C54[r6i_g413178];
        hp = Stats_Get(&g_stats, 1) - dmg;
        if (hp < 0)
            hp = 0;
        Stats_Set(&g_stats, 1, hp);
        Grade_AddDamage(dmg);
        st->phase++;
        break;
    case 12:
        st->phase++;
        break;
    case 13:
        sub_00036C00(1, 0, 1.0f);
        st->phase++;
        return 1;
    case 14:
        if (sub_00036D40() != 0)
            break;
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        st->phase++;
        return 1;
    case 15:
        sub_000DDEF0(0x19, sub_000D9A70(0x124) != 0 ? 3 : 0);
        sub_000DDF40();
        st->phase++;
        st->count = 0;
        return 1;
    case 16:
        if (!(count > a50_framesPerSecond + a50_framesPerSecond))
            break;
        if (Stats_Get(&g_stats, 1) != 0) {
            st->phase++;
            break;
        }
        sub_000D1930(&g_stats);
        PlayerObj_SetFlags(&g_stats, 0x80000, 0);
        sub_0019D8B0();
        st->phase = 0x14;
        return 1;
    case 17:
        st->phase++;   /* before the fade (0x00036C00 only touches the fade globals) */
        sub_00036C00(0, 0, 1.0f);
        return 1;
    case 18:
        if (sub_00036D40() != 0)
            break;
        st->phase++;
        return 1;
    case 19:
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        st->phase = 10;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000AF6D0: fifth trap event like 0x000BAE80: phase 10 waits for bits
   0xF00 at 0x00420DAC and plays sound 0x2DB (no camera event there; camera
   event 3 starts in phase 14 after the player is stopped); the damage
   table is 0x002E4FF0 and phase 15 calls 0x000DDEF0(0xF, 4). Here the
   original shares one fade call between phases 13 (out) and 17 (in),
   written as a goto to a shared tail. Returns 1; phase 0x14 returns 0. */
int r6j_RoomScriptTrap5(int mode, R6jStep *st)
{
    int hp;
    int dmg;
    int count;
    int dir;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
        st->count = 0;
        return 1;
    }
    if (mode == 1) {
        st->flags |= 1;
        st->count = 0;
        st->phase = 10;
        return 1;
    }
    if (mode == 3) {
        st->flags = 0;
        st->phase = 0x14;
    }
    count = ++st->count;
    switch (st->phase) {
    case 10:
        if ((r6j_g420DAC & 0xF00) == 0)
            break;
        sub_00048AF0(0x2DB);
        st->phase++;
        return 1;
    case 11:
        dmg = r6j_trapDamage2E4FF0[r6i_g413178];
        hp = Stats_Get(&g_stats, 1) - dmg;
        if (hp < 0)
            hp = 0;
        Stats_Set(&g_stats, 1, hp);
        Grade_AddDamage(dmg);
        st->phase++;
        break;
    case 12:
        st->phase++;
        break;
    case 17:
        dir = 0;
        goto fade;
    case 13:
        dir = 1;
        /* fall through */
    fade:
        sub_00036C00(dir, 0, 1.0f);
        st->phase++;
        return 1;
    case 14:
        if (sub_00036D40() != 0)
            break;
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        sub_0019BE90(3);
        st->phase++;
        return 1;
    case 15:
        sub_000DDEF0(0xF, 4);
        sub_000DDF40();
        st->phase++;
        st->count = 0;
        return 1;
    case 16:
        if (!(count > a50_framesPerSecond + a50_framesPerSecond))
            break;
        if (Stats_Get(&g_stats, 1) != 0) {
            st->phase++;
            break;
        }
        sub_000D1930(&g_stats);
        PlayerObj_SetFlags(&g_stats, 0x80000, 0);
        sub_0019D8B0();
        st->phase = 0x14;
        return 1;
    case 18:
        if (sub_00036D40() != 0)
            break;
        st->phase++;
        return 1;
    case 19:
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        st->phase = 10;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}
