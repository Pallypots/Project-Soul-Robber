/* Area r4f: stream file close at 0x001A3A80 (r4f_14). Names inferred. */
#include "r4f.h"

/* 0x001A3A80: close an open stream file: free its lock, close the handle, clear the
   name. regargs: f=ECX (member function without stack arguments). Calls 0x001A38C0 with
   ECX=f and stack (0 -1); CloseHandle is stdcall. */
void R4D_FASTCALL r4f_FileClose(R4fStrFile *f)
{
    if (f->open30 != 1)
        return;
    if (f->lock2C) {
        sub_001AA1D0(f->lock2C);
        f->lock2C = 0;
    }
    if (f->h20 != (void *)-1) {
        sub_001BC6FD(f->h20);
        f->h20 = (void *)-1;
    }
    f->f38 = 0;
    r4f_StrErase1A38C0(f, 0, -1);
    f->open30 = 0;
}
