/* Area m1, file 332: minion hop step (rise and fall, landing, timed finish). Names inferred. */
#include <stdint.h>

typedef struct M1MnCtl332 {
    uint8_t unk000[0x8C];
    int32_t i8C;               /* +0x8C */
    uint8_t unk090[4];
    int32_t f94;               /* +0x94 */
    uint8_t unk098[4];
    int32_t step9C;            /* +0x9C */
    float   tA0;               /* +0xA0 */
    uint8_t unkA4[2];
    int16_t wA6;               /* +0xA6 */
    uint8_t unkA8[0xBC - 0xA8];
    int16_t doneBC;            /* +0xBC */
    uint8_t unkBE[0x174 - 0xBE];
    float   g174;              /* +0x174 gravity */
    float   vy178;             /* +0x178 */
    float   vx17C, vz180;      /* +0x17C */
    float   p184[4];           /* +0x184 */
    float   p194[4];           /* +0x194 */
    uint8_t unk1A4[4];
    uint8_t *obj1A8;           /* +0x1A8 */
} M1MnCtl332;
typedef struct M1MnObj332 { uint8_t unk000[0x60]; int32_t p60[3]; uint8_t unk06C[0x128 - 0x6C]; uint8_t b128; } M1MnObj332;
extern M1MnCtl332 *m1_minion3F6120;
extern float m1_frameRate42C85C;
extern float m1_fps42C964;
int  sub_000F5D00(void *o);
void sub_000FE330(int snd);
void sub_001ADAF0(void *out, const void *a, const void *b);
void sub_00194D30(void *o, int k);
void sub_0001D720(int v);
void sub_0001D7A0(void *o);
void sub_0001D700(int v);

/* 0xFFB40: minion hop. Steps 0/1 fly the arc (step 0 waits for the take-off check), copy
   the position to the carried object and on landing (falling and touching ground) play
   the landing effects and go to step 2; step 2 sinks until 0xF5D00 reports done; step 3
   sinks and finishes after 0.01 units. */
void m1_MinionHop0FFB40(M1MnObj332 *o) {
    M1MnCtl332 *g = m1_minion3F6120;
    int32_t *st = &g->step9C;
    switch (g->step9C) {
    case 0:
    case 1:
        if (*st == 0 && sub_000F5D00(o)) {
            sub_000FE330(0x29);
            (*st)++;
        }
        sub_001ADAF0(o->p60, g->p194, g->p184);
        g->p184[0] = g->vx17C + g->p184[0];
        g->p184[2] = g->vz180 + g->p184[2];
        g->p184[1] = g->p184[1] - g->vy178;
        g->vy178 = g->g174 + g->vy178;
        if (g->obj1A8) {
            *(int32_t *)(g->obj1A8 + 0x60) = o->p60[0];
            *(int32_t *)(g->obj1A8 + 0x68) = o->p60[2];
        }
        if (0.0f > g->vy178 && (o->b128 & 0x18)) {
            sub_000FE330(0x2A);
            sub_00194D30(g->obj1A8, 0xB);
            sub_0001D720(m1_minion3F6120->i8C);
            sub_0001D7A0(m1_minion3F6120->obj1A8);
            *st = 2;
        }
        return;
    case 2:
        *(float *)((uint8_t *)o + 0x64) = 34.0f / m1_fps42C964 + *(float *)((uint8_t *)o + 0x64);
        if (sub_000F5D00(o)) {
            (*st)++;
            g->tA0 = 0.0f;
            g->wA6 = 0;
        }
        return;
    case 3:
        *(float *)((uint8_t *)o + 0x64) = 34.0f / m1_fps42C964 + *(float *)((uint8_t *)o + 0x64);
        if (g->tA0 > 0.01f) {
            sub_0001D700(g->f94);
            g->doneBC = 1;
            return;
        }
        g->tA0 = m1_frameRate42C85C + g->tA0;
        return;
    default:
        g->doneBC = 1;
        return;
    }
}
