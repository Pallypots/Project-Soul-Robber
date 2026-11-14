/* Area m1, file 164: yes/no prompt input (revisited). Names inferred. */
#include <stdint.h>

typedef struct M1Sv164 { uint8_t unk00[0x1204A0]; int32_t sel; } M1Sv164;
extern int32_t m1_ynDone3E3988;
extern int32_t m1_ynSel3E3964;
extern M1Sv164 *m1_save3E3934;
extern uint32_t *m1_padMasks2C4AE8;
uint32_t m1_PadHit04ECE0(int pad);
uint32_t sub_0004ED20(int pad);
int sub_00048AF0(int k);

/* 0x54D50: yes/no prompt: left/right moves the cursor, confirm returns 1 (yes) or 2 (no), cancel returns 2. */
int m1_YesNo054D50(void) {
    uint32_t b; int ret = 0; int volatile r;
    if (m1_ynDone3E3988 == 1) return 0;
    b = m1_PadHit04ECE0(0) | sub_0004ED20(0);
    if (b & 0x8000) {
        if (m1_ynSel3E3964 <= 0) goto out;
        m1_ynSel3E3964 = 0;
        goto snd;
    }
    if (b & 0x2000) {
        if (m1_ynSel3E3964 >= 1) goto out;
        m1_ynSel3E3964 = 1;
        goto snd;
    }
    if (m1_padMasks2C4AE8[0] & b) {
        if (m1_ynSel3E3964 == 0) { r = sub_00048AF0(1); ret = 1; m1_ynDone3E3988 = 1; goto out; }
        ret = 2;
        r = sub_00048AF0(2);
        m1_ynDone3E3988 = 1;
        goto out;
    }
    if (!(m1_padMasks2C4AE8[1] & b)) goto out;
    ret = 2;
    m1_ynDone3E3988 = 1;
snd:
    r = sub_00048AF0(ret);
out:
    m1_save3E3934->sel = m1_ynSel3E3964;
    return ret;
}
