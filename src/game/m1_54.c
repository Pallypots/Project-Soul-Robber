/* Area m1, file 54: sound voice timing. Names inferred. */
#include <stdint.h>

typedef struct M1Wave { uint32_t flags00; uint8_t unk04[0x1C - 4]; float pre1C; uint8_t unk20[0x5C - 0x20]; float len5C, tail60; } M1Wave;
typedef struct M1Trk12C { uint8_t unk000[0xB0]; uint32_t flagsB0; uint8_t unkB4[0x118 - 0xB4]; M1Wave *wave118; uint8_t unk11C[0x12C - 0x11C]; } M1Trk12C;
typedef struct M1Cue { uint8_t unk00[0xB0]; uint32_t countB0; M1Trk12C *trksB4; uint32_t flagsB8; } M1Cue;
typedef struct M1CueOwner { uint8_t unk00[0xB0]; M1Cue *cueB0; float lenB4; } M1CueOwner;

/* 0x001B6A90: cue length: the longest wave (length + tail, plus pre-delay with wave flag 2)
 * over the cue's enabled tracks goes to o +0xB4, and the cue gets flag 0x200. */
void m1_CueLength1B6A90(M1CueOwner *o)
{
    M1Cue *c = o->cueB0;
    M1Trk12C *t;
    M1Wave *w;
    float m, v;
    uint32_t n;
    if (c == 0)
        return;
    m = 0.0f;
    if (c->countB0 > 0) {
        t = c->trksB4;
        for (n = c->countB0; n != 0; n--, t++) {
            if (!(t->flagsB0 & 1) || (w = t->wave118) == 0)
                continue;
            v = w->tail60 + w->len5C;
            if (w->flags00 & 2)
                v = w->pre1C + v;
            if (v > m)
                m = v;
        }
    }
    o->lenB4 = m;
    c->flagsB8 |= 0x200;
}
