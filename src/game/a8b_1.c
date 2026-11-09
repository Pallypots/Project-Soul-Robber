/* Area a8b, group 1: demo event leaf helpers (0x8A210-0x8B0D0). Names inferred. */
#include "a8b.h"

/* 0x0008A210: descriptor for event type at 0x2E0A48. */
uint8_t *a8b_Desc2E0A48(void) { return a8b_desc2E0A48; }
/* 0x0008A5C0: descriptor at 0x2E0B48. */
uint8_t *a8b_Desc2E0B48(void) { return a8b_desc2E0B48; }
/* 0x0008A600: descriptor at 0x2E0BC0. */
uint8_t *a8b_Desc2E0BC0(void) { return a8b_desc2E0BC0; }
/* 0x0008A980: descriptor at 0x2E0C38. */
uint8_t *a8b_Desc2E0C38(void) { return a8b_desc2E0C38; }
/* 0x0008AB30: descriptor at 0x2E0CD8. */
uint8_t *a8b_Desc2E0CD8(void) { return a8b_desc2E0CD8; }

/* 0x0008A420: reset work ints 0x10..0x18 to -1; -1 if no work. */
int a8b_ResetWork3(A8bObj *o)
{
    A8bWork *w = o->work1C;
    if (w == 0) return -1;
    w->v10.i[0] = -1; w->v10.i[1] = -1; w->v10.i[2] = -1;
    return 0;
}
/* 0x0008A4B0: 0 if the object has work, else -1. */
int a8b_HasWork(A8bObj *o) { return (o->work1C != 0) - 1; }

/* 0x0008A4F0: set work floats 0x10/0x14 to 1 and 0x18 to 0. */
int a8b_WorkSetScale(A8bObj *o)
{
    A8bWork *w = o->work1C;
    w->v10.f[0] = 1.0f; w->v10.f[1] = 1.0f; w->v10.f[2] = 0.0f;
    return 0;
}
/* 0x0008A5D0: copy work flag 0x10 into target's shown bit. */
int a8b_SyncShown(A8bObj *o)
{
    A8bWork *w = o->work1C;
    A8bObj *t = w->target08;
    if (t) {
        if (w->v10.i[0]) t->flags24 |= 1;
        else t->flags24 &= ~1u;
    }
    return 0;
}
/* 0x0008A990: reset work ints 0x10..0x18 and 0x20 to -1. */
int a8b_ResetWork4(A8bObj *o)
{
    A8bWork *w = o->work1C;
    if (w == 0) return -1;
    w->v10.i[0] = -1; w->v10.i[1] = -1; w->v10.i[2] = -1; w->i20 = -1;
    return 0;
}
/* 0x0008AA80: reset work ints 0x10..0x18 to -1 (no null check). */
int a8b_ResetWork3NoCheck(A8bObj *o)
{
    A8bWork *w = o->work1C;
    w->v10.i[0] = -1; w->v10.i[1] = -1; w->v10.i[2] = -1;
    return 0;
}
/* 0x0008AEB0: set target's shown bit. */
int a8b_ShowTarget(A8bObj *o)
{
    A8bObj *t = o->work1C->target08;
    if (t) t->flags24 |= 1;
    return 0;
}
/* 0x0008AF60: clear target's shown bit. */
int a8b_HideTarget(A8bObj *o)
{
    A8bObj *t = o->work1C->target08;
    if (t) t->flags24 &= ~1u;
    return 0;
}
/* 0x0008AF80: address of record i (0x24 bytes) in type t's descriptor. */
uint8_t *a8b_DescRecord(int t, int i) { return a8b_descGetters[t]() + i * 0x24; }
/* 0x0008AFA0: work target if it is active (flag bit 1), else 0. */
A8bObj *a8b_GetActiveTarget(A8bObj *o)
{
    A8bObj *t = o->work1C->target08;
    if (t && !(t->flags18 & 2)) return 0;
    return t;
}
/* 0x0008AFC0: active flag (bit 1) of an object. */
int a8b_IsActive(A8bObj *o) { return (o->flags18 >> 1) & 1; }
/* 0x0008B0C0: get the work block. */
A8bWork *a8b_GetWork(A8bObj *o) { return o->work1C; }
/* 0x0008B0D0: work kind byte. */
int a8b_GetWorkKind(A8bObj *o) { return o->work1C->kind04; }
/* 0x0008C480: increment an object's reference count. */
void a8b_RefInc(A8bObj *o) { o->ref23++; }
/* 0x0008C490: decrement an object's reference count, not below 0. */
void a8b_RefDec(A8bObj *o) { if (o->ref23) o->ref23--; }
/* 0x0008BBB0: descriptor at 0x2E0DB8. */
uint8_t *a8b_Desc2E0DB8(void) { return a8b_desc2E0DB8; }
/* 0x0008BBF0: descriptor at 0x2E0E30. */
uint8_t *a8b_Desc2E0E30(void) { return a8b_desc2E0E30; }
/* 0x0008BC00: descriptor at 0x2E0EA0. */
uint8_t *a8b_Desc2E0EA0(void) { return a8b_desc2E0EA0; }
/* 0x0008BDB0: descriptor at 0x2E1000. */
uint8_t *a8b_Desc2E1000(void) { return a8b_desc2E1000; }
/* 0x0008BE70: descriptor at 0x2E1078. */
uint8_t *a8b_Desc2E1078(void) { return a8b_desc2E1078; }
/* 0x0008BF60: descriptor at 0x27001C. */
uint8_t *a8b_Desc27001C(void) { return a8b_desc27001C; }
/* 0x0008BC10: set work flag 0x10. */
int a8b_WorkSetFlag(A8bObj *o) { o->work1C->v10.i[0] = 1; return 0; }
/* 0x0008BCF0: store a value in slot i. */
void a8b_SetSlot(int i, int32_t v) { a8b_slots428EE0[i] = v; }
/* 0x0008BD00: read slot i. */
int32_t a8b_GetSlot(int i) { return a8b_slots428EE0[i]; }
/* 0x0008CD50: clear the global at 0x3ED528. */
void a8b_ClearG3ED528(void) { a8b_g3ED528 = 0; }
/* 0x0008CD60: read the global at 0x3ED528. */
int32_t sub_0008CD60(void) { return a8b_g3ED528; }
/* 0x0008CD70: bit 2 of the first byte. */
int a8b_TestBit2(const uint8_t *p) { return (*p >> 2) & 1; }
/* 0x0008CD80: set bits 0 and 1 of the first word. */
void a8b_SetBits01(uint32_t *p) { *p |= 3; }
/* 0x0008CD90: signed byte at +4. */
int a8b_GetByte04(const int8_t *p) { return p[4]; }
/* 0x0008CDA0: field 4 of the sub-record at +0x0C, or -1. */
typedef struct A8bRec { int32_t x00; int32_t x04; } A8bRec;
int a8b_GetSubX04(A8bRec **p) { A8bRec *r = p[3]; if (r == 0) return -1; return r->x04; }
