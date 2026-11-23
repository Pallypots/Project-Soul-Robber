/* Shared types for the player object (abc_player, 0x41FEC0) in area m1. */
#ifndef M1_PLAYER_H
#define M1_PLAYER_H
#include <stdint.h>

typedef struct M1Player {
    uint8_t  unk000[0x150];
    uint32_t stateFlags;    /* +0x150  bit 0x800 = locked (no slot actions) */
} M1Player;

#endif
