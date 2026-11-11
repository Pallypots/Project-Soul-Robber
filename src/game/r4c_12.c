/* Area r4c: session poll, option defaults and loader set-up 0x0019C2D0-0x0019D78F (r4c_12). Names inferred. */
#include "r4c.h"

/* 0x0019C2D0: poll for a session request: needs both buttons of mask 0x900 held for 120 frames; returns 1 when sent. No inputs. */
int r4c_SessionPoll(void)
{
    int held;
    if (sub_000325D0())
        return 0;
    if (sub_00032450(0))
        return 0;
    held = (sub_0004ECD0(0) & 0x900) == 0x900;
    if (!held) {
        r4c_g402FA4 = 0;
        return 0;
    }
    if (r4c_g402FA4)
        return 0;
    if (++r4c_g402780 < 0x78)
        return 0;
    r4c_g402780 = 0x78;
    if (Session_Request(-1))
        return 0;
    return 1;
}

/* 0x0019C350: restore the default option bytes at 0x00413140 and apply them (0x0019BED0). No inputs. */
void r4c_OptionsDefaults(void)
{
    r4c_opt413140 = 1;
    r4c_opt413141 = 0;
    r4c_opt413142 = 1;
    r4c_opt413143 = 1;
    r4c_opt413144 = 1;
    r4c_opt413145 = 1;
    r4c_opt413146 = 0;
    r4c_opt413147 = sub_001AB610();
    r4c_opt41314A = 0;
    r4c_opt41314B = 0;
    r4c_opt41314C = 0;
    r4c_opt413148 = 8;
    r4c_opt413149 = 8;
    sub_0019BED0();
}

/* 0x0019C940: set up loader l for resource id and start its worker (0x0019C620). Stack args (l id). */
void r4c_LoaderInit(R4cLoader *l, int id)
{
    int size = sub_0004F680(id + 0x11D);
    l->b14 = 0;
    l->id = id;
    l->buf = sub_00053AB0(size, 0, 0x146);
    l->i10 = sub_0008D340();
    l->i08 = 0;
    l->i0C = sub_00037FC0();
    sub_00058540(sub_0019C620, l);
}

/* 0x0019D0A0: register the three entries of group g and release the old ones. Stack args. */
void r4c_GroupSetup(R4cGroup *g)
{
    g->i04 = 0;
    sub_001A1030(g, 0, 1, sub_0019C9A0, 8, 0x10000);
    sub_001A1030(g, 1, 2, sub_0019C6F0, 8, 0x10000);
    sub_001A1030(g, -1, 4, sub_0019CE60, 8, 0x10000);
    sub_001A10F0(g);
}

/* 0x0019D720: load resource pack 0xE3 if it is not resident, pump the loader until done, then release it. No inputs. */
void r4c_LoadPackE3(void)
{
    if (!sub_0004F6D0(0xE3)) {
        sub_00053710(0);
        sub_0004FA70(0xE3, sub_00053AB0(sub_0004F680(0xE3), 0, 0xEF));
        while (sub_0004F4D0())
            sub_000586E0(0);
        sub_00053740();
    }
    sub_0004F700(0xE3);
    sub_0005EE40();
    sub_0004F720();
}
