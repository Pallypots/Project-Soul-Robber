/* Area r1d, group 5: pack loader and sequence state blocks 0x00022630..0x0002C300. Names inferred. */
#include "r1d.h"

/* 0x00022630: load a pack file into a temporary slot and parse it with the
   "@CPB" parser (0x00021B00) or the plain one (0x000201C0). */
int r1d_LoadPack(void *a, const char *name)
{
    void *h = a50_AllocTop(name, 0x725);
    uint32_t *buf = sub_00037570(name, 0x40);
    int r;
    if (buf == 0) {
        a5b_CurSlotEndTemp();
        sub_00053880(h);
        return 0;
    }
    if (*buf == 0x42504340) {
        r = sub_00021B00(a, name, buf, h);
        a5b_CurSlotEndTemp();
        return r;
    }
    r = sub_000201C0(a, name, buf, h);
    a5b_CurSlotEndTemp();
    return r;
}

/* 0x000267A0: set (on=1) or clear (on=0) flag bit 0 of sequence block
   `which`; hangs on a bad argument. */
void r1d_SeqEnable(int which, unsigned int on)
{
    uint32_t *f = 0;
    if (on >= 2) for (;;) ;
    switch (which) {
    case 0: f = &r1d_seqA37C4FC.flags; break;
    case 1: f = &r1d_seqB37D424.flags; break;
    case 2: f = &r1d_seqC37DA98.flags; break;
    case 3: f = &r1d_seqD37DC24.flags; break;
    case 5: f = &r1d_flags37ED00; break;
    case 6: f = &r1d_flags37E090; break;
    case 7: f = &r1d_seqF37EDEC.flags; break;
    case 8: f = &r1c_flags37F0C8; break;
    case 9: f = &r1d_seqE37F480.flags; break;
    }
    if (f == 0) for (;;) ;
    if (on)
        *f |= 1;
    else
        *f &= ~1u;
}

/* 0x00026850: reset the work area and every sequence block from its
   template (the first one takes the current health). */
void r1d_SeqInitAll(void)
{
    r1c_ClearWork42CE80();
    r1d_seqA37FB78.health = Stats_Get(&g_stats, 1);
    r1d_seqA37FB78.d7C = 0;
    r1d_seqA37FB78.w84 = 0;
    r1d_seqA37C4FC = r1d_seqA37FB78;
    r1d_seqB37D424 = r1d_seqB380C48;
    r1d_seqC37DA98 = r1d_seqC380AA0;
    r1d_seqE37F480 = r1d_seqE3812C0;
    r1d_seqD37DC24.dD8 = 0;
    r1d_seqD37DC24.d108 = 0xD0;
}

/* 0x0002BA70: forward ten values to 0x00026910.
   calls 0x00026910 with stack=(a b c d g h i) EDX=e ECX=f EBX=j */
int r1d_Fwd26910(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j)
{
    return sub_00026910(a, b, c, d, e, f, g, h, i, j);
}

/* 0x0002C1B0: run the step of sequence block B for its current state. */
void r1d_SeqBStep(void)
{
    switch (r1d_seqB37D424.state) {
    case 0: r1d_seqB37D424.flags &= ~1u; break;
    case 1: sub_00028EB0(); break;
    case 2: sub_00028FE0(); break;
    case 3:
        if (r1d_seqB37D424.armed == 0)
            r1d_seqB37D424.armed = 1;
        break;
    case 4: sub_000290F0(); break;
    case 5: sub_00029230(); break;
    case 6: sub_00029310(); break;
    case 7: sub_00029470(); break;
    case 8: sub_00029580(); break;
    }
}

/* 0x0002C230: run the step of sequence block D for its current state. */
void r1d_SeqDStep(void)
{
    switch (r1d_seqD37DC24.state) {
    case 0: r1d_seqD37DC24.flags &= ~1u; break;
    case 1: sub_000299F0(); break;
    case 2: sub_00029AE0(); break;
    case 3:
        if (r1d_seqD37DC24.armed == 0) {
            r1d_seqD37DC24.b2D = 0;
            r1d_seqD37DC24.armed = 1;
        }
        break;
    case 4: sub_00023A70(); break;
    case 5: sub_00029BC0(); break;
    case 6: sub_00029CE0(); break;
    }
}
