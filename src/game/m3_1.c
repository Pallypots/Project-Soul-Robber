/* Area m3, file 1: character-type table helpers. Names inferred. */
#include <stdint.h>

typedef struct M3CharType {
    int32_t kind;
    int32_t id4;
    const char *name8;
    void (*fnC)(void *);
    void (*fn10)(void *);
    void (*fn14)(void *);
    void (*fn18)(void *);
    void (*fn1C)(void *);
    void (*fn20)(void *);
    void (*fn24)(void *);
    void (*fn28)(void *);
} M3CharType;

extern M3CharType m3_charTypes278248[];
extern char m3_fmtCharDir2783FC[];
void a6b_Printf2(void *dst, const char *fmt, ...);
void aab_Effect494D0(int id, void *pos, int a);
void aab_Attach36750(void *o, int mode);

/* 0xED520: find the character type whose kind is k (first entry is kind 2; a negative kind ends the table) and call its +0x14 handler on o. */
void m3_CharCall14ED520(int k, void *o) {
    int i = 0; int c = 2; M3CharType *p = m3_charTypes278248;
    while (c != k) { c = p[1].kind; p++; i++; if (c < 0) break; }
    m3_charTypes278248[i].fn14(o);
}

/* 0xED590: same lookup, calls the +0x1C handler. */
void m3_CharCall1CED590(int k, void *o) {
    int i = 0; int c = 2; M3CharType *p = m3_charTypes278248;
    while (c != k) { c = p[1].kind; p++; i++; if (c < 0) break; }
    m3_charTypes278248[i].fn1C(o);
}

/* 0xEE080: walk the type table for kind k (result unused), then format the character data path "host0:data/char/%s" into dst. */
void m3_CharPathEE080(char *dst, int k) {
    int c = 2; volatile M3CharType *p = m3_charTypes278248;
    do { if (c == k) break; c = p[1].kind; p++; } while (c >= 0);
    if (dst) a6b_Printf2(dst, m3_fmtCharDir2783FC);
}

/* 0xF4280: play effect 0x3B2 at the object's position, then attach it in mode 3 (flag set) or 4. */
void m3_FxAttachF4280(uint8_t *o, int flag) {
    aab_Effect494D0(0x3B2, o + 0x60, 1);
    volatile int z;
    if (flag) { aab_Attach36750(o, 3); z = 1; }
    else { aab_Attach36750(o, 4); z = 1; }
}
