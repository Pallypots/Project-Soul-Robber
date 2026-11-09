/* Area a1b, group 1: string/buffer helpers near 0x00012F90..0x000134C0. Names inferred. */
#include "a1b.h"

/* 0x00012F90: clear the buffer base pointer. */
void a1b_ClearBuf(void) { a1b_buf4326A0 = 0; }

/* 0x000133B0: cut the name returned by sub_00013370 at its first '.'. */
void a1b_StripExt(const char *path)
{
    char *s = sub_00013370(path);
    for (; *s; s++) {
        if (*s == '.') { *s = 0; return; }
    }
}

/* 0x000134C0: set buffer base and, if non-null, its end. */
void a1b_SetBuf(int32_t base, int32_t len)
{
    a1b_buf4326A0 = base;
    if (base) a1b_end4326A4 = base + len;
}
