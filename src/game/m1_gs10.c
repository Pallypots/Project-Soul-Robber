/* Area m1, /GS file 10: sound-effect trigger by event code. Names inferred. */
#include <stdint.h>
#include <intrin.h>

extern int32_t m1_sfxMute40E6A4;
extern void   *m1_sfxDev40E690;
extern uint8_t m1_sfxTable365660[];          /* 0x30-byte entries */
extern const char m1_strXactFx6_10144_27B7F0[]; /* "d:\Xact_data\effect\6_10144.bin" */
int  sub_001C7FDE(char *buf, const char *fmt, ...); /* sprintf */
void __stdcall sub_002224DD(void *dev, void *entry, int k);

/* 0x1AB3D0: b == -1 sets the mute flag from a; otherwise kind 6 (code 0x27A0 picks entry 5,
   any other code entry 0) and kind 4 (codes 0x284/0x478/0x7FC/0x860/0x1800 pick entries 0..4)
   start the matching table entry. */
void m1_SfxTrigger1AB3D0(int a, int b) {
    char buf[0x28];
    int idx = 0;
    if (b == -1) {
        m1_sfxMute40E6A4 = a != 0;
        return;
    }
    if (a == 6) {
        if (b == 0x27A0) {
            sub_001C7FDE(buf, m1_strXactFx6_10144_27B7F0);
            idx = 5;
        }
    } else if (a == 4) {
        if (b == 0x284) idx = 0;
        else if (b == 0x478) idx = 1;
        else if (b == 0x7FC) idx = 2;
        else if (b == 0x860) idx = 3;
        else if (b == 0x1800) idx = 4;
        else return;
    } else {
        return;
    }
    sub_002224DD(m1_sfxDev40E690, m1_sfxTable365660 + idx * 0x30, 0);
}

extern const char m1_fmtShkd27B390[];   /* "host0:data/movie/shock/shkd%02x.shd" */
extern uint8_t *m1_shkBuf40431C;
int   sub_0007E0A0(char *buf, const char *fmt, ...);
int   sub_000374C0(const void *path);              /* file size */
void *sub_00037550(const char *path, int k);       /* load file */
void  sub_00053880(void *p);                       /* free */
void *sub_00053820(int pool, int size, void *a, int b);
void  sub_0005EEA0(int i, void *data);

/* 0x1A00C0: load the 25 shock data files into one buffer (each padded to 64 bytes),
   replacing the previous buffer, and register each part. */
void m1_ShkLoadAll1A00C0(void) {
    char path[0x50];
    uint8_t *dst;
    int i, n, total = 0;
    for (i = 0; i < 25; i++) {
        sub_0007E0A0(path, m1_fmtShkd27B390, i);
        total += (sub_000374C0(path) + 0x3F) & ~0x3F;
    }
    if (m1_shkBuf40431C)
        sub_00053880(m1_shkBuf40431C);
    dst = m1_shkBuf40431C = sub_00053820(4, total, 0, 0);
    for (i = 0; i < 25; i++) {
        uint8_t *src;
        sub_0007E0A0(path, m1_fmtShkd27B390, i);
        n = (sub_000374C0(path) + 0x3F) & ~0x3F;
        src = sub_00037550(path, 0);
        {
            volatile unsigned c = n;   /* keeps the byte tail copy cl would drop (n is 64-aligned) */
            __movsd((unsigned long *)dst, (unsigned long *)src, c >> 2);
            __movsb(dst + (c >> 2) * 4, src + (c >> 2) * 4, c & 3);
        }
        sub_0005EEA0(i, dst);
        dst += n;
    }
}
