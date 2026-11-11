/* Area rbh: game functions in 0x000E0000..0x000EFFFF (rbh_2). Names inferred. */
#include "rbh.h"

/* 0x000E70C0: step the checkpoint screen loader for set (6 counts as 5). Step 0 loads movie
   0xB9 once; step 1 allocates the file buffer, clears the screen block and loads the seven
   files; step 2 creates the three textures and builds every sprite of the screen, then parks at
   step 10000. At step 10000 a different set reloads its two set files and goes back to step 2.
   Returns 1 while loading, 0 when the screen is ready. */
int rbh_CkptLoad0E70C0(int set)
{
    int busy = 1;
    uint8_t *buf;
    int i;

    if (set == 6)
        set = 5;
    switch (g_acb_3F57BC) {
    case 0:
        if (!sub_0004F6D0(0xB9))
            sub_0004FAE0(0xB9, sub_00053820(3, sub_0004F6B0(0xB9), 0, 0));
        g_acb_3F57BC++;
        break;
    case 1:
        if (sub_0004F4D0())
            break;
        buf = sub_00053820(3, 0x27D80, 0, 0);
        RBH_ZEROD(rbh_block3F1B58, 0xF15);
        rbh_ckptBuf3F57AC = buf;
        rbh_ckptSet3F49D8 = set;
        sub_00053ED0(rbh_ckptFiles317E1C[0], buf);
        sub_00053E20(rbh_ckptFiles317E1C[1], rbh_ckptBuf3F57AC + 0x10080);
        sub_00053E20(rbh_ckptFiles317E1C[5 + set], rbh_ckptBuf3F57AC + 0x14100);
        sub_00053ED0(rbh_ckptFiles317E1C[2], rbh_ckptBuf3F57AC + 0x18180);
        sub_00053E20(rbh_ckptFiles317E1C[3], rbh_ckptBuf3F57AC + 0x21180);
        sub_00053E20(rbh_ckptFiles317E1C[4], rbh_ckptBuf3F57AC + 0x22180);
        sub_00053E20(rbh_ckptFiles317E1C[11 + set], rbh_ckptBuf3F57AC + 0x27180);
        g_acb_3F57BC++;
        break;
    case 2:
        if (sub_00053CA0(1))
            break;
        rbh_tex3F57B0 = sub_00084C00(rbh_ckptBuf3F57AC, 0);
        rbh_tex3F57B4 = sub_00084C00(rbh_ckptBuf3F57AC + 0x10080, 0);
        rbh_tex3F57B8 = sub_00084C00(rbh_ckptBuf3F57AC + 0x14100, 0);
        sub_00014DA0(rbh_ckptBuf3F57AC + 0x18180);
        sub_00014DA0(rbh_ckptBuf3F57AC + 0x21180);
        sub_00014DA0(rbh_ckptBuf3F57AC + 0x22180);
        sub_00014DA0(rbh_ckptBuf3F57AC + 0x27180);
        sub_00014D00(&r2c_fadeD3F4B1C.spr[0], rbh_ckptBuf3F57AC + 0x18180, rbh_tex3F57B0);
        sub_00014E30(&r2c_fadeD3F4B1C.spr[0], 0, 0, 0, 0);
        r2c_fadeD3F4B1C.spr[2] = r2c_fadeD3F4B1C.spr[0];
        r2c_fadeD3F4B1C.spr[1] = r2c_fadeD3F4B1C.spr[0];
        r2c_fadeA3F43E0.spr[1] = r2c_fadeD3F4B1C.spr[0];
        r2c_fadeA3F43E0.spr[0] = r2c_fadeD3F4B1C.spr[0];
        r2c_fadeB3F47B8.spr1C = r2c_fadeD3F4B1C.spr[0];
        r2c_fadeA3F43E0.spr[2] = r2c_fadeD3F4B1C.spr[0];
        r2c_fadeA3F43E0.spr[3] = r2c_fadeD3F4B1C.spr[0];
        r2c_fadeA3F43E0.spr[4] = r2c_fadeD3F4B1C.spr[0];
        sub_000150B0(&r2c_fadeA3F43E0.spr[1], 0xB);
        sub_000150B0(&r2c_fadeA3F43E0.spr[2], 0xD);
        sub_000150B0(&r2c_fadeA3F43E0.spr[3], 0xE);
        sub_000150B0(&r2c_fadeA3F43E0.spr[4], 0xF);
        sub_000150E0(&r2c_fadeA3F43E0.spr[2], 2);
        sub_000150E0(&r2c_fadeA3F43E0.spr[3], 4);
        sub_000150E0(&r2c_fadeA3F43E0.spr[4], 6);
        sub_00014D00(&r2c_fx3F1B5C[0].sprA8, rbh_ckptBuf3F57AC + 0x21180, rbh_tex3F57B0);
        sub_00014E30(&r2c_fx3F1B5C[0].sprA8, 0, 0, 0, 0);
        for (i = 1; i < 32; i++)
            r2c_fx3F1B5C[i].sprA8 = r2c_fx3F1B5C[0].sprA8;
        r2c_fadeC3F4874.spr24 = r2c_fx3F1B5C[0].sprA8;
        sub_00014D00(&r2c_fadeA3F43E0.spr[5], rbh_ckptBuf3F57AC + 0x22180, rbh_tex3F57B4);
        r2c_fadeC3F4874.sprC0 = r2c_fadeA3F43E0.spr[5];
        for (i = 0; i < 16; i++)
            r2_slots3F4D10[i].spr04 = r2c_fadeA3F43E0.spr[5];
        sub_00014D00(&r2_fade3F4A7C, rbh_ckptBuf3F57AC + 0x27180, rbh_tex3F57B0);
        r2_fade3F4A7C.tex44 = rbh_tex3F57B8;
        sub_00014E30(&r2_fade3F4A7C, 0, 0, 0, 0);
        r2_fade3F49E0 = r2c_fadeD3F4B1C.spr[0];
        sub_000150B0(&r2_fade3F49E0, 3);
        rbh_spr3F5710 = r2c_fadeD3F4B1C.spr[0];
        g_acb_3F57BC = 10000;
        busy = 0;
        break;
    case 10000:
        if (rbh_ckptSet3F49D8 == set) {
            busy = 0;
            break;
        }
        if (rbh_tex3F57B8 != -1) {
            sub_001B9FC0(rbh_tex3F57B8);
            rbh_tex3F57B8 = -1;
        }
        sub_00053E20(rbh_ckptFiles317E1C[5 + set], rbh_ckptBuf3F57AC + 0x14100);
        sub_00053E20(rbh_ckptFiles317E1C[11 + set], rbh_ckptBuf3F57AC + 0x27180);
        g_acb_3F57BC = 2;
        break;
    }
    return busy;
}
