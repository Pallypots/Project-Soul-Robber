/* Area m1, file 208: event handlers. Names inferred. */
#include <stdint.h>

typedef struct M1Ev208 { uint32_t flags0; int32_t phase4; } M1Ev208;
void sub_000DFD40(int *a, int *st);
void sub_000A4340(int slot, int mode);
int  sub_000A4370(int slot);

/* 0xB77C0: slot event handler: 0 clears, 1 arms (phase 0xA), 3 resets; while armed open the slot (mode 0), wait for it, then set mode 3 and move to phase 0x14, which resets. A flagged event first waits for the story to settle and uses slot 3. */
int m1_SlotEvent0B77C0(int msg, M1Ev208 *t) {
    int st, slot; int volatile a, s;
    if (msg == 0) { t->flags0 = 0; t->phase4 = 0; return 1; }
    if (msg == 1) { t->flags0 |= 1; t->phase4 = 0xA; return 1; }
    if (msg == 3) { t->flags0 = 0; t->phase4 = 0; return 0; }
    if (t->flags0 & 1) {
        sub_000DFD40(&msg, &st);
        a = msg;
        while (a != 0) ;
        s = st;
        while (s != 0 && s != 1 && s != 2) ;
        slot = 3;
    } else slot = msg;
    switch (t->phase4) {
    case 0xA:
        sub_000A4340(slot, 0);
        t->phase4++;
        return 1;
    case 0xB:
        if (sub_000A4370(slot)) { sub_000A4340(slot, 3); t->phase4 = 0x14; return 1; }
        return 1;
    case 0x14:
        t->flags0 = 0; t->phase4 = 0;
        return 0;
    }
    return 1;
}

typedef struct M1VcO208 { uint8_t unk00[0x2E8]; int32_t snd2E8; int32_t ch2EC; uint8_t unk2F0[0x10]; int32_t st300[7]; int32_t ch31C; } M1VcO208;
typedef struct M1VcC208 { uint8_t unk00[0xC]; int32_t modeC; int32_t part10; int32_t state14; } M1VcC208;
uint8_t *sub_000E3DA0(M1VcO208 *o, int st);
int  sub_0019AD10(int snd, int part);
void sub_000497E0(int ch, int part, int r, void *pos, int a, float b, int c);
void sub_00048450(int ch, int part);
void r1c_SetRecThunk(int ch, int part, int v);

/* 0xEB080: set a voice part's state: 0 stops it, 1 restarts it plain, other states play it positioned at the state's emitter (range 1000); remember the state. */
void m1_VoicePart0EB080(M1VcO208 *o, M1VcC208 *c) {
    int ch; uint8_t *p;
    if (c == 0 || o == 0) return;
    switch (c->modeC) {
    case 0: ch = o->ch2EC; break;
    case 1: ch = o->ch31C; break;
    default: return;
    }
    if (ch < 0) return;
    switch (c->state14) {
    case 0:
        sub_00048450(ch, c->part10);
        r1c_SetRecThunk(ch, c->part10, 0);
        o->st300[c->part10] = c->state14;
        return;
    case 1:
        sub_00048450(ch, c->part10);
        r1c_SetRecThunk(ch, c->part10, sub_0019AD10(o->snd2E8, c->part10));
        o->st300[c->part10] = c->state14;
        return;
    default:
        p = sub_000E3DA0(o, c->state14);
        sub_000497E0(ch, c->part10, sub_0019AD10(o->snd2E8, c->part10), p + 0x60, 0, 1000.0f, 1);
        o->st300[c->part10] = c->state14;
        return;
    }
}
