/* Area r1k, group 9: axis gizmo lines 0x0003A540.
   Names inferred. */
#include "r1k.h"

/* 0x0003A540: draw three axis lines through the origin, half-lengths
   sx/2, sy/2, sz/2, as a six-vertex line batch (mode 2); the end flags
   are 0x8000 except on the first y and z vertices. Returns the packet end
   from closing the batch. */
void *r1k_DrawAxes(void *p, float sx, float sy, float sz)
{
    float zy, zz, zx;
    r1g_BatchBegin(p, 2, 6);
    zy = sy * 0.0f;
    zz = sz * 0.0f;
    r1g_batchCur3DCEFC->x = sx * -0.5f;
    r1g_batchCur3DCEFC->flags = 0x8000;
    r1g_batchCur3DCEFC->y = zy;
    r1g_batchCur3DCEFC->z = zz;
    r1g_batchCur3DCEFC++;
    r1g_batchCur3DCEFC->flags = 0x8000;
    r1g_batchCur3DCEFC->x = sx * 0.5f;
    r1g_batchCur3DCEFC->y = zy;
    r1g_batchCur3DCEFC->z = zz;
    r1g_batchCur3DCEFC++;
    r1g_batchCur3DCEFC->y = sy * -0.5f;
    zx = sx * 0.0f;
    r1g_batchCur3DCEFC->x = zx;
    r1g_batchCur3DCEFC->z = zz;
    r1g_batchCur3DCEFC->flags = 0;
    r1g_batchCur3DCEFC++;
    r1g_batchCur3DCEFC->z = zz;
    r1g_batchCur3DCEFC->x = zx;
    r1g_batchCur3DCEFC->flags = 0x8000;
    r1g_batchCur3DCEFC->y = sy * 0.5f;
    r1g_batchCur3DCEFC++;
    r1g_batchCur3DCEFC->x = zx;
    r1g_batchCur3DCEFC->y = zy;
    r1g_batchCur3DCEFC->flags = 0;
    r1g_batchCur3DCEFC->z = sz * -0.5f;
    r1g_batchCur3DCEFC++;
    r1g_batchCur3DCEFC->x = zx;
    r1g_batchCur3DCEFC->y = zy;
    r1g_batchCur3DCEFC->flags = 0x8000;
    r1g_batchCur3DCEFC->z = sz * 0.5f;
    r1g_batchCur3DCEFC++;
    return sub_0003A2A0();
}
