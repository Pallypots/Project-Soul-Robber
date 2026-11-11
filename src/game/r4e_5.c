/* Area r4e: scene setup, fades and the scene loop around 0x0019FCF0-0x001A0633 (r4e_5). Names inferred. */
#include "r4e.h"

/* 0x0019FCF0: clear the scene block and store its parameters; mode 9 becomes the
   0x000529F0 value plus one when option 0x00413140 is on, else 0.
   Stack args (stage b mode c d e). */
void r4e_SceneSetup(int stage, int b, int mode, int c, int d, int e)
{
    R4E_ZERO(&r4e_scene403950, sizeof(r4e_scene403950));
    r4e_scene403950.stage20 = stage;
    r4e_scene403950.d30 = d;
    r4e_scene403950.b24 = b;
    r4e_scene403950.c2C = c;
    r4e_scene403950.e34 = e;
    if (mode == 9) {
        if (r4c_opt413140)
            mode = sub_000529F0() + 1;
        else
            mode = 0;
    }
    r4e_scene403950.mode28 = mode;
}

/* 0x001A0540: scene loop: per frame build the command buffer, apply the fade colour,
   the stage effect and the screen shake, until 0x001A7FD0 reports done and the
   state is not 6. Stack arg (state). */
void r4e_SceneRunLoop(int *state)
{
    int fx = r4e_stageTab337518[r4e_scene403950.stage20].fx00;
    uint32_t *cmd;
    if (fx) {
        sub_000226B0();
        sub_00022750(4);
        sub_00022780(52.0f);
    }
    r4e_g40432C = 0x80;
    r4e_g404328 = 0x80;
    r4e_g404324 = 0x80;
    r4e_g404320 = 0x80;
    do {
        sub_001A5310();
        cmd = r4c_bufs42CAC8[r4c_bufIndex42CAC0].cmd;
        if (sub_001A7FD0()) {
            sub_001A8020(r4e_g404320, r4e_g404324, r4e_g404328, r4e_g40432C);
            sub_001A7FE0();
            sub_001A7E30();
            if (fx)
                cmd = sub_00022900(cmd);
        }
        if (r4e_scene403950.mode28)
            cmd = sub_0003FBD0(cmd, r4d_shake4042F8);
        r4c_bufs42CAC8[r4c_bufIndex42CAC0].cmd = cmd;
        sub_000580D0();
    } while (sub_001A7FD0() || *state == 6);
    sub_00058190();
}

/* 0x001A0660: end the running scene: drain its job, fade out with the given
   parameters, stop the screen shake, wait for the scene threads, then release the
   scene resources. Stack args (a b c d e f) with a a float; returns 0. */
int r4e_SceneEnd(float a, int b, int c, int d, int e, int f)
{
    if (!r4d_g40396C)
        return 0;
    sub_001A53F0();
    sub_0019BE50(0);
    r4e_AD090(r4e_g3DE5B0, 0);
    r4e_AD090(r4e_g3DE5B0, 1);
    while (r4e_JobCurrent57E90() == (void *)sub_001A0640) {
        sub_0004F0B0();
        sub_0005E9B0();
        sub_0004F4C0();
        sub_00049470();
        sub_001A53F0();
    }
    sub_0019FEF0(a, b, c, d, e, f);
    while (r4e_g404334 > 0) {
        sub_001A0200();
        sub_0004F0B0();
        sub_0005E9B0();
        sub_0004F4C0();
        sub_00049470();
        sub_001A53F0();
    }
    if (r4c_g404318) {
        sub_0003FC10(r4d_shake4042F8);
        sub_0003FCB0(r4d_shake4042F8, sub_0003FA70(r4c_g404318, 0), 0, 20.0f, -1.0f);
    }
    sub_0005EB50();
    sub_0005E9B0();
    sub_0005EE40();
    sub_001A7F90(r4d_g403960);
    while (sub_001A7DC0()) {
        sub_001A7E30();
        sub_0004F0B0();
        sub_0005E9B0();
        sub_0004F4C0();
        sub_00049470();
        sub_000586E0(0);
    }
    sub_001BB6E0();
    sub_0019BE50(0);
    sub_00058540(0, 0);
    r4c_g404318 = 0;
    r4c_g403988 = 0;
    r4c_g40398C = 0;
    if (sub_0004F6D0(0xE6))
        r4e_Release4F5D0(0xE6);
    if (r4d_g403964) {
        sub_00053880(r4d_g403964);
        r4d_g403964 = 0;
    }
    if (r4c_g40431C) {
        sub_00053880(r4c_g40431C);
        r4c_g40431C = 0;
    }
    r4d_g40396C = 0;
    return 0;
}

/* 0x001A0830: scene job: wait for other jobs, run the 0x001A0640 job, set the
   volume from option 0x00413148, then start the two scene threads (0x001A0970 and
   r4e_SceneRunLoop) unless the stage load failed. Stack arg (state). */
void r4e_SceneJob(int *state)
{
    int err;
    while (sub_00057E90())
        sub_000580D0();
    sub_00058540(sub_001A0640, 0);
    while (sub_00057E90())
        sub_000580D0();
    err = sub_001A7C10(r4e_scene403950.stage20);
    r4e_g404330 = (int8_t)r4c_opt413148 * 0x7FFF / 8;
    sub_001A80D0(r4e_g404330);
    if (err == 0) {
        r4e_SetFrameHook19BE50(sub_0019FFE0);
        sub_00058540(r4e_Nop102FA0, 0);
        sub_001A1030(state, 0x101, 1, sub_001A0970, 4, 0x2000);
        sub_001A1030(state, 0x102, 4, (void (*)(void))r4e_SceneRunLoop, 4, 0x2000);
        sub_001A1060(state, 0x101);
        sub_001A1060(state, 0x102);
        sub_00058190();
        return;
    }
    if (*state == 6)
        sub_001A0D70();
    sub_00058190();
}
