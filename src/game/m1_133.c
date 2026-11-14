/* Area m1, file 133: small helpers. Names inferred. */
#include <stdint.h>

extern int32_t m1_sm37F484, m1_sm37F488, m1_sm37F48C, m1_sm37F490, m1_sm37F4A4;
extern float m1_sm37F4A8, m1_sm37F4AC;

/* 0x00025FD0: menu slide request (as 0x261A0 on 0x37F484): mode 1 stores the argument as a
 * float (0 becomes -1) and opens it, mode 0 closes it. */
void m1_MenuSlide025FD0(int mode, int arg)
{
    switch (mode) {
    case 0:
        switch (m1_sm37F484) {
        case 1:
            m1_sm37F4A8 = 20.0f - m1_sm37F4A8;
            m1_sm37F484 = 2;
            m1_sm37F488 = 0;
            return;
        case 3:
            m1_sm37F4A4 = 0;
            m1_sm37F484 = 2;
            m1_sm37F488 = 0;
            return;
        }
        return;
    case 1:
        if (arg == 0)
            arg = -1;
        m1_sm37F4AC = (float)arg;
        switch (m1_sm37F484) {
        case 0:
            m1_sm37F484 = 1;
            m1_sm37F488 = 3;
            m1_sm37F48C = 2;
            m1_sm37F490 = 0;
            m1_sm37F4A4 = 0;
            return;
        case 2:
            m1_sm37F484 = 1;
            m1_sm37F488 = 3;
            m1_sm37F48C = 2;
            m1_sm37F490 = 0;
            return;
        case 3:
            m1_sm37F4A4 = 0;
            return;
        }
        return;
    }
}

typedef struct M1Voice133 { uint8_t unk[0xDC]; } M1Voice133;
extern M1Voice133 m1_voices420F20[];
extern int32_t m1_msgCount423F60;
extern int32_t m1_msgIds423F64[29];
extern int32_t m1_g420F00, m1_g420F04, m1_g420EF4, m1_g423F50;
void sub_000A7700(void *v);

#define M1_N133(i) m1_msgIds423F64[i] = -1;

/* 0x000A8A90: reset the effect system: stop all 56 effect slots at 0x420F20, mark the 28
 * message ids unused and clear the counters. */
void m1_FxReset0A8A90(void)
{
    M1Voice133 *v;
    for (v = m1_voices420F20; (int)v < (int)(m1_voices420F20 + 56); v++)
        sub_000A7700(v);
    M1_N133(0) M1_N133(1) M1_N133(2) M1_N133(3) M1_N133(4) M1_N133(5) M1_N133(6)
    M1_N133(7) M1_N133(8) M1_N133(9) M1_N133(10) M1_N133(11) M1_N133(12) M1_N133(13)
    M1_N133(14) M1_N133(15) M1_N133(16) M1_N133(17) M1_N133(18) M1_N133(19) M1_N133(20)
    M1_N133(21) M1_N133(22) M1_N133(23) M1_N133(24) M1_N133(25)
    m1_msgCount423F60 = 0;
    M1_N133(26) M1_N133(27)
    m1_g420F00 = 0;
    m1_g420F04 = 0;
    m1_g420EF4 = 0;
    m1_g423F50 = 0;
}

typedef struct M1KV133 { int32_t k; void *v; } M1KV133;
extern M1KV133 m1_keys3189A0[];
extern M1KV133 *m1_kList3F60E8;
extern int32_t m1_kIdx3F60EC;
extern int32_t m1_k1_3189DC, m1_k2_3189E0;

/* 0x000EDCB0: next entry of the list for (k1, k2): continues the cached list when the keys
 * match, else looks k1 up in table 0x3189A0 and k2 in its sub-table; returns the entry key
 * (and its value through out), -1 at the end or when not found (cache cleared). */
int m1_KeyNext0EDCB0(int k1, int k2, int *out)
{
    M1KV133 *e;
    M1KV133 *p;
    int i, c;
    if (m1_kList3F60E8 != 0 && m1_k1_3189DC == k1 && m1_k2_3189E0 == k2) {
        p = m1_kList3F60E8;
        i = m1_kIdx3F60EC + 1;
    } else {
        for (e = m1_keys3189A0; e->k >= 0; e++)
            if (e->k == k1)
                break;
        if (e->k < 0)
            goto fail;
        for (e = (M1KV133 *)e->v; e->k >= 0; e++)
            if (e->k == k2)
                break;
        if (e->k < 0)
            goto fail;
        p = (M1KV133 *)e->v;
        m1_k2_3189E0 = k2;
        m1_kList3F60E8 = p;
        m1_k1_3189DC = k1;
        i = 0;
    }
    c = p[i].k;
    m1_kIdx3F60EC = i;
    if (c < 0) {
        m1_kList3F60E8 = 0;
        m1_k1_3189DC = -1;
        m1_k2_3189E0 = -1;
        m1_kIdx3F60EC = 0;
        return -1;
    }
    if (out)
        *out = (int)p[i].v;
    return c;
fail:
    m1_kList3F60E8 = 0;
    m1_kIdx3F60EC = 0;
    m1_k1_3189DC = -1;
    m1_k2_3189E0 = -1;
    return -1;
}
