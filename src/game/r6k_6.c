/* Area r6k: actor update loop (r6k_6). Names inferred. */
#include "r6k.h"

/* 0x000A4F50: per-frame update of the 32 actor records. For each active
   actor (flag bit 0): copy the model position +0x60 to +0x70 and, unless
   the actor type is 0x1F, the model +0x50 to +0x80; run its script
   (0x00090560); if still active, step it (0x000A3AE0), call the per-kind
   update 0x002E40B0[+0x18] unless flag 0x10000 is set, make it follow the
   player (0x000A2FB0) while flags 0x300000 are set. Except for the types
   0x1D, 0x4C, 0x95, 0xA8..0xAA, 0xD7..0xE1 and 0xF7, and unless flag
   0x1000 is set, the eight local points +0x15C are moved to the world
   (+0x1DC, 0x001ADAF0) and tested against the scene area of +0x25C
   (0x00082E50 with 0x000847F0(scene +0x44, id) + 0x230): outside, a
   model shown with flag 0x40000000 is hidden (0x0001D610) and the flag
   cleared; inside, unless flag 0x20000000, it is shown (0x0001D700) and
   the flag set. Then 0x000A3990. Finally 0x000A0FD0(player) and
   0x000A1020. Calls 0x000A3AE0 with ESI=actor and 0x000A3990 with
   EAX=actor. */
void r6k_ActorsUpdate(void)
{
    R6kScene *scene = r6k_scene42C8E4;
    R6kActor *a;
    float *pos;
    int i;

    a = aa0_slots;
    do {
        if (!(a->flags & 1))
            continue;
        pos = a->pos70;
        sub_000F5D40(pos, a->model120->pos60);
        if (a->type04 != 0x1F)
            sub_000F5D40(a->vec80, a->model120->pos50);
        sub_00090560(a);
        if (!(a->flags & 1))
            continue;
        sub_000A3AE0(a);
        if (!(a->flags & 0x10000))
            r6k_actorUpdate2E40B0[a->kind18](a);
        if (a->flags & 0x300000)
            sub_000A2FB0(a, g_playerObj);
        switch (a->type04) {
        case 0x1D: case 0x4C: case 0x95:
        case 0xA8: case 0xA9: case 0xAA:
        case 0xD7: case 0xD8: case 0xD9: case 0xDA: case 0xDB: case 0xDC:
        case 0xDD: case 0xDE: case 0xDF: case 0xE0: case 0xE1:
        case 0xF7:
            break;
        default:
            if (a->flags & 0x1000)
                break;
            for (i = 0; i < 8; i++)
                sub_001ADAF0(a->world1DC[i], a->local15C[i], pos);
            if (sub_00082E50(a->world1DC,
                             (uint8_t *)sub_000847F0(scene->list44, a->id25C) + 0x230) == 0) {
                if (a->flags & 0x40000000) {
                    sub_0001D610(a->model120);
                    a->flags &= ~0x40000000u;
                }
            } else if (!(a->flags & 0x20000000)) {
                sub_0001D700(a->model120);
                a->flags |= 0x40000000;
            }
            break;
        }
        sub_000A3990(a);
    } while ((intptr_t)++a < (intptr_t)(aa0_slots + 32));
    sub_000A0FD0(g_playerObj);
    sub_000A1020();
}

