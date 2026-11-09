/* Compile-time checks that recovered structure layouts match the offsets seen
 * in the original code. Built by tools/check_all.bat. */
#include "oogie.h"
#include <stddef.h>
#define AT(T, f, off) typedef char chk_##T##_##f[(offsetof(T, f) == (off)) ? 1 : -1]
AT(GradeBlock, rank, 0x10); AT(GradeBlock, grade, 0x14);
typedef char chk_grade_size[sizeof(GradeBlock) == 0x18 ? 1 : -1];
AT(PlayerStats, unkD8, 0xD8); AT(PlayerStats, unk1B8, 0x1B8); AT(PlayerStats, flags, 0xD60);
AT(PlayerStats, maxHealth, 0xD64); AT(PlayerStats, health, 0xD68); AT(PlayerStats, slotsD6C, 0xD6C);
AT(PlayerStats, stat3, 0xD8C); AT(PlayerStats, timerD90, 0xD90); AT(PlayerStats, timerD94, 0xD94);
AT(PlayerStats, stat2, 0xD98); AT(PlayerStats, fD9C, 0xD9C); AT(PlayerStats, soulsLifetime, 0xDA0);
AT(PlayerStats, soulsWallet, 0xDA4); AT(PlayerStats, levels, 0xDA8); AT(PlayerStats, unkEFC, 0xEFC);
AT(PlayerObj, unkD4, 0xD4); AT(PlayerObj, modeEC, 0xEC); AT(PlayerObj, angleFC, 0xFC);
AT(PlayerObj, angle108, 0x108); AT(PlayerObj, f10C, 0x10C); AT(PlayerObj, anim128, 0x128);
AT(PlayerObj, anim12C, 0x12C); AT(PlayerObj, timer130, 0x130); AT(PlayerObj, timer134, 0x134);
AT(PlayerObj, flags, 0x150); AT(PlayerObj, unkFD8, 0xFD8);
AT(BackgroundJob, func, 0x18); AT(SessionSlot, scale, 4);
typedef char chk_slot_size[sizeof(SessionSlot) == 0xF0 ? 1 : -1];
