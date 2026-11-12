/* Area m1, file 30: lazy resource setup and hit reactions. Names inferred. */
#include <stdint.h>

typedef struct M1Res8 {
    uint8_t unk00[8];
    int32_t id08;              /* +0x08 */
} M1Res8;
typedef struct M1Scene1E8 {
    uint8_t unk000[0x1E8];
    void   *list1E8;           /* +0x1E8 */
} M1Scene1E8;
extern M1Scene1E8 *m1_scene42C8E4S;  /* 0x0042C8E4 */
extern int32_t m1_resId3F6100;       /* 0x003F6100, 0 = not set up */
extern int32_t m1_resA3F6104;        /* 0x003F6104 */
extern void   *m1_resB3F60F4;        /* 0x003F60F4 */
extern M1Res8 *m1_res3F60FC;         /* 0x003F60FC */
M1Res8 *sub_0001F930(int a, void *parent);
void    sub_0001CFF0(void *list, M1Res8 *r, int layer);

/* 0x000F3630: creates the resource once and adds it to the scene list on layer 3. */
void m1_EnsureResF3630(void)
{
    M1Res8 *r;
    if (m1_resId3F6100 != 0)
        return;
    r = sub_0001F930(m1_resA3F6104, m1_resB3F60F4);
    m1_res3F60FC = r;
    m1_resId3F6100 = r->id08;
    sub_0001CFF0(m1_scene42C8E4S->list1E8, r, 3);
}


void    sub_000A56C0(void);
void    sub_00053710(int heap);
void    sub_00053740(void);
void    sub_000A3780(void);
M1Res8 *sub_0001F210(int a, int b);
void    sub_0001DA40(M1Res8 *a);
void    sub_000A49F0(int a);           /* regargs: a=ECX */
extern M1Res8 *m1_resA3ED534;          /* 0x003ED534 */
extern int32_t m1_idA3ED52C;           /* 0x003ED52C */
extern M1Res8 *m1_resB3ED538;          /* 0x003ED538 */
extern int32_t m1_idB3ED530;           /* 0x003ED530 */

/* 0x000A5730: under heap 3, resets (0xA56C0, 0xA3780), creates the shared resource
 * once, runs 0xA49F0 for a, then creates the second resource and adds it to the
 * scene list on layer 0xC. */
void m1_SetupA5730(int a)
{
    M1Res8 *r;
    sub_000A56C0();
    sub_00053710(3);
    sub_000A3780();
    if (m1_resA3ED534 == 0) {
        r = sub_0001F210(2, 1);
        m1_resA3ED534 = r;
        m1_idA3ED52C = r->id08;
        sub_0001DA40(r);
    }
    sub_000A49F0(a);
    r = sub_0001F930(2, m1_resA3ED534);
    m1_resB3ED538 = r;
    m1_idB3ED530 = r->id08;
    sub_0001CFF0(m1_scene42C8E4S->list1E8, r, 0xC);
    sub_00053740();
}
