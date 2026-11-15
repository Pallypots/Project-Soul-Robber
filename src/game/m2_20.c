/* Area m2, file 20. Names inferred. */
#include <stdint.h>

extern int32_t r1e_qB37E094[8];
extern int32_t r1e_qStateB37E0B4;
extern float   r1e_qWaitB37E0B8;
extern int16_t r1e_qLeftB37E0BE;
extern int16_t m2_qCnt37E0C0;
extern uint8_t m2_qBase37E03C[];
void a60_StepByFrame(float *t, int dir);

/* 0x2A830: message queue step. State 0 arms a 10-frame wait; with nothing pending it shifts the queue down one entry, else goes to state 1. State 1 shrinks the last glyph with the wait (scale = wait/10) and at 0 removes it and returns to state 0. */
void m2_QueueStep2A830(void) {
    uint8_t *s;
    switch (r1e_qStateB37E0B4) {
    case 0:
        r1e_qWaitB37E0B8 = 10.0f;
        if (m2_qCnt37E0C0 == 0) {
            r1e_qB37E094[0] = r1e_qB37E094[1];
            r1e_qB37E094[1] = r1e_qB37E094[2];
            r1e_qB37E094[2] = r1e_qB37E094[3];
            r1e_qB37E094[3] = r1e_qB37E094[4];
            r1e_qB37E094[4] = r1e_qB37E094[5];
            r1e_qB37E094[5] = r1e_qB37E094[6];
            r1e_qB37E094[6] = r1e_qB37E094[7];
            r1e_qB37E094[7] = 0;
            r1e_qStateB37E0B4 = 0;
            return;
        }
        r1e_qStateB37E0B4 = 1;
        break;
    case 1: {
        uint8_t *volatile base = m2_qBase37E03C;
        a60_StepByFrame(&r1e_qWaitB37E0B8, 0);
        { int volatile k = (uint16_t)r1e_qLeftB37E0BE - 1; s = base + k * 0x9C; }
        *(float *)(s + 0xA8) = *(float *)(s + 0xA4) = r1e_qWaitB37E0B8 * 0.1f;
        if (r1e_qWaitB37E0B8 <= 0.0f) {
            *(float *)(s + 0xA8) = *(float *)(s + 0xA4) = 0.0f;
            m2_qCnt37E0C0--;
            r1e_qLeftB37E0BE--;
            r1e_qStateB37E0B4 = 0;
        }
        break;
    }
    }
}



typedef struct M2JNode20 { struct M2JNode20 *next0; uint8_t unk04[8]; uint8_t *jobC; } M2JNode20;
typedef struct M2Bucket20 { uint8_t unk00[4]; M2JNode20 *first4; uint8_t unk08[8]; } M2Bucket20;
typedef struct M2SemSt20 { int32_t a0; int32_t b4, c8; int32_t dC; } M2SemSt20;
extern uint8_t r1c_threads3E46A0[];
extern M2Bucket20 r1e_buckets3E46E0[6];
extern int32_t r1j_jobBucketCur;
extern int32_t *m1_ld3E3F50;
extern uint8_t r1j_jobFree3E3F54[];
void r1e_QueueDrain(void *q);
void m1_Stub102FA0();
void sub_001AA520(int sem);
int  sub_001AA550(int sem, M2SemSt20 *st);
void sub_001AD6A0(void);
void sub_00053880(void *p);
void a4c_ListRemove(void *node);
void a4c_ListAppend(void *list, void *node);

/* 0x583C0: sweep the 6 job buckets: release every running job's semaphore and wait (yielding) while it is still held and busy; finished jobs (state 3) free their buffer, reset and go back to the free list. The current bucket and job are published while sweeping. */
void m2_JobSweep583C0(void) {
    M2SemSt20 st;
    int i;
    r1e_QueueDrain(r1c_threads3E46A0);
    for (i = 0; i < 6; i++) {
        M2JNode20 *n = r1e_buckets3E46E0[i].first4;
        r1j_jobBucketCur = i;
        while (n != 0) {
            int32_t *volatile vs = (int32_t *)(n->jobC + 0x10);
            int32_t *s = vs;
            m1_ld3E3F50 = s;
            m1_Stub102FA0(0);
            if (s[0] == 1) {
                sub_001AA520(s[2]);
                while (s[0] == 1) {
                    if (s[2] == -1) break;
                    if (sub_001AA550(s[2], &st) == -1) break;
                    if (st.a0 <= 0 && st.dC > 0) break;
                    sub_001AD6A0();
                }
            }
            m1_Stub102FA0(0);
            n = n->next0;
            if (s[0] == 3) {
                sub_00053880((void *)s[4]);
                s[4] = 0; s[1] = -1; s[2] = -1;
                { int volatile d = -0x10; s = (int32_t *)((uint8_t *)s + d); }
                a4c_ListRemove(s);
                a4c_ListAppend(r1j_jobFree3E3F54, s);
            }
        }
    }
    m1_ld3E3F50 = 0;
    r1j_jobBucketCur = -1;
}

typedef struct M2Anim20 { int32_t id0; uint8_t unk04[4]; uint8_t flags8; uint8_t unk09[3]; void *motC; float speed10; int32_t frames14; int32_t mode18; uint8_t unk1C[4]; struct M2Anim20 *next20; } M2Anim20;
typedef struct M2AnCtx20 { uint8_t unk00[8]; int32_t cur8; uint8_t unk0C[4]; M2Anim20 *list10; void *parts14; } M2AnCtx20;
void r4e_MotionStart(void *p, void *mot, int mode, int secs);
void r4d_PartsClearMask(void *p, int m);
void r4d_PartsSetMask(void *p, int m);
void sub_001AEDD0(void *p, float speed);
void sub_00082F90(M2AnCtx20 *c, M2Anim20 *a);

/* 0x832D0: switch the context to animation id (-1 = current): find it in the list (none: current = -1), start its motion with mode bits {4,8,0x10,0x20}[mode]|2 and its length rounded up to whole seconds, clear mask 2, set or clear mask 4 by its loop flag, set its speed (x60/60) and apply it. */
void m2_AnimSet832D0(M2AnCtx20 *c, int id) {
    int modes[4];
    M2Anim20 *a;
    modes[0] = 4; modes[1] = 8; modes[2] = 0x10; modes[3] = 0x20;
    if (id == c->cur8) return;
    if (id == -1) id = c->cur8;
    c->cur8 = id;
    for (a = c->list10; a != 0; a = a->next20)
        if (id == a->id0) break;
    if (a == 0) { c->cur8 = -1; return; }
    if (a->motC == 0) return;
    {
        int volatile k = 60;
        r4e_MotionStart(c->parts14, a->motC, modes[a->mode18] | 2, (a->frames14 * k + 59) / 60);
    }
    r4d_PartsClearMask(c->parts14, 2);
    if (!(a->flags8 & 1)) r4d_PartsSetMask(c->parts14, 4);
    else r4d_PartsClearMask(c->parts14, 4);
    sub_001AEDD0(c->parts14, a->speed10 * 60.0f * 0.016666668f);
    sub_00082F90(c, a);
}
