/* Area r1d, group 13: file writer 0x000372F0. Names inferred. */
#include "r1d.h"

/* 0x000372F0: write a file: mode 0 creates/truncates, 1 only creates it
   when missing (returns 1 when it exists), 2 appends. 0 on success,
   -1 on failure. */
int r1d_FileWrite(const char *name, void *buf, int size, int mode)
{
    int flags = 0x202;
    int h;
    if (mode == 0) {
        flags = 0x602;
    } else if (mode == 1) {
        h = sub_001A8210(name, 1, 0x1FF);
        if (h >= 0) {
            r4b_FileClose(h);
            return 1;
        }
    }
    h = sub_001A8210(name, flags, 0x1FF);
    if (h < 0) {
        sub_000586E0(0);
        sub_001C8036(r1d_fmt2615AC, name);
        return -1;
    }
    if (mode == 2)
        r4b_FileSeek(h, 0, 2);
    if ((int)sub_000AD090((void *)(intptr_t)h, buf, size) != size)
        return -1;
    r4b_FileClose(h);
    return 0;
}
