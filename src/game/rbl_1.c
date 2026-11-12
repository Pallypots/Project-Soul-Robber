/* Area rbl: event-script opcode handlers. Names inferred. */
#include "rbl.h"

/* 0x000DBEA0: script opcode "channel request". Operands: a channel kind byte (0..9), a
   byte argument and a 32-bit value; the request goes to that channel's setter. Unknown
   kinds are skipped. Always advances 6 operand bytes. Stack arg (c). */
int rbl_ScrChannel0DBEA0(ScriptCtx *c)
{
    switch (c->pc[0]) {
    case 0:
        sub_00023D80(c->pc[1], OP_U32(c->pc + 2));
        break;
    case 1:
        sub_000243B0(c->pc[1], OP_U32(c->pc + 2));
        break;
    case 2:
        sub_00024D30(c->pc[1], OP_U32(c->pc + 2));
        break;
    case 3:
        sub_000251B0(c->pc[1], OP_U32(c->pc + 2));
        break;
    case 4:
        sub_000252A0(c->pc[1], OP_U32(c->pc + 2));
        break;
    case 5:
        sub_000253D0(c->pc[1], OP_U32(c->pc + 2));
        break;
    case 6:
        sub_00025C10(c->pc[1], OP_U32(c->pc + 2));
        break;
    case 7:
        sub_00025D50(c->pc[1], OP_U32(c->pc + 2));
        break;
    case 8:
        sub_00025F50(c->pc[1], OP_U32(c->pc + 2));
        break;
    case 9:
        sub_00025F90(c->pc[1], OP_U32(c->pc + 2));
        break;
    }
    return SCR_NEXT(6);
}

/* 0x000DC700: script opcode "play sound". Operands: a sound group byte (0..0x6C), an
   index byte within the group and a 32-bit parameter. The group selects the first sound
   id of its block; ids below 0x264 are played (0x00048B20) and the handle is kept in the
   thread (+0x58). Always advances 6 operand bytes. Stack arg (t).
   Unknown groups: the original leaves the base uninitialised (cl reused the argument slot,
   so base = the thread pointer value, which is always >= 0x264 and the play is skipped);
   written here as an explicit skip with the same result. */
int rbl_ScrSound0DC700(AdcThread *t)
{
    int base, id;

    switch (t->pc[0]) {
    case 0: base = 0x30; break;
    case 1: base = 0x58; break;
    case 2: base = 0x5D; break;
    case 3: base = 0x79; break;
    case 4: base = 0x86; break;
    case 5: base = 0x8A; break;
    case 6: base = 0x8B; break;
    case 7: base = 0x8D; break;
    case 8: base = 0x92; break;
    case 9: base = 0x93; break;
    case 10: base = 0x94; break;
    case 11: base = 0x95; break;
    case 12: base = 0x9C; break;
    case 13: base = 0x9D; break;
    case 14: base = 0x9E; break;
    case 15: base = 0x9F; break;
    case 16: base = 0xA0; break;
    case 17: base = 0xA1; break;
    case 18: base = 0xA2; break;
    case 19: base = 0xA3; break;
    case 20: base = 0xA5; break;
    case 21: base = 0xA6; break;
    case 22: base = 0xA7; break;
    case 23: base = 0xAB; break;
    case 24: base = 0xAC; break;
    case 25: base = 0xAD; break;
    case 26: base = 0xAF; break;
    case 27: base = 0xB3; break;
    case 28: base = 0xBB; break;
    case 29: base = 0xD4; break;
    case 30: base = 0xD5; break;
    case 31: base = 0xD6; break;
    case 32: base = 0xD7; break;
    case 33: base = 0xDB; break;
    case 34: base = 0xDC; break;
    case 35: base = 0xE0; break;
    case 36: base = 0xE1; break;
    case 37: base = 0xE2; break;
    case 38: base = 0xE3; break;
    case 39: base = 0xE7; break;
    case 40: base = 0xE8; break;
    case 41: base = 0xE9; break;
    case 42: base = 0xEA; break;
    case 43: base = 0xEB; break;
    case 44: base = 0xEC; break;
    case 45: base = 0xF0; break;
    case 46: base = 0xF5; break;
    case 47: base = 0xF9; break;
    case 48: base = 0xFA; break;
    case 49: base = 0xFB; break;
    case 50: base = 0xFC; break;
    case 51: base = 0xFD; break;
    case 52: base = 0xFE; break;
    case 53: base = 0xFF; break;
    case 54: base = 0x100; break;
    case 55: base = 0x101; break;
    case 56: base = 0x102; break;
    case 57: base = 0x103; break;
    case 58: base = 0x104; break;
    case 59: base = 0x105; break;
    case 60: base = 0x106; break;
    case 61: base = 0x107; break;
    case 62: base = 0x108; break;
    case 63: base = 0x10C; break;
    case 64: base = 0x10D; break;
    case 65: base = 0x111; break;
    case 66: base = 0x112; break;
    case 67: base = 0x116; break;
    case 68: base = 0x117; break;
    case 69: base = 0x118; break;
    case 70: base = 0x119; break;
    case 71: base = 0x11A; break;
    case 72: base = 0x11E; break;
    case 73: base = 0x11F; break;
    case 74: base = 0x120; break;
    case 75: base = 0x124; break;
    case 76: base = 0x125; break;
    case 77: base = 0x128; break;
    case 78: base = 0x12E; break;
    case 79: base = 0x12F; break;
    case 80: base = 0x130; break;
    case 81: base = 0x131; break;
    case 82: base = 0x132; break;
    case 83: base = 0x136; break;
    case 84: base = 0x137; break;
    case 85: base = 0x138; break;
    case 86: base = 0x139; break;
    case 87: base = 0x13A; break;
    case 88: base = 0x13E; break;
    case 89: base = 0x13F; break;
    case 90: base = 0x140; break;
    case 91: base = 0x141; break;
    case 92: base = 0x142; break;
    case 93: base = 0x143; break;
    case 94: base = 0x146; break;
    case 95: base = 0x147; break;
    case 96: base = 0x148; break;
    case 97: base = 0x149; break;
    case 98: base = 0x14D; break;
    case 99: base = 0x14E; break;
    case 100: base = 0x14F; break;
    case 101: base = 0x150; break;
    case 102: base = 0x151; break;
    case 103: base = 0x155; break;
    case 104: base = 0x156; break;
    case 105: base = 0x157; break;
    case 106: base = 0x17B; break;
    case 107: base = 0x183; break;
    case 108: base = 0x1A6; break;
    default:
        return SCR_NEXT(6);
    }
    id = base + t->pc[1];
    if (id < 0x264)
        t->unk58 = sub_00048B20(id, OP_U32(t->pc + 2));
    return SCR_NEXT(6);
}
