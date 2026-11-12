/* Area m1, /GS file 6: save/system helpers. Names inferred. */
#include "m1.h"

/* 0x001A88D0: fill a request block {2, 0, 0x55, 3, ...} and pass it to library 0x1BD5DF. */
void m1_SysCall1A88D0(void)
{
    M1SysInfo info;
    info.a = 2;
    info.b = 0;
    info.c = 0x55;
    info.d = 3;
    sub_001BD5DF(0, &info);
}

/* 0x001A9A30: is "<root>TitleMeta.xbx" present? (library 0x1BED78 returns -1 when not). */
int m1_TitleMetaExists1A9A30(void)
{
    char path[0x80];
    sub_001C7FDE(path, m1_fmtSS2780E0, m1_saveRoot40C040, m1_strTitleMeta27B694);
    return sub_001BED78(path) != -1;
}

/* 0x0008C3C0: search from n for a task whose kind byte matches (mask 2 = compare kind). */
M1Task *m1_FindKind8C3C0(M1Task *n, int kind)
{
    M1Task ref;
    if (n == 0)
        return 0;
    sub_0007F1E0(&ref, 0, sizeof(ref));
    ref.kind = (uint8_t)kind;
    return sub_0008C350_m1(n, &ref, 2);
}

/* 0x0004F810: split "a/b..." into the part before the first '/' and the rest. */
void m1_SplitPath4F810(const char *src, char *first, char *rest)
{
    char buf[0x100];
    char *t;
    sub_001C7DB0(buf, src, 0xFF);
    t = sub_001C80F6(buf, m1_strSlash26B81C);
    if (t == 0)
        *first = 0;
    else
        strcpy(first, t);
    t = sub_001C80F6(0, m1_strEmpty26B818);
    if (t == 0)
        *rest = 0;
    else
        strcpy(rest, t);
}

/* 0x0004F8E0: find the stream entry whose file name ("<name>.stm", or "<name>.lz" when
 * packed) equals name; the loop stops at 0x2CCCA0 (541 of the table's entries). */
M1Stream *m1_FindStream4F8E0(const char *name)
{
    char buf[0x100];
    M1Stream *e;
    int i;
    for (i = 0; i < 541; i++) {
        e = &m1_streams2C8900[i];
        if (e->packed == 0)
            sub_0007E070(buf, 0xFF, m1_fmtStm26B828, e->name);
        else
            sub_0007E070(buf, 0xFF, m1_fmtLz26B820, e->name);
        if (sub_001C9A37(buf, name) == 0)
            return e;
    }
    return 0;
}
