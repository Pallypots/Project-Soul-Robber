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
