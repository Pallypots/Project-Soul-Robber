/* Area m1, file 40: Jack per-frame item/target update. Names inferred. */
#include <stdint.h>

typedef struct M1JackT {
    uint8_t  unk000[0x150];
    uint32_t flags150;         /* +0x150, 0x10000000 = busy */
    uint8_t  unk154[0x318 - 0x154];
    int32_t  count318;         /* +0x318 */
    uint8_t  unk31C[0x3A8 - 0x31C];
    int32_t  kind3A8[0x20];    /* +0x3A8 */
    int32_t  a428[0x20];       /* +0x428 */
    int32_t  a4A8[0x20];       /* +0x4A8 */
    int32_t  order528[0x20];   /* +0x528 */
    uint8_t  b5A8;             /* +0x5A8 bit 0: add an entry this frame */
} M1JackT;
void  sub_000CB340(M1JackT *p);
void *m1_FindFirstEDB10(int k);
void *sub_000EDB90(void);
void  sub_000CB390(M1JackT *p, void *it);
void  m1_ApplyActiveCC030(M1JackT *p);
void  sub_000CB490(M1JackT *p);
void  sub_000CB540(M1JackT *p);
void  sub_000CB640(M1JackT *p);
void  sub_0003AF70(void);
void  sub_000CC180(M1JackT *p);

/* 0x000CC2A0: per-frame update: unless busy, offers every filter-0 item to 0xCB390;
 * applies active entries; unless busy, appends an entry of kind 1 when requested;
 * then the remaining per-frame steps. */
void m1_JackFrameCC2A0(M1JackT *p)
{
    void *it;
    int i;
    sub_000CB340(p);
    if (!(p->flags150 & 0x10000000)) {
        for (it = m1_FindFirstEDB10(0); it != 0; it = sub_000EDB90())
            sub_000CB390(p, it);
    }
    m1_ApplyActiveCC030(p);
    if (!(p->flags150 & 0x10000000) && (p->b5A8 & 1)) {
        i = p->count318;
        p->order528[i] = i;
        p->a428[i] = 0;
        p->kind3A8[i] = 1;
        p->a4A8[i] = 0;
        p->count318++;
    }
    sub_000CB490(p);
    sub_000CB540(p);
    sub_000CB640(p);
    sub_0003AF70();
    sub_000CC180(p);
}
