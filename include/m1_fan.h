/* Shared types for fan-shaped slot layouts in area m1 (m1_fanTbl2DF0C4 rows of 0x10, slots of 0x14). */
#ifndef M1_FAN_H
#define M1_FAN_H
#include <stdint.h>

typedef struct M1Fan {
    uint8_t  unk00[0xA];
    uint8_t  count;         /* +0x0A  number of slots */
    uint8_t  unk0B;
    float    span;          /* +0x0C  total angle */
} M1Fan;

typedef struct M1FanSlot {
    float    angle;         /* +0x00 */
    uint8_t  unk04[0x10];
} M1FanSlot;

#endif
