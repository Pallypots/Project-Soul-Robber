/* Area m2, file 10. Names inferred. */
#include <stdint.h>

typedef struct M2Pose10 { uint8_t unk00[0xB8]; uint32_t flagsB8; } M2Pose10;
typedef struct M2Anm10 { uint8_t unk00[8]; int32_t cur8; uint8_t unk0C[8]; M2Pose10 *pose14; } M2Anm10;
typedef struct M2Clip10 { uint8_t unk00[0xC]; void *clipC; float speed10; } M2Clip10;
typedef struct M2Node10 { uint8_t unk00[0xC]; uint32_t flagsC; uint8_t unk10[0x20]; M2Anm10 *anim30; uint8_t unk34[8]; struct M2Node10 *next3C; } M2Node10;
typedef struct M2Mdl10 { uint8_t unk00[0x5C]; M2Node10 *nodes5C; } M2Mdl10;
M2Clip10 *sub_00083120(M2Anm10 *a, int id);
void r1_NodeShow(M2Node10 *n);
void sub_00033B30(M2Node10 *n);
void aab_SetAnim832D0(M2Anm10 *a, int id);
void m1_AnimClip1AF640(M2Pose10 *p, void *clip);
void sub_001AEDD0(M2Pose10 *p, float speed);

/* 0x7E9B0: play animation id on every animated node of the model (until a node without bit 0): a node whose animation lacks the clip gets pose flag 2 and stops the walk; otherwise the flag is cleared, the node is shown and, unless already playing id, its clip and speed are set. -1 when the model, a node animation or a clip is missing. */
int m2_PlayAnim7E9B0(M2Mdl10 *m, int id) {
    int r = 0;
    M2Node10 *n;
    if (m == 0) return -1;
    n = m->nodes5C;
    if (n == 0) return -1;
    do {
        M2Anm10 *a; M2Clip10 *c;
        if (!(n->flagsC & 1)) return r;
        a = n->anim30;
        if (a == 0) { r = -1; return r; }
        c = sub_00083120(a, id);
        if (c == 0) {
            if ((n->flagsC & 1) && n->anim30 != 0) n->anim30->pose14->flagsB8 |= 2;
            return r;
        }
        if ((n->flagsC & 1) && n->anim30 != 0) n->anim30->pose14->flagsB8 &= ~2u;
        r1_NodeShow(n);
        if (c->clipC == 0) { r = -1; return r; }
        if (a->cur8 != id) {
            sub_00033B30(n);
            aab_SetAnim832D0(a, id);
            m1_AnimClip1AF640(a->pose14, c->clipC);
            sub_001AEDD0(a->pose14, c->speed10 * 60.0f * 0.016666668f);
        }
        n = n->next3C;
    } while (n != 0);
    return r;
}

extern int m1_track3DFECC;
extern int m1_mode3DFEC0;
extern int r1e_g3DFED4;
int  sub_00199B00(int k);
void r4d_VoiceSetVolume(int track, int vol);
int  sub_0019A8E0(int k);
void m1_Stub102FA0();
int  sub_0019ADE0(int k);
int  sub_0019AD10(int k, int part);
void r4d_TrackSetPartVolume(int track, int part, int vol);

/* 0x47C80: re-apply the master volume (0..128 scale) to the playing track: modes 0-1 set the voice volume, mode 2 goes to the debug stub, modes 3..49 and 50+ (bank offset 0x1E3) set every part's volume from its base level. */
void m2_TrackVolume47C80(void) {
    int k, i, n;
    if (m1_track3DFECC < 0) return;
    k = m1_mode3DFEC0;
    if (k < 2) {
        r4d_VoiceSetVolume(m1_track3DFECC, sub_00199B00(k) * r1e_g3DFED4 / 128);
    } else if (k < 3) {
        m1_Stub102FA0(m1_track3DFECC, sub_0019A8E0(k - 2) * r1e_g3DFED4 / 128);
    } else if (k < 0x32) {
        n = sub_0019ADE0(k - 3);
        for (i = 0; i < n; i++)
            r4d_TrackSetPartVolume(m1_track3DFECC, i, sub_0019AD10(m1_mode3DFEC0 - 3, i) * r1e_g3DFED4 / 128);
    } else {
        n = sub_0019ADE0(k + 0x1E3);
        for (i = 0; i < n; i++)
            r4d_TrackSetPartVolume(m1_track3DFECC, i, sub_0019AD10(m1_mode3DFEC0 + 0x1E3, i) * r1e_g3DFED4 / 128);
    }
}

typedef struct M2Pen10 { uint8_t unk00[0x20]; int32_t x20, y24; } M2Pen10;
typedef struct M2TBox10 { int32_t on0; uint8_t unk04[4]; int32_t end8; int32_t startC; int32_t count10; uint8_t unk14[4]; int32_t x18, y1C; uint8_t unk20[0x14]; M2Pen10 *pen34; char **title38; } M2TBox10;
extern int *m1_pg2C4B08;
extern const char a4c_strMenu[];
extern const char m1_strFmtBracket266FB0[];
extern const char r1d_fmt266FC0[];
int m1_DrawTextf2E8C0(int a1, int x, int y, int font, int *px, int *py, const char *fmt, ...);
int sub_0003F5A0(int a, int x, int y, int *px, int *py, void *r);

/* 0x3F650: draw a text list box: its title at the remembered pen (or its own corner), a '^' marker when scrolled down, the visible records, and a 'v' marker when more records follow. Returns the draw state. */
int m2_ListBoxDraw3F650(int a, M2TBox10 *b) {
    int x, y;
    if ((b->pen34 != 0) & b->on0) { x = b->pen34->x20; y = b->pen34->y24; }
    else { x = b->x18; y = b->y1C; }
    a = m1_DrawTextf2E8C0(a, x, y, m1_pg2C4B08[0], &x, &y, m1_strFmtBracket266FB0, b->title38 ? *b->title38 : a4c_strMenu);
    if (b->count10 < b->end8)
        a = m1_DrawTextf2E8C0(a, x, y, m1_pg2C4B08[1], &x, &y, r1d_fmt266FC0, b->startC > 0 ? '^' : ' ');
    a = sub_0003F5A0(a, x, y, &x, &y, b);
    if (b->count10 < b->end8)
        a = m1_DrawTextf2E8C0(a, x, y, m1_pg2C4B08[1], &x, &y, r1d_fmt266FC0, b->startC + b->count10 >= b->end8 ? ' ' : 'v');
    return a;
}
