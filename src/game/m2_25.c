/* Area m2, file 25: debug menu record drawing. Names inferred. */
#include <stdint.h>

typedef struct M2MRec25 { const char *name0; int32_t i4; uint32_t kind8; const char **listC; int32_t val10; } M2MRec25;
extern int *m1_pg2C4B08;
extern const char m2_fmtDec267014[], m2_fmtHex267004[], m2_fmtStr266FF8[], m2_fmtFlt266FE8[];
extern const char m2_fmtNone266FDC[], m2_fmtSep266FD0[], m2_strOn260964[], m2_strOff260960[];
int m1_DrawTextf2E8C0(int a, int x, int y, int font, int *px, int *py, const char *fmt, ...);
int sub_0002E8C0(int a, int x, int y, int font, int *px, int *py, const char *fmt, ...);
int m2_TxtA2E8C0(int a, int x, int y, int font, int *px, int *py, const char *fmt, ...);
int m2_TxtB2E8C0(int a, int x, int y, int font, int *px, int *py, const char *fmt, ...);
int m2_TxtC2E8C0(int a, int x, int y, int font, int *px, int *py, const char *fmt, ...);
int m2_TxtD2E8C0(int a, int x, int y, int font, int *px, int *py, const char *fmt, ...);
int m2_TxtE2E8C0(int a, int x, int y, int font, int *px, int *py, const char *fmt, ...);
int m2_TxtF2E8C0(int a, int x, int y, int font, int *px, int *py, const char *fmt, ...);


/* 0x3E6D0: draw one debug-menu record at the pen: hidden records (bit 12) draw a separator; others draw a marker ('+' for submenus) and their name with the value formatted by kind (2 decimal, 3 hex, 4 list entry name, 5 ON/off, 6 float, else name only). The marked record uses the highlight font. Returns the draw state. */
int m2_MenuRecDraw3E6D0(int a, int x, int y, int *px, int *py, int marked, M2MRec25 *r) {
    uint32_t k = r->kind8;
    int vis = ~(k >> 12) & 1;
    char mk;
    if (vis && (r->i4 != 0 || k == 1)) mk = '+';
    else mk = ' ';
    if (vis) {
        switch (k) {
        case 2:
            return m2_TxtA2E8C0(a, x, y, marked ? m1_pg2C4B08[2] : m1_pg2C4B08[1], px, py, m2_fmtDec267014, mk, r->name0, r->val10);
        case 3:
            return m2_TxtB2E8C0(a, x, y, marked ? m1_pg2C4B08[2] : m1_pg2C4B08[1], px, py, m2_fmtHex267004, mk, r->name0, r->val10);
        case 4: {
            int n = r->val10, i;
            const char **l = r->listC;
            if (n >= 0 && l != 0) {
                const char *s;
                for (i = 0; i < n; i++) if (l[i] == 0) break;
                s = l[i];
                if (s != 0)
                    return m2_TxtC2E8C0(a, x, y, marked ? m1_pg2C4B08[2] : m1_pg2C4B08[1], px, py, m2_fmtStr266FF8, mk, r->name0, s);
            }
            return m2_TxtD2E8C0(a, x, y, marked ? m1_pg2C4B08[2] : m1_pg2C4B08[1], px, py, m2_fmtDec267014, mk, r->name0, n);
        }
        case 5:
            return m2_TxtE2E8C0(a, x, y, marked ? m1_pg2C4B08[2] : m1_pg2C4B08[1], px, py, m2_fmtStr266FF8, mk, r->name0, r->val10 ? m2_strOn260964 : m2_strOff260960);
        case 6:
            return m2_TxtF2E8C0(a, x, y, marked ? m1_pg2C4B08[2] : m1_pg2C4B08[1], px, py, m2_fmtFlt266FE8, mk, r->name0, (double)*(float *)&r->val10);
        default:
            return sub_0002E8C0(a, x, y, marked ? m1_pg2C4B08[2] : m1_pg2C4B08[1], px, py, m2_fmtNone266FDC, mk, r->name0);
        }
    }
    return m1_DrawTextf2E8C0(a, x, y, marked ? m1_pg2C4B08[2] : m1_pg2C4B08[1], px, py, m2_fmtSep266FD0, mk);
}
