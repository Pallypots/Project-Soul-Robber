/* Area r4f: render state presets at 0x001A2500 (r4f_4). Names inferred. */
#include "r4f.h"

/* 0x001A2500: select one of four blend/alpha presets (0..3; others ignored), setting each
   render state through 0x001D4350 and mirroring it in the device's state cache.
   Stack arg (mode). 0x001D4350 is fastcall (ECX EDX); the other XDK callees are stdcall. */
void r4f_SetBlendPreset(int mode)
{
    switch (mode) {
    case 0:
        sub_001D4350(0x40300, 1);
        aac_g1E2440 = 1;
        sub_001D55A0(1);
        sub_001D4350(0x4035C, 1);
        r4d_g1E2450 = 1;
        sub_001D5630(0);
        sub_001D4350(0x40358, 0x1010101);
        r4e_rs1E245C = 0x1010101;
        return;
    case 1:
        sub_001D4350(0x40300, 0);
        aac_g1E2440 = 0;
        sub_001D4720(0x901);
        sub_001D4350(0x4035C, 0);
        r4d_g1E2450 = 0;
        sub_001D5630(1);
        sub_001D4350(0x40358, 0);
        r4e_rs1E245C = 0;
        sub_001D4350(0x40364, 0x207);
        r4f_rs1E2468 = 0x207;
        sub_001D4350(0x40374, 0x1E00);
        r4f_rs1E2460 = 0x1E00;
        goto set_blend_op;
    case 2:
        sub_001D4350(0x40300, 0);
        aac_g1E2440 = 0;
        sub_001D4350(0x40304, 1);
        aac_g1E243C = 1;
        sub_001D4720(0x900);
        sub_001D4350(0x4035C, 0);
        r4d_g1E2450 = 0;
        sub_001D5630(1);
        sub_001D4350(0x40358, 0x1010101);
        r4e_rs1E245C = 0x1010101;
        sub_001D4350(0x40364, 0x204);
        r4f_rs1E2468 = 0x204;
        sub_001D4350(0x40374, 0x1E00);
        r4f_rs1E2460 = 0x1E00;
        sub_001D56D0(0x1E00);
    set_blend_op:
        sub_001D4350(0x40378, 0x8507);
        r4f_rs1E2464 = 0x8507;
        break;
    case 3:
        sub_001D4350(0x40300, 0);
        aac_g1E2440 = 0;
        sub_001D4350(0x40304, 1);
        aac_g1E243C = 1;
        sub_001D4720(0x901);
        sub_001D4350(0x4035C, 0);
        r4d_g1E2450 = 0;
        sub_001D5630(1);
        sub_001D4350(0x40358, 0);
        r4e_rs1E245C = 0;
        sub_001D4350(0x40364, 0x203);
        r4f_rs1E2468 = 0x203;
        sub_001D4350(0x40364, 0x207);
        r4f_rs1E2468 = 0x207;
        sub_001D56D0(0x8508);
        sub_001D4350(0x40378, 0x8508);
        r4f_rs1E2464 = 0x8508;
        sub_001D4350(0x40374, 0x1E00);
        r4f_rs1E2460 = 0x1E00;
        break;
    default:
        return;
    }
    sub_001D4350(0x40368, 1);
    r4f_rs1E246C = 1;
    sub_001D4350(0x4036C, -1);
    r4f_rs1E2470 = -1;
    sub_001D4350(0x40360, -1);
    r4f_rs1E2474 = -1;
}

/* 0x001A27D0: second set of four blend/alpha presets (0..3; others ignored), same scheme
   as r4f_SetBlendPreset. Stack arg (mode). 0x001D4350 is fastcall (ECX EDX); the other
   XDK callees are stdcall. */
void r4f_SetBlendPresetB(int mode)
{
    switch (mode) {
    case 0:
        sub_001D4350(0x40300, 1);
        aac_g1E2440 = 1;
        sub_001D55A0(1);
        sub_001D5630(0);
        sub_001D4350(0x40358, 0x1010101);
        r4e_rs1E245C = 0x1010101;
        return;
    case 1:
        sub_001D4350(0x40300, 0);
        aac_g1E2440 = 0;
        sub_001D4720(0x900);
        sub_001D4350(0x4035C, 0);
        r4d_g1E2450 = 0;
        sub_001D5630(1);
        sub_001D4350(0x40358, 0x10000);
        r4e_rs1E245C = 0x10000;
        sub_001D4350(0x40358, 0);
        r4e_rs1E245C = 0;
        sub_001D4350(0x40364, 0x207);
        r4f_rs1E2468 = 0x207;
        sub_001D4350(0x40374, 0x1E00);
        r4f_rs1E2460 = 0x1E00;
        sub_001D4350(0x40378, 0x8507);
        r4f_rs1E2464 = 0x8507;
        break;
    case 2:
        sub_001D4350(0x40300, 0);
        aac_g1E2440 = 0;
        sub_001D4720(0x901);
        sub_001D4350(0x4035C, 0);
        r4d_g1E2450 = 0;
        sub_001D5630(1);
        sub_001D4350(0x40358, 0);
        r4e_rs1E245C = 0;
        sub_001D4350(0x40364, 0x203);
        r4f_rs1E2468 = 0x203;
        sub_001D4350(0x40374, 0x1E00);
        r4f_rs1E2460 = 0x1E00;
        sub_001D4350(0x40378, 0);
        r4f_rs1E2464 = 0;
        break;
    case 3:
        sub_001D4350(0x40300, 0);
        aac_g1E2440 = 0;
        sub_001D4720(0x900);
        sub_001D4350(0x4035C, 0);
        r4d_g1E2450 = 0;
        sub_001D5630(1);
        sub_001D4350(0x40358, 0x1000000);
        r4e_rs1E245C = 0x1000000;
        sub_001D4350(0x40364, 0x203);
        r4f_rs1E2468 = 0x203;
        sub_001D56D0(0x8508);
        sub_001D56D0(0x1E00);
        sub_001D4350(0x40378, 0x1E00);
        r4f_rs1E2464 = 0x1E00;
        sub_001D4350(0x40378, 0x8507);
        r4f_rs1E2464 = 0x8507;
        sub_001D4350(0x40374, 0x1E00);
        r4f_rs1E2460 = 0x1E00;
        sub_001D4350(0x40304, 1);
        aac_g1E243C = 1;
        break;
    default:
        return;
    }
    sub_001D4350(0x40368, 1);
    r4f_rs1E246C = 1;
    sub_001D4350(0x4036C, -1);
    r4f_rs1E2470 = -1;
    sub_001D4350(0x40360, -1);
    r4f_rs1E2474 = -1;
}
