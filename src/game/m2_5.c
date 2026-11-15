/* Area m2, file 5. Names inferred. */
#include <stdint.h>

typedef struct M2Part5 { uint8_t unk00[0x88]; void *tree88; uint8_t unk8C[4]; uint32_t flags90; } M2Part5;
typedef struct M2Node5 { uint8_t unk00[0xC]; uint32_t flagsC; uint8_t unk10[0x10]; M2Part5 *a20; uint8_t unk24[4]; M2Part5 *b28; uint8_t unk2C[0x10]; struct M2Node5 *next3C; } M2Node5;
void r1b_PartsHideTree(void *t);
void r1b_PartsUnhideTree(void *t);

/* 0x1D610: clear the head's 0x10000 bit, then walk the sibling list: nodes with the bit set hide their two parts (set part flag 0x10 and hide its tree), others unhide them; a first part already in the wanted state skips the node. */
void m2_NodeShow1D610(M2Node5 *n) {
    M2Part5 *p;
    if (n == 0) return;
    n->flagsC &= ~0x10000u;
    do {
        p = n->a20;
        if (!(n->flagsC & 0x10000)) {
            if (p != 0) {
                if (!(p->flags90 & 0x10)) goto next;
                p->flags90 &= ~0x10u;
                if (p->tree88 != 0) r1b_PartsUnhideTree(p->tree88);
            }
            p = n->b28;
            if (p != 0 && (p->flags90 & 0x10)) {
                p->flags90 &= ~0x10u;
                if (p->tree88 != 0) r1b_PartsUnhideTree(p->tree88);
            }
        } else {
            if (p != 0) {
                if (p->flags90 & 0x10) goto next;
                p->flags90 |= 0x10;
                if (p->tree88 != 0) r1b_PartsHideTree(p->tree88);
            }
            p = n->b28;
            if (p != 0 && !(p->flags90 & 0x10)) {
                p->flags90 |= 0x10;
                if (p->tree88 != 0) r1b_PartsHideTree(p->tree88);
            }
        }
    next:
        n = n->next3C;
    } while (n != 0);
}

typedef struct M2Blk5 { uint32_t used0; struct M2Heap5 *heap4; struct M2Blk5 *next8, *prevC; uint8_t link10[0x10]; uint32_t size20, avail24; uint8_t unk28[0x14]; uint32_t flags3C; } M2Blk5;
typedef struct M2Heap5 { uint8_t unk00[4]; M2Blk5 *first4; M2Blk5 *last8; uint8_t freeC[0x24]; int32_t sem30; } M2Heap5;
void r4d_SemWait(int s);
int  sub_001AA520(int s);
void a4c_ListRemove(void *node);
void a4c_ListAppend(void *list, void *node);

/* 0x47640: free a heap block (header 0x40 bytes before ptr) under the heap lock: mark it free, move it to the free list, merge the free blocks after it and then the free block before it, update its usable size and the heap's last block, then release the lock. */
void m2_HeapFree47640(uint8_t *ptr) {
    M2Blk5 *b = (M2Blk5 *)(ptr - 0x40), *n;
    M2Heap5 *h;
    if (ptr == 0 || (b->flags3C & 1)) return;
    h = b->heap4;
    if (h->sem30 != -1) r4d_SemWait(h->sem30);
    b->used0 = 0; b->flags3C = 0;
    a4c_ListRemove(b->link10);
    a4c_ListAppend(h->freeC, b->link10);
    for (n = b->next8; n != 0; n = n->next8) {
        if (n->used0 & 1) break;
        b->next8 = n->next8;
        if (n->next8 != 0) n->next8->prevC = b;
        b->size20 += n->size20;
        a4c_ListRemove(n->link10);
    }
    if (h->first4 != b) {
        n = b->prevC;
        if (n != 0 && !(n->used0 & 1)) {
            n->next8 = b->next8;
            if (b->next8 != 0) b->next8->prevC = n;
            n->size20 += b->size20;
            a4c_ListRemove(b->link10);
            b = n;
        }
    }
    b->avail24 = b->size20 - 0x44;
    if (b->next8 == 0) h->last8 = b;
    if (h->sem30 != -1) {
        while (sub_001AA520(h->sem30) == -1) ;
    }
}
