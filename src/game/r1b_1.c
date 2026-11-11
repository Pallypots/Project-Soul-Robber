/* Area r1b, group 1: text tokenizer and file buffer 0x00013140..0x00013480. Names inferred. */
#include "r1b.h"

/* 0x00013140: skip separators (space, '=', ',') and copy the next token into
   the shared token buffer; returns the buffer, or 0 when no token. */
char *r1b_NextToken(char **pp)
{
    int n;
    char c;
    for (;;) {
        c = **pp;
        if (c > ' ' && c != '=' && c != ',') break;
        if (c == 0) break;
        (*pp)++;
    }
    R1B_ZEROB(r1b_tok37B1A0, 255);
    n = 0;
    while (**pp > ' ' && **pp != '=' && **pp != ',') {
        r1b_tok37B1A0[n++] = **pp;
        (*pp)++;
    }
    r1b_tok37B1A0[n] = 0;
    return n > 0 ? r1b_tok37B1A0 : 0;
}

/* 0x00013300: skip spaces and '/' and copy the next path segment into the
   segment buffer; returns the buffer, or 0 when none.
   regargs: pp=EDX */
char *r1b_NextSegment(char **pp)
{
    int n;
    char c;
    for (;;) {
        c = **pp;
        if (c > ' ' && c != '/') break;
        if (c == 0) break;
        (*pp)++;
    }
    R1B_ZERO(r1b_seg37B120, 64);
    n = 0;
    while (**pp > ' ' && **pp != '/') {
        r1b_seg37B120[n++] = **pp;
        (*pp)++;
    }
    r1b_seg37B120[n] = 0;
    return n > 0 ? r1b_seg37B120 : 0;
}

/* 0x00013480: load a file into a 64-byte aligned buffer and record its end. */
int32_t r1b_LoadFile(const char *name)
{
    int32_t p;
    a1b_buf4326A0 = 0;
    p = sub_00037570(name, 0x40);
    a1b_buf4326A0 = p;
    if (p == 0) return 0;
    a1b_end4326A4 = sub_000374C0(name) + a1b_buf4326A0;
    return a1b_buf4326A0;
}

/* 0x000130C0: pop the file record stack (record 1 back into record 0,
   records 2..6 shift down). */
void r1b_PopFile(void)
{
    int i;
    r1b_files4326A0[0].buf = r1b_files4326A0[1].buf;
    r1b_files4326A0[0].end = r1b_files4326A0[1].end;
    strcpy(r1b_files4326A0[0].name, r1b_files4326A0[1].name);
    for (i = 1; i < 6; i++) {
        r1b_files4326A0[i].buf = r1b_files4326A0[i + 1].buf;
        r1b_files4326A0[i].end = r1b_files4326A0[i + 1].end;
        strcpy(r1b_files4326A0[i].name, r1b_files4326A0[i + 1].name);
    }
}

/* 0x00012110: fill a render state block with its defaults. */
void r1b_StateDefaults(R1bState *s)
{
    s->w02 = 0x42;
    s->d08 = 0x44;
    s->d0C = 0;
    s->w12 = 0x47;
    s->d18 = 0x5000D;
    s->d1C = 0;
    s->b23 = 0x80;
    s->b22 = 0x80;
    s->b21 = 0x80;
    s->b24 = 0x80;
    s->d2C = 0xFFFFF0;
    s->w36 = 0;
    s->w34 = 0;
    s->w32 = 0;
    s->w30 = 0;
}

/* 0x00012300: write a packet header, optionally a payload, and an end tag;
   returns the end tag. */
uint32_t *r1b_PacketWrap(uint32_t *p, int kind, int sub, int a, int b)
{
    uint32_t *q;
    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x11000000;
    q = p + 4;
    if (kind == 0x42 && sub == 0) sub_001A69C0(a, b);
    q[1] = 0;
    q[2] = 0;
    q[3] = 0;
    q[0] = 0x70000000;
    return q;
}
