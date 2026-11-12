/* Area m1, file 34: fade channel colour (records at 0x003DA4A8 / quads at 0x003DA500). Names inferred. */
#include <stdint.h>

typedef struct M1FadeChan2C {
    uint8_t unk00[0x10];
    uint8_t level10;           /* +0x10 */
    uint8_t unk11[0x2C - 0x11];
} M1FadeChan2C;
extern M1FadeChan2C m1_fadeChans3DA4A8[];  /* 0x003DA4A8 */
typedef struct M1QVert38 {
    uint8_t b00;
    uint8_t r01, g02, b03, a04;  /* +0x01..+0x04 */
    uint8_t unk05[0x38 - 5];
} M1QVert38;
typedef struct M1FadeQuad {
    uint8_t   unk0000[0x1340];
    M1QVert38 v[4];            /* +0x1340 */
    uint8_t   unk1420[0x1450 - 0x1420];
} M1FadeQuad;
extern M1FadeQuad m1_fadeQuads3DA500[];   /* 0x003DA500 */

/* 0x00039660: sets the four vertices of channel i's quad to grey level (alpha 0x80).
 * regargs: i=EAX */
void m1_FadeColour39660(int i)
{
    M1FadeQuad *q = &m1_fadeQuads3DA500[i];
    uint8_t c = m1_fadeChans3DA4A8[i].level10;
    int k;
    for (k = 0; k < 4; k++) {
        q->v[k].r01 = c;
        q->v[k].g02 = c;
        q->v[k].b03 = c;
        q->v[k].a04 = 0x80;
    }
}

