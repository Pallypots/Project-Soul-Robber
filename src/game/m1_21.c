/* Area m1, file 21: actor input reactions. Names inferred. */
#include <stdint.h>

typedef struct M1Act150 {
    uint8_t  unk000[0xD4];
    int32_t  modeD4;           /* +0x0D4 */
    uint8_t  unk0D8[0xEC - 0xD8];
    int32_t  stateEC;          /* +0x0EC */
    uint8_t  unk0F0[0x150 - 0xF0];
    uint32_t flags150;         /* +0x150 */
    uint8_t  unk154[0x18C - 0x154];
    int32_t  swap18C;          /* +0x18C swapped confirm/cancel layout */
    uint8_t  unk190[0x1B8 - 0x190];
    int32_t  handler1B8;       /* +0x1B8 index into the 0xCDA00 handler list */
    uint8_t  unk1BC[0x1D8 - 0x1BC];
    int32_t  pick1D8;          /* +0x1D8 */
} M1Act150;
extern uint32_t r6g_keyMask41CD00[13];  /* 0x0041CD00 button mask per action */
void abc_SetState(M1Act150 *a, int state);

/* 0x000CC840: when idle, enters state 0x24 for buttons b in mask A or state
 * 0x28 for buttons a in mask B; 1 when started, else -1. */
int m1_ReactButtonsCC840(M1Act150 *o, uint32_t a, uint32_t b)
{
    if (o->stateEC != 0 || (o->flags150 & 1))
        return -1;
    if (b & r6g_keyMask41CD00[0]) {
        o->stateEC = 4;
        o->flags150 |= 0x800;
        abc_SetState(o, 0x24);
        return 1;
    }
    if (a & r6g_keyMask41CD00[1]) {
        o->stateEC = 4;
        o->flags150 |= 0x800;
        abc_SetState(o, 0x28);
        return 1;
    }
    return -1;
}

typedef struct M1Seq {
    uint32_t flags00;          /* +0x00 */
    int32_t  step04;           /* +0x04 */
    int32_t  ticks08;          /* +0x08 */
} M1Seq;
void sub_000A43C0(int slot, int fx);

/* 0x000AC9D0: tiny sequencer. cmd 0 clears, 1 arms (step 10), 3 finishes (step 0x14);
 * other commands tick; step 10 fires event 0x24 once. 0 when finished, else 1. */
int m1_SeqStepAC9D0(int cmd, M1Seq *s, int slot)
{
    if (cmd == 0) {
        s->flags00 = 0;
        s->step04 = 0;
        s->ticks08 = 0;
        return 1;
    }
    if (cmd == 1) {
        s->flags00 |= 1;
        s->step04 = 10;
        s->ticks08 = 0;
        return 1;
    }
    if (cmd == 3) {
        s->flags00 = 0;
        s->step04 = 0x14;
    }
    s->ticks08++;
    if (s->step04 == 10) {
        sub_000A43C0(slot, 0x24);
        s->step04++;
    } else if (s->step04 == 0x14) {
        s->flags00 = 0;
        s->step04 = 0;
        return 0;
    }
    return 1;
}

/* 0x000ADB60: twin of 0xAC9D0: arming sets flags 3 and step 10 fires fx 0x25. */
int m1_SeqStepADB60(int cmd, M1Seq *s, int slot)
{
    if (cmd == 0) {
        s->flags00 = 0;
        s->step04 = 0;
        s->ticks08 = 0;
        return 1;
    }
    if (cmd == 1) {
        s->flags00 |= 3;
        s->step04 = 10;
        s->ticks08 = 0;
        return 1;
    }
    if (cmd == 3) {
        s->flags00 = 0;
        s->step04 = 0x14;
    }
    s->ticks08++;
    if (s->step04 == 10) {
        sub_000A43C0(slot, 0x25);
        s->step04++;
    } else if (s->step04 == 0x14) {
        s->flags00 = 0;
        s->step04 = 0;
        return 0;
    }
    return 1;
}

void sub_000A42F0(int slot, int v);

/* 0x000AC8A0: twin of 0xAC9D0; step 10 resets the slot (0xA42F0 v=0) then fires fx 0x23. */
int m1_SeqStepAC8A0(int cmd, M1Seq *s, int slot)
{
    if (cmd == 0) {
        s->flags00 = 0;
        s->step04 = 0;
        s->ticks08 = 0;
        return 1;
    }
    if (cmd == 1) {
        s->flags00 |= 1;
        s->step04 = 10;
        s->ticks08 = 0;
        return 1;
    }
    if (cmd == 3) {
        s->flags00 = 0;
        s->step04 = 0x14;
    }
    s->ticks08++;
    if (s->step04 == 10) {
        sub_000A42F0(slot, 0);
        sub_000A43C0(slot, 0x23);
        s->step04++;
    } else if (s->step04 == 0x14) {
        s->flags00 = 0;
        s->step04 = 0;
        return 0;
    }
    return 1;
}

/* 0x000AC930: variant: step 10 fires fx 0x22 on slots 0x10, 0x12 and 0x14;
 * the sequence ends at step 11 or 0x14. */
int m1_SeqStepAC930(int cmd, M1Seq *s)
{
    if (cmd == 0) {
        s->flags00 = 0;
        s->step04 = 0;
        s->ticks08 = 0;
        return 1;
    }
    if (cmd == 1) {
        s->flags00 |= 1;
        s->step04 = 10;
        s->ticks08 = 0;
        return 1;
    }
    if (cmd == 3) {
        s->flags00 = 0;
        s->step04 = 0x14;
    }
    s->ticks08++;
    switch (s->step04) {
    case 10:
        sub_000A43C0(0x10, 0x22);
        sub_000A43C0(0x12, 0x22);
        sub_000A43C0(0x14, 0x22);
        s->step04++;
        break;
    case 11:
    case 0x14:
        s->flags00 = 0;
        s->step04 = 0;
        return 0;
    }
    return 1;
}

/* 0x000CC8C0: idle, unflagged actor: buttons in key mask 2 or 5 -> state 0xB,
 * mask 3 -> 0xC, mask 4 -> 0xD; then marks it busy (0x40000001).
 * regargs: o=ESI buttons=EAX */
void m1_ReactButtonsCC8C0(M1Act150 *o, uint32_t buttons)
{
    int st;
    if (o->flags150 & 0x80000001)
        return;
    if (o->stateEC != 0)
        return;
    if ((buttons & r6g_keyMask41CD00[2]) || (buttons & r6g_keyMask41CD00[5]))
        st = 0xB;
    else if (buttons & r6g_keyMask41CD00[3])
        st = 0xC;
    else if (buttons & r6g_keyMask41CD00[4])
        st = 0xD;
    else
        return;
    abc_SetState(o, st);
    o->flags150 |= 0x40000001;
}

typedef int (*M1ActHandler)(M1Act150 *o, uint32_t a, uint32_t b);
int  sub_000CD8D0(M1Act150 *o, uint32_t a, uint32_t b);
int  sub_000CCF60(M1Act150 *o, uint32_t a, uint32_t b);

/* 0x000CDA00: unless flagged 0xC0000000, runs the actor's current handler
 * (0xCD8D0, 0xCCF60 or 0xCC840); a positive result sets flag 1.
 * regargs: o=ESI a=EDX b=ECX */
void m1_RunHandlerCDA00(M1Act150 *o, uint32_t a, uint32_t b)
{
    M1ActHandler fns[3];
    fns[0] = sub_000CD8D0;
    fns[1] = sub_000CCF60;
    fns[2] = m1_ReactButtonsCC840;
    if (o->flags150 & 0xC0000000)
        return;
    if (fns[o->handler1B8](o, a, b) > 0)
        o->flags150 |= 1;
}


/* 0x000B6300: sequencer twin of 0xAC8A0 (step 10 resets the slot and fires fx 0x20).
 * regargs: cmd=EAX s=ESI slot=EDI */
int m1_SeqStepB6300(int cmd, M1Seq *s, int slot)
{
    if (cmd == 0) {
        s->flags00 = 0;
        s->step04 = 0;
        s->ticks08 = 0;
        return 1;
    }
    if (cmd == 1) {
        s->flags00 |= 1;
        s->step04 = 10;
        s->ticks08 = 0;
        return 1;
    }
    if (cmd == 3) {
        s->flags00 = 0;
        s->step04 = 0x14;
    }
    s->ticks08++;
    if (s->step04 == 10) {
        sub_000A42F0(slot, 0);
        sub_000A43C0(slot, 0x20);
        s->step04++;
    } else if (s->step04 == 0x14) {
        s->flags00 = 0;
        s->step04 = 0;
        return 0;
    }
    return 1;
}

typedef struct M1Pad4C {
    uint32_t pressed00;        /* +0x00 (0x0042CA34 for pad 0) */
    uint32_t held04;           /* +0x04 */
    uint8_t  unk08[0x4C - 8];
} M1Pad4C;
extern M1Pad4C  m1_pads42CA34[4];      /* 0x0042CA34 */
extern uint32_t aa0_flags420010;       /* 0x00420010 */
extern int32_t  m1_gameMode41FF94;     /* 0x0041FF94 */
int sub_0019BE60(int k);

/* 0x000CCD60: key mask k on pad p (pressed when edge is set, else held), or 0 while
 * input is blocked (flags 0x82006, game modes 2/4/5, or system key 0x4101). */
uint32_t m1_PadKeyCCD60(int p, int k, int edge)
{
    if (aa0_flags420010 & 0x82006)
        return 0;
    if (m1_gameMode41FF94 == 2 || m1_gameMode41FF94 == 4 || m1_gameMode41FF94 == 5)
        return 0;
    if (sub_0019BE60(0x4101))
        return 0;
    if (edge == 0)
        return m1_pads42CA34[p].held04 & r6g_keyMask41CD00[k];
    return m1_pads42CA34[p].pressed00 & r6g_keyMask41CD00[k];
}

extern uint32_t *m1_padMasks2C4AE8;    /* 0x002C4AE8 */

/* 0x000CC430: default key masks for the 13 actions; action 6 then takes the pad
 * table's entry 5. */
void m1_DefaultKeysCC430(void)
{
    r6g_keyMask41CD00[0] = 0x80;
    r6g_keyMask41CD00[6] = 0x40;
    r6g_keyMask41CD00[7] = 2;
    r6g_keyMask41CD00[8] = 4;
    r6g_keyMask41CD00[9] = 8;
    r6g_keyMask41CD00[10] = 1;
    r6g_keyMask41CD00[4] = 0x2000;
    r6g_keyMask41CD00[3] = 0x8000;
    r6g_keyMask41CD00[11] = 0x10;
    r6g_keyMask41CD00[5] = 0x4000;
    r6g_keyMask41CD00[12] = 0x80;
    r6g_keyMask41CD00[1] = 0x10;
    r6g_keyMask41CD00[2] = 0x1000;
    r6g_keyMask41CD00[6] = m1_padMasks2C4AE8[5];
}
