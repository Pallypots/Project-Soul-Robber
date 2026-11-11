/* Area r1g, group 9: primitive batch start 0x0003A0D0 and music volume 0x00047DA0. Names inferred. */
#include "r1g.h"

/* 0x0003A0D0: start a primitive batch of `count` items at packet `p` in
   blend mode `mode` (0..6; modes 0..2 use buffer 0x0042C900, 3..6 buffer
   0x0042C800), writing the header with matrix 0 and recording the batch
   pointers. calls 0x0003A020 with EAX=p EBX=matrix */
void r1g_BatchBegin(int p, uint32_t mode, int count)
{
    uint8_t *q;
    mode &= 7;
    switch (mode) {
    case 0:
        p = r4_Set40F324(p, r1g_buf42C900);
        r1g_batchB3DCFE8 = 0;
        r1g_batchC3DCF08 = 0;
        r1g_batchA3DCFE4 = 1;
        break;
    case 1:
        p = r4_Set40F324(p, r1g_buf42C900);
        r1g_batchA3DCFE4 = 2;
        r1g_batchB3DCFE8 = 0;
        r1g_batchC3DCF08 = 1;
        break;
    case 2:
        p = r4_Set40F324(p, r1g_buf42C900);
        r1g_batchA3DCFE4 = 1;
        r1g_batchB3DCFE8 = 1;
        r1g_batchC3DCF08 = 1;
        break;
    case 3:
        p = r4_Set40F324(p, r1g_buf42C800);
        r1g_batchA3DCFE4 = 3;
        r1g_batchB3DCFE8 = 0;
        r1g_batchC3DCF08 = 5;
        break;
    case 4:
        p = r4_Set40F324(p, r1g_buf42C800);
        r1g_batchA3DCFE4 = 1;
        r1g_batchB3DCFE8 = 2;
        r1g_batchC3DCF08 = 5;
        break;
    case 5:
        p = r4_Set40F324(p, r1g_buf42C800);
        r1g_batchA3DCFE4 = 1;
        r1g_batchB3DCFE8 = 1;
        r1g_batchC3DCF08 = 5;
        break;
    case 6:
        p = r4_Set40F324(p, r1g_buf42C800);
        r1g_batchA3DCFE4 = 2;
        r1g_batchB3DCFE8 = 0;
        r1g_batchC3DCF08 = 5;
        break;
    }
    q = sub_0003A020((uint8_t *)(intptr_t)p, rtc_mtx3DCE70[0]);
    r1g_batchHead3DCEF0 = q;
    r1g_batchStart3DCEF8 = q + 0x10;
    r1g_batchCur3DCEFC = q + 0x10;
    r1g_batchCount3DCF00 = count;
    r1g_batchFlags3DCF04 = (r1g_batchFlags3DCF04 & ~7u) | mode;
}

/* 0x00047DA0: set the volume (0..128) of the playing music track and
   apply it, scaled by each voice's or part's base volume: ids below 2 are
   single voices, 2 a stream, 3..49 and 50 up multi-part tracks. */
void r1g_MusicSetVolume(int vol, int pan)
{
    int id, n, i;
    r1e_g3DFED4 = vol;
    if (r1c_q3DFECC < 0)
        return;
    id = r1c_q3DFEC0;
    if (id < 2) {
        r4d_VoiceStoreVolume(r1c_q3DFECC, sub_00199B00(id) * r1e_g3DFED4 / 128, pan);
    } else if (id < 3) {
        r1b_PktOp((void *)(intptr_t)r1c_q3DFECC, sub_0019A8E0(id - 2) * r1e_g3DFED4 / 128, pan);
    } else if (id < 50) {
        n = sub_0019ADE0(id - 3);
        for (i = 0; i < n; i++)
            r4d_TrackSetPartVolumeIfPlaying(r1c_q3DFECC, i, sub_0019AD10(r1c_q3DFEC0 - 3, i) * r1e_g3DFED4 / 128, pan);
    } else {
        n = sub_0019ADE0(id + 0x1E3);
        for (i = 0; i < n; i++)
            r4d_TrackSetPartVolumeIfPlaying(r1c_q3DFECC, i, sub_0019AD10(r1c_q3DFEC0 + 0x1E3, i) * r1e_g3DFED4 / 128, pan);
    }
}

