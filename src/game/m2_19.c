/* Area m2, file 19: text control-code scanners. Names inferred. */
#include <stdint.h>

typedef struct M2Font19 { uint8_t unk00[8]; uint16_t count8; } M2Font19;
typedef struct M2Text19 { uint8_t unk00[0x2C]; uint8_t buf2C[0x800]; int32_t pos82C; } M2Text19;
extern M2Font19 *r6c_textFont;

/* 0x76180: count the line breaks (code 5) from the current position to the page end (code 6 or the terminator). Code 7 skips its argument (and two more bytes after a 5), code 4 and characters past the font skip one byte. */
int m2_TextLines76180(M2Text19 *t) {
    int i = t->pos82C, n = 0;
    uint8_t c;
    M2Font19 *f;
    if (t->buf2C[i] == 0) return 0;
    f = r6c_textFont;
    c = t->buf2C[i];
    do {
        if (c == 6) break;
        if (c == 5) n++;
        switch (c) {
        case 1: case 2: case 3: case 5: case 6: break;
        case 4: i++; break;
        case 7: {
            uint8_t a = t->buf2C[i + 1];
            i++;
            if (a == 5) i += 2;
            break;
        }
        default:
            if ((uint16_t)c >= f->count8) i++;
            break;
        }
        c = t->buf2C[i + 1];
        i++;
    } while (c != 0);
    return n;
}

/* 0x76210: 1 when a page end (code 6) follows the current position before the terminator, else 0 (same skipping rules as 0x76180). */
int m2_TextHasPage76210(M2Text19 *t) {
    int i = t->pos82C;
    uint8_t c;
    M2Font19 *f;
    if (t->buf2C[i] == 0) return 0;
    f = r6c_textFont;
    c = t->buf2C[i];
    do {
        if (c == 6) return 1;
        switch (c) {
        case 1: case 2: case 3: case 5: case 6: break;
        case 4: i++; break;
        case 7: {
            uint8_t a = t->buf2C[i + 1];
            i++;
            if (a == 5) i += 2;
            break;
        }
        default:
            if ((uint16_t)c >= f->count8) i++;
            break;
        }
        c = t->buf2C[i + 1];
        i++;
    } while (c != 0);
    return 0;
}
