/* Area r1e, group 7: resources, file loads, info record, messages, pad check 0x000524A0..0x00054E20. Names inferred. */
#include "r1e.h"

/* 0x000524A0: release the scene resources and forget their handles. */
void r1e_SceneResFree(void)
{
    sub_00014940(0, 0, 0, 0);
    sub_001B9FC0(r1e_h2DCD48);
    r1e_h2DCD48 = -1;
    sub_00053880(r1e_res3E1204);
    sub_00053880(r1e_res3E1208);
    r1e_res3E1204 = 0;
    r1e_res3E1208 = 0;
    sub_00053880(r1e_res3E1210);
    sub_00053880(r1e_res3E1214);
    sub_00053880(r1e_res3E1218);
    r1e_res3E1210 = 0;
    r1e_res3E1214 = 0;
    r1e_res3E1218 = 0;
}

/* 0x000532D0: frame number of motion `key` in the (a, b) entry, or -1. */
int r1e_MotionFrame(int a, int b, int key)
{
    R1eMotEnt *e = sub_000531C0(a, b);
    R1eMotSet *m;
    R1eMotHdr *h;
    R1eMotRef *p;
    unsigned i, n;
    if (e != 0 && (m = e->set) != 0 && (h = m->hdr) != 0) {
        p = h->refs;
        n = h->count;
        for (i = 0; i < n; i++, p++)
            if (p->key == (key & 0xFFFF))
                break;
        if (i < n && p != 0)
            return m->frames[p->anim->info->index + 1].d08;
    }
    return -1;
}

/* 0x00053630: load a whole file into a fresh low block (0x00053AB0);
   returns the block or 0. */
void *r1e_FileLoadLow(const char *name, int a, int b)
{
    int size = r1e_FileSize(name);
    char *buf, *got;
    if (size < 0)
        return 0;
    buf = sub_00053AB0(size, a, b);
    got = r1c_LoadThunk(name, 0, size, buf);
    if (got == 0) {
        sub_00053880(buf);
        return 0;
    }
    if (got != buf) {
#if defined(_M_IX86)
        __movsd((unsigned long *)buf, (const unsigned long *)got, (unsigned)size >> 2);
        __movsb((unsigned char *)buf + (size - (size & 3)), (const unsigned char *)got + (size - (size & 3)), size & 3);
#else
        memcpy(buf, got, size);
#endif
    }
    return buf;
}

/* 0x000536A0: as 0x00053630 with a high block (0x00053B10). */
void *r1e_FileLoadHigh(const char *name, int a, int b)
{
    int size = r1e_FileSize(name);
    char *buf, *got;
    if (size < 0)
        return 0;
    buf = a5b_AllocCurHigh(size, a, b);
    got = r1c_LoadThunk(name, 0, size, buf);
    if (got == 0) {
        sub_00053880(buf);
        return 0;
    }
    if (got != buf) {
#if defined(_M_IX86)
        __movsd((unsigned long *)buf, (const unsigned long *)got, (unsigned)size >> 2);
        __movsb((unsigned char *)buf + (size - (size & 3)), (const unsigned char *)got + (size - (size & 3)), size & 3);
#else
        memcpy(buf, got, size);
#endif
    }
    return buf;
}

/* 0x00054700: fill an information record from the current settings.
   regargs: o=ESI */
void r1e_InfoFill(R1eInfo *o)
{
    o->d28 = r1e_g3E393C;
    o->wide = r1e_mode413168 == 0x18;
    o->d14 = r1e_g413178;
    o->d18 = (int)sub_0019C110();
    o->d1C = r1e_g413164 > 0x18 ? 0x18 : r1e_g413164;
    o->d20 = sub_00057660(r1e_g41316C, r1e_g413170);
    o->d24 = sub_000CF790(r1e_buf41FEC0, 0xC);
}

/* 0x00054800: stop message slot i's sound and print message id there.
   regargs: i=EAX */
void r1e_MsgShow(int i, int id)
{
    sub_00076060(r1e_world3E3934->msg[i].snd);
    sub_0003FCB0(&r1e_world3E3934->msg[i], sub_0003FA70(r1e_world3E3934->font[i], id), 0, 0, -1.0f);
}

/* 0x00054E20: accept (1) or cancel (2) on a pad press, once. */
int r1e_PadDecide(void)
{
    int r = 0;
    uint32_t m;
    if (r1e_g3E3988 == 1)
        return 0;
    m = sub_0004ECE0(0) | sub_0004ED20(0);
    if (m & r1e_padMasks2C4AE8[0]) {
        sub_00048AF0(1);
        r1e_g3E3988 = 1;
        return 1;
    }
    if (m & r1e_padMasks2C4AE8[1]) {
        r = 2;
        r1e_g3E3988 = 1;
        sub_00048AF0(r);
    }
    return r;
}
