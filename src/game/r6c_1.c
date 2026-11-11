/* Area r6c: encoded text helpers and sound channels around 0x00076120-0x00077410 (r6c_1). Names inferred. */
#include "r6c.h"

/* 0x00076120: rewind both animation players of a text box unless a movie owns the screen.
   regargs: t=EAX */
void r6c_TextReset(R6cText *t)
{
    uint32_t saved;
    if (!t)
        return;
    if (sub_0019BE60(0x8000) && sub_00079460())
        return;
    saved = a19_g413174;
    sub_0019BEB0(0x8000);
    sub_00014E80(t->anim8CC);
    sub_00014E80(t->anim830);
    a19_g413174 = saved;
}

/* 0x000762A0: number of visible characters in an encoded string; hangs on NULL. */
int r6c_TextCount(const uint8_t *s)
{
    int i = 0;
    int n = 0;
    if (!s)
        for (;;) ;
    while (s[i]) {
        if (s[i] == 6)
            break;
        if (s[i] >= 8 || s[i] == 5)
            n++;
        R6C_TEXT_SKIP(s, i);
        i++;
    }
    return n;
}

/* 0x00076330: length in bytes of an encoded string; hangs on NULL. */
int r6c_TextLen(const uint8_t *s)
{
    int i = 0;
    if (!s)
        for (;;) ;
    while (s[i]) {
        R6C_TEXT_SKIP(s, i);
        i++;
    }
    return i;
}

/* 0x000763A0: byte index of visible character n of an encoded string. */
int r6c_TextIndex(const uint8_t *s, int n)
{
    int i = 0;
    while (s[i]) {
        if (s[i] == 6)
            break;
        if (s[i] >= 8 || s[i] == 5)
            n--;
        if (n < 0)
            break;
        R6C_TEXT_SKIP(s, i);
        i++;
    }
    return i;
}

/* 0x00076620: move the cursor past the next page break and recount the page. */
void r6c_TextNextPage(R6cText *t)
{
    int i = t->pos;
    while (t->buf[i]) {
        if (t->buf[i] == 6) {
            R6C_TEXT_SKIP(t->buf, i);
            i++;
            break;
        }
        R6C_TEXT_SKIP(t->buf, i);
        i++;
    }
    t->pos = i;
    t->pageChars = r6c_TextPageChars(t);
}

/* 0x000773A0: restart a channel at the given level and write its registers. */
void r6c_ChannelPlay(int ch, uint16_t level)
{
    a60_chFlags[ch] &= ~0x80;
    *a60_chReg660[ch] &= ~0x80u;
    a60_chFlags[ch] |= 0x80;
    *a60_chReg650[ch] = (*a60_chReg650[ch] & 0xFFFF0000u) | level;
    *r6c_chReg670[ch] = a60_chVol[ch];
    *a60_chReg660[ch] = a60_chFlags[ch];
}
