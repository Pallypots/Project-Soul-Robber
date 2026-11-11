/* Area r4c: D3D resource release 0x001A3F60 (r4c_14). Names inferred. */
#include "r4c.h"

/* 0x001A3F60: release the render resources held at 0x0040AD70..0x0040AE14 (D3D library calls). No inputs. */
void r4c_D3dRelease(void)
{
    sub_001D3210(r4c_g40AD70, r4c_g40AD74);
    sub_001D3850(r4c_g40AD78);
    sub_001D3D80(r4c_g40AE10, r4c_g40AE14, r4c_g40AD90);
    sub_001D5F50(r4c_g40AD74);
    sub_001D5F50(r4c_g40AD70);
}
