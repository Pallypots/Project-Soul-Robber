/* Area r6g: entity teardown (r6g_13). Names inferred. */
#include "r6g.h"

/* 0x000A5520: tear down the entities of the current area: release every active
   entity slot (0x000A4DE0) while stepping 0x000A3810 once per slot, detach the
   paired model records (2 in mode 12, else 16) and free both model tables,
   then clear the entity id table and count. */
void r6g_EntitiesRelease(void)
{
    R6gCtx *ctx = (R6gCtx *)r6f_ctx42C8E4;
    R6gSlot *s;
    int i;

    for (s = aa0_slots; s < aa0_slots + 32; s++) {
        if (s->u.flags & 1)
            sub_000A4DE0(s);
        sub_000A3810();
    }
    if (r6g_entMdlA3ED52C) {
        if (r6g_entMode423FE4 != 0xC) {
            for (i = 0; i < 16; i++) {
                r6g_entMdlA3ED52C[i].flags &= ~1u;
                sub_0001EB80((R6eModel *)&r6g_entMdlA3ED52C[i]);
                r6g_entMdlB3ED530[i].flags &= ~1u;
                sub_0001EB80((R6eModel *)&r6g_entMdlB3ED530[i]);
            }
        } else {
            for (i = 0; i < 2; i++) {
                r6g_entMdlA3ED52C[i].flags &= ~1u;
                sub_0001EB80((R6eModel *)&r6g_entMdlA3ED52C[i]);
                r6g_entMdlB3ED530[i].flags &= ~1u;
                sub_0001EB80((R6eModel *)&r6g_entMdlB3ED530[i]);
            }
        }
        sub_0001D030(ctx->list1E8, r6g_entTblA3ED538);
        sub_00020170(r6g_entTblA3ED538);
        r6g_entTblA3ED538 = 0;
        r6g_entMdlB3ED530 = 0;
        sub_0001D030(ctx->list1E8, r6g_entTblB3ED534);
        sub_00020170(r6g_entTblB3ED534);
        r6g_entTblB3ED534 = 0;
        r6g_entMdlA3ED52C = 0;
    }
    sub_00053880(r6g_entTblB3ED534);
    sub_00053880(r6g_entMdlA3ED52C);
    for (i = 0; i < 16; i++)
        r6g_entIds423FEC[i] = -1;
    r6g_entCount423FE8 = 0;
}
