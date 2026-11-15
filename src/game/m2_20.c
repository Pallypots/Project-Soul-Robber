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


