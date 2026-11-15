/* Area m3, file 4: menu mode setup, random enemy pick. Names inferred. */
#include <stdint.h>

typedef struct M3Slot4 { uint8_t unk00[0x48]; int32_t i48; } M3Slot4;
M3Slot4 *m1_SlotGet0A4290(int i);
void sub_000A42F0(int i, int v);
int  r2b_TestBit(int bit);

/* 0xB7EE0: mode setup for a 2-int setting: 0 clears, 1 sets bit 0 and 10; mode 3 or a setting of 20 clears and returns 0; a setting of 10 syncs slot 2 with story bit 0xC0 (bit clear and slot set -> 0, bit set and slot not 1 -> 1). */
int m3_ModeSetupB7EE0(int k, int *s) {
    if (k == 0) { s[0] = 0; s[1] = 0; return 1; }
    if (k == 1) { s[0] |= 1; s[1] = 10; return 1; }
    if (k != 3) {
        if (s[1] == 10) {
            M3Slot4 *o = m1_SlotGet0A4290(2);
            int b = r2b_TestBit(0xC0);
            int v = o->i48;
            if (!b) {
                if (v) { sub_000A42F0(2, 0); return 1; }
            } else if (v != 1) {
                sub_000A42F0(2, 1);
            }
            return 1;
        }
        if (s[1] != 0x14) return 1;
    }
    s[0] = 0; s[1] = 0;
    return 0;
}

extern int m3_forceKind420090;
int  aab_Rand(void);
void sub_000A8990(int kind, int a, int b, int c, float *pos, float *dir);

/* 0xA9340: pick a random enemy kind: from {3, 4, 0x17} when c is 0, else from {-1, 3, 4, 0x17}; kind 0x17 becomes 3 or 4 at random unless 0x420090 is set. Spawn it via 0xA8990 at the origin. */
void m3_SpawnRandomA9340(int c) {
    int t[4]; float v[4]; int d;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    t[0] = -1; t[1] = 3; t[2] = 4; t[3] = 0x17;
    if (c == 0) d = t[aab_Rand() % 3 + 1];
    else { volatile int z; z = 0; d = t[aab_Rand() % 4]; }
    if (d == 0x17 && m3_forceKind420090 == 0) d = (aab_Rand() & 1) ? 3 : 4;
    sub_000A8990(d, 2, 0, c, v, v);
}

typedef struct M3Ob4 { uint8_t unk00[0x10]; uint32_t f10; } M3Ob4;
typedef struct M3En4 { uint8_t unk00[0x20]; uint32_t f20; uint8_t unk24[0x28]; uint32_t f4C; uint8_t unk50[4]; int32_t i54; uint8_t unk58[0x1C]; float f74; } M3En4;

/* 0x138640: AI idle entry: flags |= 6 (clear 0x20), clear bit 0x10; unless bit 0 of +0x20 is set, pick a random wait: 1..2 for kinds 11 and 6, else 8..10 or 5..8 at random. */
void m3_AiIdleWait138640(M3Ob4 *a, M3En4 *o) {
    a->f10 = (a->f10 & ~0x20u) | 6;
    o->f4C &= ~0x10u;
    if (*(uint8_t *)&o->f20 & 1) return;
    if (o->i54 == 0xB || o->i54 == 6) { o->f74 = (float)(aab_Rand() % 2) + 1.0f; return; }
    if (aab_Rand() % 2 < 1) o->f74 = (float)(aab_Rand() % 3) + 8.0f;
    else o->f74 = (float)(aab_Rand() % 4) + 5.0f;
}
