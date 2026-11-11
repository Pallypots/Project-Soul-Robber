/* Area a1b, group 3: global setters near 0x00017D30..0x000193C0. Names inferred. */
#include "a1b.h"

/* 0x00017DC0: set value. */
void a1b_SetVal(int32_t v) { a1b_val37B558 = v; }
/* 0x00017DD0: get value. */
int32_t a1b_GetVal(void) { return a1b_val37B558; }
/* 0x00018550: init the shared object. */
void a1b_ObjInit(void) { sub_0003FCE0(&a1b_obj37B560); }
/* 0x00018560: pass a value to the shared object. */
void a1b_ObjPut(void *a) { sub_0003FBD0(a, &a1b_obj37B560); }
/* 0x00018610: release the shared object. */
void a1b_ObjFree(void) { sub_0003FC10(&a1b_obj37B560); }
/* 0x000186A0: set slot i. */
void a1b_SetSlot(int i, int32_t v) { a1b_slots37BEE8[i] = v; }
/* 0x000186B0: get slot i. */
int32_t a1b_GetSlot(int i) { return a1b_slots37BEE8[i]; }

/* 0x00018AE0: reset all six fields. */
void a1b_ResetAll(void)
{
    a1b_i37C048 = 0; a1b_f37C04C = 0.0f; a1b_i37C050 = 0;
    a1b_f37C054 = 0.0f; a1b_f37C058 = 0.0f; a1b_i37C05C = 0;
}
/* 0x00019350: set first pair. */
void a1b_SetPair(int32_t i, float f) { a1b_i37C048 = i; a1b_f37C04C = f; }
/* 0x000193C0: reset all but the first float. */
void a1b_ResetPart(void)
{
    a1b_i37C050 = 0; a1b_f37C054 = 0.0f; a1b_f37C058 = 0.0f;
    a1b_i37C048 = 0; a1b_i37C05C = 0;
}

