/* Area m1, file 216: the other character-type table calls (siblings of m3_1.c). Names inferred. */
#include <stdint.h>

typedef struct M1CharType {
    int32_t kind;
    int32_t id4;
    const char *name8;
    int (*fnC)(int, void *);
    int (*fn10)(int, void *);
    void (*fn14)(void *);
    int (*fn18)(int, void *);
    void (*fn1C)(void *);
    int (*fn20)(int, void *);
    int (*fn24)(int, void *);
    void (*fn28)(void *);
} M1CharType;

extern M1CharType m3_charTypes278248[];

/* 0xED4C0: find the character type whose kind is k (first entry is kind 2; a negative kind ends the table) and call its +0x0C handler on o. */
#pragma optimize("s", on)
int m1_CharCallCED4C0(int k, void *o) {
    int i = 0; int c = 2; M1CharType *p = m3_charTypes278248;
    for (;;) { if (c == k) break; c = p[1].kind; p++; i++; if (c < 0) break; }
    return m3_charTypes278248[i].fnC(k, o);
}
#pragma optimize("", on)

/* 0xED4F0: same lookup, calls the +0x10 handler. */
#pragma optimize("s", on)
int m1_CharCall10ED4F0(int k, void *o) {
    int i = 0; int c = 2; M1CharType *p = m3_charTypes278248;
    for (;;) { if (c == k) break; c = p[1].kind; p++; i++; if (c < 0) break; }
    return m3_charTypes278248[i].fn10(k, o);
}
#pragma optimize("", on)

/* 0xED560: same lookup, calls the +0x18 handler. */
#pragma optimize("s", on)
int m1_CharCall18ED560(int k, void *o) {
    int i = 0; int c = 2; M1CharType *p = m3_charTypes278248;
    for (;;) { if (c == k) break; c = p[1].kind; p++; i++; if (c < 0) break; }
    return m3_charTypes278248[i].fn18(k, o);
}
#pragma optimize("", on)

/* 0xED5D0: same lookup, calls the +0x20 handler. */
#pragma optimize("s", on)
int m1_CharCall20ED5D0(int k, void *o) {
    int i = 0; int c = 2; M1CharType *p = m3_charTypes278248;
    for (;;) { if (c == k) break; c = p[1].kind; p++; i++; if (c < 0) break; }
    return m3_charTypes278248[i].fn20(k, o);
}
#pragma optimize("", on)

/* 0xED600: same lookup, calls the +0x24 handler. */
#pragma optimize("s", on)
int m1_CharCall24ED600(int k, void *o) {
    int i = 0; int c = 2; M1CharType *p = m3_charTypes278248;
    for (;;) { if (c == k) break; c = p[1].kind; p++; i++; if (c < 0) break; }
    return m3_charTypes278248[i].fn24(k, o);
}
#pragma optimize("", on)
