#ifndef R4J_H
#define R4J_H
#include "oogie.h"
#include "shared_decls.h"
#include "r4f.h"
#include "r4c.h"
#include "r4i.h"
/* Area r4j: larger game functions in 0x00190000..0x001BC6D0 (tenth pass).
   All names inferred. Register mappings are in the comments and in
   config/function_states_r4j.csv. */

/* Zero a block (the original inlines this as rep stosd). The intrinsic is
   used only for the 32-bit x86 comparison build; other targets use memset. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <intrin.h>
#define R4J_ZERO(p, n) __stosd((unsigned long *)(p), 0, (n) / 4)
#else
#include <string.h>
#define R4J_ZERO(p, n) memset((p), 0, (n))
/* ------------------------------------------------------------ scene node update (0x001B2270) */
typedef struct R4jHook {      /* hook list entry (R4Hook in r4.h) */
    struct R4jHook *next;     /* +0x00 */
    void (*fn)(struct R4jSNode *n, struct R4jHook *h); /* +0x04 */
} R4jHook;
typedef void (*R4jSNodeFn)(struct R4jSNode *n);
typedef struct R4jSNode {     /* scene node (R4Node in r4.h) */
    float    local00[16];     /* +0x00 */
    float    world40[16];     /* +0x40 */
    struct R4jSNode *parent80; /* +0x80 */
    struct R4jSNode *next84;  /* +0x84 next sibling */
    struct R4jSNode *child88; /* +0x88 first child */
    int32_t  type8C;          /* +0x8C */
    uint32_t flags90;         /* +0x90 bit 0 done, 4 no sort, 5 hidden, 6 keep world, 8 front */
    float    depth94;         /* +0x94 sort depth */
    R4jSNodeFn *passFns98;    /* +0x98 per-pass callbacks */
    uint8_t  unk9C[4];
    struct R4jSNode *prevA0;  /* +0xA0 depth bucket chain */
    struct R4jSNode *nextA4;  /* +0xA4 */
    R4jHook *hooksA8;         /* +0xA8 */
    R4jHook *hooksAC;         /* +0xAC */
} R4jSNode;
extern int32_t   r4j_typeCount412EE0[20];                    /* 0x00412EE0 nodes seen per type */
extern R4jSNode *r4j_bucketTail412F80[0x33];                 /* 0x00412F80 (r4_g412F80) */
extern R4jSNode *r4j_bucketHead413060[0x33];                 /* 0x00413060 (r4_g413060) */
extern int32_t   r4j_pass40F1BC;                             /* 0x0040F1BC (r4_g40F1BC) */
extern uint32_t  r4j_doneMask40F1C0;                         /* 0x0040F1C0 (r4_g40F1C0) AND of all node flags */
extern float     r4j_depthMax377F48;                         /* 0x00377F48 (r4_g377F48) */
extern float     r4j_depthMin40F1C4;                         /* 0x0040F1C4 (r4_g40F1C4) */
extern uint8_t   r4j_renderFlags412F30;                      /* 0x00412F30 */
void r4_HookRunA8(R4jSNode *n);                               /* 0x001B2240 */
R4jSNode *sub_001B2270(R4jSNode *n);                          /* 0x001B2270 */

/* ------------------------------------------------------------ matrix to quaternion (0x001AF0A0) */
extern const int32_t r4j_next367E58[3];                       /* 0x00367E58 {1, 2, 0} next axis */
void r4j_MatToQuat(const float *m, float *q);                 /* 0x001AF0A0 regargs: m=ESI */

/* ------------------------------------------------------------ animation player update (0x001AFD80) */
typedef struct R4jAnimPart {  /* 0x130-byte animated part */
    uint8_t  unk00[0xB8];
    uint32_t flagsB8;         /* +0xB8 bit 0 loop, bit 2 loop next */
    void    *curBC;           /* +0xBC current track (0 = idle) */
    int32_t  iC0, iC4, iC8, iCC; /* +0xC0 */
    float    fD0;             /* +0xD0 */
    void    *nextD4;          /* +0xD4 queued track */
    int32_t  iD8, iDC, iE0, iE4; /* +0xD8 queued values */
    float    fE8;             /* +0xE8 */
    uint8_t  unkEC[0x130 - 0xEC];
} R4jAnimPart;
typedef struct R4jAnimPlayer {
    uint8_t  unk00[0xB0];
    int32_t  count;           /* +0xB0 parts */
    R4jAnimPart *parts;       /* +0xB4 */
    uint32_t flagsB8;         /* +0xB8 bit 1 frozen */
    uint32_t modeBC;          /* +0xBC bit 0 queued, bit 1 blending, 0x10/0x20 kinds */
    void    *animC0;          /* +0xC0 */
    float    speedC4;         /* +0xC4 */
    void    *nextC8;          /* +0xC8 */
    uint32_t waitCC;          /* +0xCC */
    uint32_t tickD0;          /* +0xD0 */
    void   (*onEndD4)(struct R4jAnimPlayer *p); /* +0xD4 */
    float    timeD8;          /* +0xD8 */
    float    lenDC;           /* +0xDC */
} R4jAnimPlayer;
void r4j_AnimPlayerTick(R4jAnimPlayer *p);                    /* 0x001AFD80 */

/* ------------------------------------------------------------ look-at transform (0x001AE210) */
typedef struct R4jVec4 { float v[4]; } R4jVec4;
void sub_001AE060(void *xf, const float *m);                  /* 0x001AE060 (r4g.h) */
void r4j_LookAt(void *xf, const float *pos, const float *dir, const float *up); /* 0x001AE210 */

/* ------------------------------------------------------------ title fade job (0x0019D120) */
extern int32_t a30_g41316C, a30_g413170;                      /* 0x0041316C, 0x00413170 */
void sub_00033250(void);                                      /* 0x00033250 */
void sub_001A5380(int v);                                     /* 0x001A5380 stores v to 0x0040B0EC */
void r4j_FadeJob(void);                                       /* 0x0019D120 */

#endif

/* ------------------------------------------------------------ world model draw (0x001A2EB0) */
extern int32_t aac_g1E243C;                                   /* 0x001E243C render-state shadow */
extern const char r4j_strDrawWorldModel27B5D4[];              /* 0x0027B5D4 "DrawWorldModel" */
typedef struct R4jVtxCursor {  /* vertex block cursor; only cur is read by 0x001A2130 */
    R4eVtxHdr *cur;
    int32_t   *flags;           /* &group->flags04 */
} R4jVtxCursor;
int r4j_DrawWorldModel(R4fDrawObj *o);                        /* 0x001A2EB0 */

/* ------------------------------------------------------------ blend presets (0x001A69C0) */
extern int32_t aac_g1E2440;                                   /* 0x001E2440 render-state shadow */
void r4j_BlendByFormat(uint64_t fmt);                         /* 0x001A69C0 (sub_001A69C0 in r4f.h as two halves) */

/* ------------------------------------------------------------ texture bind (0x001A6820) */
typedef struct R4jTexHdr {    /* texture header */
    uint8_t  unk00[0x0C];
    int32_t  h0C;             /* +0x0C height in texels (v divisor) */
    int32_t  w10;             /* +0x10 width in texels (u divisor) */
} R4jTexHdr;
typedef struct R4jTexBind {   /* texture entry as read by 0x001A6820 (R4bTexEnt) */
    uint8_t  unk00[0x14];
    R4jTexHdr *hdr14;         /* +0x14 texture header (0x001A6820 reads and discards it) */
    uint8_t  unk18[0x48 - 0x18];
    uint64_t wrap48;          /* +0x48 bits 0-1 U address mode, bits 2-3 V */
    uint8_t  unk50[4];
    void    *tex54;           /* +0x54 device texture */
} R4jTexBind;
extern R4jTexBind *r4j_curTex40B0E8;                          /* 0x0040B0E8 last bound entry (r4d_g40B0E8) */
extern int32_t r4j_tss1E2164, r4j_tss1E2188, r4j_tss1E2180, r4j_tss1E218C, r4j_rs1E2438;
extern float   r4j_tss1E2168;                                 /* 0x001E2168 mip bias */
extern int32_t aac_g1E2444;
void r4j_TexBind(R4jTexBind *e);                              /* 0x001A6820 */

/* ------------------------------------------------------------ small block heap (0x001BB440) */
typedef struct R4jBlk {       /* 0x10-byte block record (R4Blk in r4.h) */
    struct R4jBlk *prev;      /* +0x00 */
    struct R4jBlk *next;      /* +0x04 */
    uint8_t  used;            /* +0x08 record in use */
    uint8_t  unk9;
    uint8_t  lock0A;          /* +0x0A owner bits */
    uint8_t  lock0B;          /* +0x0B reserved bits */
    uint16_t addr;            /* +0x0C */
    uint16_t size;            /* +0x0E */
} R4jBlk;
typedef struct R4jBlkHeap { uint32_t unk0; uint32_t count; R4jBlk *first; } R4jBlkHeap;
extern R4jBlkHeap *r4j_blkHeap40F75C;                         /* 0x0040F75C (r4_g40F75C) */
extern R4jBlk     *r4j_blks40F760;                            /* 0x0040F760 (r4_g40F760) record array */
R4jBlk *r4_HeapFindBlock(uint16_t addr);                      /* 0x001BB120 regargs: addr=EDX */
int sub_001BB440(uint16_t size, uint16_t addr, uint8_t code, int release); /* 0x001BB440 regargs: size=EAX addr=EDX */

/* ------------------------------------------------------------ bone tree (0x001BBA20) */
typedef struct R4jBoneDef {   /* 0x50-byte bone definition */
    uint16_t unk00;
    uint16_t child02;         /* +0x02 first child, 0xFFFF = none */
    uint16_t sib04;           /* +0x04 next sibling, 0xFFFF = none */
    uint16_t unk06;
    int32_t  off08;           /* +0x08 data offset from the file base */
    uint8_t  unk0C[4];
    float    mat10[16];       /* +0x10 bind matrix */
} R4jBoneDef;
typedef struct R4jBoneHdr {   /* 16-byte per-bone header; entry 0 also holds the definitions */
    int32_t     f00;          /* +0x00 */
    R4jBoneDef *defs04;       /* +0x04 */
    uint8_t     unk08[8];
} R4jBoneHdr;
typedef struct R4jBoneFile { uint8_t *base00; R4jBoneHdr *hdrs04; } R4jBoneFile;
typedef struct R4jBoneOwner { /* model owning the bone nodes */
    uint8_t      unk00[0xB4];
    int32_t      iB4, iB8;    /* +0xB4 */
    R4jBoneFile *fileBC;      /* +0xBC */
    uint8_t      unkC0[0xC8 - 0xC0];
    float        colC8[4];    /* +0xC8 */
    int32_t      iD8, iDC;    /* +0xD8 */
} R4jBoneOwner;
typedef struct R4jBone {      /* 0x100-byte bone node */
    float        mat00[16];   /* +0x00 */
    uint8_t      unk40[0x80 - 0x40];
    struct R4jBone *parent80; /* +0x80 */
    struct R4jBone *sib84;    /* +0x84 */
    struct R4jBone *child88;  /* +0x88 */
    uint8_t      unk8C[0xB0 - 0x8C];
    int32_t      iB0;         /* +0xB0 */
    int32_t      idxB4;       /* +0xB4 */
    R4jBoneDef  *defB8;       /* +0xB8 */
    uint8_t     *dataBC;      /* +0xBC */
    R4jBoneOwner *ownerC0;    /* +0xC0 */
    int32_t      iC4, iC8, iCC, iD0; /* +0xC4 */
    float        colD4[4];    /* +0xD4 */
    float        vE4[4];      /* +0xE4 */
    uint8_t      unkF4[4];
    int32_t      iF8, iFC;    /* +0xF8 */
} R4jBone;
void sub_001BBA20(R4jBoneOwner *m, R4jBone *nodes, int idx);  /* 0x001BBA20 */

/* ------------------------------------------------------------ axis rotation (0x001B3700) */
/* 0x001A3ED0 is fsin and 0x001A3EE0 fcos (declared in r4i.h) */
void r4j_MatRotUnitAxis(float *m, const float *axis, float angle); /* 0x001B3700 regargs: m=EDI axis=ESI */

/* ------------------------------------------------------------ camera matrices (0x001B7100) */
typedef struct R4jLens {      /* camera lens block (R4fLens in r4f.h) */
    float    w00;             /* +0x00 aspect width */
    float    sx04, sy08;      /* +0x04 screen scale */
    float    ox0C, oy10;      /* +0x0C screen offset */
    float    zmax14, zmin18;  /* +0x14 depth range */
    float    near1C;          /* +0x1C */
    float    far20;           /* +0x20 */
    float    halfW24;         /* +0x24 */
    float    halfH28;         /* +0x28 */
} R4jLens;
typedef struct R4jView {
    uint8_t  unk00[0xF0];
    float    m0F0[16];        /* +0xF0 */
    float    proj130[16];     /* +0x130 */
    float    frus170[16];     /* +0x170 */
    float    scr1B0[16];      /* +0x1B0 */
} R4jView;
void sub_001B6FE0(float *out, const R4jLens *l);              /* 0x001B6FE0 */

/* ------------------------------------------------------------ lobbed shot update (0x00191010) */
typedef struct R4jLob {       /* work block of the lobbed kind 0x18/0x19 shot */
    int32_t  i00, i04;
    float    glow08;          /* +0x08 glow size */
    int32_t  i0C;
    int32_t  live10;          /* +0x10 cleared after a wall bounce */
    float    vel14[4];        /* +0x14 velocity */
    float    dist24;          /* +0x24 */
    float    grav28;          /* +0x28 subtracted from vel14[1] each frame */
    float    sink2C;          /* +0x2C subtracted from the height each frame */
} R4jLob;
extern float r4j_spin32C678[3];                               /* 0x0032C678 spin rate of the lobbed shot */
void r4j_FxLobUpdate(R4cNode *o, R4cActor *a);                /* 0x00191010 */

/* ------------------------------------------------------------ pad merge (0x001A8EA0) */
typedef struct R4jPad {       /* 0x11C-byte pad record (R4dPad in r4d.h) */
    uint16_t buttons00;       /* +0x00 */
    uint8_t  analog02[8];     /* +0x02 */
    int16_t  stick0A[4];      /* +0x0A */
    uint8_t  unk12[2];
    float    axis14[4];       /* +0x14 */
    uint16_t w24;             /* +0x24 */
    uint8_t  unk26[2];
    uint32_t edge28[8];       /* +0x28 */
    uint16_t w48;             /* +0x48 */
    uint8_t  unk4A[2];
    uint32_t hold4C[8];       /* +0x4C */
    uint8_t  unk6C[0xD0 - 0x6C];
    void    *hD0;             /* +0xD0 device handle */
    uint8_t  unkD4[0xDC - 0xD4];
    int32_t  fDC;             /* +0xDC */
    uint8_t  unkE0[0x11C - 0xE0];
} R4jPad;
extern R4jPad *r4j_pads40B9A4;                                /* 0x0040B9A4 four pad records (r4d_pads40B9A4) */
extern R4jPad  r4j_padAll40B888;                              /* 0x0040B888 all pads merged */
void sub_001A8B60(R4jPad *pads);                              /* 0x001A8B60 regargs: pads=EAX */
void r4j_PadMergeAll(void);                                   /* 0x001A8EA0 */

/* ------------------------------------------------------------ scene node update (0x001B2270) */
typedef struct R4jHook {      /* hook list entry (R4Hook in r4.h) */
    struct R4jHook *next;     /* +0x00 */
    void (*fn)(struct R4jSNode *n, struct R4jHook *h); /* +0x04 */
} R4jHook;
typedef void (*R4jSNodeFn)(struct R4jSNode *n);
typedef struct R4jSNode {     /* scene node (R4Node in r4.h) */
    float    local00[16];     /* +0x00 */
    float    world40[16];     /* +0x40 */
    struct R4jSNode *parent80; /* +0x80 */
    struct R4jSNode *next84;  /* +0x84 next sibling */
    struct R4jSNode *child88; /* +0x88 first child */
    int32_t  type8C;          /* +0x8C */
    uint32_t flags90;         /* +0x90 bit 0 done, 4 no sort, 5 hidden, 6 keep world, 8 front */
    float    depth94;         /* +0x94 sort depth */
    R4jSNodeFn *passFns98;    /* +0x98 per-pass callbacks */
    uint8_t  unk9C[4];
    struct R4jSNode *prevA0;  /* +0xA0 depth bucket chain */
    struct R4jSNode *nextA4;  /* +0xA4 */
    R4jHook *hooksA8;         /* +0xA8 */
    R4jHook *hooksAC;         /* +0xAC */
} R4jSNode;
extern int32_t   r4j_typeCount412EE0[20];                    /* 0x00412EE0 nodes seen per type */
extern R4jSNode *r4j_bucketTail412F80[0x33];                 /* 0x00412F80 (r4_g412F80) */
extern R4jSNode *r4j_bucketHead413060[0x33];                 /* 0x00413060 (r4_g413060) */
extern int32_t   r4j_pass40F1BC;                             /* 0x0040F1BC (r4_g40F1BC) */
extern uint32_t  r4j_doneMask40F1C0;                         /* 0x0040F1C0 (r4_g40F1C0) AND of all node flags */
extern float     r4j_depthMax377F48;                         /* 0x00377F48 (r4_g377F48) */
extern float     r4j_depthMin40F1C4;                         /* 0x0040F1C4 (r4_g40F1C4) */
extern uint8_t   r4j_renderFlags412F30;                      /* 0x00412F30 */
void r4_HookRunA8(R4jSNode *n);                               /* 0x001B2240 */
R4jSNode *sub_001B2270(R4jSNode *n);                          /* 0x001B2270 */

/* ------------------------------------------------------------ matrix to quaternion (0x001AF0A0) */
extern const int32_t r4j_next367E58[3];                       /* 0x00367E58 {1, 2, 0} next axis */
void r4j_MatToQuat(const float *m, float *q);                 /* 0x001AF0A0 regargs: m=ESI */

/* ------------------------------------------------------------ animation player update (0x001AFD80) */
typedef struct R4jAnimPart {  /* 0x130-byte animated part */
    uint8_t  unk00[0xB8];
    uint32_t flagsB8;         /* +0xB8 bit 0 loop, bit 2 loop next */
    void    *curBC;           /* +0xBC current track (0 = idle) */
    int32_t  iC0, iC4, iC8, iCC; /* +0xC0 */
    float    fD0;             /* +0xD0 */
    void    *nextD4;          /* +0xD4 queued track */
    int32_t  iD8, iDC, iE0, iE4; /* +0xD8 queued values */
    float    fE8;             /* +0xE8 */
    uint8_t  unkEC[0x130 - 0xEC];
} R4jAnimPart;
typedef struct R4jAnimPlayer {
    uint8_t  unk00[0xB0];
    int32_t  count;           /* +0xB0 parts */
    R4jAnimPart *parts;       /* +0xB4 */
    uint32_t flagsB8;         /* +0xB8 bit 1 frozen */
    uint32_t modeBC;          /* +0xBC bit 0 queued, bit 1 blending, 0x10/0x20 kinds */
    void    *animC0;          /* +0xC0 */
    float    speedC4;         /* +0xC4 */
    void    *nextC8;          /* +0xC8 */
    uint32_t waitCC;          /* +0xCC */
    uint32_t tickD0;          /* +0xD0 */
    void   (*onEndD4)(struct R4jAnimPlayer *p); /* +0xD4 */
    float    timeD8;          /* +0xD8 */
    float    lenDC;           /* +0xDC */
} R4jAnimPlayer;
void r4j_AnimPlayerTick(R4jAnimPlayer *p);                    /* 0x001AFD80 */

/* ------------------------------------------------------------ look-at transform (0x001AE210) */
typedef struct R4jVec4 { float v[4]; } R4jVec4;
void sub_001AE060(void *xf, const float *m);                  /* 0x001AE060 (r4g.h) */
void r4j_LookAt(void *xf, const float *pos, const float *dir, const float *up); /* 0x001AE210 */

/* ------------------------------------------------------------ title fade job (0x0019D120) */
extern int32_t a30_g41316C, a30_g413170;                      /* 0x0041316C, 0x00413170 */
void sub_00033250(void);                                      /* 0x00033250 */
void sub_001A5380(int v);                                     /* 0x001A5380 stores v to 0x0040B0EC */
void r4j_FadeJob(void);                                       /* 0x0019D120 */

#endif
