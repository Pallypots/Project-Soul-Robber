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

typedef struct M1EntSlot { uint8_t raw[0x260]; } M1EntSlot;
extern M1EntSlot m1_entsRaw4242C0[32];  /* 0x004242C0 */
void sub_000A3810R(M1EntSlot *e);      /* 0x000A3810 regargs: e=ESI */
extern int32_t m1_handles423FEC[16];    /* 0x00423FEC */
extern int32_t m1_count423FE8;          /* 0x00423FE8 */

/* 0x000A4B80: forgets both shared resources, resets all 32 entries (0xA3810),
 * clears the 16 handles to -1 and the count to 0. */
void m1_ResetAllA4B80(void)
{
    int i;
    m1_resA3ED534 = 0;
    m1_idA3ED52C = 0;
    m1_resB3ED538 = 0;
    m1_idB3ED530 = 0;
    for (i = 0; i < 32; i++)
        sub_000A3810R(&m1_entsRaw4242C0[i]);
    for (i = 0; i < 16; i++)
        m1_handles423FEC[i] = -1;
    m1_count423FE8 = 0;
}

typedef struct M1Key0C {
    int32_t a00;               /* +0x00, -1 ends the table */
    int32_t b04;               /* +0x04 */
    int32_t val08;             /* +0x08 */
} M1Key0C;
extern M1Key0C m1_keys2E2D50[];        /* 0x002E2D50 */
extern int32_t m1_keyVal423FE0;        /* 0x00423FE0 */
extern int32_t m1_keyA423FE4;          /* 0x00423FE4 */
void sub_000DFD40(int *a, int *b);

/* 0x000A3780: looks up the current (a, b) pair from 0xDFD40 in the key table and
 * stores its key and value; 0 when a value was found, else -1. */
int m1_LookupKeyA3780(void)
{
    int b, a;
    int i;
    m1_keyVal423FE0 = 0;
    m1_keyA423FE4 = -1;
    sub_000DFD40(&a, &b);
    for (i = 0; m1_keys2E2D50[i].a00 != -1; i++) {
        if (m1_keys2E2D50[i].a00 == a && m1_keys2E2D50[i].b04 == b) {
            m1_keyA423FE4 = m1_keys2E2D50[i].a00;
            m1_keyVal423FE0 = m1_keys2E2D50[i].val08;
            break;
        }
    }
    if (m1_keyVal423FE0 == 0)
        return -1;
    return 0;
}
