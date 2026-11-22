/* Area r4b, /GS file 1: open a file slot (r4b_gs1). Names inferred. */
#include "r4b.h"

void r4b_MakeDvdPath(char *dst, const char *src);   /* 0x001A81C0 */
void *OOG_STDCALL sub_001BCD0D(const char *path, uint32_t access, uint32_t share, void *sa,
                               uint32_t disp, uint32_t attrs, void *tmpl); /* CreateFileA */

/* 0x001A8210: open name (made into a DVD path) with the mode in flags (1 read, 2 write,
   3 both; 0x200/0x400 change the creation mode; 0x8000 overlapped) and put the handle in
   the first free slot; returns the slot or -1. Stack args (name flags). */
int r4b_FileOpen(const char *name, uint32_t flags)
{
    char path[0x80];
    volatile uint32_t access = 0x80000000;
    volatile uint32_t disp = 3;
    volatile uint32_t attrs = 0;
    void *h;
    int i;
    r4b_MakeDvdPath(path, name);
    if (r4b_g40B318 >= 0x40)
        return -1;
    if (flags & 1)
        ;
    else if (flags & 2)
        access = 0x40000000;
    else if (flags & 3)
        access = 0xC0000000;
    if (flags & 0x200)
        disp = 1;
    if (flags & 0x400)
        disp = 5;
    if ((int8_t)(flags >> 8) < 0)   /* flag 0x8000 */
        attrs = 0x40000000;
    h = sub_001BCD0D(path, access, 1, 0, disp, attrs, 0);
    if (h == (void *)-1)
        return -1;
    for (i = 0; i < 0x40; i++) {
        if (r4b_g40B210[i] == 0) {
            r4b_g40B210[i] = h;
            r4b_g40B320[i].pos = 0;
            r4b_g40B320[i].event = 0;
            r4b_g40B320[i].status = 0;
            r4b_g40B320[i].done = 0;
            r4b_g40B320[i].posHigh = 0;
            r4b_g40B318++;
            return i;
        }
    }
    return -1;
}
