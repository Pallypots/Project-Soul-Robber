/* Area m1, file 17: sweeps over the 32-entry 0x260 table at 0x004242C0. Names inferred. */
#include <stdint.h>

typedef struct M1Ent260W {
    uint32_t flags00;          /* +0x000 bit 0 = in use, 0x20000000 = keep, 0x40000000 = paused */
    void    *owner004;         /* +0x004 */
    uint8_t  unk008[0x18 - 8];
    int32_t  kind018;          /* +0x018 handler index */
    uint8_t  unk01C[0x120 - 0x1C];
    void    *obj120;           /* +0x120 */
    uint8_t  unk124[0x154 - 0x124];
    int32_t  snd154[2];        /* +0x154 effect/sound handles, -1 = none */
    uint8_t  unk15C[0x260 - 0x15C];
} M1Ent260W;
extern M1Ent260W m1_ents4242C0[32];  /* 0x004242C0 */
void sub_0001D700(void *o);
void sub_0001D610(void *o);

/* 0x000A46D0: resume == 0 pauses every in-use entry not marked keep;
 * otherwise resumes every paused entry. */
void m1_PauseAllA46D0(int resume)
{
    int i;
    for (i = 0; i < 32; i++) {
        if (m1_ents4242C0[i].flags00 & 1) {
            if (resume == 0) {
                if (!(m1_ents4242C0[i].flags00 & 0x20000000)) {
                    sub_0001D700(m1_ents4242C0[i].obj120);
                    m1_ents4242C0[i].flags00 |= 0x40000000;
                }
            } else if (m1_ents4242C0[i].flags00 & 0x40000000) {
                sub_0001D610(m1_ents4242C0[i].obj120);
                m1_ents4242C0[i].flags00 &= ~0x40000000;
            }
        }
    }
}

typedef struct M1ObjC {
    uint8_t  unk00[0xC];
    uint32_t flags0C;          /* +0x0C */
} M1ObjC;
typedef struct M1VoiceDC {
    uint8_t  flags00;          /* +0x00 bit 0 = playing */
    uint8_t  unk01[0x1C - 1];
    int32_t  kind01C;          /* +0x1C */
    uint8_t  unk020[0xD4 - 0x20];
    void    *res0D4;           /* +0xD4 */
    M1ObjC  *obj0D8;           /* +0xD8 */
} M1VoiceDC;
extern M1VoiceDC m1_voices420F20[56];  /* 0x00420F20 */
void sub_0001EB80(M1ObjC *o);
void sub_00033A40(void *h);
void sub_000A7700(M1VoiceDC *v);

/* 0x000A8B80: stops every playing voice (clears its object's bit 0, frees its
 * resource), then resets every voice; playing voices get the reset twice. */
void m1_StopVoicesA8B80(void)
{
    int i;
    for (i = 0; i < 56; i++) {
        if (m1_voices420F20[i].flags00 & 1) {
            m1_voices420F20[i].obj0D8->flags0C &= ~1u;
            sub_0001EB80(m1_voices420F20[i].obj0D8);
            if (m1_voices420F20[i].res0D4 != 0)
                sub_00033A40(m1_voices420F20[i].res0D4);
            sub_000A7700(&m1_voices420F20[i]);
        }
        sub_000A7700(&m1_voices420F20[i]);
    }
}


/* 0x000A8150: stops playing voices of kinds 2, 8, 12 and 15. */
void m1_StopKindsA8150(void)
{
    int i;
    for (i = 0; i < 56; i++) {
        if (m1_voices420F20[i].flags00 & 1) {
            int k = m1_voices420F20[i].kind01C;
            if (k == 2 || k == 8 || k == 12 || k == 15) {
                m1_voices420F20[i].obj0D8->flags0C &= ~1u;
                sub_0001EB80(m1_voices420F20[i].obj0D8);
                if (m1_voices420F20[i].res0D4 != 0)
                    sub_00033A40(m1_voices420F20[i].res0D4);
                sub_000A7700(&m1_voices420F20[i]);
            }
        }
    }
}

#define M1_OWNFLAG(e) if (((e).flags00 & 1) && (e).owner004 == owner) (e).flags00 |= bits
/* 0x000A4970: ORs bits into the flags of every in-use entry owned by owner. */
void m1_FlagOwnedA4970(void *owner, uint32_t bits)
{
    int i;
    for (i = 0; i < 32; i += 4) {   /* the original is unrolled by four */
        M1_OWNFLAG(m1_ents4242C0[i]);
        M1_OWNFLAG(m1_ents4242C0[i + 1]);
        M1_OWNFLAG(m1_ents4242C0[i + 2]);
        M1_OWNFLAG(m1_ents4242C0[i + 3]);
    }
}

typedef int (*M1EntFn)(M1Ent260W *e, void *arg);
extern M1EntFn m1_entFns2E2758[];  /* 0x002E2758 per-kind handlers */

/* 0x000A0FD0: counts in-use, non-paused entries whose kind handler returns nonzero. */
int m1_CountHandledA0FD0(void *arg)
{
    int n = 0;
    int i;
    for (i = 0; i < 32; i++) {
        if ((m1_ents4242C0[i].flags00 & 1) && !(m1_ents4242C0[i].flags00 & 0x40) &&
            m1_entFns2E2758[m1_ents4242C0[i].kind018](&m1_ents4242C0[i], arg))
            n++;
    }
    return n;
}

void sub_00048250(int h);

/* 0x000A4670: stops both sounds of every in-use entry owned by owner. */
void m1_StopOwnedSoundsA4670(void *owner)
{
    int i, j;
    for (i = 0; i < 32; i++) {
        if ((m1_ents4242C0[i].flags00 & 1) && m1_ents4242C0[i].owner004 == owner) {
            for (j = 0; j < 2; j++) {
                if (m1_ents4242C0[i].snd154[j] != -1) {
                    sub_00048250(m1_ents4242C0[i].snd154[j]);
                    m1_ents4242C0[i].snd154[j] = -1;
                }
            }
        }
    }
}

int sub_00049700(int id, int r, int g, int b, const void *pos, int a, float size, int c);

/* 0x000A36E0: if effect slot j of entry i is free, spawns effect id (grey 0x80 colour)
 * at the entry's object (position at +0x60) and stores the handle. */
void m1_StartSlotEffectA36E0(int i, int id, int j, int a, float size, int c)
{
    M1Ent260W *e = &m1_ents4242C0[i];
    if (e->snd154[j] != -1)
        return;
    e->snd154[j] = sub_00049700(id, 0x80, 0x80, 0x80, (uint8_t *)e->obj120 + 0x60, a, size, c);
}
