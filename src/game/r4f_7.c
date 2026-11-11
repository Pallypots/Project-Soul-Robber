/* Area r4f: texture creation and blend formats at 0x001A6540 (r4f_7). Names inferred. */
#include "r4f.h"

/* 0x001A6540: create a texture from an in-memory DDS image (size from the header,
   summing the compressed mip levels); on a bad image or failure use the default texture
   0x0040AECC (with a reference). Stack args (d out). Kernel and XDK callees are stdcall. */
void r4f_TexCreateDDS(R4fDDS *d, void **out)
{
    int size, lin, i;
    if (d->magic00 != 0x20534444) {
        *out = r4e_g40AECC;
        r4f_AddRef1D5F10(r4e_g40AECC);
        return;
    }
    RtlEnterCriticalSection(g_renderLock);
    if (d->fourcc54) {
        lin = d->linear14;
        size = lin + 0x80;
        for (i = d->mips1C; i > 0; i--) {
            if (lin > 16)
                lin /= 4;
            size += lin;
        }
    } else {
        size = d->linear14 * d->height0C + 0x80;
    }
    if (r4f_TexFromMemEx1E5CCD(a1a_g40F124, d, size, -1, -1, d->mips1C == 0 ? 1 : -1,
            0, -1, 0, -1, -1, 0, 0, 0, out) < 0) {
        if (*out)
            r4e_Release1D5F50(*out);
        *out = r4e_g40AECC;
        r4f_AddRef1D5F10(r4e_g40AECC);
    }
    RtlLeaveCriticalSection(g_renderLock);
}

