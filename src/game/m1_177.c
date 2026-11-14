/* Area m1, file 177: link fire by owner (revisited). Names inferred. */
#include <stdint.h>

typedef struct M1An177 { uint8_t unk00[0x30]; void *anim30; } M1An177;
typedef struct M1St177 { uint8_t unk00[0x50]; int32_t n50; } M1St177;
typedef struct M1Lk177 { M1An177 *o0; M1St177 *o4; int32_t who8; uint8_t rest[0x18]; } M1Lk177;
extern M1Lk177 m1_links3FE2DC[4];
void sub_000832D0(void *a, int id);

/* 0x181CE0: play animation `anim` on the first active link owned by `who`. */
void m1_LinkAnim181CE0(int who, int anim) {
    int32_t *q;
    for (q = &m1_links3FE2DC[0].who8; (int32_t)q < (int32_t)&m1_links3FE2DC[4].who8; q += 9)
        if (((M1St177 *)q[-1])->n50 != 2 && *q == who) { sub_000832D0(((M1An177 *)q[-2])->anim30, anim); return; }
}


typedef struct M1Vo177 { uint8_t unk00[0x12C]; int32_t x12C; int32_t x130; uint8_t unk134[4]; int32_t x138; uint8_t rest[0x150 - 0x13C]; } M1Vo177;
typedef struct M1Res177 { uint8_t unk00[8]; void *x8; } M1Res177;
typedef struct M1Sc177 { uint8_t unk00[0x1E8]; void *x1E8; } M1Sc177;
extern M1Sc177 *m1_scene42C8E4;
extern M1Res177 *m1_g420F00;
extern M1Vo177 *m1_g420F04;
extern M1Res177 *m1_g420EF4;
extern void *m1_g423F50;
extern float m1_sndPos423F40[4];
M1Res177 *sub_0001F210(int n, int k);
void sub_0001DA40(M1Res177 *r);
M1Res177 *sub_00022260(int n, int a, int b, int c);
void sub_0001CFF0(void *sc, void *m, int k);
void m1_MsgQueue0A7570(int id);
void sub_00036790(M1Vo177 *v);

/* 0xA86D0: set up the 28 message records: load them, queue each message id, copy the first record settings to the rest. */
void m1_MsgInit0A86D0(void) {
    int ids[28]; M1Sc177 *sc = m1_scene42C8E4; int i;
    ids[0] = 1; ids[1] = 2; ids[2] = 3; ids[3] = 4; ids[4] = 0x17; ids[5] = 0x18; ids[6] = 0x19;
    ids[7] = 0x1A; ids[8] = 0x1B; ids[9] = 0x1C; ids[10] = 0x1D; ids[11] = 0x2D; ids[12] = 0x2F; ids[13] = 0x30;
    ids[14] = 0x33; ids[15] = 0x34; ids[16] = 0x35; ids[17] = 0x36; ids[18] = 0x37; ids[19] = 0x38; ids[20] = 0x3A;
    ids[21] = 0x3C; ids[22] = 0x47; ids[23] = 0x48; ids[24] = 0x49; ids[25] = 0x4A; ids[26] = 0x4B; ids[27] = 0x4E;
    m1_g420F00 = sub_0001F210(0x1C, 0);
    m1_g420F04 = (M1Vo177 *)m1_g420F00->x8;
    sub_0001DA40(m1_g420F00);
    m1_g420EF4 = sub_00022260(0x38, 0, 3, 0);
    m1_g423F50 = m1_g420EF4->x8;
    sub_0001CFF0(sc->x1E8, m1_g420EF4, 0xB);
    for (i = 0; i < 0x1C; i++) m1_MsgQueue0A7570(ids[i]);
    for (i = 0; i < 0x1C; i++) {
        if (i == 0) { sub_00036790(m1_g420F04); continue; }
        m1_g420F04[i].x12C = m1_g420F04->x12C;
        m1_g420F04[i].x130 = m1_g420F04->x130;
        m1_g420F04[i].x138 = m1_g420F04->x138;
    }
    m1_sndPos423F40[3] = -1.0f; m1_sndPos423F40[2] = -1.0f; m1_sndPos423F40[1] = -1.0f; m1_sndPos423F40[0] = -1.0f;
}
