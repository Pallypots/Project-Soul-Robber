/* Area m1, file 33: actor input step (kept apart so cl does not inline its callees). Names inferred. */
#include <stdint.h>

typedef struct M1ActIn {
    uint8_t  unk000[0xD4];
    int32_t  modeD4;           /* +0x0D4 */
    uint8_t  unk0D8[0x150 - 0xD8];
    uint32_t flags150;         /* +0x150 */
} M1ActIn;
void sub_000CC4D0(M1ActIn *o);                    /* regargs: o=EAX */
void m1_RunHandlerCDA00(M1ActIn *o, uint32_t a, uint32_t b);
void m1_ReactButtonsCC8C0(M1ActIn *o, uint32_t buttons);
void sub_000CD930(M1ActIn *o, uint32_t a);        /* regargs: o=ESI a=ECX */
void sub_000CBAF0(M1ActIn *o);
void sub_000CCDD0(M1ActIn *o);                    /* regargs: o=ESI */

/* 0x000CDA50: per-frame input step for an actor that is not busy (flags 0x282004)
 * and not in mode 2, 4 or 5. */
void m1_InputStepCDA50(M1ActIn *o, uint32_t a, uint32_t b)
{
    if (o->flags150 & 0x282004)
        return;
    if (o->modeD4 == 2 || o->modeD4 == 4 || o->modeD4 == 5)
        return;
    sub_000CC4D0(o);
    m1_RunHandlerCDA00(o, a, b);
    m1_ReactButtonsCC8C0(o, a);
    sub_000CD930(o, a);
    sub_000CBAF0(o);
    sub_000CCDD0(o);
}
