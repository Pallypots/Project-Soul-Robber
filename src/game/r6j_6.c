/* Area r6j: script text tokenizer (r6j_6). Names inferred. */
#include "r6j.h"

/* Character class used by the tokenizer (inlined twice in the original):
   1 upper case letter, 2 lower case letter, 3 digit, 4 ':', 5 new line,
   6 end of text, 0 anything else. */
static int r6j_CharClass(char c)
{
    if (c == '\0')
        return 6;
    if (c == '\n')
        return 5;
    if (c == ':')
        return 4;
    if (c >= '0' && c <= '9')
        return 3;
    if (c >= 'A' && c <= 'Z')
        return 1;
    if (c >= 'a' && c <= 'z')
        return 2;
    return 0;
}

/* 0x00090100: read one token from `src` into `tok`. Leading spaces, tabs
   and carriage returns are skipped and counted in tok->lead. A word of
   letters and digits is copied upper-cased (kind 1) until the next
   character is not part of a word; ':' (kind 0) and a new line (kind 2)
   are single-character tokens; the end of the text gives an empty token
   of kind 3. Any other character ends the token without setting the kind.
   At most 0x100 characters are copied. regargs: src=EAX tok=stack. */
void r6j_ReadToken(const char *src, R6jToken *tok)
{
    uint32_t n = 0;
    uint32_t skip = 0;
    char *out = tok->text;
    char c;
    int cls, next;

    while (*src == ' ' || *src == '\r' || *src == '\t') {
        skip++;
        src++;
    }
    tok->lead = (uint8_t)skip;
    do {
        c = src[0];
        cls = r6j_CharClass(c);
        next = r6j_CharClass(src[1]);
        if (cls == 0)
            break;
        switch (cls) {
        case 2:
            c -= 0x20;
            /* fall through */
        case 1:
        case 3:
            *out++ = c;
            n++;
            src++;
            if (next == 0 || (next > 4 && next <= 6)) {
                *out = '\0';
                tok->len = (uint8_t)n;
                tok->kind = 1;
                return;
            }
            break;
        case 4:
            out[0] = c;
            out[1] = '\0';
            tok->len = (uint8_t)(n + 1);
            tok->kind = 0;
            return;
        case 5:
            out[0] = c;
            out[1] = '\0';
            tok->len = (uint8_t)(n + 1);
            tok->kind = 2;
            return;
        case 6:
            *out = '\0';
            tok->len = 0;
            tok->kind = 3;
            return;
        }
    } while (n < 0x100);
    *out = '\0';
    tok->len = (uint8_t)n;
}
