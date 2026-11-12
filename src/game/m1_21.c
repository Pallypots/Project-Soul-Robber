/* Area m1, file 21: actor input reactions. Names inferred. */
#include <stdint.h>

typedef struct M1Act150 {
    uint8_t  unk000[0xEC];
    int32_t  stateEC;          /* +0x0EC */
    uint8_t  unk0F0[0x150 - 0xF0];
    uint32_t flags150;         /* +0x150 */
} M1Act150;
extern uint32_t r6g_keyMask41CD00[10];  /* 0x0041CD00 button mask per action */
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
