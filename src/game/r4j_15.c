/* Area r4j: lobbed shot update (0x00191010). Names inferred. */
#include "r4j.h"

/* 0x00191010: per-frame update of the lobbed kind 0x18/0x19 shot. Measures
   the XZ distance to Jack (result unused), picks the probe radius (3 for
   kind 0x19, 5 for 0x18; 0x18 also sets node flag 0x20 above height -10),
   moves by the velocity with gravity and sink applied, sets the glow size
   from the height (3.3 below -100, else 1.5 - 0.018 * y), then tests a
   sphere at the position against collision mask 0. A hit kills the shot;
   0x00190B40 may handle it; floor contact (bits 3/4) kills kind 0x19 and
   kind 0x18 below -41, else puts 0x18 into state 3; wall contact (bits
   1/2) above -41 kills it, else bounces (X/Z velocity negated). Survivors
   spin. Stack args (o a); calls 0x00190B40 with EAX=o and 0x00190A00 with
   EDI=o. The radius is left uninitialised for other kinds in the original
   (only 0x18 and 0x19 use this callback); here it is 0. The kill/spin
   choice is kept in a flag so both calls stay single, as in the original. */
void r4j_FxLobUpdate(R4cNode *o, R4cActor *a)
{
    R4jLob *w = (R4jLob *)a->work;
    float *pos = o->pos;
    float *glow;
    float diff[4];
    float hit[4];
    R4iSphere s;
    int mask;
    int is19, is18;
    uint32_t f;
    int dead;

    is19 = o->kind == 0x19;
    is18 = o->kind == 0x18;
    r4c_VecSub(diff, pos, r4i_player->pos);
    r4c_VecLenXZ(diff);
    s.r = 0.0f;
    mask = 0;
    if (is19) {
        s.r = 3.0f;
    } else if (is18) {
        s.r = 5.0f;
        if (o->pos[1] > -10.0f)
            o->flagsC |= 0x20;
    }
    r4c_VecAdd(pos, pos, w->vel14);
    w->vel14[1] = w->vel14[1] - w->grav28;
    o->pos[1] = o->pos[1] - w->sink2C;
    glow = &w->glow08;
    if (glow) {
        if (-100.0f > o->pos[1])
            *glow = 3.3f;
        else
            *glow = (o->pos[1] * -0.01f) * 1.8f + 1.5f;
    }
    sub_000F5D40(s.c, pos);
    dead = sub_000F61D0(o, &s, mask, hit) != -1;
    if (!dead) {
        if (r4c_FxCollide(o))
            return;
        f = o->flags128;
        if (f & 0x18) {
            if (is19)
                dead = 1;
            else if (is18) {
                if (-41.0f > o->pos[1])
                    dead = 1;
                else
                    sub_00189DA0(o, a, 3);
            }
        } else if (f & 6) {
            if (o->pos[1] > -41.0f) {
                dead = 1;
            } else {
                w->vel14[0] = w->vel14[0] * -1.0f;
                w->vel14[2] = w->vel14[2] * -1.0f;
                if (is19 || is18)
                    w->live10 = 0;
            }
        }
    }
    if (!dead)
        r4c_Spin(o, r4j_spin32C678);
    else
        r4c_FxKill(o);
}
