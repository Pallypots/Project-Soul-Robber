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

typedef struct M2Cls18 { uint8_t unk00[4]; int32_t kind4; int32_t sub8; } M2Cls18;

/* 0x1BC40: map a (kind, sub-kind) pair to its class number (0 when unknown). */
int m2_Classify1BC40(M2Cls18 *r) {
    switch (r->kind4) {
    case 1: return 3;
    case 2:
        switch (r->sub8) {
        case 0: case 1: case 6: case 7: case 14: return 4;
        case 2: case 3: case 4: case 16: return 5;
        case 5: case 15: return 14;
        case 11: case 12: case 13: return 6;
        }
        return 0;
    case 3: {
        int volatile b = r->sub8;
        if (b == 2) return 0;
        if (b > 2 && b <= 5) return 9;
        return 8;
    }
    case 4:
        switch (r->sub8) {
        case 2: case 3: case 4: case 7: case 9: case 10: return 0;
        case 5: case 6: return 11;
        case 22: return 12;
        case 29: case 30: case 31: return 7;
        }
        return 13;
    case 5:
        switch (r->sub8) {
        case 1: case 2: case 3: case 27: return 11;
        case 19: return 7;
        case 24: return 2;
        }
        return 0;
    case 6: return 8;
    case 7: return r->sub8 ? 10 : 0;
    case 8: case 9: return 7;
    }
    return 0;
}

extern uint32_t r1b_state37DC28;
extern int32_t m2_g37DC2C, m2_g37DC30, m2_g37DC34;
extern int32_t r1b_armed37DC48;
extern float a12_float37DC54;

/* 0x251B0: menu state command: 0 backs out of states 3-4 to state 2, 1 enters state 1, 2 enters state 4, 3 enters state 5, 4 returns from state 4 to state 3, 5 sets the float value v; entering a state resets its step fields and the armed flag. */
void m2_MenuCmd251B0(int cmd, int v) {
    switch (cmd) {
    case 0: {
        uint32_t volatile s = r1b_state37DC28;
        if (s < 3 || s > 4) return;
        r1b_state37DC28 = 2; m2_g37DC2C = 0; r1b_armed37DC48 = 0;
        return;
    }
    case 1:
        r1b_state37DC28 = 1; m2_g37DC2C = 3; m2_g37DC30 = 2; m2_g37DC34 = 0; r1b_armed37DC48 = 0;
        return;
    case 2:
        r1b_state37DC28 = 4;
        goto step2;
    case 3:
        r1b_state37DC28 = 5; m2_g37DC2C = 6; m2_g37DC30 = 0; r1b_armed37DC48 = 0;
        return;
    case 4:
        if (r1b_state37DC28 != 4) return;
        r1b_state37DC28 = 3;
    step2:
        m2_g37DC2C = 2; m2_g37DC30 = 0; r1b_armed37DC48 = 0;
        return;
    case 5:
        a12_float37DC54 = (float)v;
        return;
    }
}
