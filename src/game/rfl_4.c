/* Area rfl, group 4: table lookups (0x00171D50). Names inferred. */
#include "rfl.h"

/* 0x00171D50: random entry of a 16-wide row of table tbl/row, scaled by the
   difficulty factor (0.5, 1.0, 1.5) picked by the level at 0x00413178. */
float rfl_TableValue(int tbl, int row, int col)
{
    int32_t *vals = rfl_tables32B110[tbl][row]->vals;
    int r = sub_001C7EE1() & 0xF;
    float scale[3];
    scale[0] = 0.5f;
    scale[1] = 1.0f;
    scale[2] = 1.5f;
    return (float)vals[col * 16 + r] * scale[rfl_level413178];
}
