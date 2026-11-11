/* Area rbi: thrown particles (rbi_7). Names inferred. */
#include "rbi.h"

/* 0x0010B5B0: launch a debris particle: random sideways speed (-7..-3) and a random upward
   arc (45 +- 7.5 units of height reached in 1.4 s, gravity to match), a random spin on the third rotation axis
   (4 pi .. 16 pi per second) and a first-axis rotation that undoes angD0 over 1.68 s. Sets
   flag 4 and 0x20 of the owner. */
void rbi_Debris10B5B0(void *owner, RbiParticle *p)
{
    float t, a, b, inv;

    p->gravB4 = a50_frameSeconds * 98.0f;
    p->velB8[2] = 0.0f;
    p->velB8[1] = 0.0f;
    p->velB8[0] = 0.0f;
    p->angD0 = 0.0f;
    p->rotC4[2] = 0.0f;
    p->rotC4[1] = 0.0f;
    p->rotC4[0] = 0.0f;
    t = a50_framesPerSecond * 1.39999998f;
    a = ((float)sub_001C7EE1() * 6.10370189e-05f - 1.0f) * 2.0f - 5.0f;
    b = ((float)sub_001C7EE1() * 6.10370189e-05f - 1.0f) * 7.5f - 45.0f;
    p->gravB4 = b * -8.0f / (t * t);
    inv = 1.0f / t;
    p->velB8[0] = a50_frameSeconds * 0.0f;
    p->velB8[1] = inv * b * 4.0f;
    p->velB8[2] = inv * a;
    t = a50_framesPerSecond * 1.68000007f;
    p->rotC4[2] = ((float)sub_001C7EE1() * 3.05185094e-05f * 12.566371f + 50.2654839f)
                  * a50_frameSeconds;
    p->rotC4[0] = p->angD0 / t * -1.0f;
    sub_000F3B00(owner, 4);
    sub_000F3B30(owner, 0x20);
}

/* 0x0010B760: the same launch with a faster, flatter arc: sideways -32..-28, height
   15 +- 2.5 in 0.7 s, a small sideways drift (0.02 per second) and the first-axis rotation over 0.84 s. */
void rbi_Debris10B760(void *owner, RbiParticle *p)
{
    float t, a, b, inv;

    p->gravB4 = a50_frameSeconds * 98.0f;
    p->velB8[2] = 0.0f;
    p->velB8[1] = 0.0f;
    p->velB8[0] = 0.0f;
    p->angD0 = 0.0f;
    p->rotC4[2] = 0.0f;
    p->rotC4[1] = 0.0f;
    p->rotC4[0] = 0.0f;
    t = a50_framesPerSecond * 0.699999988f;
    a = ((float)sub_001C7EE1() * 6.10370189e-05f - 1.0f) * 2.0f - 30.0f;
    b = ((float)sub_001C7EE1() * 6.10370189e-05f - 1.0f) * 2.5f - 15.0f;
    p->gravB4 = b * -8.0f / (t * t);
    inv = 1.0f / t;
    p->velB8[0] = a50_frameSeconds * 0.0200000014f;
    p->velB8[1] = inv * b * 4.0f;
    p->velB8[2] = inv * a;
    t = a50_framesPerSecond * 0.840000033f;
    p->rotC4[2] = ((float)sub_001C7EE1() * 3.05185094e-05f * 12.566371f + 50.2654839f)
                  * a50_frameSeconds;
    p->rotC4[0] = p->angD0 / t * -1.0f;
    sub_000F3B00(owner, 4);
    sub_000F3B30(owner, 0x20);
}

/* 0x0010D870: stop an effect: clear its drift (frame time * 0), stop the owner and its part
   (mode 5), detach it, clear the scene list entry and the 0x0041FFF8 value, hide the owner,
   clear flag 0x20 of owner and part, reset the state block and restart the frame counter
   from f54 - 1. */
void rbi_FxStop10D870(RbiFxNode *o, RbiFxWork *w)
{
    int i;

    w->v15C[0] = a50_frameSeconds * 0.0f;
    w->v15C[1] = a50_frameSeconds * 0.0f;
    w->v15C[2] = a50_frameSeconds * 0.0f;
    w->v15C[3] = a50_frameSeconds * 0.0f;
    sub_000F3D70(o);
    sub_000F3B00(o, 5);
    sub_000F3B00(w->partC8, 5);
    sub_000F3BB0(o, 0, 0);
    sub_000192B0(ae0_obj3E1270, 0);
    sub_00019000(ae0_obj3E1270, 1);
    sub_000BCA50(0);
    sub_0001D700(o);
    o->flags0C &= ~0x20u;
    w->partC8->flags0C &= ~0x20u;
    for (i = 0; i < 20; i++)
        w->zFC[i] = 0;
    w->i188 = RBI_FTOI(w->f54 - 1.0f);
    w->i18C = 0;
    w->f190 = 0.0f;
}

/* 0x0010A9E0: launch a spinning piece: sideways -80..-20, height 17.5 +- 12.5 reached in
   0.9 s (gravity to match), a random spin 2 pi .. 4 pi stored in the owner (+0x50) and undone
   over the flight (third rotation axis), flags 0x44 and 0x20 on the owner and a random delay up to 0.9. */
void rbi_Spin10A9E0(RbiSpinner *owner, RbiParticle *p)
{
    float t, a, b, inv, s;

    p->gravB4 = a50_frameSeconds * 98.0f;
    p->velB8[2] = 0.0f;
    p->velB8[1] = 0.0f;
    p->velB8[0] = 0.0f;
    p->angD0 = 0.0f;
    p->rotC4[2] = 0.0f;
    p->rotC4[1] = 0.0f;
    p->rotC4[0] = 0.0f;
    t = a50_framesPerSecond * 0.899999976f;
    a = ((float)sub_001C7EE1() * 6.10370189e-05f - 1.0f) * 30.0f - 50.0f;
    b = ((float)sub_001C7EE1() * 6.10370189e-05f - 1.0f) * 12.5f - 17.5f;
    p->gravB4 = b * -8.0f / (t * t);
    inv = 1.0f / t;
    p->velB8[0] = a50_frameSeconds * 0.0f;
    p->velB8[1] = inv * b * 4.0f;
    p->velB8[2] = inv * a;
    s = ((float)sub_001C7EE1() * 3.05185094e-05f + 1.0f) * 6.28318548f;
    owner->spin50 = s;
    p->rotC4[2] = (0.0f - s) * inv;
    sub_000F3B00(owner, 0x44);
    sub_000F3B30(owner, 0x20);
    p->fF8 = (float)sub_001C7EE1() * 3.05185094e-05f * 0.899999976f;
}

/* 0x0010B330: launch a piece with a random flight time (0.4..0.8 s), sideways -12..-8 and a
   height of -12..-10 units, spinning 10 pi over the flight on the third axis. A fourth
   random number is drawn and not used (kept: it advances the generator). Then flags 4 and
   0x20 and value 0 through 0x000F3F00 on the owner. */
void rbi_Toss10B330(void *owner, RbiParticle *p)
{
    float t, a, b, inv;

    p->gravB4 = a50_frameSeconds * 98.0f;
    p->velB8[2] = 0.0f;
    p->velB8[1] = 0.0f;
    p->velB8[0] = 0.0f;
    p->angD0 = 0.0f;
    p->rotC4[2] = 0.0f;
    p->rotC4[1] = 0.0f;
    p->rotC4[0] = 0.0f;
    t = (((float)sub_001C7EE1() * 6.10370189e-05f - 1.0f) * 0.2f + 0.6f) * a50_framesPerSecond;
    a = ((float)sub_001C7EE1() * 6.10370189e-05f - 1.0f) * 2.0f - 10.0f;
    b = (float)sub_001C7EE1() * 6.10370189e-05f - 1.0f - 11.0f;
    p->gravB4 = b * -8.0f / (t * t);
    inv = 1.0f / t;
    p->velB8[0] = a50_frameSeconds * 0.0f;
    p->velB8[1] = inv * b * 4.0f;
    p->velB8[2] = inv * a;
    sub_001C7EE1();
    p->rotC4[2] = inv * 31.4159279f;
    sub_000F3B00(owner, 4);
    sub_000F3B30(owner, 0x20);
    sub_000F3F00(owner, 0.0f);
}

/* 0x0010C0D0: debris launch with a random flight time (0.4..0.8 s), sideways -36..-24,
   height -23..-17 reached over the flight, a random third-axis spin (4 pi .. 16 pi
   per second) and a first-axis rotation undoing angD0 over 0.72 s; then flags 4, 0x20 and
   value 0 through 0x000F3F00 on the owner. */
void rbi_Debris10C0D0(void *owner, RbiParticle *p)
{
    float t, a, b, inv;

    p->gravB4 = a50_frameSeconds * 98.0f;
    p->velB8[2] = 0.0f;
    p->velB8[1] = 0.0f;
    p->velB8[0] = 0.0f;
    p->angD0 = 0.0f;
    p->rotC4[2] = 0.0f;
    p->rotC4[1] = 0.0f;
    p->rotC4[0] = 0.0f;
    t = (((float)sub_001C7EE1() * 6.10370189e-05f - 1.0f) * 0.2f + 0.6f) * a50_framesPerSecond;
    a = ((float)sub_001C7EE1() * 6.10370189e-05f - 1.0f) * 6.0f - 30.0f;
    b = ((float)sub_001C7EE1() * 6.10370189e-05f - 1.0f) * 3.0f - 20.0f;
    p->gravB4 = b * -8.0f / (t * t);
    inv = 1.0f / t;
    p->velB8[0] = a50_frameSeconds * 0.0f;
    p->velB8[1] = inv * b * 4.0f;
    p->velB8[2] = inv * a;
    t = a50_framesPerSecond * 0.720000029f;
    p->rotC4[2] = ((float)sub_001C7EE1() * 3.05185094e-05f * 12.566371f + 50.2654839f)
                  * a50_frameSeconds;
    p->rotC4[0] = p->angD0 / t * -1.0f;
    sub_000F3B00(owner, 4);
    sub_000F3B30(owner, 0x20);
    sub_000F3F00(owner, 0.0f);
}
