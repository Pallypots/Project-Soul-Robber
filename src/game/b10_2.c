/* Area b10, group 2: screen commands and actor callbacks 0x00102F10-0x0010CA80. Names inferred. */
#include "b10.h"

/* 0x00102F10: wait for the screen resource, apply setting 1 and flag +0x1C0. */
void b10_ScrApply1(void)
{
    B10Scr *s = b10_scr;
    B10Res * volatile r = s->res8C;
    while (r == 0) { }
    sub_000F3D10(r, s, 1);
    b10_scr->i1C0 = 1;
}

/* 0x00102FB0: set +0x1C0. */
void b10_ScrSet1C0(void) { b10_scr->i1C0 = 1; }

/* 0x00103840: reset the screen timer, send command 0x21 and clear +0x20C. */
void b10_ScrCmd21(void)
{
    B10Scr *s = b10_scr;
    s->w1A8 = 0;
    s->f1AC = 0.0f;
    sub_00101280(0x21);
    s->i20C = 0;
}

/* 0x00103A70: send command 0x23. */
void b10_ScrCmd23(void) { sub_00101280(0x23); }

/* 0x00103F90: reset the screen timer and send command 3. */
void b10_ScrCmd3(void)
{
    b10_scr->w1A8 = 0;
    b10_scr->f1AC = 0.0f;
    sub_00101280(3);
}

/* 0x00103FC0: clear +0x1A8 and send command 0x32. */
void b10_ScrCmd32(void)
{
    b10_scr->w1A8 = 0;
    sub_00101280(0x32);
}

/* 0x001045B0: send command 0x34. */
void b10_ScrCmd34(void) { sub_00101280(0x34); }

/* 0x00104610: clear +0x1A8 and send command 0x35. */
void b10_ScrCmd35(void)
{
    b10_scr->w1A8 = 0;
    sub_00101280(0x35);
}

/* 0x00106010: forget object 0x003F6134. */
void b10_Obj34Reset(void) { b10_obj3F6134 = 0; }

/* 0x00106090: free object 0x003F6134. */
void b10_Obj34Free(void)
{
    sub_00053880(b10_obj3F6134);
    b10_obj3F6134 = 0;
}

/* 0x00106140: attach object 0x003F6134 when the target is in mode 2. */
void b10_Obj34Attach(void *o)
{
    if (sub_000F3B50(o) == 2)
        sub_000F3CD0(o, b10_obj3F6134);
}

/* 0x00106340: forget object 0x003F6138. */
void b10_Obj38Reset(void) { b10_obj3F6138 = 0; }

/* 0x001063A0: free object 0x003F6138. */
void b10_Obj38Free(void)
{
    sub_00053880(b10_obj3F6138);
    b10_obj3F6138 = 0;
}

/* 0x001065B0: constant 1.2. */
float b10_Const1_2(void) { return 1.2f; }

/* 0x00108B00: forget object 0x003F6150. */
void b10_Obj50Reset(void) { b10_obj3F6150 = 0; }

/* 0x00108B60: free object 0x003F6150. */
void b10_Obj50Free(void)
{
    sub_00053880(b10_obj3F6150);
    b10_obj3F6150 = 0;
}

/* 0x001094E0: switch component 5 to mode 3 when +0xD0 is negative. */
void b10_ActMode3(void *o, B10Act *a)
{
    void * volatile obj;
    B10Hit *c;
    if (!(a->fD0 < 0.0f))
        return;
    obj = o;
    while (obj == 0) { }
    c = sub_0001D960(obj, 5);
    if (c->mode6C != 3)
        sub_000F3D10(obj, c, 3);
}

/* 0x00109520: switch component 5 to mode 0x18 when +0xBC is positive and flags 0x18 set. */
void b10_ActMode18(B10Pawn *o, B10Act *a)
{
    B10Hit *c;
    if (!(a->fBC > 0.0f))
        return;
    if ((o->b128 & 0x18) == 0)
        return;
    c = sub_0001D960(o, 5);
    if (c->mode6C != 0x18)
        sub_000F3D10(o, c, 0x18);
}

/* 0x00109570: switch component 5 to mode 0x1A once +0x54 is not positive. */
void b10_ActMode1A(void *o, B10Act *a)
{
    void * volatile obj;
    B10Hit *c;
    if (0.0f < a->f54)
        return;
    obj = o;
    while (obj == 0) { }
    c = sub_0001D960(obj, 5);
    if (c->mode6C != 0x1A)
        sub_000F3D10(obj, c, 0x1A);
}

/* 0x001095B0: switch component 5 to mode 2 when +0xBC is positive and flags 0x18 set. */
void b10_ActMode2(B10Pawn *o, B10Act *a)
{
    B10Hit *c;
    if (!(a->fBC > 0.0f))
        return;
    if ((o->b128 & 0x18) == 0)
        return;
    c = sub_0001D960(o, 5);
    if (c->mode6C != 2)
        sub_000F3D10(o, c, 2);
}

/* 0x00109610: switch component 5 to mode 0xC once +0x54 is not positive. */
void b10_ActModeC(void *o, B10Act *a)
{
    void * volatile obj;
    B10Hit *c;
    if (0.0f < a->f54)
        return;
    obj = o;
    while (obj == 0) { }
    c = sub_0001D960(obj, 5);
    if (c->mode6C != 0xC)
        sub_000F3D10(obj, c, 0xC);
}

/* 0x00109670: set values 4 and 0x20. */
void b10_Set4_20(void *o)
{
    sub_000F3B30(o, 4);
    sub_000F3B00(o, 0x20);
}

/* 0x00109710: set values 4 and 0x20 and apply 0.5. */
void b10_Set4_20Half(void *o)
{
    sub_000F3B30(o, 4);
    sub_000F3B00(o, 0x20);
    sub_000F3F00(o, 0.5f);
}

/* 0x00109E20: set values 0x44 and 0x20. */
void b10_Set44_20(void *o)
{
    sub_000F3B30(o, 0x44);
    sub_000F3B00(o, 0x20);
}

/* 0x0010C830: forget object 0x003F6160. */
void b10_Obj60Reset(void) { b10_obj3F6160 = 0; }

/* 0x0010CA80: free object 0x003F6160. */
void b10_Obj60Free(void)
{
    sub_00053880(b10_obj3F6160);
    b10_obj3F6160 = 0;
}
