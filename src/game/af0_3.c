/* Area af0, group 3: state accessors 0x000DF960..0x000DFE80. Names inferred. */
#include "af0.h"

/* 0x000DF960: get 0x3EDD18. */ int  af0_GetVar3EDD18(void)  { return af0_var3EDD18; }
/* 0x000DF9B0: set 0x3EDD1C. */ void af0_SetVar3EDD1C(int v) { af0_var3EDD1C = v; }
/* 0x000DFC80: set state 0x3F0734 to 4. */
int af0_SetState4(void) { af0_var3F0734 = 4; return 0; }
/* 0x000DFD00: get 0x3F0738. */ int  af0_GetVar3F0738(void)  { return af0_var3F0738; }
/* 0x000DFD10: set 0x3F0738. */ void af0_SetVar3F0738(int v) { af0_var3F0738 = v; }
/* 0x000DFD20: get 0x3F073C. */ int  af0_GetVar3F073C(void)  { return af0_var3F073C; }
/* 0x000DFD30: set 0x3F073C. */ void af0_SetVar3F073C(int v) { af0_var3F073C = v; }
/* 0x000DFDF0: get 0x3EE6AC. */ int  af0_GetVar3EE6AC(void)  { return af0_var3EE6AC; }
/* 0x000DFE00: get 0x3EE6C0. */ int  af0_GetVar3EE6C0(void)  { return af0_var3EE6C0; }
/* 0x000DFE10: clear 0x3EE6C0. */ void af0_ClearVar3EE6C0(void){ af0_var3EE6C0 = 0; }
/* 0x000DFE20: set 0x3EE6AC. */ void af0_SetVar3EE6AC(int v) { af0_var3EE6AC = v; }
/* 0x000DFE60: pass 0x3EE6A8 to 0x0003FC10. */
void af0_Release3EE6A8(void) { sub_0003FC10(&af0_var3EE6A8); }
/* 0x000DFE70: get 0x3EE6A8. */ int  af0_GetVar3EE6A8(void)  { return af0_var3EE6A8; }
/* 0x000DFE80: set 0x3EE6A8. */ void af0_SetVar3EE6A8(int v) { af0_var3EE6A8 = v; }
