/* Area a6b, group 3: 0x0007E210..0x0007F2A3 allocation/lifetime. Names inferred. */
#include "a6b.h"

/* 0x0007E210: allocate and initialise a camera animation (y_camera.c line 39). */
A6bCamAnim *a6b_CamAnim_New(void)
{
    A6bCamAnim *c = (A6bCamAnim *)a6b_AllocAt(0, 4, 0xCC, 0x27, a6b_srcYCamera);
    sub_0007E1A0(c);
    return c;
}

/* 0x0007E240: drop a reference; free the animation when it reaches zero. */
int a6b_CamAnim_Release(A6bCamAnim *c)
{
    if (c == 0)
        return -1;
    c->set.refs--;
    if (c->set.refs == 0) {
        a6b_TrackSet_Free(&c->set);
        sub_0008BCC0(c);
    }
    return 0;
}

/* 0x0007E270: parse a camera animation (header then ten tracks). */
float *a6b_CamAnim_Load(A6bCamAnim *c, uint8_t *data)
{
    uint8_t *p;
    if (c == 0 || data == 0)
        return 0;
    p = sub_0007E0D0(c, data);
    if (p == 0)
        return 0;
    return a6b_TrackSet_Load(&c->set, (float *)p);
}

/* 0x0007F240: zeroed block of at least 0x18 bytes, allocated (flags 3) when buf is null. */
uint32_t *a6b_Block_Init(uint32_t *buf, uint32_t size, int line, const char *file)
{
    uint32_t flags;
    if (size < 0x18)
        return 0;
    flags = 1;
    if (buf == 0) {
        buf = (uint32_t *)a6b_AllocAt(4, 0x20, size, line, file);
        if (buf == 0)
            return 0;
        flags = 3;
    }
    sub_0007F1E0(buf, 0, size);
    buf[0] = flags;
    buf[1] = size;
    a6b_allocCount3E9308++;
    return buf;
}
