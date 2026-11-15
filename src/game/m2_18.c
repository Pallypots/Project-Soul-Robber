/* Area m2, file 18. Names inferred. */
#include <stdint.h>

typedef struct M2Body18 { uint8_t unk00[0x10]; uint32_t flags10; } M2Body18;
typedef struct M2Ent18 { uint32_t flags0; int32_t kind4; uint8_t unk08[0x118]; M2Body18 *body120; uint8_t unk124[0x13C]; } M2Ent18;
extern M2Ent18 aab_slots[32];
int Stats_HasEFC(void);

/* 0x95010: toggle the solid bit of the active doors: with the item (count > 0) kinds 0x1D/0x52 open (bit cleared) and kinds 0x50/0xFB close (bit set); without it the other way round. */
void m2_DoorSync95010(void) {
    int i;
    if (Stats_HasEFC() > 0) {
        for (i = 0; i < 32; i++) {
            M2Ent18 *e = &aab_slots[i];
            if (!(e->flags0 & 1)) continue;
            switch (e->kind4) {
            case 0x1D: case 0x52: e->body120->flags10 &= ~1u; break;
            case 0x50: case 0xFB: e->body120->flags10 |= 1; break;
            }
        }
    } else {
        for (i = 0; i < 32; i++) {
            M2Ent18 *e = &aab_slots[i];
            if (!(e->flags0 & 1)) continue;
            switch (e->kind4) {
            case 0x1D: case 0x52: e->body120->flags10 |= 1; break;
            case 0x50: case 0xFB: e->body120->flags10 &= ~1u; break;
            }
        }
    }
}
