/* Area m1, file 53: system tables (semaphores, threads, channel select). Names inferred. */
#include <stdint.h>

typedef struct M1Thr18 { void *handle00; int32_t id04; uint8_t unk08[0x18 - 8]; } M1Thr18;
extern M1Thr18 m1_threads40EDD8[32];
void sub_001BD290(void *h);

/* 0x001AD4B0: finds the thread record with id, closes its handle (0x1BD290) and returns
 * the id (reads through a null record when the id is not found). */
int m1_ThreadClose1AD4B0(int id)
{
    M1Thr18 *t;
    for (t = m1_threads40EDD8; t != m1_threads40EDD8 + 32; t++)
        if (t->id04 == id) {
            sub_001BD290(t->handle00);
            return t->id04;
        }
    t = 0;
    sub_001BD290(t->handle00);
    return t->id04;
}
