/* Area m1, /GS file 5. Names inferred. */
#include "m1.h"

/* 0x0001DBF0: load "<dir>pig/<name>.pig" (name cut to 8 chars) into o->pigA; returns 8. */
int m1_LoadPigA1DBF0(M1PigOwner *o, const char *name, const M1PigDir *d)
{
    char nm[0xC];
    char path[0x100];
    sub_001C7DB0(nm, name, 8);
    nm[8] = 0;
    sub_0007E070(path, 0xFF, m1_fmtPig25FBE8, d->dir, nm);
    o->pigA = sub_00084CE0(path);
    return 8;
}

/* 0x0001DC70: load "<dir>pig/<name>.pig" (name cut to 8 chars) into o->pigB; returns 8. */
int m1_LoadPigB1DC70(M1PigOwner *o, const char *name, const M1PigDir *d)
{
    char nm[0xC];
    char path[0x100];
    sub_001C7DB0(nm, name, 8);
    nm[8] = 0;
    sub_0007E070(path, 0xFF, m1_fmtPig25FBE8, d->dir, nm);
    o->pigB = sub_00084CE0(path);
    return 8;
}

/* 0x00036660: look up id (a,b); if found, set mode 2, get its file name and load it. */
int m1_LoadById36660(int arg, int a, int b)
{
    char path[0x100];
    int id = sub_00057660(a, b);
    if (id < 0)
        return 0;
    sub_000535F0(2, 0, id);
    sub_000340D0_m1(path, id);
    return sub_000364A0_m1(path, arg);
}

/* 0x000366F0: set mode (0x10,0x12), then load demo dtNN effect file n. */
int m1_LoadDemoEff366F0(int arg, int n)
{
    char path[0x100];
    sub_000535F0(0x10, 0x12, 0);
    sub_0007E070(path, 0xFF, m1_fmtDemoEff2614C8, n, n, n);
    return sub_000364A0_m1(path, arg);
}

/* 0x00040E90: flip between two 0x10080-byte buffers and load the stage file into the new one. */
void m1_LoadStageFlip40E90(const char *fmt, int idx)
{
    char path[0x40];
    m1_flip3DF2F0 = 1 - m1_flip3DF2F0;
    sub_0007E0A0(path, fmt, m1_stageNames2C58C4[idx]);
    sub_00053E20(path, m1_stage3DFA5C + m1_flip3DF2F0 * 0x10080 + 0x102600);
}

/* 0x000371A0: on heap 4, load bonus figure chr0<n+0xE10>, rebuild the figure node and set it up. */
M1Node *m1_LoadFigure371A0(int n)
{
    char path[0x40];
    void *tmpl;
    M1Node *node;
    sub_00053710(4);
    tmpl = m1_figTmpl3DA0C0;
    sub_0007E0A0(path, m1_fmtFigure261558, n + 0xE10, n + 0xE10);
    sub_00022630(tmpl, path);
    node = m1_figNode3DA0B8;
    sub_00022380(node, tmpl, m1_scene42C8E4);
    sub_0001E9B0(m1_scene42C8E4, node, node->x14C, 5, 0x11);
    sub_00053740();
    return node;
}
