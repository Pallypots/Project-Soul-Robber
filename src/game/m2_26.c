/* Area m2, file 26. Names inferred. */
#include <stdint.h>

extern int a12_state37DCFC;
extern int m2_g37DD00, m2_g37DD04, m2_g37DD08, m2_g37DD1C;
extern float r1i_hudSpin37DD20;
extern float m2_g37DD24;
void sub_00032140(int a, int b, int c);

/* 0x252A0: HUD counter command. Command 0 closes it (state 1: start closing and flip the spin; state 3: reset to state 2). Command 1 sets value v (negative values hang, 0 means -1): state 0 opens it, state 1 only updates, state 2 reopens and flips the spin, state 3 sets the spin value. */
void m2_HudCounter252A0(int cmd, int v) {
    sub_00032140(1, 0, 0);
    switch (cmd) {
    case 0:
        switch (a12_state37DCFC) {
        case 1:
            a12_state37DCFC = 2;
            m2_g37DD00 = 0;
            goto flip;
        case 3:
            m2_g37DD00 = 0;
            m2_g37DD1C = 0;
            a12_state37DCFC = 2;
            return;
        }
        return;
    case 1:
        if (v < 0) for (;;) ;
        if (v == 0) v = -1;
        switch (a12_state37DCFC) {
        case 0:
            m2_g37DD08 = 0;
            m2_g37DD1C = 0;
            a12_state37DCFC = 1;
            m2_g37DD00 = 3;
            m2_g37DD04 = 2;
            m2_g37DD24 = (float)v;
            return;
        case 1:
            m2_g37DD24 = (float)v;
            return;
        case 2: {
            int volatile one = 1;
            a12_state37DCFC = one;
            m2_g37DD00 = 3;
            m2_g37DD04 = 2;
            m2_g37DD08 = 0;
            m2_g37DD24 = (float)v;
            goto flip;
        }
        case 3:
            r1i_hudSpin37DD20 = (float)v;
            return;
        }
        return;
    }
    return;
flip:
    r1i_hudSpin37DD20 = 20.0f - r1i_hudSpin37DD20;
}


extern int a60_v3E60D8, a60_v3E60F4, a60_state3E60D4, a60_v3E60DC, a60_v3E60E0;
extern float r6d_timer3E6100;
void m1_SndPlay023D80(int a, int b);
void m1_SndBank0243B0(int a, int b);
void aab_Add24D30(int a, int b);
void a60_StepByFrame(float *t, int dir);
void sub_00048AF0(int id);

/* 0x601E0: four-step sound sequence: step 0 starts the base sounds, steps 1-3 wait out a 20-frame timer and then start the next layer (bank 5 with the saved parameter, then two adds); the last step plays sound 0x393 and resets the sequence (state 2). */
void m2_SndSequence601E0(void) {
    switch (a60_v3E60D8) {
    case 0:
        m1_SndPlay023D80(1, 0);
        m1_SndBank0243B0(0, 0);
        aab_Add24D30(0, 0);
        goto next;
    case 1:
        a60_StepByFrame(&r6d_timer3E6100, 0);
        if (!(0.0f >= r6d_timer3E6100)) return;
        m1_SndBank0243B0(5, a60_v3E60F4);
        goto next;
    case 2:
        a60_StepByFrame(&r6d_timer3E6100, 0);
        if (!(0.0f >= r6d_timer3E6100)) return;
        aab_Add24D30(5, 1);
        aab_Add24D30(1, 0);
        goto next;
    case 3:
        a60_StepByFrame(&r6d_timer3E6100, 0);
        if (!(0.0f >= r6d_timer3E6100)) return;
        sub_00048AF0(0x393);
        a60_state3E60D4 = 2;
        a60_v3E60D8 = 0;
        a60_v3E60DC = 0;
        a60_v3E60E0 = 0;
        return;
    }
    return;
next:
    r6d_timer3E6100 = 20.0f;
    a60_v3E60D8++;
}

extern int r1j_ioStep3E3954;
extern uint32_t *m1_ioBuf3E397C;
extern int r1h_mode3E3950;
extern int r1j_fadeState428F20;
extern uint8_t a4c_obj428F40[];
void *a50_Alloc(int heap, int size, int a, int b);
void  sub_001A9740(void *buf);
short a60_TimerKind(void *o);
int   sub_00056A40(void);
void  sub_00072F30(void *o, int a, float t, int b, int c);
void  sub_00053880(void *p);
void __stosd(unsigned long *d, unsigned long v, unsigned int n);
#pragma intrinsic(__stosd)

/* 0x57260: save/load I/O step: step 0 allocates and clears the 0x8A0-byte work buffer and starts the device; steps 0-1 then run the fade machine (wait for the timer, wait for the device, fade over 8 frames, then advance); any later step frees the buffer and returns to mode 3. */
void m2_IoStep57260(void) {
    switch (r1j_ioStep3E3954) {
    case 0:
        m1_ioBuf3E397C = (uint32_t *)a50_Alloc(1, 0x8A0, 0, 0);
        __stosd((unsigned long *)m1_ioBuf3E397C, 0, 0x228);
        sub_001A9740(m1_ioBuf3E397C);
        r1j_ioStep3E3954++;
    case 1:
        switch (r1j_fadeState428F20) {
        case 0:
            r1j_fadeState428F20 = 1;
        case 1:
            if (a60_TimerKind(a4c_obj428F40) == 0) r1j_fadeState428F20 = 2;
            return;
        case 2:
            if (sub_00056A40() == 1) {
                sub_00072F30(a4c_obj428F40, 0, 8.0f, 0, 0);
                r1j_fadeState428F20 = 3;
            }
            return;
        case 3:
            if (a60_TimerKind(a4c_obj428F40) == 0) r1j_ioStep3E3954++;
            return;
        }
        return;
    default:
        sub_00053880(m1_ioBuf3E397C);
        m1_ioBuf3E397C = 0;
        r1h_mode3E3950 = 3;
        r1j_ioStep3E3954 = 0;
        return;
    }
}
