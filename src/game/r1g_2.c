/* Area r1g, group 2: button-sequence matcher 0x0001B150. Names inferred. */
#include "r1g.h"

/* 0x0001B150: age the recent-button ring of `kb`, append the letter of the
   button newly pressed on `pad` (kept for 180 frames), then look for a code
   in kb->codes whose letters end the ring. On a match the ring is emptied,
   kb->matched is set and the code's index is returned; otherwise -1. */
int r1g_KeySeqUpdate(R1gKeyBuf *kb, int pad)
{
    int found = -1;
    int i;
    uint32_t bits;
    for (i = kb->head; i != kb->tail; i = (i + 1) % 32) {
        if (--kb->ent[i].life <= 0)
            kb->head = (i + 1) % 32;
    }
    bits = sub_0004ECE0(pad);
    if (bits) {
        int t = kb->tail;
        int h = kb->head;
        char c;
        if ((t + 1) % 32 == h)
            kb->head = (h + 1) % 32;
        if (bits & 0x1000) c = 'u';
        else if (bits & 0x4000) c = 'd';
        else if (bits & 0x2000) c = 'r';
        else if ((int8_t)(bits >> 8) < 0) c = 'l';   /* bit 0x8000 */
        else if (bits & 0x4) c = 'a';
        else if (bits & 0x1) c = 'b';
        else if (bits & 0x200) c = 'c';
        else if (bits & 0x10) c = 'U';
        else if (bits & 0x40) c = 'D';
        else if (bits & 0x20) c = 'R';
        else if (bits & 0x80) c = 'L';
        else if (bits & 0x8) c = 'A';
        else if (bits & 0x2) c = 'B';
        else c = (bits & 0x400) ? 'C' : '?';
        kb->ent[t].key = c;
        kb->ent[kb->tail].life = 180;
        kb->tail = (kb->tail + 1) % 32;
    }
    if (kb->head == kb->tail)
        return -1;
    {
        R1gCode *codes = kb->codes;
        int k;
        if (codes[0].seq == 0)
            return -1;
        k = 0;
        do {
            const char *s = codes[k].seq;
            int n = (int)strlen(s) - 1;
            int j = kb->tail;
            do {
                j = (j + 31) % 32;
                if (s[n] != kb->ent[j].key) break;
                n--;
                if (kb->head == j) break;
            } while (n >= 0);
            if (n < 0) {
                found = k;
                kb->tail = 0;
                kb->head = 0;
                kb->matched = k;
            }
            k++;
        } while (kb->codes[k].seq);
    }
    return found;
}
