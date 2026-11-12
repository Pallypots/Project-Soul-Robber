/* Area m1, /GS file 2: data file path builders. Names inferred. */
#include "m1.h"

/* 0x0008DC40: "<dir>/dtII/dtIINN.yca" path for object o (o in ESI). */
void m1_PathYca8DC40(char *out, int n, M1DtObj *o)
{
    char dir[0x40];
    a80_PrintId(o, dir);
    sub_0007E0A0(out, m1_fmtYca270200, dir, o->id, o->id, n);
}

/* 0x0008E8B0: "<dir>/dtII/dtIINN.clp" path for object o (o in ESI). */
void m1_PathClp8E8B0(char *out, int n, M1DtObj *o)
{
    char dir[0x40];
    a80_PrintId(o, dir);
    sub_0007E0A0(out, m1_fmtClp270290, dir, o->id, o->id, n);
}

/* 0x0008ED70: "<dir>/dtII/dtIINN.dfd" path for object o (o in ESI). */
void m1_PathDfd8ED70(char *out, int n, M1DtObj *o)
{
    char dir[0x40];
    a80_PrintId(o, dir);
    sub_0007E0A0(out, m1_fmtDfd270364, dir, o->id, o->id, n);
}

/* 0x0008EFB0: ".lgt" path; here the object is a normal stack argument. */
void m1_PathLgt8EFB0(char *out, M1DtObj *o, int n)
{
    char dir[0x40];
    a80_PrintId(o, dir);
    sub_0007E0A0(out, m1_fmtLgt2703C8, dir, o->id, o->id, n);
}

/* 0x0008F210: ".bms" path; the last part is a name looked up by index. */
void m1_PathBms8F210(char *out, int i, M1DtObj *o)
{
    char dir[0x40];
    uint32_t id = o->id;
    a80_PrintId(o, dir);
    sub_0007E0A0(out, m1_fmtBms270408, dir, id, id, a80_IdValue(o, i));
}

