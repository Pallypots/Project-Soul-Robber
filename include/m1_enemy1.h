/* State block of the FIRST enemy type (M1EnemyAi.st for that type; its layout differs from M1Enemy2State). */
#ifndef M1_ENEMY1_H
#define M1_ENEMY1_H
#include <stdint.h>

typedef struct M1Enemy1State {
    uint8_t  unk00[4];
    uint32_t aiFlags;       /* +0x04  bit 15 = forced attack, bit 28 = keep distance */
    union {                 /* +0x08  bit 0 = can counter, bit 7 = counter from the left */
        uint32_t reactFlags;
        int8_t   reactByte;
    };
    uint8_t  unk0C[0x74 - 0x0C];
    float    aimDist;       /* +0x74 */
    float    aimAngle;      /* +0x78 */
} M1Enemy1State;

#endif
