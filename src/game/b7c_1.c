/* Area b7c, group 1: enemy helpers 0x001711C0-0x00175430. Names inferred. */
#include "b7c.h"

/* 0x001711C0: if the object has flag 0x18, put the state block into state 2. */
typedef struct B7CState50 { uint8_t unk00[0x50]; int32_t i50; int32_t i54; float f58; } B7CState50;
void b7c_Reset1711C0(B7CFlag128 *o, B7CState50 *s)
{
    if (o->flags128 & 0x18) {
        s->i50 = 2;
        s->i54 = 0;
        s->f58 = 0.0f;
    }
}

typedef struct B7CParam14 { uint8_t unk00[0x14]; int32_t *list; } B7CParam14;

/* 0x00171E70: random entry (one of 16) from a parameter record's int list. */
int b7c_RandParam171E70(int t, int i, int row, int sel)
{
    int32_t *list = ((B7CParam14 **)b16_tables[t])[i]->list;
    int k = (sel == 1) + row * 2;
    return list[(k << 4) + (aab_Rand() & 15)];
}

/* 0x00171FC0: stop task 6 and release its registration. */
void b7c_TaskStop171FC0(void)
{
    if (b16_taskId3FD7B4 != 0) {
        sub_000ED560(6);
        sub_00020170(b16_task3FD7B0);
        b16_task3FD7B0 = 0;
        b16_taskId3FD7B4 = 0;
    }
}

/* 0x00172070: clear group 6 and run commands 0x8C..0x9A that are pending. */
void b7c_Flush172070(void)
{
    int i = 0x8C, n = 15;
    sub_000ED600(6);
    do {
        if (sub_0004F6D0(i))
            sub_0004F5D0(i);
        i++;
    } while (--n);
}

/* 0x00172950: value 0xCC of the hit component (default handle when null), -1 if none. */
int b7c_HitValue172950(B7CHandle *h)
{
    B7CHit *c;
    if (h == 0) {
        h = sub_000EDBE0(6, 1);
        if (h == 0)
            return -1;
    }
    c = sub_0001D960(h, 8);
    if (c == 0)
        return -1;
    return c->iCC;
}

/* 0x00172990: 1 if the type-6 handle's hit component has bit 0 clear. */
int b7c_HitIdle172990(B7CHandle *h)
{
    B7CHit *c;
    if (h == 0 || h->type != 6)
        for (;;) ;
    c = sub_0001D960(h, 8);
    if (c == 0)
        for (;;) ;
    return !(c->flags5C & 1);
}

/* 0x00172A00: set the hit component's value 0xBC (0..2) on a type-6 handle. */
void b7c_HitSetBC172A00(B7CHandle *h, int v)
{
    B7CHit *c;
    if (h->type == 6) {
        c = sub_0001D960(h, 8);
        if (c == 0)
            for (;;) ;
        if (v >= 0 && v < 3)
            c->iBC = v;
    }
}

typedef struct B7CObj30 { uint8_t unk00[0x30]; void *anim30; } B7CObj30;

/* 0x00173FA0: when the animation is done, enter state 1 through the state table. */
void b7c_Enter1_173FA0(B7CObj30 *o, B7CState *s)
{
    if (sub_000833E0(o->anim30)) {
        s->i4C = 1;
        s->i50 = 0;
        s->f54 = 0.0f;
        b7c_stateFns32B1B0[1](o, s);
    }
}

/* 0x00174BE0: register task 7 (slot 4) once. */
void b7c_TaskStart174BE0(void)
{
    if (b7c_taskId3FD7CC == 0) {
        b7c_task3FD7C8 = sub_0001F210(7, 4);
        b7c_taskId3FD7CC = b7c_task3FD7C8->id;
        sub_0001DA40(b7c_task3FD7C8);
    }
}

/* 0x00174C10: stop task 4 and release its registration. */
void b7c_TaskStop174C10(void)
{
    if (b7c_taskId3FD7CC != 0) {
        sub_000ED560(4);
        sub_00020170(b7c_task3FD7C8);
        b7c_task3FD7C8 = 0;
        b7c_taskId3FD7CC = 0;
    }
}

/* 0x00175190: take a free 0x30-byte record from the pool, zeroed and marked used. */
B7CRec30 *b7c_Alloc175190(void)
{
    int i = 0;
    B7CRec30 *r;
    for (r = b7c_pool3FD7E0; r < b7c_pool3FD7E0 + 5; r++, i++)
        if (!(r->flags & 1))
            goto found;
    return 0;
found:
    r = &b7c_pool3FD7E0[i];
    B7C_ZERO(r, sizeof *r);
    r->flags |= 1;
    return r;
}

/* 0x001753F0: release the three effects of the work block and clear its active bit. */
int b7c_Release1753F0(void *o, B7CEnemy *e)
{
    B7CWorkA *w = e->work;
    int i;
    for (i = 0; i < 3; i++)
        if (w->fx24[i])
            sub_0018D650(w->fx24[i]);
    w->flags &= ~1u;
    return 1;
}
