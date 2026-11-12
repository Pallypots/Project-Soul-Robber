/* Area m1, file 29: save / restore / clear a bone value set. Names inferred. */
#include <stdint.h>

typedef struct M1Bone180 {
    uint8_t unk000[0x17C];
    int32_t v17C;              /* +0x17C */
} M1Bone180;
typedef struct M1Skel {
    uint8_t    unk00[0xC4];
    M1Bone180 *bonesC4;        /* +0xC4, stride 0x180 */
} M1Skel;
typedef struct M1Mdl20 {
    uint8_t unk00[0x20];
    M1Skel *skel20;            /* +0x20 */
} M1Mdl20;
typedef struct M1BoneRef14 {
    int32_t bone00;            /* +0x00 */
    uint8_t unk04[0x14 - 4];
} M1BoneRef14;
typedef struct M1BoneSet {
    uint8_t      unk00[4];
    int32_t      count04;      /* +0x04 */
    uint8_t      unk08[0x28 - 8];
    M1BoneRef14 *refs28;       /* +0x28 */
    uint8_t      unk2C[4];
    int32_t      saved30[1];   /* +0x30, count04 entries */
    uint8_t      unk34[0x50 - 0x34];
    M1Mdl20     *mdl50;        /* +0x50 */
} M1BoneSet;

/* 0x000CDB00: saves the value of every referenced bone. regargs: s=EDI */
void m1_BonesSaveCDB00(M1BoneSet *s)
{
    M1Skel *k = s->mdl50->skel20;
    M1BoneRef14 *r = s->refs28;
    int i;
    for (i = 0; i < s->count04; i++, r++)
        s->saved30[i] = k->bonesC4[r->bone00].v17C;
}

/* 0x000CDB50: restores the saved values. regargs: s=EDI */
void m1_BonesRestoreCDB50(M1BoneSet *s)
{
    M1Skel *k = s->mdl50->skel20;
    M1BoneRef14 *r = s->refs28;
    int i;
    for (i = 0; i < s->count04; i++, r++)
        k->bonesC4[r->bone00].v17C = s->saved30[i];
}

/* 0x000CDBA0: clears the value of every referenced bone. regargs: s=ESI */
void m1_BonesClearCDBA0(M1BoneSet *s)
{
    M1Skel *k = s->mdl50->skel20;
    M1BoneRef14 *r = s->refs28;
    int i;
    for (i = 0; i < s->count04; i++, r++)
        k->bonesC4[r->bone00].v17C = 0;
}
