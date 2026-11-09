/* Area ac0, group 4: counters and misc 0x000CCB00-0x000CFF90. Names inferred. */
#include "ac0.h"

/* 0x000CCB00: band of the global value: 0 below 0.1, 1 below 0.4, else 2. */
int ac0_Band420EB0(void)
{
    float f = g_ac0_420EB0;
    if (0.1f > f) return 0;
    return (0.4f > f) ? 1 : 2;
}
/* 0x000CD050: forward (a, a->argFC) to 0x000CCA40. */
void ac0_Call_CCA40(Ac0Actor *a)
{
    sub_000CCA40(a, a->argFC);
}
/* 0x000CFF90: set the D2C value and D30 float. */
void ac0_SetD2C(Ac0Actor *a, int v, float f)
{
    a->vD2C = v;
    a->fD30 = f;
}

/* 0x000CC9E0: read the stick into -1..1 floats and its squared length. */
void ac0_Stick_Read(void)
{
    float x = (float)((int)g_ac0_stickX - 0x7F) * (1.0f / 127.0f);
    float y = (float)((int)g_ac0_stickY - 0x7F) * (1.0f / 127.0f);
    g_ac0_stickFY = y;
    g_ac0_stickFX = x;
    g_ac0_420EB0 = y * y + x * x;
}
