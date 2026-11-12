/* Area m1, file 35: one-time scene rig setup. Names inferred. */
#include <stdint.h>

typedef struct M1Slot28 {
    void   *obj00;             /* +0x00 */
    uint8_t unk04[0x28 - 4];
} M1Slot28;
typedef struct M1RigMgr {
    uint8_t  unk000[0x864];
    void    *task864;          /* +0x864, 0 = not set up */
    void    *root868;          /* +0x868 */
    M1Slot28 slots86C[5];      /* +0x86C */
} M1RigMgr;
extern int32_t m1_flag3F1B20;            /* 0x003F1B20 */
extern const char m1_rigPath2777BC[];    /* 0x002777BC */
void *r1_StateNew(int i);
void  r1b_RecAddChild(void *root, void *child);
void  sub_0001DA10(void *root);
int   sub_00022630(void *o, const void *path);
void *sub_0001F6C0(int a, int b, int c, int d, void *e);

/* 0x000E1E00: builds the rig once (root with children 0 and 1, loaded from the
 * path at 0x2777BC), starts task 5 on it and clears the five slots. */
void m1_SetupRigE1E00(M1RigMgr *m)
{
    void *root;
    int i;
    if (m->task864 != 0)
        return;
    m1_flag3F1B20 = 0;
    root = r1_StateNew(0);
    if (root == 0)
        for (;;) ;
    r1b_RecAddChild(root, r1_StateNew(0));
    r1b_RecAddChild(root, r1_StateNew(1));
    sub_0001DA10(root);
    sub_00022630(root, m1_rigPath2777BC);
    m->root868 = root;
    m->task864 = sub_0001F6C0(5, 0, 0, 0, root);
    for (i = 0; i < 5; i++)
        m->slots86C[i].obj00 = 0;
}

typedef struct M1Pair8C {
    uint8_t a00[0x10];         /* +0x00 */
    uint8_t b10[0x8C - 0x10];  /* +0x10 */
} M1Pair8C;
extern M1Pair8C m1_pairs3FEB18[19];   /* 0x003FEB18 */
extern int32_t m1_g3FF57C, m1_g3FF584, m1_g414440, m1_g414444, m1_g3FF580;
void sub_0001D8B0(void *o, int kind);
void sub_0018DFC0(void); void sub_0018B620(void); void sub_00196750(void);
void sub_0018A250(void); void sub_001983E0(void); void sub_00196A10(void);
void sub_001905B0(void); void sub_00193990(void); void sub_00191B00(void);
void sub_00191B30(void); void sub_00191C70(void); void sub_0018D3A0(void);
void sub_0018C3E0(void); void sub_00193DF0(void);

/* 0x00189960: stage reset: clears four globals, initialises both halves of the
 * 19 pair records (kinds 7 and 0xD), runs the 14 subsystem resets, clears 0x3FF580. */
void m1_StageReset189960(void)
{
    int i;
    m1_g3FF57C = 0;
    m1_g3FF584 = 0;
    m1_g414440 = 0;
    m1_g414444 = 0;
    for (i = 0; i < 19; i++) {
        sub_0001D8B0(m1_pairs3FEB18[i].a00, 7);
        sub_0001D8B0(m1_pairs3FEB18[i].b10, 0xD);
    }
    sub_0018DFC0(); sub_0018B620(); sub_00196750(); sub_0018A250();
    sub_001983E0(); sub_00196A10(); sub_001905B0(); sub_00193990();
    sub_00191B00(); sub_00191B30(); sub_00191C70(); sub_0018D3A0();
    sub_0018C3E0(); sub_00193DF0();
    m1_g3FF580 = 0;
}

void sub_00189510(int h);
void sub_0001F300(void *o);
void sub_00020170(void *task);
void sub_0001E550(void *root);
void sub_00053880(void *p);

/* 0x000E1E90: tears down what 0xE1E00 built: releases the pending handle, the five
 * slot objects, the task and the rig root. */
void m1_FreeRigE1E90(M1RigMgr *m)
{
    int i;
    if (m1_flag3F1B20 != 0)
        sub_00189510(m1_flag3F1B20);
    m1_flag3F1B20 = 0;
    for (i = 0; i < 5; i++) {
        if (m->slots86C[i].obj00 != 0)
            sub_0001F300(m->slots86C[i].obj00);
        m->slots86C[i].obj00 = 0;
    }
    if (m->task864 != 0)
        sub_00020170(m->task864);
    if (m->root868 != 0) {
        sub_0001E550(m->root868);
        sub_0001F300(m->root868);
        sub_00053880(m->root868);
    }
    m->root868 = 0;
    m->task864 = 0;
}
