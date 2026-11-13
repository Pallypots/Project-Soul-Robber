/* Area m1, file 42: hold / release a model's bone entry. Names inferred. */
#include <stdint.h>

typedef struct M1BoneEnt {
    uint32_t flags00;          /* +0x00 bit 1 = held */
    uint8_t  unk04[0xC];
    int32_t  f10;              /* +0x10 */
    uint8_t  unk14[8];
    float    f1C;              /* +0x1C */
    uint8_t  unk20[8];
    void    *refs28;           /* +0x28 */
    uint8_t  unk2C[0x54 - 0x2C];
} M1BoneEnt;
extern M1BoneEnt m1_boneEnts41C7C0[16];   /* 0x0041C7C0 */
int  m1_FindEntryCDAB0(void *m, int key);   /* regargs: m=EAX key=ESI */
void m1_BonesRestoreCDB50(M1BoneEnt *e);    /* regargs: e=EDI */
void m1_BonesClearCDBA0(M1BoneEnt *e);      /* regargs: e=ESI */
void sub_000CDBE0(M1BoneEnt *e, void *refs);/* regargs: refs=EAX */
void m1_PartsLookCE4C0(void *m);            /* regargs: m=ESI */

#define M1_BONE_HOLD(name, key) \
void name(void *m) \
{ \
    int i = m1_FindEntryCDAB0(m, key); \
    if (i >= 0) { \
        M1BoneEnt *e = &m1_boneEnts41C7C0[i]; \
        e->flags00 |= 2; \
        m1_BonesRestoreCDB50(e); \
        e->f10 = 0; \
        e->f1C = 0.0f; \
        sub_000CDBE0(e, e->refs28); \
    } \
    m1_PartsLookCE4C0(m); \
}
#define M1_BONE_RELEASE(name, key) \
void name(void *m) \
{ \
    int i = m1_FindEntryCDAB0(m, key); \
    if (i >= 0) { \
        M1BoneEnt *e = &m1_boneEnts41C7C0[i]; \
        e->flags00 &= ~2u; \
        m1_BonesClearCDBA0(e); \
        e->f10 = 0; \
        e->f1C = 0.0f; \
        sub_000CDBE0(e, e->refs28); \
    } \
    m1_PartsLookCE4C0(m); \
}
/* 0x000CED00 / 0x000CEDA0: hold the model's key-0 / key-1 bone entry (restore saved
 * bone values) and refresh its look. 0x000CED50 / 0x000CEDF0: release (clear bones). */
M1_BONE_HOLD(m1_BoneHold0CED00, 0)
M1_BONE_RELEASE(m1_BoneRelease0CED50, 0)
M1_BONE_HOLD(m1_BoneHold1CEDA0, 1)
M1_BONE_RELEASE(m1_BoneRelease1CEDF0, 1)

/* 0x000CEC90: holds (hold != 0) or releases the bone entry for (m, key); returns
 * the entry index or -1. regargs: m=EAX key=ECX */
int m1_BoneSetCEC90(void *m, int key, int hold)
{
    int i = m1_FindEntryCDAB0(m, key);
    M1BoneEnt *e;
    if (i < 0)
        return -1;
    e = &m1_boneEnts41C7C0[i];
    if (hold == 0) {
        e->flags00 &= ~2u;
        m1_BonesClearCDBA0(e);
    } else {
        e->flags00 |= 2;
        m1_BonesRestoreCDB50(e);
    }
    e->f10 = 0;
    e->f1C = 0.0f;
    sub_000CDBE0(e, e->refs28);
    return i;
}

typedef struct M1BoneEntFull {
    int32_t  f00, f04, f08, f0C, f10;  /* +0x00 */
    float    f14, f18;         /* +0x14, +0x18: 1.0 */
    float    f1C, f20, f24;    /* +0x1C..+0x24: 0.0 */
    int32_t  f28, f2C;         /* +0x28 */
    int32_t  f30[8];           /* +0x30 */
    int32_t  f50;              /* +0x50 */
} M1BoneEntFull;
extern M1BoneEntFull m1_boneEntsF41C7C0[16];  /* 0x0041C7C0 */

/* 0x000CE880: clears all 16 bone entries (scales 1.0, everything else 0). */
void m1_BoneEntsInitCE880(void)
{
    int i, k;
    for (i = 0; i < 16; i++) {
        M1BoneEntFull *e = &m1_boneEntsF41C7C0[i];
        e->f00 = 0;
        e->f04 = 0;
        e->f08 = 0;
        e->f0C = 0;
        e->f10 = 0;
        e->f14 = 1.0f;
        e->f18 = 1.0f;
        e->f1C = 0.0f;
        e->f20 = 0.0f;
        e->f24 = 0.0f;
        e->f28 = 0;
        e->f2C = 0;
        e->f50 = 0;
        for (k = 0; k < 8; k++)
            e->f30[k] = 0;
    }
}
