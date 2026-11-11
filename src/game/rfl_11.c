/* Area rfl, group 11: boss damage transfer (0x00108FC0). Names inferred. */
#include "rfl.h"

/* 0x00108FC0: apply the boss's pending damage: when flagged, pass up to the
   remaining health on to the linked object (kind 4) and subtract it from
   the health, clamping at 0; then clear the pending value. Returns 1.
   regargs: o=EDI */
int rfl_BossApplyDamage(RflActor *o)
{
    RflHealth *h = (RflHealth *)sub_0001D960(o, 5);
    float dmg = sub_000F3C70(o);
    float amt;
    if (sub_000F3CB0(o)) {
        if (h->link90) {
            amt = dmg;
            if (amt > h->hp54)
                amt = h->hp54;
            sub_000F3BF0(h->link90, amt, 4);
        }
        h->hp54 -= dmg;
        if (!(0.0f < h->hp54))
            h->hp54 = 0.0f;
    }
    sub_000F3C40(o);
    return 1;
}
