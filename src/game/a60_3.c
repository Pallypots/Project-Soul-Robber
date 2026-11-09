/* Area a60, group 3: 0x00072000..0x00076FFF. Names inferred. */
#include "a60.h"

/* 0x000720A0: step a float by one frame, down if bit 0 of dir is clear, up if set. */
void a60_StepByFrame(float *v, int dir)
{
    if (dir & 1)
        *v += a50_frameUnits;
    else
        *v -= a50_frameUnits;
}

/* 0x00072EB0: store an unsigned 24-bit count as the timer value (asserts range). */
void a60_TimerSetCount(A60Timer *t, uint32_t n)
{
    if (n >= 0x1000000) for (;;) ;
    t->value = (float)n;
}

/* 0x00072FA0: timer kind. */
int16_t a60_TimerKind(A60Timer *t) { return t->kind; }

/* 0x00072FB0: clear five handles. */
void a60_Clear72FB0(void)
{
    a60_h3E694C[0] = a60_h3E694C[1] = -1;
    a60_h3E6940[0] = a60_h3E6940[1] = a60_h3E6940[2] = -1;
}

/* 0x00072FD0: release five handles. */
void a60_Release72FD0(void)
{
    int i;
    for (i = 0; i < 2; i++)
        if (a60_h3E694C[i] != -1) { sub_001B9FC0(a60_h3E694C[i]); a60_h3E694C[i] = -1; }
    for (i = 0; i < 3; i++)
        if (a60_h3E6940[i] != -1) { sub_001B9FC0(a60_h3E6940[i]); a60_h3E6940[i] = -1; }
}

/* 0x00074700: phase dispatch (0..2); otherwise return the argument. */
int a60_Dispatch74700(int a)
{
    switch (a60_phase428F81) {
    case 0: return sub_00073030(a);
    case 1: return sub_00073660(a);
    case 2: return sub_00073A50(a);
    }
    return a;
}

/* 0x00074DB0: phase dispatch (0..2). */
void a60_Dispatch74DB0(void)
{
    switch (a60_phase428F81) {
    case 0: sub_00074730(); break;
    case 1: sub_00073C80(); break;
    case 2: sub_00073FC0(); break;
    }
}

/* 0x00074DE0: init list 0x003E6994. */
void a60_InitList6994(void) { sub_0003D860(a60_list3E6994); }

/* 0x00074F10: remove and free the node keyed by obj from list 0x003E6994. */
void a60_Remove6994(void *obj)
{
    void *n;
    if (obj == 0) for (;;) ;
    n = sub_0003DBC0(a60_list3E6994, 0, obj);
    if (n) {
        sub_0003D8C0(n);
        sub_00053880(n);
    }
}

/* 0x00075140: init list 0x003E6984. */
void a60_InitList6984(void) { sub_0003D860(a60_list3E6984); }

/* 0x00075410: init list 0x003E6974. */
void a60_InitList6974(void) { sub_0003D860(a60_list3E6974); }

/* 0x000754A0: for a type-9 object, remove its node from list 0x003E6974 and release its handle. */
void a60_Remove6974(A60Obj *obj)
{
    A60Node *n;
    if (obj == 0) for (;;) ;
    if (obj->type != 9)
        return;
    n = (A60Node *)sub_0003DBC0(a60_list3E6974, 0, obj);
    if (n) {
        sub_0003D8C0(n);
        sub_001B9FC0(n->handle);
        sub_00053880(n);
    }
}

/* 0x00075EF0: point at the default glyph table. */
void a60_SetDefaultTable(void) { a60_table3E69A4 = a60_table266AD8; }

/* 0x00075FC0: set flag bits. */
void a60_FlagsSet(uint32_t *f, uint32_t bits)
{
    if (f == 0) for (;;) ;
    *f |= bits;
}

/* 0x00075FE0: clear flag bits. */
void a60_FlagsClear(uint32_t *f, uint32_t bits)
{
    if (f == 0) for (;;) ;
    *f &= ~bits;
}

/* 0x00076000: set or clear bit 0. */
void a60_FlagBit1(uint32_t *f, int on)
{
    if (f == 0) for (;;) ;
    if (on) *f |= 1; else *f &= ~1u;
}

/* 0x00076020: set or clear bit 1. */
void a60_FlagBit2(uint32_t *f, int on)
{
    if (f == 0) for (;;) ;
    if (on) *f |= 2; else *f &= ~2u;
}

/* 0x00076040: set or clear bit 3. */
void a60_FlagBit8(uint32_t *f, int on)
{
    if (f == 0) for (;;) ;
    if (on) *f |= 8; else *f &= ~8u;
}

/* 0x00076060: empty the text buffer. */
void a60_TextClear(A60Text *t)
{
    t->len = 0;
    t->buf[0] = 0;
    t->pos = 0;
}

/* 0x00076080: set the first corner. */
void a60_RectSet0(A60Rect *r, int16_t x, int16_t y) { r->x0 = x; r->y0 = y; }

/* 0x000760A0: set the second corner. */
void a60_RectSet1(A60Rect *r, int16_t x, int16_t y) { r->x1 = x; r->y1 = y; }

/* 0x00075150: attach a 0x20-byte effect node to a type 1/5 object (type 9 hangs). */
void a60_AttachEff6984(A60Obj *obj, int a, int b)
{
    A60EffNode20 *n;
    if (obj == 0) for (;;) ;
    switch (obj->type) {
    case 1:
    case 5:
        n = (A60EffNode20 *)sub_00053AB0(0x20, a60_srcTexEx, 0x191);
        sub_0003D860(n);
        n->a10 = b;
        n->a18 = 0;
        n->t1C = 0.0f;
        n->a14 = a;
        n->obj = obj;
        sub_0003D880(a60_list3E6984, n);
        break;
    case 9:
        for (;;) ;
    }
}

/* 0x000751C0: detach and free every effect node of a type 1/5 object. */
void a60_DetachEff6984(A60Obj *obj)
{
    A60Node *n, *next;
    if (obj == 0) for (;;) ;
    switch (obj->type) {
    case 1:
    case 5:
        n = (A60Node *)sub_0003DBC0(a60_list3E6984, 0, obj);
        while (n) {
            next = (A60Node *)sub_0003DC10(n, 0, obj);
            sub_0003D8C0(n);
            sub_00053880(n->data);
            sub_00053880(n);
            n = next;
        }
        break;
    }
}

/* 0x00075420: attach a 0x24-byte effect node to a type 9 object (types 1/5 hang). */
void a60_AttachEff6974(A60Obj *obj, int a, int b, int c)
{
    A60EffNode *n;
    if (obj == 0) for (;;) ;
    switch (obj->type) {
    case 1:
    case 5:
        for (;;) ;
    case 9:
        n = (A60EffNode *)sub_00053AB0(0x24, a60_srcTexEx, 0x2BF);
        sub_0003D860(n);
        n->a10 = c;
        n->a1C = 0;
        n->t20 = 0.0f;
        n->a14 = a;
        n->a18 = b;
        n->obj = obj;
        sub_0003D880(a60_list3E6974, n);
        break;
    }
}
