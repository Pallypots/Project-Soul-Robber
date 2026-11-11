/* Area rbi: Jack's reset (rbi_11). Names inferred. */
#include "rbi.h"

/* 0x000D3260: reset Jack's state: motion and timers cleared, all three headings taken from
   yaw108, scale fields 1.0, turn rate 0.1, the animation and request slots set to -1, then
   the sub-systems reset in order (0x000D2440, 0x000CB340, 0x000CBD10, both 0x000CCC50
   halves, 0x000C4420, 0x000C5B10), the combo block cleared, 0x000C42B0 and 0x000CC430, the
   target slots -1, the spawn point taken from the model 15 units below it, and finally
   0x000C52B0 (tail call). */
void rbi_JackReset0D3260(RbiJackInit *p)
{
    int i;

    p->f11C = 1.0f;
    p->f01C = 1.0f;
    p->i020 = 0;
    p->f0E8 = 0.0f;
    p->f148 = 0.0f;
    p->f14C = 0.0f;
    p->f118 = 0.0f;
    p->f114 = 0.0f;
    p->f110 = 0.0f;
    p->f018 = 0.0f;
    p->f014 = 0.0f;
    p->f010 = 0.0f;
    p->f10C = 0.1f;
    p->yaw0FC = p->yaw108;
    p->yaw100 = p->yaw108;
    p->yaw104 = p->yaw108;
    p->i0EC = 0;
    p->i0D4 = 0;
    p->i128 = 0;
    p->i12C = 0;
    p->f130 = 0.0f;
    p->f134 = 0.0f;
    p->i138 = 0;
    p->i13C = 0;
    p->i140 = 0;
    p->i144 = 0;
    p->i150 = 0;
    p->i154 = 0;
    p->i158 = 0;
    p->f15C = 0.0f;
    p->f160 = 0.0f;
    p->i164 = 0;
    p->f168 = 0.0f;
    p->f16C = 0.0f;
    p->i170 = 0;
    p->i174 = 0;
    p->i180 = -1;
    p->i17C = -1;
    p->i178 = -1;
    p->i184 = -1;
    p->i188 = -1;
    p->i18C = 1;
    p->iEE8 = 0;
    p->iEEC = 0;
    p->i31C = 0;
    p->i320 = 0;
    sub_000D2440(p);
    sub_000CB340(p);
    sub_000CBD10(p);
    sub_000CCC50(p, 0);
    sub_000CCC50(p, 1);
    sub_000C4420(p);
    sub_000C5B10();
    p->iD2C = 0;
    p->fD30 = 0.0f;
    p->iD34 = 0;
    p->iD38 = -1;
    p->iD3C = -1;
    p->iD40 = 0;
    p->fD44 = 0.0f;
    p->fD48 = 0.0f;
    p->fD58 = 0.0f;
    p->fD54 = 0.0f;
    p->fD50 = 0.0f;
    p->fD4C = 0.0f;
    p->iD5C = 0;
    sub_000C42B0(p);
    sub_000CC430(p);
    for (i = 0; i < 4; i++)
        p->i5F0[i] = -1;
    for (i = 0; i < 9; i++)
        p->i600[i] = 0;
    rbi_VecCopy(&p->pos1A8, &p->nodeFD8->pos60);
    p->pos1A8.y = p->nodeFD8->pos60.y - 15.0f;
    sub_000C52B0(p);
}
