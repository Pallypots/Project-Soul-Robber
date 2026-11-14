/* Area m1, file 186: attachment position helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Att186 { uint8_t unk00[0x10]; int32_t kind10; uint8_t unk14[4]; int32_t slot18; int32_t bone1C; float v20[4]; } M1Att186;
typedef struct M1Ent186 { uint8_t unk00[0xC]; M1Att186 *att0C; } M1Ent186;
typedef struct M1Obj186 { uint8_t unk00[0xC]; uint32_t flagsC; uint8_t unk10[0x50]; float mtx60[4]; float mtx70[4]; } M1Obj186;
void a3c_VecCopy(float *dst, const float *src);
M1Obj186 *m1_SlotObj0A42A0(int slot);
uint8_t *sub_0001D0F0(M1Obj186 *o, int bone);
void sub_001ADAF0(float *dst, const float *src, const void *m);

/* 0x3AAF0: world position of an attachment: kind 1 transforms its offset by the slot object's matrix (or a bone's), other kinds use the offset as is. */
int m1_AttachPos03AAF0(M1Ent186 *e, float *out) {
    M1Att186 *a; M1Obj186 *o; uint8_t *b; const void *m;
    if (e == 0 || (a = e->att0C) == 0) return -1;
    switch (a->kind10) {
    case 0:
        a3c_VecCopy(out, a->v20);
        return 0;
    case 1:
        a3c_VecCopy(out, a->v20);
        o = m1_SlotObj0A42A0(e->att0C->slot18);
        if (o == 0) return -1;
        { uint32_t volatile f = o->flagsC; if (!(f & 1) || (f & 0x10000)) return -1; }
        if (e->att0C->bone1C > 0) {
            b = sub_0001D0F0(o, e->att0C->bone1C);
            if (b == 0) return -1;
            m = b + 0x70;
        } else m = o->mtx60;
        sub_001ADAF0(out, out, m);
        out[3] = 1.0f;
        return 0;
    default:
        a3c_VecCopy(*(float *volatile *)&out, a->v20);
        return 0;
    }
}

#include <xmmintrin.h>
typedef struct M1SndSl186 { int32_t id0; int32_t unk4; } M1SndSl186;
extern int32_t rtc_level3DFED8;
extern float rtc_scale3DFEDC;
extern int32_t m1_track3DFECC;
extern M1SndSl186 r1e_pairs3DFEA0[4];
void sub_00199820(int v);
void sub_00199840(int v);
int  sub_00199E70(int s);
int  sub_0019A460(int s);
void r4d_StreamSetVolume(int s, int v);
int  sub_0019A930(int t);
int  sub_0019ACE0(int t, int p);
void r4d_TrackSetPartVolume(int t, int p, int v);

/* 0x486F0: set the master sound level (max 0x3FFF), then refresh every active stream and every playing music track except the current one. */
void m1_SndLevelSet0486F0(int lvl) {
    int i; int volatile id;
    if (lvl > 0x3FFF) lvl = 0x3FFF;
    rtc_level3DFED8 = lvl;
    sub_00199820(_mm_cvtt_ss2si(_mm_set_ss((float)lvl * rtc_scale3DFEDC)));
    sub_00199840(rtc_level3DFED8 * 0x3FFF / 0x3FFF);
    for (i = 0; i < 0x2D; i++)
        if (sub_00199E70(i)) r4d_StreamSetVolume(i, sub_0019A460(i));
    for (i = 0; i < 3; i++) {
        if (i == m1_track3DFECC || !sub_0019A930(i)) continue;
        id = r1e_pairs3DFEA0[i].id0;
        if (id < 0x30 || id >= 0x215) continue;
        r4d_TrackSetPartVolume(i, 0, sub_0019ACE0(i, 0));
    }
}

extern const char r1b_fmtF[];
char  *r1b_NextToken(char **cur);
int    r1b_sscanf(const char *s, const char *fmt, ...);
float *sub_000390A0(void);

/* 0x7A8B0: script command: read four floats from the argument string into the shared colour (0x3DCDA8); stops quietly if a value is missing. */
void m1_CmdColor07A8B0(char *s) {
    float v[4]; char *t; float *d;
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &v[0]);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &v[1]);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &v[2]);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &v[3]);
    d = sub_000390A0();
    d[0] = v[0]; d[1] = v[1]; d[2] = v[2]; d[3] = v[3];
}
