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
