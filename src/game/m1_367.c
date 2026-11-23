/* Area m1, file 367: register-argument revisits (written with normal parameters). Names inferred. */
#include <stdint.h>
#include "m1_panel.h"

extern M1PanelRow a3c_tbl3DA4A8[];
/* 0x39440 and 0x390E0 take the panel index in eax plus the display list; written as ordinary parameters. */
void *sub_00039440(int i, void *dl);
void *sub_000390E0(int i, void *dl);
void *sub_000396E0(void *dl);

#pragma optimize("s", on)
/* 0x398D0: draw HUD panel i by its kind (text or icon), then finish the panel pass. */
void *m1_PanelDraw0398D0(void *dl, int i) {
    switch (a3c_tbl3DA4A8[i].kind) {
    case 1: return sub_000396E0(sub_00039440(i, dl));
    case 0: dl = sub_000390E0(i, dl); break;
    }
    return sub_000396E0(dl);
}
#pragma optimize("", on)

#include "m1_player.h"
typedef void (*M1PlAct)(M1Player *p);
extern M1PlAct m1_plActsA2E68E8[];
extern M1PlAct m1_plActsB2E69A8[];
extern M1PlAct m1_plActsC2E6A68[];
/* 0xBD770 takes the player in esi; written as an ordinary parameter. */
void sub_000BD770(M1Player *p);

/* 0xC2A40: run the player's current action from the handler table of its costume set; special modes 4 and 5 go to 0xBD770. */
void m1_PlActRun0C2A40(M1Player *p) {
    M1PlAct *t[3];
    t[0] = m1_plActsA2E68E8; t[1] = m1_plActsB2E69A8; t[2] = m1_plActsC2E6A68;
    if (p->mode == 4 || p->mode == 5) { sub_000BD770(p); return; }
    t[p->costumeSet][p->action](p);
}
