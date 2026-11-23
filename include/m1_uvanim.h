/* Shared types for texture-UV animations in area m1 (linked lists such as 0x3E6978 and 0x3E6988). */
#ifndef M1_UVANIM_H
#define M1_UVANIM_H
#include <stdint.h>

/* One UV key: how long it lasts, then the UV data handed to the model. */
typedef struct M1UvKey {
    float    dur;           /* +0x00 */
    float    uv[3];         /* +0x04 */
} M1UvKey;

typedef struct M1UvSeq {
    int32_t  unk0;
    int32_t  count;         /* +0x04 */
    uint8_t  unk08[8];
    M1UvKey  keys[1];       /* +0x10 */
} M1UvSeq;

/* A running UV animation (list node). */
typedef struct M1UvAnim {
    struct M1UvAnim *next;  /* +0x00 */
    uint8_t  unk04[8];
    int32_t  model;         /* +0x0C */
    M1UvSeq *seq;           /* +0x10 */
    int32_t  part;          /* +0x14 */
    int32_t  key;           /* +0x18 */
    float    time;          /* +0x1C */
} M1UvAnim;

#endif
