/* Area m1, file 273: loader job setup. Names inferred. */
#include <stdint.h>

typedef struct M1Job273 { int32_t state0; int32_t thread4; int32_t sem8; uint8_t unkC[4]; int32_t a10, a14, a18, a1C; } M1Job273;
typedef struct M1SemD273 { int32_t f00; int32_t max04; int32_t init08; int32_t f0C, f10; int32_t f14; } M1SemD273;
typedef struct M1ThD273 { void (*entry)(void); int32_t a, b; void *stack; int32_t f10; } M1ThD273;
extern M1Job273 m1_job3E3F64;
extern int32_t m1_jobPoll3E3F8C;
extern uint8_t m1_stack40B860[];
void sub_00058260(void);
int32_t sub_001AA240(M1SemD273 *d);                          /* create semaphore */
void sub_000584E0(void);                                     /* loader entry */
int32_t sub_001AD720(M1ThD273 *t, M1Job273 *j);              /* create thread */
void sub_001AD3D0(int32_t th, M1Job273 *j);                  /* start thread */
int32_t sub_00102FA0(int32_t a);                             /* debug trace */
int32_t sub_001A85D0(int32_t k);
int32_t sub_001A85C0(int32_t fn);
uint64_t sub_001A7C00(uint64_t v);
void sub_001A8600(int32_t k);
void sub_00057EE0(void);

/* 0x00058540: start the background loader job for (a, b): create its semaphore and thread (entry 0x000584E0,
   priority 0x78), start it, then install the job poller (remembering any other poller), set flag 0x800 in the
   64-bit system word and restore message callback 2 if it was set. Returns the thread handle, or 0 when a is 0. */
int32_t m1_LoaderStart58540(int32_t a, int32_t b)
{
    M1SemD273 d;
    M1ThD273 t;
    int32_t had, prev;
    sub_00058260();
    if (a == 0) return 0;
    d.init08 = 0;
    d.max04 = 1;
    d.f14 = 0;
    m1_job3E3F64.sem8 = sub_001AA240(&d);
    m1_job3E3F64.a10 = 0;
    m1_job3E3F64.a14 = 0;
    m1_job3E3F64.state0 = 0;
    t.entry = sub_000584E0;
    t.a = m1_job3E3F64.a10;
    t.b = m1_job3E3F64.a14;
    t.f10 = 0x78;
    t.stack = m1_stack40B860;
    m1_job3E3F64.thread4 = sub_001AD720(&t, &m1_job3E3F64);
    m1_job3E3F64.a18 = a;
    m1_job3E3F64.a1C = b;
    sub_00102FA0(0);
    if (m1_job3E3F64.thread4 != -1) {
        sub_001AD3D0(m1_job3E3F64.thread4, &m1_job3E3F64);
        m1_job3E3F64.state0 = 2;
    }
    had = sub_001A85D0(2);
    prev = sub_001A85C0(0);
    if (prev != (int32_t)(intptr_t)sub_00057EE0)
        m1_jobPoll3E3F8C = prev;
    sub_001A85C0((int32_t)(intptr_t)sub_00057EE0);   /* XBOX32: function address as a 32-bit word */
    sub_001A7C00(sub_001A7C00(0) | 0x800);
    if (had)
        sub_001A8600(2);
    return m1_job3E3F64.thread4;
}

extern const char m1_s278210[], m1_s27823C[], m1_s278208[], m1_s2781F8[], m1_s2781E0[], m1_s2781D8[], m1_s2781C4[],
    m1_s2781AC[];
extern uint32_t m1_ioTbl3F5A90[0x58];
int32_t sub_00102FA0b(const char *a, ...);                    /* debug trace (retail stub) */
int32_t sub_000AD090(const char *a, ...);                     /* device probe (retail stub) */
int32_t sub_000AD090z(void);

/* 0x000ED290: device start-up: trace, then for each of two devices probe it and, while it is not there,
   retry the mount (tracing each retry); finally clear the 0x160-byte I/O table at 0x003F5A90. */
void m1_IoInitED290(void)
{
    sub_00102FA0b(m1_s278210, m1_s27823C, 2);
    if (sub_000AD090(m1_s278208) < 0) {
        while (sub_000AD090(m1_s2781F8, 0, 0) < 0)
            sub_00102FA0b(m1_s2781E0);
    }
    if (sub_000AD090(m1_s2781D8) < 0) {
        while (sub_000AD090(m1_s2781C4, 0, 0) < 0)
            sub_00102FA0b(m1_s2781AC);
    }
    sub_000AD090z();
    {
        int32_t i;
        for (i = 0; i < 0x58; i++) m1_ioTbl3F5A90[i] = 0;
    }
}

typedef struct M1Ce273 { uint8_t unk00[4]; int32_t a4, a8, aC; } M1Ce273;
typedef struct M1Cm273 { uint8_t unk00[8]; int32_t f8; } M1Cm273;
typedef struct M1Co273 { uint8_t unk00[0x30]; M1Cm273 *m30; } M1Co273;
typedef struct M1Sn273 { uint8_t unk00[0x1E8]; void *p1E8; } M1Sn273;
extern M1Sn273 *m1_scene42C8E4;
M1Ce273 *sub_000E0C30(void *s, int32_t a, int32_t k, int32_t b);
int32_t sub_000E2420(void *s);
int32_t sub_000F3140(int32_t c);
M1Co273 *sub_0001D080(void *list, int32_t a, int32_t b);
void sub_000E4050(int32_t a, int32_t c, int32_t x, int32_t y, int32_t z);
void sub_000F0430(int32_t x, int32_t y, int32_t z);

/* 0x000E4DD0: find entry k of stage s; unless it is missing or equals skip, refresh it: in stage mode 7 just
   re-place it, otherwise reset the mode's linked objects (their marker to -1, once per object of that mode)
   and re-register the entry. Returns the entry. regargs: k=EAX; stack args (s skip). */
M1Ce273 *m1_StageRefreshE4DD0(int32_t k, void *s, M1Ce273 *skip)
{
    M1Ce273 *e = sub_000E0C30(s, 0, k, 0);
    int32_t c, n;
    M1Co273 *o;
    if (!e || e == skip) return e;
    if (sub_000E2420(s) != 7) {
        c = sub_000E2420(s);
        n = sub_000F3140(c);
        o = sub_0001D080(m1_scene42C8E4->p1E8, 3, c);
        if (o && n > 0) {
            do {
                o->m30->f8 = -1;
            } while (--n);
        }
        sub_000E4050(3, sub_000E2420(s), e->a4, e->a8, e->aC);
        return e;
    }
    sub_000F0430(e->a4, e->a8, e->aC);
    return e;
}
