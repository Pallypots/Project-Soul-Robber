/* Area r1j, group 19: title model draw 0x0004AC90.
   Names inferred. */
#include "r1j.h"

/* 0x0004AC90: draw the title screen model: scale and place its matrix
   (saved and restored around the draw) by the object's scale (+0x70) and
   position (+0x60), run the scene passes on the stage object
   (0x0007A9D0, 0x0007A9F0 with the packet 0x003DE5B0 and the frame
   counter, 0x00079DA0, 0x0007B060, 0x0007D1B0 with arg), tick the
   textures, then queue the two logo sprites at a video-mode dependent x
   position (y 196 for the first). */
void r1j_TitleModelDraw(int arg)
{
    R1jTitleObj *o = r1j_titleObj3E00E8;
    float *m = o->mat;
    R1iMat saved, s;
    void *cmd;
    sub_001ADA40(saved, m);
    sub_001AD940(s);
    s[0][0] = o->scale[0];
    s[1][1] = o->scale[1];
    s[2][2] = o->scale[2];
    sub_000F5D40(s[3], o->pos);
    sub_001AD7C0(m, m, s);
    sub_0007A9D0(r1j_stage42C8E4);
    sub_00102FA0(r1j_stage42C8E4);
    sub_0007A9F0(r1j_stage42C8E4, r1j_pkt3DE5B0, r1j_frame42C918);
    sub_00102FA0(1);
    sub_00079DA0(r1j_stage42C8E4);
    sub_0007B060(r1j_stage42C8E4);
    cmd = sub_0007D1B0(r1j_stage42C8E4, arg);
    sub_001B96D0();
    sub_001ADA40(m, saved);
    r1j_logoA3E0494.x = 0.0f;
    r1j_logoA3E0494.y = 0.0f;
    cmd = sub_00017C00(cmd, &r1j_logoA3E0494);
    switch (sub_000529F0()) {
    case 0: r1j_logoPos3E0030.x = 188.0f; break;
    case 1:
    case 2: r1j_logoPos3E0030.x = 178.0f; break;
    case 3: r1j_logoPos3E0030.x = 155.0f; break;
    case 4:
    case 6: r1j_logoPos3E0030.x = 159.0f; break;
    case 5: r1j_logoPos3E0030.x = 151.0f; break;
    }
    r1j_logoPos3E0030.y = 196.0f;
    sub_000150B0(&r1j_logoPos3E0030, 0);
    cmd = sub_00017C90(cmd, &r1j_logoPos3E0030);
    switch (sub_000529F0()) {
    case 0: r1j_logoPos3E0030.x = 267.0f; break;
    case 1:
    case 2: r1j_logoPos3E0030.x = 253.0f; break;
    case 3: r1j_logoPos3E0030.x = 230.0f; break;
    case 4:
    case 6: r1j_logoPos3E0030.x = 234.0f; break;
    case 5: r1j_logoPos3E0030.x = 226.0f; break;
    }
    sub_000150B0(&r1j_logoPos3E0030, 6);
    sub_00017C90(cmd, &r1j_logoPos3E0030);
}
