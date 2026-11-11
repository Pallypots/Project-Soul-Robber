/* Area r4: skin bone masks, worker-thread records and device handles, 0x001A1CE0-0x001AEFC4 (r4_7). Names inferred. */
#include "r4.h"

/* 0x001A1CE0: reset the device handle table and query the eight device slots. No register inputs. */
int r4_DevicesInit(void)
{
    int i;
    a1a_g4046D8[0] = 0;
    a1a_g4046D8[1] = -1;
    a1a_g4046D8[2] = -1;
    a1a_g4046D8[3] = -1;
    a1a_g4046D8[4] = -1;
    a1a_g4046D8[5] = -1;
    a1a_g4046D8[6] = -1;
    a1a_g4046D8[7] = -1;
    a1a_g4046D8[8] = -1;
    a1a_g4046D4 = 0;
    for (i = 0; i < 8; i++)
        sub_001D1B80(r4_g337EE4[i], &a1a_g4046D8[1 + i]);
    return 1;
}

/* 0x001AD340: set the state of the worker thread with the given id; 0 on success, -1 if unknown.
   regargs: id=EAX state=stack. */
int r4_ThreadSetState(int id, int state)
{
    R4ThreadRec *t;
    sub_001AA1E0(r4_g40F0D8);
    for (t = aac_g40EDD8; t != aac_g40EDD8 + 32; t++) {
        if (t->id == id) {
            t->state = state;
            sub_001AA1F0(r4_g40F0D8);
            return 0;
        }
    }
    sub_001AA1F0(r4_g40F0D8);
    return -1;
}

/* 0x001AEE50: AND of the masks of all bones that have a +0xBC entry (-1 when none). Stack arg
   (callers push a 2nd one that is never read). */
uint32_t r4_SkinBoneMask(R4Skin *s, int unused)
{
    uint32_t mask = 0xFFFFFFFF;
    int i;
    R4Bone *b = s->bones;
    for (i = 0; i < s->count; i++, b++)
        if (b->iBC)
            mask &= b->maskB8;
    return mask;
}

/* 0x001AEF60: reset the shared skin state and clear every bone's runtime fields. regargs: s=EAX. */
void r4_SkinReset(R4Skin *s)
{
    int i, n;
    R4Bone *b;
    r4_g40F150 = 1;
    r4_g40F154 = 0;
    r4_g40F158 = 0;
    r4_g40F15C = 0;
    sub_001AD940(r4_g40F160);
    n = s->count;
    b = s->bones;
    for (i = 0; i < n; i++, b++) {
        b->iBC = 0;
        b->fD0 = 0.0f;
        b->iCC = 0;
    }
}
