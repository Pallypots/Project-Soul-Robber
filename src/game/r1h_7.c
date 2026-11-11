/* Area r1h, group 7: stage texture release 0x0005FE00. Names inferred. */
#include "r1h.h"

/* 0x0005FE00: if the stage textures are loaded, release the ten texture
   handles and the two buffers, stop sound 0xAF and the two per-language
   sounds (0xB1 and 0xA0 plus 0x000529F0) when playing; always clears the
   loaded flag. */
void r1h_StageTexRelease(void)
{
    if (r1h_flag3E64C0) {
        int id;
        if (r1h_texB3E60B0[0] != -1) { sub_001B9FC0(r1h_texB3E60B0[0]); r1h_texB3E60B0[0] = -1; }
        if (r1h_texB3E60B0[1] != -1) { sub_001B9FC0(r1h_texB3E60B0[1]); r1h_texB3E60B0[1] = -1; }
        if (r1h_texB3E60B0[2] != -1) { sub_001B9FC0(r1h_texB3E60B0[2]); r1h_texB3E60B0[2] = -1; }
        if (r1h_texB3E60B0[3] != -1) { sub_001B9FC0(r1h_texB3E60B0[3]); r1h_texB3E60B0[3] = -1; }
        if (r1h_texB3E60B0[4] != -1) { sub_001B9FC0(r1h_texB3E60B0[4]); r1h_texB3E60B0[4] = -1; }
        if (r1h_texB3E60B0[5] != -1) { sub_001B9FC0(r1h_texB3E60B0[5]); r1h_texB3E60B0[5] = -1; }
        if (r1h_texA3E60A0[0] != -1) { sub_001B9FC0(r1h_texA3E60A0[0]); r1h_texA3E60A0[0] = -1; }
        if (r1h_texA3E60A0[1] != -1) { sub_001B9FC0(r1h_texA3E60A0[1]); r1h_texA3E60A0[1] = -1; }
        if (r1h_texA3E60A0[2] != -1) { sub_001B9FC0(r1h_texA3E60A0[2]); r1h_texA3E60A0[2] = -1; }
        if (r1h_texA3E60A0[3] != -1) { sub_001B9FC0(r1h_texA3E60A0[3]); r1h_texA3E60A0[3] = -1; }
        if (r1h_buf3E60C8) { sub_00053880(r1h_buf3E60C8); r1h_buf3E60C8 = 0; }
        if (r1h_buf3E60CC) { sub_00053880(r1h_buf3E60CC); r1h_buf3E60CC = 0; }
        sub_0004F5D0(0xAF);
        id = sub_000529F0() + 0xB1;
        if (sub_0004F6D0(id))
            sub_0004F5D0(id);
        id = sub_000529F0() + 0xA0;
        if (sub_0004F6D0(id))
            sub_0004F5D0(id);
    }
    r1h_flag3E64C0 = 0;
}
