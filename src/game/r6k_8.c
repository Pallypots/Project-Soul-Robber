/* Area r6k: trigger zones (r6k_8). Names inferred. */
#include "r6k.h"

/* 0x000877E0: per-frame trigger zone test. Needs a zone list (0x003ED248)
   and 0x00086C30. Clears the current zone (index -1, pointer and 0x003ED238
   0); when 0x00087AE0 returns 1 sets state 3 and stops. Takes Jack's
   position with the height from his model node (+0x374) and does nothing
   more while it moved less than 0.0001 from the last tested position.
   Otherwise the first used zone that 0x000875E0 accepts becomes current;
   the position is remembered; a forced zone id (0x003ED23C) overrides the
   choice and is cleared; with a current zone, 0x00085390(0) == 1 sets
   state 3. Returns 0. Calls 0x000875E0 with ESI=zone EDI=position
   EBX=last position. */
int r6k_ZonesUpdate(void)
{
    float pos[4];
    R6kZone *zones, *z;
    R6kZoneList *list;
    int i, id;

    if (r6c_v3ED248 == 0 || sub_00086C30() == 0)
        return 0;
    r6c_v3ED234 = -1;
    r6c_v3ED240 = 0;
    r6c_v3ED238 = 0;
    if (sub_00087AE0() == 1) {
        r6c_state3ED21C = 3;
        return 0;
    }
    sub_000F5D40(pos, r6k_player420E98->pos60);
    pos[1] = r6k_player420E98->info20->nodeC4->y374;
    if (0.0001f > sub_001B2730(pos, r6c_target3ED224))
        return 0;
    list = r6c_v3ED248;
    zones = list->zones;
    z = zones;
    for (i = 0; i < list->count; i++, z++) {
        if (z->id != 0) {
            if (sub_000875E0(z, pos, r6c_target3ED224) == 1) {
                r6c_v3ED234 = i;
                r6c_v3ED240 = &zones[i];
                break;
            }
            list = r6c_v3ED248;
        }
    }
    sub_000F5D40(r6c_target3ED224, pos);
    id = r6c_v3ED23C;
    if (id != -1) {
        list = r6c_v3ED248;
        for (i = 0; i < list->count; i++) {
            if (list->zones[i].id == id)
                goto found;
        }
        goto done;
    found:
        if (i != -1) {
            r6c_v3ED234 = i;
            r6c_v3ED240 = &zones[i];
            r6c_v3ED23C = -1;
        }
    }
done:
    if (r6c_v3ED234 >= 0 && sub_00085390(0) == 1)
        r6c_state3ED21C = 3;
    return 0;
}
