/* Area m1, file 35: one-time scene rig setup. Names inferred. */
#include <stdint.h>

typedef struct M1Slot28 {
    int32_t f00;               /* +0x00 */
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
        m->slots86C[i].f00 = 0;
}
