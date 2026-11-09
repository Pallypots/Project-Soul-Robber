/* Area b16, group 3: parameter tables and enemy handlers 0x00171C30-0x0017A120. Names inferred. */
#include "b16.h"

/* 0x00171C30: int from table 1 list 1 at the owner's base. */
int b16_TabInt84(B16TabOwner *o) { return ((int32_t **)b16_tables[1])[1][o->base84]; }

/* 0x00171C50: float from table 1 list 1, entry i. */
float b16_TabFloat7C(B16TabOwner *o, int i)
{
    return ((float **)b16_tables[1])[1][o->base7C[i] + i * 3 + 3];
}

/* 0x00171C80: int from table 1 list 2, entry i. */
int b16_TabInt74(B16TabOwner *o, int i) { return ((int32_t **)b16_tables[1])[2][o->base74 + i * 3]; }

/* 0x00171CA0: float from table 1 list 2, entry i field 6. */
float b16_TabFloat74(B16TabOwner *o, int i) { return ((float **)b16_tables[1])[2][o->base74 + i * 3 + 6]; }

/* 0x00171CD0: int from table 1 list 2 field 12. */
int b16_TabInt74_12(B16TabOwner *o) { return ((int32_t **)b16_tables[1])[2][o->base74 + 12]; }

/* 0x00171DC0: parameter record float list 4, second value when sel is 1. */
float b16_ParamF4(int t, int i, int sel) { return ((B16Param **)b16_tables[t])[i]->f4[sel == 1]; }
/* 0x00171DF0: parameter record float list 8. */
float b16_ParamF8(int t, int i, int sel) { return ((B16Param **)b16_tables[t])[i]->f8[sel == 1]; }
/* 0x00171E20: parameter record float at +0x0C. */
float b16_ParamFC(int t, int i) { return *((B16Param **)b16_tables[t])[i]->fC; }
/* 0x00171E40: parameter record int list 0x10. */
int b16_ParamI10(int t, int i, int sel) { return ((B16Param **)b16_tables[t])[i]->i10[sel == 1]; }
/* 0x00171F10: parameter record int at +0x1C, through float. */
int b16_ParamI1C(int t, int i) { return (int)(float)*((B16Param **)b16_tables[t])[i]->i1C; }

/* 0x001729D0: 1 if the hit component is in mode 1. */
int b16_HitMode1(void)
{
    B16Hit *h;
    if (b16_obj3FD7C4 == 0)
        for (;;) ;
    h = sub_0001D960(b16_obj3FD7C4, 8);
    if (h == 0)
        for (;;) ;
    return h->mode == 1;
}

/* 0x00175880: state 3, and count ticks on work flag 4. */
void b16_E3Tick(void *o, B16Enemy *e)
{
    B16EWork *w = e->work;
    sub_00113090(o, e, 3);
    if (w->flags & 4)
        e->ticks++;
}

/* 0x00175A10..0x0017A120: enemy goes to a fixed state. */
void b16_EState0(void *o, B16Enemy *e) { sub_00113090(o, e, 0); }
void b16_EState3(void *o, B16Enemy *e) { sub_00113090(o, e, 3); }
void b16_EState2(void *o, B16Enemy *e) { sub_00113090(o, e, 2); }
void b16_EState7(void *o, B16Enemy *e) { sub_00113090(o, e, 7); }
void b16_EState5(void *o, B16Enemy *e) { sub_00113090(o, e, 5); }

/* 0x00175CB0: state 3 and work flags 0x402. */
void b16_E3Flags(void *o, B16Enemy *e)
{
    sub_00113090(o, e, 3);
    e->work->flags |= 0x402;
}

/* 0x001764E0: deactivate the work block and release its object. */
int b16_EWorkFree(void *o, B16Enemy *e)
{
    B16EWork *w = e->work;
    w->flags &= ~1;
    if (w->obj2C != 0)
        sub_0018C6A0(w->obj2C);
    return 1;
}

/* 0x00177FA0: count ticks on work flag 4. */
void b16_ETick(void *o, B16Enemy *e)
{
    if (e->work->flags & 4)
        e->ticks++;
}

/* 0x001789C0: f68 = f74 / 8. */
void b16_EScale(void *o, B16Enemy *e) { e->f68 = e->f74 * 0.125f; }
