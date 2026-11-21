/* Area m1, file 272: worker thread setup. Names inferred. */
#include <stdint.h>

typedef struct M1Wk272 { int32_t state0; int32_t thread4; int32_t sem8; uint8_t unkC[4]; int32_t a10, a14, a18, a1C, a20, a24; } M1Wk272;
typedef struct M1SemD272 { int32_t f00; int32_t max04; int32_t init08; int32_t f0C, f10; int32_t f14; } M1SemD272;
typedef struct M1ThD272 { void (*entry)(void); int32_t a, b; void *stack; int32_t f10; } M1ThD272;
extern uint8_t m1_stack40B860[];
M1Wk272 *sub_000589E0(void);
int32_t sub_001AA240(M1SemD272 *d);                          /* create semaphore */
void sub_00057E60(void);                                     /* worker entry */
int32_t sub_001AD720(M1ThD272 *t, M1Wk272 *w);               /* create thread */
void sub_001AD570(int32_t th, int32_t prio);
void sub_001AD3D0(int32_t th, M1Wk272 *w);                   /* start thread */

/* 0x00058A40: set up a worker: take a free worker record (hangs if none), give it a semaphore (max 300), store
   its six parameters, create its thread (entry 0x00057E60) at priority prio + 10 and start it. Returns the
   thread handle. */
int32_t m1_WorkerStart58A40(int32_t prio, int32_t a18, int32_t a10, int32_t a14, int32_t a1C, int32_t a20, int32_t a24)
{
    M1Wk272 *w;
    M1SemD272 d;
    M1ThD272 t;
    w = sub_000589E0();
    if (!w) for (;;) ;
    d.init08 = 0;
    d.f14 = 0;
    d.max04 = 0x12C;
    w->sem8 = sub_001AA240(&d);
    w->a10 = a10;
    w->a14 = a14;
    w->state0 = 2;
    t.entry = sub_00057E60;
    t.a = w->a10;
    t.b = w->a14;
    t.f10 = 1;
    t.stack = m1_stack40B860;
    w->a1C = a1C;
    w->a18 = a18;
    w->a20 = a20;
    w->a24 = a24;
    w->thread4 = sub_001AD720(&t, w);
    sub_001AD570(w->thread4, prio + 10);
    sub_001AD3D0(w->thread4, w);
    return w->thread4;
}

