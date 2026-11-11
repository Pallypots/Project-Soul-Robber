/* Area r3e: game functions in 0x00180000..0x0018FFFF (r3e_4). Names inferred. */
#include "r3e.h"

/* 0x00186400: nonzero when the target of kind blk->i08 can be grabbed (0x00113670). */
int r3e_CanGrab186400(R3eObj *obj, R3eObj *act, R3eWork *blk)
{
    int buf[4];

    if (sub_00113670(obj, act, blk->flags08, buf) >= 0)
        return 1;
    return 0;
}

/* 0x00184120: release the key record holding key (hangs if none) and clear act's work pointer. */
int r3e_Release184120(int key, R3eObj *act)
{
    int i;

    for (i = 0; i < 1; i++) {
        if (r3b_i3FE3A4[i].key == key)
            break;
    }
    if (i >= 1)
        for (;;) ;
    r3b_i3FE3A4[i].key = 0;
    act->work278 = 0;
    return 1;
}

/* 0x0018B6B0: count the records at 0x003FF738 that hold a key. */
int r3e_CountRecs18B6B0(void)
{
    int n = 0;
    int i;

    for (i = 0; i < 15; i++) {
        if (r3c_recs3FF738[i].key != 0)
            n++;
    }
    return n;
}

/* 0x0018B700: release the record at 0x003FF738 holding key (hangs if none) and clear obj's
   link at +0x74. */
int r3e_Release18B700(int key, R3eObj *obj)
{
    int i = 0;

    do {
        if (r3c_recs3FF738[i].key == key)
            break;
        i++;
    } while (i < 15);
    if (i >= 15)
        for (;;) ;
    r3c_recs3FF738[i].key = 0;
    obj->p74 = 0;
    return 1;
}

/* 0x00183DF0: choose a follow-up state: 3 while Jack is in states 4, 5, 7 or 8, 2 when the game
   block's +0x32C is set; state 4 overrides both when 0x000E3380 returns 4. */
void r3e_Follow183DF0(R3eObj *obj, R3eObj *act)
{
    int st = 0;

    switch (PlayerObj_GetState(&g_stats)) {
    case 4:
    case 5:
    case 7:
    case 8:
        st = 3;
        break;
    }
    if (((R3eGame *)sub_000E0770())->i32C)
        st = 2;
    if (sub_000E3380() == 4) {
        sub_00113040(obj, act, 4);
        return;
    }
    if (st)
        sub_00113040(obj, act, st);
}

/* 0x00186A80: run condition 0x20, reset the work vector at +0x20 to (0, 0, 0, 1), attach obj
   (mode 3), play effect 0x114 at obj and set node 2 to (0, 0, 1, 0). */
void r3e_Enter186A80(R3eObj *obj, R3eObj *act)
{
    R3eWorkV *w;
    R3eNode *n;

    sub_001456E0(obj, act, 0x20, 0);
    w = (R3eWorkV *)act->work278;
    w->v20[2] = 0.0f;
    w->v20[1] = 0.0f;
    w->v20[0] = 0.0f;
    w->v20[3] = 1.0f;
    sub_00036750(obj, 3);
    sub_000494D0(0x114, obj->pos60, 0);
    n = sub_00113400(act, 2);
    n->f10 = 0.0f;
    n->f14 = 0.0f;
    n->f18 = 1.0f;
    n->f1C = 0.0f;
}

/* 0x00189610: create the two hold records (tables 0x0032C2E8/0x0032C388 and 0x0032C338/0x0032C398,
   range 118) at obj's position and reset the shared hold state. */
void r3e_Holds189610(R3eObj *obj)
{
    if (obj == 0)
        return;
    r3c_i3FEB10 = sub_001890F0(0, r3e_tbl32C2E8, r3e_tbl32C388, 118.0f);
    r3d_Hold188C00(r3c_i3FEB10, obj->pos60);
    r3c_i3FEB14 = sub_001890F0(1, r3e_tbl32C338, r3e_tbl32C398, 118.0f);
    r3d_Hold188C00(r3c_i3FEB14, obj->pos60);
    r3c_s3FEAB8 = 0;
    r3c_f3FEAC0 = 0.0f;
    r3c_f3FEAC4 = 0.0f;
    r3c_f3FEAC8 = sub_001065B0();
    r3c_f3FEABC = 0.0f;
}
