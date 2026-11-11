/* Area r1b, group 10: menu state machines and a session screen 0x0002A240..0x0002EB80. Names inferred. */
#include "r1b.h"

/* 0x0002C7A0: when the screen is finished (10000), release its two handles,
   run the closing command and free its buffer. */
void r1b_ScreenClose(void)
{
    int32_t *h;
    if (a1b_i3816D0 != 10000) return;
    a1b_i3816D0 = 0;
    for (h = r1b_handles3813F4; h < &r1b_handles3813F4[2]; h++) {
        if (*h != -1) {
            sub_001B9FC0(*h);
            *h = -1;
        }
    }
    r1b_Cmd4F5D0(sub_000529F0() + 0xC3);
    sub_00053880(r1b_buf3816C4);
}

/* 0x0002C810: report the screen's sub-state as a small code (0 when not running). */
int r1b_ScreenCode(void)
{
    int32_t v;
    if (a1b_i3816D0 != 10000) return 0;
    v = r1b_mode381400;
    if (v == 0) {
        if (r1b_step381404 < 6u) return 1;
        return (r1b_flag381420 != 0) + 2;
    }
    if (v == 1) return 4;
    return (v != 2) + 5;
}

/* 0x0002C870: enter screen mode 4. */
void r1b_ScreenMode4(void)
{
    r1b_mode381400 = 4;
    r1b_step381404 = 0;
    r1b_v381408 = 0;
    r1b_v38140C = 0;
    sub_000243B0(0, 0);
    sub_00024D30(0, 0);
    sub_00038070(r1b_v3816CC);
}

/* 0x0002E4E0: register the screen's three handlers in group s and start it. */
void r1b_ScreenStart(int s)
{
    sub_00038960();
    a1a_GroupAdd(s, 0, 1, sub_0002CF50, 4, 0x2000);
    a1a_GroupAdd(s, 1, 1, sub_0002E470, 4, 0x2000);
    a1a_GroupAdd(s, -1, 4, sub_0002E2F0, 4, 0x2000);
    a1a_GroupReleaseOne(s, 0);
    a1a_GroupReleaseOne(s, -1);
    a50_RecsClear();
    a1b_i3816D0 = 0;
}

/* 0x0002EB80: bind a value to an object and look up its resource; 0 on success, -1 on failure. */
int r1b_BindValue(R1bBindObj *o, int v)
{
    int r = 0;
    if (o == 0 || v == 0) return -1;
    o->v2C = v;
    if (sub_0003F9C0(o->p30, r1b_name282884) == 0) r = -1;
    return r;
}
