/* Area b10, group 1: controller helpers around 0x00100000. Names inferred. */
#include "b10.h"

/* 0x00100020: wait for the controller resources, then apply a setting. */
void b10_CtlApply(int arg)
{
    void * volatile res = b10_ctl->res8C;
    void * volatile aux;
    while (res == 0) { }
    aux = b10_res3F612C;
    while (aux == 0) { }
    sub_000F3D10(res, aux, arg);
    b10_ctl->wBC = 0;
}

/* 0x00100110: wait until the controller exists and return it. */
B10Ctl *b10_CtlWait(void)
{
    B10Ctl * volatile c = b10_ctl;
    while (c == 0) { }
    return c;
}

/* 0x00100370: copy a word from the record into the controller when enabled. */
void b10_CtlCopyWord(uint8_t *rec)
{
    if (*(int32_t *)((uint8_t *)sub_000FC4D0() + 0xE8) != 0)
        b10_ctl->wA8 = *(int16_t *)(rec + 0xC);
}

/* 0x001006F0: clear word +0x1C8. */
void b10_CtlClear1C8(void) { b10_ctl->w1C8 = 0; }

/* 0x00101140: mark the controller when the test succeeds. */
void b10_CtlMark(void *a)
{
    if (sub_000F5D00(a) != 0)
        b10_ctl->wBC = 1;
}

/* 0x001011F0: forget the screen object. */
void b10_ScrReset(void) { b10_scr = 0; }

/* 0x00101200: free the screen object. */
void b10_ScrFree(void)
{
    sub_00053880(b10_scr);
    b10_scr = 0;
}

/* 0x00101220: wait for the screen's first resource. */
B10Res *b10_ScrWait(void)
{
    B10Res * volatile r = b10_scr->res8C;
    while (r == 0) { }
    return r;
}

/* 0x00101240: wait for the screen resource, then apply a setting. */
void b10_ScrApply(int arg)
{
    B10Scr *s = b10_scr;
    B10Res * volatile r = s->res8C;
    while (r == 0) { }
    sub_000F3D10(r, s, arg);
    b10_scr->i1C0 = 0;
}

/* 0x00101280: wait for both screen resources and send an id to both. */
void b10_ScrSend(int id)
{
    B10Res * volatile a = b10_scr->res8C;
    B10Res * volatile b;
    while (a == 0) { }
    b = b10_scr->res90;
    while (b == 0) { }
    sub_000832D0(a->handle, id);
    sub_000832D0(b10_scr->res90->handle, id);
}

/* 0x001012D0: value of entry i. */
int b10_ScrEntry(int i) { return b10_scr->entries[i].value; }

/* 0x00101340: apply 0x000F5D40 to the screen's sub-record. */
void b10_ScrVec(void *a) { b10_VecOp2(a, b10_scr->sub224); }

/* 0x00101360: 1 if the player's +0x64 value is at most -30. */
int b10_PlayerLow(void)
{
    if (*(float *)((uint8_t *)g_playerObj + 0x64) > -30.0f)
        return 0;
    return 1;
}
