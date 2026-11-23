/* Shared types for the area m1 player bone/attachment slots (m1_ents41C7C0, stride 0x54). */
#ifndef M1_SLOTS_H
#define M1_SLOTS_H
#include <stdint.h>

typedef struct M1BoneSlot {
    uint32_t flags;         /* +0x00  bit 2 = hidden */
    uint8_t  unk04[0x10 - 0x04];
    int32_t  frame;         /* +0x10 */
    uint8_t  unk14[0x1C - 0x14];
    float    blend;         /* +0x1C */
    uint8_t  unk20[0x28 - 0x20];
    int32_t  bone;          /* +0x28 */
    uint8_t  unk2C[0x54 - 0x2C];
} M1BoneSlot;

#endif
