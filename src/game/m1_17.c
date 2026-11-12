/* Area m1, file 17: sweeps over the 32-entry 0x260 table at 0x004242C0. Names inferred. */
#include <stdint.h>

typedef struct M1Ent260W {
    uint32_t flags00;          /* +0x000 bit 0 = in use, 0x20000000 = keep, 0x40000000 = paused */
    void    *owner004;         /* +0x004 */
    uint8_t  unk008[0x120 - 8];
    void    *obj120;           /* +0x120 */
    uint8_t  unk124[0x260 - 0x124];
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
