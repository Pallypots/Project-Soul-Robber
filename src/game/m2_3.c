/* Area m2, file 3. Names inferred. */
#include <stdint.h>

typedef struct M2Slot3 { uint8_t unk00[0x20]; int32_t kind20; uint8_t unk24[8]; float f2C; uint8_t unk30[8]; float f38, f3C, f40; int32_t i44; } M2Slot3;
extern int r1e_g42CE38;
extern int r1e_g41316C;
extern int r1e_g413170;
extern M2Slot3 r1e_slots42CB20[11];

/* 0x376D0: append a copy of slot s to the 10-entry list (-1 when full). Kind-1 slots get f2C doubled in world 4 area 2 and world 1 area 3. The copy's last four fields are cleared and the next entry's kind reset. Returns the new index. */
int m2_SlotAdd376D0(M2Slot3 *s) {
    M2Slot3 *d;
    if (r1e_g42CE38 == 10) return -1;
    if ((r1e_g41316C == 4 && r1e_g413170 == 2 && s->kind20 == 1) ||
        (r1e_g41316C == 1 && r1e_g413170 == 3 && s->kind20 == 1)) {
        float volatile k = 2.0f; s->f2C *= k;
    }
    d = &r1e_slots42CB20[r1e_g42CE38];
    *d = *s;
    d->f38 = 0.0f; d->f3C = 0.0f; d->f40 = 0.0f; d->i44 = 0;
    r1e_g42CE38++;
    r1e_slots42CB20[r1e_g42CE38].kind20 = 0;
    return r1e_g42CE38 - 1;
}

typedef struct M2Rec3 { uint8_t b[0x24]; } M2Rec3;
typedef struct M2Lst3 { uint8_t unk00[8]; M2Rec3 *recs; } M2Lst3;
typedef struct M2Run3 { uint8_t unk00[4]; int32_t mark4; int32_t end8; int32_t startC; int32_t count10; uint8_t unk14[0xC]; int32_t x20, y24; uint8_t unk28[0x10]; M2Lst3 *lst38; } M2Run3;
int sub_0003E6D0(int a, int x, int y, int *px, int *py, int marked, M2Rec3 *r);

/* 0x3F5A0: run the records startC .. min(end8, startC+count10) of r through the step function 0x3E6D0, carrying the state a and the pen x/y; at the marked record remember x+0x20 and y. Writes the final pen to *px/*py when given and returns the state. */
int m2_RunRecs3F5A0(int a, int x, int y, int *px, int *py, M2Run3 *r) {
    int i; M2Rec3 *p;
    if (r->lst38 != 0 && r->lst38->recs != 0) {
        p = &r->lst38->recs[r->startC];
        for (i = r->startC; i < r->end8; i++, p++) {
            if (i >= r->count10 + r->startC) break;
            a = sub_0003E6D0(a, x, y, &x, &y, i == r->mark4, p);
            if (i == r->mark4) { r->x20 = x + 0x20; r->y24 = y; }
        }
    }
    if (px) *px = x;
    if (py) *py = y;
    return a;
}
