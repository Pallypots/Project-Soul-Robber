/* Area m1, file 368: register-argument revisits (written with normal parameters). Names inferred. */
#include <stdint.h>

#include "m1_fan.h"
extern M1Fan m1_fanTbl2DF0C4[];
extern M1FanSlot m1_fanSlots3E6638[];
/* 0x6C270 takes the slot index in eax, the owner in ecx and the fan id in edx; written as ordinary parameters. */
void sub_0006C270(int i, void *owner, int id);

/* 0x6CA50: lay out fan id's slots: create each one and spread their angles evenly over the fan's span. */
void m1_FanLayout06CA50(void *owner, int id) {
    int i; M1FanSlot *s = m1_fanSlots3E6638;
    for (i = 0; i < m1_fanTbl2DF0C4[id].count; i++, s++) {
        sub_0006C270(i, owner, id);
        s->angle = m1_fanTbl2DF0C4[id].span / (float)m1_fanTbl2DF0C4[id].count * (float)i;
    }
}

#include "m1_uvanim.h"
extern M1UvAnim *m1_uvAnimsB3E6988;
extern float m1_frameTime42C858;
/* 0x75780 takes the model in eax, the part in ebx and the UV data in edi; written as ordinary parameters. */
void r6d_ModelSetUV1(int model, int part, const float *uv);

/* 0x75850: step every UV animation in the second list: move to the next key when the next key's time is reached (wrapping), advance the clock and apply the UVs of the key that was current at the start of the step. */
void m1_UvAnimStepB075850(void) {
    M1UvAnim *a; M1UvKey *k;
    for (a = m1_uvAnimsB3E6988; a != 0; a = a->next) {
        k = (M1UvKey *)((uint8_t *)a->seq + (a->key + 1) * 0x10);
        if (a->time > k->dur) {
            a->key++;
            a->time = 0.0f;
            if (a->key >= a->seq->count) a->key = 0;
        }
        a->time += m1_frameTime42C858;
        r6d_ModelSetUV1(a->model, a->part, k->uv);
    }
}
