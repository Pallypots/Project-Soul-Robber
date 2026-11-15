/* Area m2, file 11. Names inferred. */
#include <stdint.h>

typedef struct M2Chn11 { uint8_t unk00[0x20]; uint8_t sh20; uint8_t unk21; uint8_t sh22; } M2Chn11;
typedef struct M2TEnt11 { M2Chn11 *chn0; uint8_t unk04[0xC]; int32_t v10; uint8_t unk14[4]; } M2TEnt11;
typedef struct M2Tbl11 { int32_t n0; uint8_t unk04[0xC]; M2TEnt11 e[1]; } M2Tbl11;
typedef struct M2Elem11 { uint32_t flags0; uint8_t unk04[0xD4]; int32_t chD8; uint32_t maskDC, maskE0; uint8_t unkE4[0xC]; } M2Elem11;
typedef struct M2Arr11 { int32_t n0; M2Elem11 *p4; } M2Arr11;
typedef struct M2LEnt11 { M2Arr11 *arr0; uint8_t unk04[0x14]; } M2LEnt11;
typedef struct M2Lst11 { uint32_t n0; uint8_t unk04[0xC]; M2LEnt11 l[1]; } M2Lst11;
typedef struct M2Mix11 { uint8_t unk00[4]; M2Tbl11 *tbl4; M2Lst11 *lst8; uint8_t unk0C[4]; int32_t v10; } M2Mix11;

/* 0x52CF0: load channel values from src (src[1] also kept at +0x10, then one per table entry), then give every active (bits 0 and 0x20000) element with a channel the bit masks 1<<shift of its channel's two shift bytes; other elements get zero masks. */
void m2_MixLoad52CF0(M2Mix11 *m, int32_t *src) {
    M2Tbl11 *t = m->tbl4;
    int32_t *p = src + 1;
    int i, n;
    uint32_t j;
    M2Lst11 *l;
    m->v10 = src[1];
    for (n = t->n0, i = 0; i < n; i++) t->e[i].v10 = *p++;
    l = m->lst8;
    for (j = 0; j < l->n0; j++) {
        M2Arr11 *a = l->l[j].arr0;
        int k;
        for (k = 0; k < a->n0; k++) {
            M2Elem11 *e = &a->p4[k];
            uint32_t volatile f = e->flags0;
            if ((f & 1) && (f & 0x20000) && e->chD8 >= 0) {
                a->p4[k].maskDC = 1 << m->tbl4->e[a->p4[k].chD8].chn0->sh20;
                a->p4[k].maskE0 = 1 << m->tbl4->e[a->p4[k].chD8].chn0->sh22;
            } else {
                a->p4[k].maskDC = 0;
                a->p4[k].maskE0 = 0;
            }
        }
    }
}

typedef struct M2Part11 { uint8_t unk00[0x88]; void *tree88; uint8_t unk8C[4]; uint32_t flags90; } M2Part11;
typedef struct M2Clp11 { uint8_t unk00[0x1C]; uint32_t mask1C; } M2Clp11;
typedef struct M2Anm11 { uint8_t unk00[8]; int32_t cur8; } M2Anm11;
typedef struct M2Node11 { uint8_t unk00[0xC]; uint32_t flagsC; uint8_t unk10[0x10]; M2Part11 *a20; uint8_t unk24[4]; M2Part11 *b28; uint8_t unk2C[4]; M2Anm11 *anim30; uint8_t unk34[8]; struct M2Node11 *next3C; } M2Node11;
M2Clp11 *sub_00083120(M2Anm11 *a, int id);
void r1b_PartsHideTree(void *t);
void r1b_PartsUnhideTree(void *t);

/* 0x1D4E0: apply the current clip's node mask to the nodes after root: node i with mask bit i set gets bit 0x10000 and its two parts hidden; others lose the bit and, unless root itself has it, get their parts shown. A first part already in the wanted state skips the node. */
void m2_NodeMask1D4E0(M2Node11 *root) {
    M2Clp11 *c = sub_00083120(root->anim30, root->anim30->cur8);
    M2Node11 *n;
    M2Part11 *p;
    int i = 0;
    for (n = root->next3C; n != 0; n = n->next3C, i++) {
        if (c->mask1C & (1 << i)) {
            n->flagsC |= 0x10000;
            p = n->a20;
            if (p != 0) {
                if (p->flags90 & 0x10) continue;
                p->flags90 |= 0x10;
                if (p->tree88 != 0) r1b_PartsHideTree(p->tree88);
            }
            p = n->b28;
            if (p != 0 && !(p->flags90 & 0x10)) {
                p->flags90 |= 0x10;
                if (p->tree88 != 0) r1b_PartsHideTree(p->tree88);
            }
        } else {
            n->flagsC &= ~0x10000u;
            if (root->flagsC & 0x10000) continue;
            p = n->a20;
            if (p != 0) {
                if (!(p->flags90 & 0x10)) continue;
                p->flags90 &= ~0x10u;
                if (p->tree88 != 0) r1b_PartsUnhideTree(p->tree88);
            }
            p = n->b28;
            if (p != 0 && (p->flags90 & 0x10)) {
                p->flags90 &= ~0x10u;
                if (p->tree88 != 0) r1b_PartsUnhideTree(p->tree88);
            }
        }
    }
}
