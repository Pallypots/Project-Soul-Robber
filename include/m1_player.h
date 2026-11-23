/* Shared types for the player object (abc_player, 0x41FEC0) in area m1. */
#ifndef M1_PLAYER_H
#define M1_PLAYER_H
#include <stdint.h>

typedef struct M1Player {
    uint8_t  unk000[0xD4];
    int32_t  mode;          /* +0xD4  4/5 = special moves handled by 0xBD770 */
    int32_t  action;        /* +0xD8  index into the mode's handler table */
    uint8_t  unk0DC[0x150 - 0xDC];
    uint32_t stateFlags;    /* +0x150  bit 0x800 = locked (no slot actions) */
    uint8_t  unk154[0x1B8 - 0x154];
    int32_t  costumeSet;    /* +0x1B8  which handler table set (0..2) */
    uint8_t  unk1BC[0xE04 - 0x1BC];
    int32_t  soulPoints;    /* +0xE04 */
} M1Player;

#endif
