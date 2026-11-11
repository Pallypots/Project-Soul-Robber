/* Area b1b, group 1: controller/screen helpers 0x00100070-0x00109650. Names inferred. */
#include "b1b.h"

/* 0x00100070: wait for the controller resources and send an id to both. */
void b1b_CtlSendBoth(int id)
{
    B1bCtl * volatile c = b10_ctl;
    B1bRes * volatile r;
    while (c == 0) { }
    r = c->res8C;
    while (r == 0) { }
    sub_000832D0(r->handle, id);
    sub_000832D0(b10_ctl->res90->handle, id);
}

/* 0x001002C0: run 0x00184610 when an entry is selected. */
void b1b_CtlRunSelected(void)
{
    if (b10_ctl->i138 != -1)
        sub_00184610();
}

/* 0x00100F70: mark the controller when the event value exceeds 0.4. */
void b1b_CtlMarkIfOver(int unused, B1bEvt *e)
{
    if (e->f68 > 0.4f)
        b10_ctl->wBC = 1;
}

/* 0x001010C0: apply setting 0x27 when in mode 2 or 0x00184610 agrees. */
void b1b_CtlApply27(void *a, void *b)
{
    if (b10_ctl->w1FC == 2 || sub_00184610() != 0)
        sub_000F3D10(a, b, 0x27);
}

/* 0x001012F0: reset an enabled component and re-register it. */
int b1b_CompReset(B1bComp *o)
{
    if (!(o->flags0C & 1))
        return 0;
    o->i20 = 0;
    o->flags10 |= 0xD;
    o->flags0C &= ~3u;
    sub_0001EB80(o);
    sub_0001D910(o, sub_0001D960(o, 0xD));
    return 1;
}

/* 0x001045C0: when the test passes, apply setting 1 to the screen. */
void b1b_ScrActivate(void *a)
{
    void * volatile r;
    if (sub_000F5D00(a) == 0)
        return;
    r = b10_scr->res8C;
    while (r == 0) { }
    sub_000F3D10(r, b10_scr, 1);
    b10_scr->i1C0 = 1;
}

/* 0x00104B40: event dispatch: kind 0x13 selects 3, otherwise forwards. */
void b1b_ScrEvent(void *a, B1bEvt *e)
{
    if (sub_000F5D00(a) == 0)
        return;
    if (e->i6C == 0x13)
        sub_00101240(3);
    else
        sub_00102F10(a, e);
}

/* 0x00104C60: allocate the screen object and initialise it. */
void b1b_ScrCreate(void)
{
    b10_scr = (B1bScr *)sub_00053AB0(sub_000F30E0(8) * 0x314, 0, 0x4B5);
    sub_00101380();
}
