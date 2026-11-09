/* Area aab, group 3: table getters and message handlers (0x000AB9C0..0x000B7EE0). Names inferred. */
#include "aab.h"

/* 0x000AB9C0: address of the table at 0x002E4A48. */
uint8_t *aab_GetTable2E4A48(void) { return aab_data2E4A48; }

/* 0x000B5C00: address of the table at 0x002E5700. */
uint8_t *aab_GetTable2E5700(void) { return aab_data2E5700; }

/* 0x000B7E90: message handler: 0 init, 1 start (step 10), 3 stop (returns 0). */
int aab_MsgHandlerB7E90(int msg, AabMsgState *st)
{
    if (msg == 0) { st->flags = 0; st->step = 0; return 1; }
    if (msg == 1) { st->flags |= 1; st->step = 10; return 1; }
    if (msg == 3) { st->flags = 0; st->step = 0; return 0; }
    return 1;
}
