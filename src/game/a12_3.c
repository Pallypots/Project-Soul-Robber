/* Area a12, group 3: global state queries. Names inferred. */
#include "a12.h"

/* state 0 -> 0, 3 -> 1, other -> 2 (global 0x0037C544). */
int a12_Level_37C544(void) { if (a12_state37C544 == 0) return 0; return (a12_state37C544 != 3) + 1; }
/* state 0 -> 0, 3 -> 1, other -> 2 (global 0x0037D434). */
int a12_Level_37D434(void) { if (a12_state37D434 == 0) return 0; return (a12_state37D434 != 3) + 1; }
/* state 0 -> 0, 3 -> 1, other -> 2 (global 0x0037DAA4). */
int a12_Level_37DAA4(void) { if (a12_state37DAA4 == 0) return 0; return (a12_state37DAA4 != 3) + 1; }
/* state 0 -> 0, 3 -> 1, other -> 2 (global 0x0037DC28). */
int a12_Level_37DC28(void) { if (a12_state37DC28 == 0) return 0; return (a12_state37DC28 != 3) + 1; }
/* state 0 -> 0, 3 -> 1, other -> 2 (global 0x0037DCFC). */
int a12_Level_37DCFC(void) { if (a12_state37DCFC == 0) return 0; return (a12_state37DCFC != 3) + 1; }
/* state 0 -> 0, 3 -> 1, other -> 2 (global 0x0037ED04). */
int a12_Level_37ED04(void) { if (a12_state37ED04 == 0) return 0; return (a12_state37ED04 != 3) + 1; }
/* state 0 -> 0, 3 -> 1, other -> 2 (global 0x0037E094). */
int a12_Level_37E094(void) { if (a12_state37E094 == 0) return 0; return (a12_state37E094 != 3) + 1; }
/* state 0 -> 0, 3 -> 1, other -> 2 (global 0x0037EECC). */
int a12_Level_37EECC(void) { if (a12_state37EECC == 0) return 0; return (a12_state37EECC != 3) + 1; }
/* 0x00026640 */ float a12_GetFloat37DC54(void) { return a12_float37DC54; }
/* 0x00026650 */ int16_t a12_GetWord37EEBC(void) { return a12_word37EEBC; }
/* 0x00026760: bit 0 of flags byte. */ int a12_FlagBit0(void) { return a12_flags37F0C8 & 1; }
/* 0x00026770: bit 1 of flags byte. */ int a12_FlagBit1(void) { return (a12_flags37F0C8 >> 1) & 1; }
/* 0x00026780: either of two flag bytes has bit 1. */
int a12_AnyBit1(void) { if (a12_flags37F550 & 2) return 1; if (a12_flags37F7F4 & 2) return 1; return 0; }
