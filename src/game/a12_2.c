/* Area a12, group 2: render-state setup callbacks (owner, unused, out). Names inferred. */
#include "a12.h"

/* 0x0001DB10..0x0001DB30: set out value. */
int a12_SetValue0(A12Owner *o, void *u, A12StateOut *s) { s->value = 0; return 0; }
int a12_SetValue1(A12Owner *o, void *u, A12StateOut *s) { s->value = 1; return 0; }
int a12_SetValue2(A12Owner *o, void *u, A12StateOut *s) { s->value = 2; return 0; }

/* 0x0001DCF0: flag 1 and set two words in the owner's resource. */
int a12_SetupRes(A12Owner *o, void *u, A12StateOut *s)
{
    A12Res *r;
    s->flags |= 1;
    r = sub_001B9650(o->handle);
    r->r28 = 0x4000;
    r->r2C = 0x2000001C;
    return 0;
}
/* 0x0001DD20: set flag bits 2. */
int a12_Flags_1DD20(A12Owner *o, void *u, A12StateOut *s) { s->flags |= 2; return 0; }
/* 0x0001DD30: set flag bits 4. */
int a12_Flags_1DD30(A12Owner *o, void *u, A12StateOut *s) { s->flags |= 4; return 0; }
/* 0x0001DD40: set flag bits 8. */
int a12_Flags_1DD40(A12Owner *o, void *u, A12StateOut *s) { s->flags |= 8; return 0; }
/* 0x0001DD50: set flag bits 6. */
int a12_Flags_1DD50(A12Owner *o, void *u, A12StateOut *s) { s->flags |= 6; return 0; }
/* 0x0001DD60: set mode pair. */
int a12_Pair_1DD60(A12Owner *o, void *u, A12StateOut *s) { s->a = 0x48; s->b = 0; return 0; }
/* 0x0001DD80: set mode pair. */
int a12_Pair_1DD80(A12Owner *o, void *u, A12StateOut *s) { s->a = 0x42; s->b = 0; return 0; }
/* 0x0001DDA0: set mode pair. */
int a12_Pair_1DDA0(A12Owner *o, void *u, A12StateOut *s) { s->a = 0xA; s->b = 0; return 0; }
/* 0x0001DDE0: set mode pair. */
int a12_Pair_1DDE0(A12Owner *o, void *u, A12StateOut *s) { s->a = 0x88; s->b = 0; return 0; }
/* 0x0001DDC0: set two mode pairs. */
int a12_Quad_1DDC0(A12Owner *o, void *u, A12StateOut *s) { s->a = 0xA; s->b = 0; s->c = 0x5040D; s->d = 0; return 0; }
/* 0x0001DE00: set two mode pairs. */
int a12_Quad_1DE00(A12Owner *o, void *u, A12StateOut *s) { s->a = 0x88; s->b = 0; s->c = 0x5040D; s->d = 0; return 0; }
/* 0x0001DE20: set two mode pairs. */
int a12_Quad_1DE20(A12Owner *o, void *u, A12StateOut *s) { s->a = 0x44; s->b = 0; s->c = 0x5340D; s->d = 0; return 0; }
/* 0x0001DE40: set two mode pairs. */
int a12_Quad_1DE40(A12Owner *o, void *u, A12StateOut *s) { s->a = 0x48; s->b = 0; s->c = 0x53001; s->d = 0; return 0; }
/* 0x0001DE60: set two mode pairs. */
int a12_Quad_1DE60(A12Owner *o, void *u, A12StateOut *s) { s->a = 0x48; s->b = 0; s->c = 0x5040D; s->d = 0; return 0; }
/* 0x0001DE80: set owner mode. */
int a12_Mode_1DE80(A12Owner *o, void *u, A12StateOut *s) { o->mode = 14; return 0; }
/* 0x0001DEA0: set owner mode. */
int a12_Mode_1DEA0(A12Owner *o, void *u, A12StateOut *s) { o->mode = 12; return 0; }
/* 0x0001DEF0: set owner mode. */
int a12_Mode_1DEF0(A12Owner *o, void *u, A12StateOut *s) { o->mode = 7; return 0; }
/* 0x0001DEC0: set owner mode 12 and pair 0xA8/0x80. */
int a12_Mode_1DEC0(A12Owner *o, void *u, A12StateOut *s) { o->mode = 12; s->a = 0xA8; s->b = 0x80; return 0; }

