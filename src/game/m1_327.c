/* Area m1, file 327: arena spinner intro state machine. Names inferred. */
#include <stdint.h>

typedef struct M1SpLink { uint8_t unk00[0x10]; uint32_t f10; } M1SpLink;
typedef struct M1SpCmp { uint8_t unk00[0x4C]; uint32_t f4C; int32_t i50; } M1SpCmp;
extern float   m1_spinT3FE370;
extern int32_t m1_spinState3FE374;
extern int32_t m1_spinDir3FE378;
extern float   m1_frameRate42C85C;
void      m1_PairAnim181CA0(int i, int a);
int       m1_LinksReady181D40(uint8_t n);
void      m1_LinkAnim181CE0(int i, int a);
M1SpLink *sub_00181BE0(int i);
void     *sub_00181C20(int i);
M1SpCmp  *sub_0001D960(void *o, int k);
int       m1_CamMode0F40B0(void);
int       m1_AiGoto113040(void *o, void *e, int st);
int       m1_AiGoto113040b(void *o, void *e, int st);   /* alias: keeps the case-3 copy */

/* 0x182980: spinner intro: reset the four links, start their spin animations, wait 2
   units, then release them, and hand over to the spin (state 4) or back to idle (state 0)
   when the camera mode is 2. */
void m1_SpinnerIntro182980(void *o, void *e) {
    int i;
    volatile int k;
    M1SpCmp *c;
    switch (m1_spinState3FE374) {
    case 0:
        for (i = 0; i < 4; i++)
            m1_PairAnim181CA0(i, 0);
        m1_spinState3FE374++;
        return;
    case 1:
        if (!m1_LinksReady181D40(2))
            return;
        if (m1_spinDir3FE378 == 2)
            break;
        for (i = 0; i < 4; i++) {
            k = 5;
            if (i & 1)
                k = 4;
            m1_PairAnim181CA0(i, k);
            m1_LinkAnim181CE0(i, 0);
        }
        m1_spinT3FE370 = 0.0f;
        m1_spinState3FE374++;
        return;
    case 2:
        if (m1_spinT3FE370 > 2.0f) {
            for (i = 0; i < 4; i++) {
                M1SpLink *l = sub_00181BE0(i);
                l->f10 &= ~0xCu;
                c = sub_0001D960(l, 6);
                if (c)
                    c->f4C |= 0x1000000;
            }
            m1_spinState3FE374++;
            return;
        }
        m1_spinT3FE370 = m1_spinT3FE370 + m1_frameRate42C85C;
        return;
    case 3:
        if (!m1_LinksReady181D40(2))
            return;
        if (m1_spinDir3FE378 != 2) {
            for (i = 0; i < 4; i++)
                m1_LinkAnim181CE0(i, 4);
            m1_spinState3FE374++;
            return;
        }
        m1_AiGoto113040b(o, e, 0);
        return;
    case 4:
        if (!m1_LinksReady181D40(1))
            return;
        m1_spinDir3FE378 = m1_CamMode0F40B0();
        if (m1_spinDir3FE378 != 2) {
            for (i = 0; i < 4; i++) {
                c = sub_0001D960(sub_00181C20(i), 6);
                if (c->i50 == 1)
                    m1_LinkAnim181CE0(i, 7);
            }
            m1_AiGoto113040(o, e, 4);
            return;
        }
        break;
    default:
        return;
    }
    m1_AiGoto113040(o, e, 0);
}
