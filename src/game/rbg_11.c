/* Area rbg: enemy reaction entry 0x00147580 kept apart from its callers (rbg_11). Names inferred. */
#include "rbg.h"

/* 0x00147580: enter reaction state st: clear the hit flags, settle the motion (keeping work
   flag 0x1000 only for st 7), apply pending events (the 0x10000 one not for st 0x21), keep or
   start the struggle sound 0x10F for st 2..4, 15..17, 19 and 21 (stop it otherwise), release
   the effect and set the state; obj flag 0x10 survives only into st 0x24.
   regargs: st=EBX act=ESI obj=stack */
void sub_00147580(RbgRec150 *obj, int st, RbgComp *act)
{
    RbgWork *w = act->work278;
    int keep;

    if ((obj->flags10 & 0x10) && st == 0x24)
        keep = 1;
    else
        keep = 0;
    sub_001134B0(act);
    obj->flags0C |= 0xE0;
    obj->flags10 &= 0xFFFFFEC8u;
    act->flags4C &= ~0x100u;
    w->flags00 &= 0xFFFFFFE8u;
    w->flags50 &= 0xFFDBFEBFu;
    if (st != 7)
        w->flags50 &= ~0x1000u;
    sub_001561D0(w, -10.0f, r3e_frameSeconds * 10.0f);
    if ((w->flags50 & 0x10000) && st != 0x21) {
        sub_00113AA0(obj, act);
        act->flags4C |= 0x200;
        w->flags50 &= ~0x10000u;
    }
    if (w->flags50 & 0x100000) {
        w->flags50 &= ~0x100000u;
        sub_00113190(obj, act, 1);
    }
    switch (st) {
    case 2:
    case 3:
    case 4:
    case 15:
    case 16:
    case 17:
    case 19:
    case 21:
        if (act->snd6C == -1)
            act->snd6C = sub_000494D0(0x10F, obj->pos60, 1);
        break;
    default:
        if (act->snd6C != -1) {
            sub_00048250(act->snd6C);
            act->snd6C = -1;
        }
        break;
    }
    sub_0005BE30(obj->h13C);
    if (act->p70) {
        sub_00033A70(act->p70);
        act->p70 = 0;
    }
    sub_00113040(obj, act, st);
    if (keep)
        obj->flags10 |= 0x10;
}

/* 0x0015A270: enter reaction state st for the second enemy family: like 0x00147580 but with
   the work flags at +0x40, the settle speed (-10) and step stored directly, the pending event
   0x4000 (not for st 0x2F), the struggle sound for st 7, 9, 10, 12..14, 31, 32, 34 and 36, and
   obj flag 0x10 surviving only into st 0x32.
   regargs: act=ESI obj=stack st=stack */
void sub_0015A270(RbgRec150 *obj, int st, RbgComp *act)
{
    RbgWorkB *w = (RbgWorkB *)act->work278;
    int keep;

    if ((obj->flags10 & 0x10) && st == 0x32)
        keep = 1;
    else
        keep = 0;
    sub_001134B0(act);
    obj->flags0C |= 0xE0;
    obj->flags10 &= 0xFFFFFECAu;
    act->flags4C &= ~0x100u;
    w->flags40 &= 0xFFFBF579u;
    w->flags00 &= 0xFFFFFFE8u;
    w->f04 = -10.0f;
    w->f08 = r3e_frameSeconds * 10.0f;
    if ((w->flags40 & 0x4000) && st != 0x2F) {
        sub_00113AA0(obj, act);
        act->flags4C |= 0x200;
        w->flags40 &= ~0x4000u;
    }
    switch (st) {
    case 7:
    case 9:
    case 10:
    case 12:
    case 13:
    case 14:
    case 31:
    case 32:
    case 34:
    case 36:
        if (act->snd6C == -1)
            act->snd6C = sub_000494D0(0x10F, obj->pos60, 1);
        break;
    default:
        if (act->snd6C != -1) {
            sub_00048250(act->snd6C);
            act->snd6C = -1;
        }
        break;
    }
    sub_0005BE30(obj->h13C);
    if (act->p70) {
        sub_00033A70(act->p70);
        act->p70 = 0;
    }
    sub_00113040(obj, act, st);
    if (keep)
        obj->flags10 |= 0x10;
}
