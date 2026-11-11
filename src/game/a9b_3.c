/* Area a9b, 0x001A2350-0x001A3F30. Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a9b.h"

/* 0x001A2350: set the 4 vertex shader constants at register n*4+0x40 from
   matrix m through 0x1D24F0 (tail jump; no meaningful return value, r4b and
   r4g declare it void). Name kept from the first draft. */
void a9b_AllocDwords(int n, const float *m)
{
    sub_001D24F0(n * 4 + 0x40, m);
}

/* 0x001A3F30: absolute value of a float. */
float a9b_Fabs(float x)
{
    if (x >= 0.0f)
        return x;
    return -x;
}
