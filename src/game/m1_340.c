/* Area m1, file 340: title / pause menu input and fades. Names inferred. */
#include <stdint.h>

typedef struct M1MnOpt340 { uint8_t unk00[0x20]; int32_t on20; } M1MnOpt340;
extern int32_t  m1_mnState3DF1F0;     /* 0x003DF1F0 */
extern int32_t  m1_mnNext3DF1E8;      /* 0x003DF1E8 */
extern int32_t  m1_mnMode3DF1EC;      /* 0x003DF1EC */
extern int32_t  m1_mnSub3DF1F4;       /* 0x003DF1F4 */
extern int32_t  m1_mnFlag3DF1D4;      /* 0x003DF1D4 */
extern float    m1_mnTime3DF200;      /* 0x003DF200 */
extern uint8_t  m1_mnFade3DF204;      /* 0x003DF204 */
extern int32_t  m1_mnSel3DFA5C;       /* 0x003DFA5C byte offset into the option table */
extern uint8_t  m1_mnOpts2B4D8C[];    /* 0x002B4D8C option pointers */
extern uint32_t *m1_mnKeys2C4AE8;     /* 0x002C4AE8 confirm / cancel masks */
extern uint8_t  m1_mnFadeObj428F40[]; /* 0x00428F40 */
int  m1_PadHeld04ECD0(int p);
int  sub_0004ECE0(int p);
int  sub_0004ECF0(int p);
int  sub_0004ED00(int p);
int  sub_0004ED20(int p);
int  sub_0004ED40(int p);
void sub_00048AF0(int k);
void r1c_StageAmbient(int k);
void sub_000720A0(float *t, int a);
void m1_FadeSet072F30(void *f, int a, float t, int b, int c);
int16_t sub_00072FA0(void *f);

/* 0x459E0: menu step. State 0 reads the pad: 0xA000 toggles the selected option, confirm
   starts the fade-out (or the fade-in path when the option is off), cancel backs out;
   0x10/0x11 fade the screen in over 30 units, 0x20/0x21 fade it out and pick the next
   screen, 0x30/0x31 run the full-screen fade and then switch to screen 4. */
void m1_MenuStep0459E0(void) {
    int pad;
    M1MnOpt340 *opt;
    m1_PadHeld04ECD0(0);
    pad = sub_0004ECE0(0);
    sub_0004ECF0(0);
    sub_0004ED00(0);
    pad |= sub_0004ED20(0);
    sub_0004ED40(0);
    switch (m1_mnState3DF1F0) {
    case 0:
        if (pad & 0xA000) {
            opt = *(M1MnOpt340 **)(m1_mnOpts2B4D8C + m1_mnSel3DFA5C);
            opt->on20 = 1 - opt->on20;
            sub_00048AF0(0);
            return;
        }
        if (m1_mnKeys2C4AE8[0] & pad) {
            if ((*(M1MnOpt340 **)(m1_mnOpts2B4D8C + m1_mnSel3DFA5C))->on20 == 0) {
                m1_mnFlag3DF1D4 = 1;
                m1_mnState3DF1F0 = 0x30;
                sub_00048AF0(1);
                return;
            }
        } else if (!(m1_mnKeys2C4AE8[1] & pad)) {
            return;
        }
        m1_mnState3DF1F0 = 0x20;
        r1c_StageAmbient(0);
        sub_00048AF0(2);
        return;
    case 0x10:
        m1_mnFade3DF204 = 0;
        m1_mnTime3DF200 = 30.0f;
        m1_mnState3DF1F0 = 0x11;
        return;
    case 0x11:
        sub_000720A0(&m1_mnTime3DF200, 0);
        m1_mnFade3DF204 = (uint8_t)(int32_t)((30.0f - m1_mnTime3DF200) * 4.26666689f);
        if (0.0f >= m1_mnTime3DF200) {
            m1_mnFade3DF204 = 0x80;
            m1_mnState3DF1F0 = 0;
            r1c_StageAmbient(0x1B);
        }
        return;
    case 0x20:
        m1_mnTime3DF200 = 30.0f;
        m1_mnFade3DF204 = 0x80;
        m1_mnState3DF1F0 = 0x21;
        return;
    case 0x21:
        sub_000720A0(&m1_mnTime3DF200, 0);
        m1_mnFade3DF204 = (uint8_t)(int32_t)(m1_mnTime3DF200 * 4.26666689f);
        if (0.0f >= m1_mnTime3DF200) {
            m1_mnFade3DF204 = 0;
            m1_mnMode3DF1EC = 0;
            m1_mnSub3DF1F4 = 0;
            m1_mnNext3DF1E8 = 2;
            m1_mnState3DF1F0 = 0x10;
        }
        return;
    case 0x30:
        m1_FadeSet072F30(m1_mnFadeObj428F40, 1, 8.0f, 0, 2);
        m1_mnState3DF1F0++;
        return;
    case 0x31:
        if (!sub_00072FA0(m1_mnFadeObj428F40)) {
            m1_mnNext3DF1E8 = 4;
            m1_mnState3DF1F0 = 0;
            m1_mnMode3DF1EC = 0;
            m1_mnSub3DF1F4 = 0;
        }
        return;
    }
}
