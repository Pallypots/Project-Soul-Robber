/* Area r1e, group 3: file retries, channel slots, matrix helper 0x000372B0..0x000385D0. Names inferred. */
#include "r1e.h"

/* 0x000372B0: seek, retrying until the call succeeds.
   regargs: fd=EBX off=EDI whence=ESI */
void r1e_SeekRetry(int fd, int off, int whence)
{
    int r;
    do {
        r = sub_001A8490(fd, off, whence);
        if (r < 0)
            sub_000586E0(0);
    } while (r < 0);
}

/* 0x000372D0: close, retrying until the call succeeds; returns 0.
   regargs: fd=ESI */
int r1e_CloseRetry(int fd)
{
    int r;
    do {
        r = sub_001A8330(fd);
        if (r != 0)
            sub_000586E0(0);
    } while (r != 0);
    return 0;
}

/* 0x000374C0: size of a file: the cached size (0x00051850) if known,
   otherwise open it and seek to the end. Returns -1 if it cannot be opened. */
int r1e_FileSize(const char *name)
{
    int size, fd, r;
    size = sub_00051850(name);
    if (size > 0)
        return size;
    fd = sub_001A8210(name, 1, 0x1FF);
    if (fd < 0) {
        sub_000586E0(0);
        sub_001C8036(r1e_strOpenErr2615AC, name);
        return -1;
    }
    do {
        size = sub_001A8490(fd, 0, 2);
        if (size < 0)
            sub_000586E0(0);
    } while (size < 0);
    do {
        r = sub_001A8330(fd);
        if (r != 0)
            sub_000586E0(0);
    } while (r != 0);
    return size;
}

/* 0x000375A0: mark all ten channel slots free and paused. */
void r1e_SlotsReset(void)
{
    int i;
    r1e_g42CE38 = 0;
    for (i = 0; i < 10; i++) {
        r1e_slots42CB20[i].state = 0;
        r1e_slots42CB20[i].flags = 1;
    }
}

/* 0x000385D0: rebuild an orthonormal transform from src's two normalised
   axes and its position. */
void r1e_MatOrtho(R1eMat dst, const R1eMat src)
{
    R1eMat m;
    sub_001AD7E0(m[2], src[2]);
    sub_001AD7E0(m[1], src[1]);
    sub_001ADA60(m[0], m[1], m[2]);
    sub_001ADA60(m[1], m[2], m[0]);
    sub_000F5D40(m[3], src[3]);
    sub_001ADA40(dst, m);
    dst[3][3] = 1.0f;
}

