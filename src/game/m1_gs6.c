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
