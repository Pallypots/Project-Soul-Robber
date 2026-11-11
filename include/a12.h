#ifndef A12_H
#define A12_H
#include "oogie.h"
#include "shared_decls.h"

/* Render-state style callbacks: (owner, unused, out-record) -> 0. */
typedef struct A12StateOut {
    int32_t  value;         /* +0x00 */
    uint32_t flags;         /* +0x04 */
    uint8_t  unk08[8];
    int32_t  a;             /* +0x10 */
    int32_t  b;             /* +0x14 */
    int32_t  c;             /* +0x18 */
    int32_t  d;             /* +0x1C */
} A12StateOut;

typedef struct A12Owner {
    uint8_t  unk000[0x44];
    int32_t  handle;        /* +0x44 */
    uint8_t  unk048[0x14C - 0x48];
    int32_t  mode;          /* +0x14C */
} A12Owner;

typedef struct A12Res {
    uint8_t  unk00[0x28];
    int32_t  r28;           /* +0x28 */
    int32_t  r2C;           /* +0x2C */
} A12Res;

typedef struct A12Actor {
    uint8_t  unk00[0xD0];
    int32_t  kind;          /* +0xD0 */
} A12Actor;

typedef struct A12Table {
    int32_t  count;         /* +0x00 */
    int32_t  unk04;
    uint8_t *entries;       /* +0x08, 0x150-byte records */
} A12Table;

typedef struct A12Node {
    int32_t  id;            /* +0x00 */
    uint8_t  unk04[0x38];
    struct A12Node *next;   /* +0x3C */
} A12Node;

void sub_0001C160(void *ctx, A12Actor *a);
void sub_0001BEE0(void *ctx, A12Actor *a);

extern int32_t a12_state37C544, a12_state37D434, a12_state37DAA4, a12_state37DC28,
               a12_state37DCFC, a12_state37ED04, a12_state37E094, a12_state37EECC;
extern float   a12_float37DC54;
extern int16_t a12_word37EEBC;
extern uint8_t a12_flags37F0C8, a12_flags37F550, a12_flags37F7F4;
#endif
