/* Area m1, file 170: HUD bar control (revisited). Names inferred. */
#include <stdint.h>

typedef struct M1Bar170 {
    uint32_t flags0; int32_t a4; int32_t a8; int32_t aC; int32_t a10; uint8_t unk14[0x10];
    int32_t a24; int32_t a28; int32_t a2C; float f30; uint8_t rest[0x2A4 - 0x34];
} M1Bar170;
extern M1Bar170 m1_hudBars37F550[2];
extern uint8_t m1_txtLv37F9FC[];
void sub_00032140(int a, int b, int c);
int  sub_000D9A70(int id);
void sub_000150B0(void *t, int k);

/* 0x260C0: open (mode 1, level n 1..4) or close (mode 0) a player HUD bar. */
void m1_HudBarSet0260C0(int p, int mode, int n) {
    M1Bar170 *s = &m1_hudBars37F550[p];
    sub_00032140(1, 0, 0);
    switch (mode) {
    case 0:
        switch (s->a4) {
        case 1: s->f30 = 20.0f - s->f30; s->a8 = 0; s->a4 = 2; return;
        case 3: s->a8 = 0; s->a24 = 0; s->a4 = 2; return;
        }
        return;
    case 1:
        if (n >= 5) for (;;) ;
        if (n < 1) n = 1;
        if (p == 1 && sub_000D9A70(0xF8) != 0) return;
        s->a4 = 1; s->a8 = 3; s->aC = 2; s->a10 = 0; s->a28 = 0xD0; s->a2C = n; s->a24 = 0;
        if (p == 1) sub_000150B0(m1_txtLv37F9FC, n + 6);
        return;
    }
}

extern int32_t m1_ldState3F6108;
extern int32_t m1_ldOn3F60F8;
extern int32_t m1_ldFiles318CA8[16];
int   m1_FileBusy04F6D0(int f);
int   m1_FileSize04F680(int f);
void *sub_00053AB0(int size, int a, int tag);
void  m1_FileRead0512D0(int f, void *buf);

/* 0xF3260: start loading data file idx (0..15) when idle; 0 when started or busy, -1 on bad input. */
int m1_FileStart0F3260(int idx) {
    volatile int k;
    switch (m1_ldState3F6108) {
    case 0:
        if (m1_ldOn3F60F8 == 0) return -1;
        k = idx;
        if (k < 0 || k >= 0x10) return -1;
        if (m1_ldFiles318CA8[idx] == -1) return 0;
        if (m1_FileBusy04F6D0(m1_ldFiles318CA8[idx]) != 0) return 0;
        m1_FileRead0512D0(m1_ldFiles318CA8[idx], sub_00053AB0(m1_FileSize04F680(m1_ldFiles318CA8[idx]), 0, 0x1B3));
    case 1:
        m1_ldState3F6108 = 0;
        return 0;
    }
    return 1;
}

int  m1_SndChCue199DE0(int ch);
void m1_SndChPlay199C10(int cue, int ch);
void m1_SndCue19B5C0(int cue);

/* 0x47A80: play a music cue (3..23): cues 5..13 go to a free channel (7, 3, 4 or 9) unless already playing. */
void m1_MusicCue047A80(int cue) {
    volatile int k = cue; int ch, r;
    if (k < 3 || k >= 0x18) return;
    if (k < 5 || k >= 0xE) { m1_SndCue19B5C0(cue); return; }
    if (m1_SndChCue199DE0(7) != -1) goto try9;
    ch = 3;
    r = m1_SndChCue199DE0(3);
    if (r == cue) return;
    if (r == -1) goto play;
    ch = 4;
    r = m1_SndChCue199DE0(4);
    if (r == cue) return;
    if (r == -1) goto play;
try9:
    ch = 9;
    if (m1_SndChCue199DE0(9) == cue) return;
play:
    m1_SndChPlay199C10(cue, ch);
}
