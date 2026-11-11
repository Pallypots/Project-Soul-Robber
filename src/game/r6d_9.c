/* Area r6d: pause handles and model part helpers around 0x0006DB00-0x0007584E (r6d_9). Names inferred. */
#include "r6d.h"

/* 0x0006DB00: mark all 32 sound handles of the pause screen as free. */
void r6d_PauseHandlesInit(void)
{
    int i;
    for (i = 0; i < 32; i++)
        a60_h3E68B8[i] = -1;
}

/* 0x00072DD0: set the four draw-order slots of a menu for a layout mode and selection.
   regargs: m=EAX sel=ECX mode=DX (zero-extended) */
void r6d_MenuSetOrder(R6dOrder *m, int sel, uint16_t mode)
{
    switch (mode) {
    case 1:
        if (sel == 0) {
            m->o[0] = 0; m->o[1] = 1; m->o[2] = 2; m->o[3] = 3;
        } else if (sel == 1) {
            m->o[3] = 1; m->o[0] = 2; m->o[1] = 3; m->o[2] = 0;
        } else if (sel == 2) {
            m->o[2] = 1; m->o[0] = 0; m->o[1] = sel; m->o[3] = 3;
        } else {
            m->o[1] = 3; m->o[2] = 0; m->o[0] = 1; m->o[3] = 2;
        }
        break;
    case 2:
        if (sel == 0) {
            m->o[0] = 0; m->o[1] = 1; m->o[2] = 2; m->o[3] = 3;
        } else if (sel == 1) {
            m->o[0] = 1; m->o[1] = 0; m->o[2] = 3; m->o[3] = 2;
        } else if (sel == 2) {
            m->o[3] = 1; m->o[0] = 2; m->o[1] = 3; m->o[2] = 0;
        } else {
            m->o[2] = 1; m->o[0] = 3; m->o[1] = 2; m->o[3] = 0;
        }
        break;
    case 3:
        if (sel == 0) {
            m->o[0] = 0; m->o[1] = 1;
        } else {
            m->o[0] = 1; m->o[1] = 0;
        }
        break;
    }
}

/* 0x00074410: release the sound handles of the current pause page. */
void r6d_PausePageStopSounds(void)
{
    int i;
    int row;
    switch (a60_phase428F81) {
    case 0:
        if (r6d_b428F84 == 3)
            return;
        if (a60_h3E694C[0] != -1) {
            sub_001B9FC0(a60_h3E694C[0]);
            a60_h3E694C[0] = -1;
        }
        if (r6d_h3E6954 != -1) {
            sub_001B9FC0(r6d_h3E6954);
            r6d_h3E6954 = -1;
        }
        break;
    case 1:
        row = r6d_g42A818 + r6d_g42A824;
        if (a60_h3E694C[1] != -1) {
            sub_001B9FC0(a60_h3E694C[1]);
            a60_h3E694C[1] = -1;
        }
        i = 0;
        if (r6d_counts2DF390[a5b_GetVideoMode()][row] > 0) {
            do {
                if (a60_h3E6940[i] != -1) {
                    sub_001B9FC0(a60_h3E6940[i]);
                    a60_h3E6940[i] = -1;
                }
                i++;
            } while (i < r6d_counts2DF390[a5b_GetVideoMode()][row]);
        }
        break;
    case 2:
        for (i = 0; i < 3; i++) {
            if (a60_h3E6940[i] != -1) {
                sub_001B9FC0(a60_h3E6940[i]);
                a60_h3E6940[i] = -1;
            }
        }
        break;
    }
}

/* 0x00074DF0: register a model in the effect list and set the second UV offset of
   every active part with the given key; hangs on NULL or an unknown model type. */
void r6d_ModelSetUV2(R6dModel *m, int key, const int32_t *v)
{
    A60EffNode *n;
    int i;
    if (!m)
        for (;;) ;
    if (!sub_0003DBC0(a60_list3E6994, 0, m)) {
        n = (A60EffNode *)sub_00053AB0(0x10, a60_srcTexEx, 0xA2);
        sub_0003D860(n);
        n->obj = (A60Obj *)m;
        sub_0003D880(a60_list3E6994, n);
    }
    if (m->type == 5) {
        for (i = 0; i < m->count; i++) {
            R6dPart5 *p = &((R6dPart5 *)m->parts)[i];
            if (p->active && p->key == key) {
                p->uvB[0] = v[0];
                p->uvB[1] = v[1];
            }
        }
    } else if (m->type == 1) {
        for (i = 0; i < m->count; i++) {
            R6dPart1 *p = &((R6dPart1 *)m->parts)[i];
            if (p->active && p->key == key) {
                p->uvB[0] = v[0];
                p->uvB[1] = v[1];
            }
        }
    } else {
        for (;;) ;
    }
}

/* 0x00075780: set the first UV offset of every active part with the given key.
   regargs: m=EAX key=EBX v=EDI */
void r6d_ModelSetUV1(R6dModel *m, int key, const int32_t *v)
{
    int i;
    if (m->type == 5) {
        for (i = 0; i < m->count; i++) {
            if (((R6dPart5 *)m->parts)[i].active && ((R6dPart5 *)m->parts)[i].key == key) {
                ((R6dPart5 *)m->parts)[i].uvA[0] = v[0];
                ((R6dPart5 *)m->parts)[i].uvA[1] = v[1];
            }
        }
    } else if (m->type == 1) {
        for (i = 0; i < m->count; i++) {
            if (((R6dPart1 *)m->parts)[i].active && ((R6dPart1 *)m->parts)[i].key == key) {
                ((R6dPart1 *)m->parts)[i].uvA[0] = v[0];
                ((R6dPart1 *)m->parts)[i].uvA[1] = v[1];
            }
        }
    }
}
