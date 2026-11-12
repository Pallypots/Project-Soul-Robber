/* Area m1, file 37: save screen shutdown. Names inferred. */
#include <stdint.h>

extern int32_t a5b_g3E3944;              /* 0x003E3944 mode */
extern int32_t m1_handles3E3914[7];      /* 0x003E3914 */
extern int32_t m1_handle3E3948;          /* 0x003E3948 */
extern int32_t m1_g3E3940;               /* 0x003E3940 */
extern uint8_t *m1_save3E3934;           /* 0x003E3934 */
void a1a_GroupFreeAll(void *g);
void sub_001B9FC0(int h);
void sub_0004F5D0(int id);
void sub_00053880(void *p);
void sub_001A1B90(void);

/* 0x000540C0: frees the group, stops the seven handles and the extra handle (unless
 * in mode 2), releases resources 0xB8, 0xBA, 0xA7 and the save buffer, then 0x1A1B90. */
void m1_SaveShutdown540C0(void *group)
{
    int i;
    a1a_GroupFreeAll(group);
    if (a5b_g3E3944 != 2) {
        for (i = 0; i < 7; i++) {
            if (m1_handles3E3914[i] != -1) {
                sub_001B9FC0(m1_handles3E3914[i]);
                m1_handles3E3914[i] = -1;
            }
        }
        if (m1_handle3E3948 != -1) {
            sub_001B9FC0(m1_handle3E3948);
            m1_handle3E3948 = -1;
        }
    }
    sub_0004F5D0(0xB8);
    sub_0004F5D0(0xBA);
    sub_0004F5D0(0xA7);
    m1_g3E3940 = 0;
    sub_00053880(m1_save3E3934);
    sub_001A1B90();
}
