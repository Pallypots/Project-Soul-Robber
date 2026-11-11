/* Area rtc: small game functions that end in a tail call passing rewritten
   arguments, across 0x00012000..0x001BC6CF. Names inferred. */
#ifndef RTC_H
#define RTC_H
#include "oogie.h"
#include "shared_decls.h"
#include <string.h>

/* ---------------------------------------------------------------- types */
/* Generic object: only the fields reached by these functions are named. */
typedef struct RtcObj RtcObj;
struct RtcObj {
    uint8_t  unk00[0x04];
    int32_t  kind4;            /* +0x04 */
    void    *p8;               /* +0x08 */
    union { int32_t iC; void *pC; }; /* +0x0C (int16 in some callers; a process reference for 0x00089420) */
    union { float f10; int32_t i10; }; /* +0x10 */
    void    *i14;              /* +0x14 */
    uint8_t  unk18[0x20 - 0x18];
    void    *p20;              /* +0x20 */
    uint8_t  unk24[0x30 - 0x24];
    void    *anim30;           /* +0x30 */
    void    *nodes34[4];       /* +0x34 */
    uint8_t  unk44[0x50 - 0x44];
    float    f50;              /* +0x50 */
    uint8_t  unk54[0x9C - 0x54];
    int32_t  i9C;              /* +0x9C */
};

/* Animation player reached through +0x14 of an anim state. */
typedef struct RtcAnimPart { uint8_t unk00[0xC4]; float rateC4; } RtcAnimPart;
/* Anim state reached through +0x30 of an actor. */
typedef struct RtcAnim {
    uint8_t  unk00[0x08];
    int32_t  cur8;             /* +0x08 current animation */
    uint8_t  unk0C[0x14 - 0x0C];
    RtcAnimPart *p14;          /* +0x14 */
} RtcAnim;

/* Actor record (fields reached by these functions only). */
typedef struct RtcActor {
    uint8_t  unk000[0x08];
    int32_t  kind8;            /* +0x008 */
    uint32_t flagsC;           /* +0x00C */
    uint32_t flags10;          /* +0x010 */
    uint8_t  unk014[0x20 - 0x14];
    uint8_t *model20;          /* +0x020 */
    uint8_t  unk024[0x30 - 0x24];
    RtcAnim *anim30;           /* +0x030 */
    uint8_t  unk034[0x4C - 0x34];
    uint32_t flags4C;          /* +0x04C */
    float    v50[4];           /* +0x050 (f50 = v50[0]) */
    float    v60[4];           /* +0x060 */
    uint8_t  unk070[0x7C - 0x70];
    float    f7C;              /* +0x07C */
    uint8_t  unk080[0x8C - 0x80];
    struct RtcActor *link8C;   /* +0x08C */
    struct RtcActor *link90;   /* +0x090 */
    uint8_t  unk094[0x9C - 0x94];
    float    f9C;              /* +0x09C */
    uint8_t  unk0A0[0xA8 - 0xA0];
    int16_t  activeA8;         /* +0x0A8 */
    uint8_t  unk0AA[0xBC - 0xAA];
    struct { uint8_t unk[0x90]; uint32_t flags90; } *partBC; /* +0x0BC */
    uint8_t  unk0C0[0xD0 - 0xC0];
    int32_t  stateD0;          /* +0x0D0 */
    uint8_t  unk0D4[0x100 - 0xD4];
    int32_t  phase100;         /* +0x100 */
    uint8_t  unk104[0x110 - 0x104];
    int32_t  i110;             /* +0x110 */
    uint8_t  unk114[0x118 - 0x114];
    float    yaw118;           /* +0x118 */
    uint8_t  unk11C[0x120 - 0x11C];
    union { void *ramp120; int32_t i120; }; /* +0x120 */
    uint8_t  unk124[0x128 - 0x124];
    uint32_t flags128;         /* +0x128 */
    uint8_t  unk12C[0x1A8 - 0x12C];
    void    *rec1A8;           /* +0x1A8 */
    uint8_t  unk1AC[0x278 - 0x1AC];
    RtcObj  *sub278;           /* +0x278 */
    uint8_t  unk27C[0x2EC - 0x27C];
    int32_t  handle2EC;        /* +0x2EC */
    uint8_t  unk2F0[0x2F8 - 0x2F0];
    int32_t  paused2F8;        /* +0x2F8 */
    uint8_t  unk2FC[0x3B0 - 0x2FC];
    RtcObj  *node3B0;          /* +0x3B0 */
} RtcActor;

/* Motion state at +0x278 of an actor, as used by 0x001598F0. */
typedef struct RtcMotion {
    uint32_t flags0;           /* +0x00 */
    uint8_t  unk04[0x0C - 0x04];
    float    speedC;           /* +0x0C */
    float    f10;              /* +0x10 */
    uint8_t  unk14[0x24 - 0x14];
    float    v24[3];           /* +0x24 */
    float    scale30;          /* +0x30 */
    uint8_t  unk34[0x74 - 0x34];
    float    v74[4];           /* +0x74 */
} RtcMotion;

/* Mover block used by 0x0010AC30. */
typedef struct RtcMover {
    uint8_t  unk00[0xB4];
    float    timeB4;           /* +0xB4 */
    float    vB8[3];           /* +0xB8 */
    float    vC4[4];           /* +0xC4 */
} RtcMover;

/* Player stats seen as the fields these functions use (same object as
   g_stats at 0x0041FEC0). */
typedef struct RtcStats {
    uint8_t  unk000[0xD8];
    int32_t  modeD8;           /* +0x0D8 (0x0041FF98) */
    uint8_t  unk0DC[0xE0 - 0xDC];
    int32_t  iE0;              /* +0x0E0 (0x0041FFA0) */
    uint8_t  unk0E4[0x150 - 0xE4];
    uint32_t flags150;         /* +0x150 (0x00420010) */
    uint8_t  unk154[0xEF4 - 0x154];
    RtcAnim *modelEF4;         /* +0xEF4 (0x00420DB4) */
} RtcStats;

/* Voice record of the 16-entry table at 0x00401B30 (0x24 bytes each). */
typedef struct RtcVoice {
    void    *p0;               /* +0x00 */
    uint8_t  unk04[0x10 - 0x04];
    int32_t  state10;          /* +0x10 */
    int32_t  handle14;         /* +0x14 */
    uint8_t  unk18[0x20 - 0x18];
    int32_t  count20;          /* +0x20 */
} RtcVoice;
/* Stream record of the 45-entry table at 0x00401D70 (0x38 bytes each). */
typedef struct RtcStream {
    void    *p0;               /* +0x00 */
    int32_t  i4;               /* +0x04 */
    int32_t  id8;              /* +0x08 */
    int32_t  iC;               /* +0x0C */
    int32_t  state10;          /* +0x10 */
    int32_t  i14;              /* +0x14 */
    uint8_t  unk18[0x34 - 0x18];
    int32_t  i34;              /* +0x34 */
} RtcStream;

/* Screen object used by 0x000E9D20. */
typedef struct RtcScrEnt { int32_t v0; uint8_t unk04[0x18]; } RtcScrEnt;
typedef struct RtcScreen {
    int32_t  kind0;            /* +0x000 page kind */
    uint8_t  unk004[0x328 - 0x04];
    int32_t  i328;             /* +0x328 */
    uint8_t  unk32C[0x408 - 0x32C];
    int32_t  i408;             /* +0x408 */
    int32_t  cur40C;           /* +0x40C */
    int32_t  max410;           /* +0x410 */
    uint8_t  unk414[0x418 - 0x414];
    int32_t  i418;             /* +0x418 */
    int32_t  i41C;             /* +0x41C */
    float    f420;             /* +0x420 */
    int32_t  i424;             /* +0x424 */
    int32_t  i428;             /* +0x428 */
    uint8_t  unk42C[0x430 - 0x42C];
    int32_t  i430;             /* +0x430 */
    uint8_t  unk434[0x44C - 0x434];
    RtcScrEnt ents44C[7];      /* +0x44C */
    uint8_t  unk510[0x518 - 0x510];
    int32_t  i518;             /* +0x518 */
} RtcScreen;
/* Track position used by 0x000E9F30. */
typedef struct RtcTrackPos { int32_t base0; int16_t off4; } RtcTrackPos;

/* Slot table owner used by 0x00033C20: 16 slots at +0x1C. */
typedef struct RtcSlot {
    int32_t  i0;               /* +0x00 */
    uint8_t  unk04[0x10 - 0x04];
    void    *chain10;          /* +0x10 */
    uint8_t  unk14[0x20 - 0x14];
    uint8_t  emit20[4];        /* +0x20 emitter set */
} RtcSlot;
typedef struct RtcSlotOwner { uint8_t unk00[0x1C]; RtcSlot *slots[16]; } RtcSlotOwner;

/* Owner of a kind record at +0x74 (0x00192910). */
typedef struct RtcKindRec { uint8_t unk00[8]; int32_t kind8; } RtcKindRec;
typedef struct RtcKindHolder { uint8_t unk00[0x74]; RtcKindRec *rec74; } RtcKindHolder;

/* Entry handled by 0x0005A9C0. */
typedef struct RtcEntry {
    uint8_t  unk00[4];
    int32_t  i4;               /* +0x04 */
    uint8_t  unk08[0x28 - 0x08];
    int32_t  i28;              /* +0x28 */
} RtcEntry;

/* Task owner shut down by 0x000893C0. */
typedef struct RtcTaskOwner {
    uint8_t  unk00[0x1C];
    void    *list1C;           /* +0x1C */
    void    *list20;           /* +0x20 */
    uint8_t  unk24[0x48 - 0x24];
    void    *ref48;            /* +0x48 */
} RtcTaskOwner;

/* Switch object updated by 0x000D5870. */
typedef struct RtcSwitch {
    uint32_t flags0;           /* +0x00 bit 0: inverted */
    uint8_t  unk04[0x14 - 0x04];
    int32_t  state14;          /* +0x14 1 = on, 2 = off */
    int32_t  i18;              /* +0x18 */
    float    f1C;              /* +0x1C */
    float    f20;              /* +0x20 */
    uint8_t  unk24[0x3B0 - 0x24];
    RtcObj  *node3B0;          /* +0x3B0 */
} RtcSwitch;

/* Scene context at *0x0042C8E4 (sound handle at +0x1F0). */
typedef struct RtcScene { uint8_t unk000[0x1F0]; void *snd1F0; } RtcScene;

/* Menu block at 0x003F0758 (0x28D words). */
typedef struct RtcMenuItem { int32_t v0; uint8_t unk04[0x10]; } RtcMenuItem;
typedef struct RtcMenu {
    int32_t  mode0;            /* +0x000 */
    int32_t  cur4;             /* +0x004 */
    RtcMenuItem items8[9];     /* +0x008 */
    uint8_t  unk0BC[0x2E8 - 0xBC];
    int32_t  sel2E8;           /* +0x2E8 */
    int32_t  sel2EC;           /* +0x2EC */
    int32_t  i2F0;             /* +0x2F0 */
    int32_t  i2F4;             /* +0x2F4 */
    int32_t  i2F8;             /* +0x2F8 */
    int32_t  i2FC;             /* +0x2FC */
    uint8_t  unk300[0x314 - 0x300];
    int32_t  i314;             /* +0x314 */
    uint8_t  unk318[0xA34 - 0x318];
} RtcMenu;

/* Camera user handled by 0x000CC180. */
typedef struct RtcCamUser {
    uint8_t  unk000[0x318];
    int32_t  on318;            /* +0x318 */
    int32_t  cur31C;           /* +0x31C */
    uint8_t  unk320[0x3A8 - 0x320];
    int32_t  kinds3A8[(0x528 - 0x3A8) / 4]; /* +0x3A8 */
    int32_t  steps528[1];      /* +0x528 */
} RtcCamUser;

/* Stage table entry at 0x002E7D58 (0x314 bytes each, ended by id -1). */
typedef struct RtcStageEnt {
    int32_t  id;               /* +0x000 */
    uint8_t  unk004[0x10 - 0x04];
    int32_t  base10;           /* +0x010 */
    uint8_t  unk014[0x314 - 0x14];
} RtcStageEnt;
/* Stage mode block at 0x003EDB60. */
typedef struct RtcModes {
    int32_t  mode60;           /* 0x003EDB60 */
    int32_t  on64;             /* 0x003EDB64 */
    int32_t  entry68;          /* 0x003EDB68 */
    int32_t  i6C;              /* 0x003EDB6C */
    int32_t  slot70;           /* 0x003EDB70 */
    float    t74;              /* 0x003EDB74 */
    int32_t  id78;             /* 0x003EDB78 */
    uint8_t  unk7C[0x8C - 0x7C];
    int32_t  v8C[5];           /* 0x003EDB8C */
    int32_t  iA0;              /* 0x003EDBA0 */
    uint32_t flagsA4;          /* 0x003EDBA4 */
} RtcModes;

/* Save request used by 0x0019C620. */
typedef struct RtcSaveReq {
    int32_t  slot0;            /* +0x00 */
    void    *p4;               /* +0x04 */
    uint8_t  unk08[0x10 - 0x08];
    void    *proc10;           /* +0x10 */
    uint8_t  done14;           /* +0x14 */
} RtcSaveReq;

/* Text box initialised by 0x00079E00. */
typedef struct RtcTextHdr { int32_t i0, i4, i8, iC; } RtcTextHdr;
typedef struct RtcTextBox {
    uint8_t  unk000[0x40];
    RtcTextHdr *hdr40;         /* +0x040 */
    uint8_t  unk044[0x1B8 - 0x44];
    int32_t  i1B8;             /* +0x1B8 */
    float    f1BC;             /* +0x1BC */
    float    f1C0;             /* +0x1C0 */
    float    rgb1C4[3];        /* +0x1C4 */
    int32_t  v1D0[3];          /* +0x1D0 */
    int32_t  i1DC;             /* +0x1DC */
    int32_t  i1E0;             /* +0x1E0 */
    float    f1E4;             /* +0x1E4 */
    int32_t  id1E8;            /* +0x1E8 */
    int32_t  v1EC[6];          /* +0x1EC */
    void    *work204;          /* +0x204 */
} RtcTextBox;

/* Object tested by 0x00094F10. */
typedef struct RtcProp {
    uint8_t  unk00[0x2C];
    float    f2C;              /* +0x2C height offset */
    uint8_t  unk30[0x70 - 0x30];
    float    v70[4];           /* +0x70 position */
} RtcProp;

/* Body record used by 0x0013B960. */
typedef struct RtcBody {
    uint8_t  unk00[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t  unk50[0x88 - 0x50];
    float    v88[4];           /* +0x88 */
} RtcBody;

/* Packet chain used by 0x0001EF00. */
typedef struct RtcPktTex {
    uint8_t  unk00[0x08];
    void    *fn8;              /* +0x08 handler, must be 0x0001ED90 */
    uint8_t  unk0C[0x1C - 0x0C];
    float    v1C[4];           /* +0x1C */
} RtcPktTex;
typedef struct RtcPktInfo { uint8_t unk00[0xA8]; RtcPktTex *texA8; } RtcPktInfo;
typedef struct RtcPkt {
    uint8_t  unk00[0x0C];
    uint8_t  flagsC;           /* +0x0C */
    uint8_t  unk0D[0x28 - 0x0D];
    RtcPktInfo *info28;        /* +0x28 */
} RtcPkt;

/* Record of the 4-entry pair table at 0x003FE2D8 (0x24 bytes each). */
typedef struct RtcPair {
    RtcActor *a;               /* +0x00 */
    RtcActor *b;               /* +0x04 */
    struct { uint8_t unk[0x50]; int32_t state50; } *owner; /* +0x08 */
    int32_t  key;              /* +0x0C */
    uint8_t  unk10[0x24 - 0x10];
} RtcPair;

/* Record of the 6-entry table at *0x00401828 (0x44 bytes each). */
typedef struct RtcRec44 { uint8_t *obj; uint8_t unk04[0x44 - 4]; } RtcRec44;

/* Record of the 4-entry table at 0x00400A88 (0x88 bytes each). */
typedef struct RtcRec88 { RtcObj *obj; uint8_t unk04[0x88 - 4]; } RtcRec88;
/* Record of the 119-entry cue table at 0x00330F30 (16 bytes each). */
typedef struct RtcCue { int32_t id; uint8_t unk04[0x0C]; } RtcCue;

/* ---------------------------------------------------------------- data */
extern uint32_t rtc_colours2C4468[];   /* 0x002C4468 text colour table */
extern void    *a50_slotHeap[];        /* 0x003E26A8 heap handle per slot */
extern int32_t  rtc_level3DFED8;       /* 0x003DFED8 */
extern float    rtc_scale3DFEDC;       /* 0x003DFEDC */
extern int32_t  adc_30D6BC;            /* 0x0030D6BC */
extern RtcActor *afc_helper;           /* 0x003F611C */
extern RtcActor *rtc_playerObj;        /* 0x00420E98 */
extern RtcRec88 r4c_recs400A88[4];     /* 0x00400A88 */
extern RtcCue   r4c_cues330F30[119];   /* 0x00330F30 */
extern int32_t  a19_g402FF4;           /* 0x00402FF4 */
extern float    rtc_mtx3DCE70[2][16];  /* 0x003DCE70 two matrices */
extern int32_t  a4c_g3DFFF8;           /* 0x003DFFF8 */
extern uint8_t  aa0_enabled413142;     /* 0x00413142 */
extern float    rfl_fps42C964;         /* 0x0042C964 */
extern float    a50_frameUnits;        /* 0x0042C858 */
extern RtcActor *g_acb_bossMgr;        /* 0x003F610C */
extern RtcActor *afc_minion;           /* 0x003F6120 */
extern RtcActor *b10_ctl;              /* 0x003F6128 */
extern RtcPair  rtc_pairs3FE2D8[4];    /* 0x003FE2D8 */
extern RtcRec44 *a19_g401828;          /* 0x00401828 */
extern int32_t  a19_g402FE4;           /* 0x00402FE4 */
extern int32_t  a19_g402FE8;           /* 0x00402FE8 */
extern float    a50_timeScale;         /* 0x002DCD4C */
extern float    a50_rateHz[];          /* 0x002DCD50 */
extern float    a50_frameSeconds;      /* 0x0042C85C */
extern RtcStats rtc_stats;             /* 0x0041FEC0 */
extern uint8_t  ae0_obj3E1270[];       /* 0x003E1270 */
extern RtcActor *g_acb_bossAux;        /* 0x003F6110 */
extern const float r4c_v27B00C[4];     /* 0x0027B00C */
extern const float r4c_v27B01C[4];     /* 0x0027B01C */
extern RtcVoice r4c_voices401B30[16];  /* 0x00401B30 */
extern RtcStream r4c_streams401D70[45];/* 0x00401D70 */
extern uint8_t  rtc_flag331748;        /* 0x00331748 */
extern int8_t   rtc_stream331758;      /* 0x00331758 */
extern int32_t  r1c_state3816D0;       /* 0x003816D0 */
extern uint32_t r1c_mode381400;        /* 0x00381400 */
extern RtcScene *rtc_scene42C8E4;      /* 0x0042C8E4 */
extern int8_t   r4c_opt413148;         /* 0x00413148 */
extern int32_t  a4c_state3E0000[0x14C];/* 0x003E0000 */
extern int32_t  rtc_count3E0540;       /* 0x003E0540 */
extern int32_t  rtc_count3E059C;       /* 0x003E059C */
extern int32_t  rtc_hidden3F0A68;      /* 0x003F0A68 */
extern int32_t  rtc_rec3F0A74;         /* 0x003F0A74 */
extern void    *r2b_g3F1B1C;           /* 0x003F1B1C */
extern uint8_t  aec_3F118C[];          /* 0x003F118C message window */
extern uint32_t rtc_cheatFlags413130;  /* 0x00413130 (g_cheatFlags as a word) */
extern RtcMenu  g_acb_3F0758;          /* 0x003F0758 */
extern void    *r4c_g402778;           /* 0x00402778 stream lock */
extern int32_t  a30_g41316C;           /* 0x0041316C */
extern int32_t  a30_g413170;           /* 0x00413170 */
extern int32_t  r1c_camFlag42CB0C;     /* 0x0042CB0C */
extern uint8_t  b3b_tbl31DBD4[];       /* 0x0031DBD4 reaction list */
extern int32_t  r1c_q3DFEC0[4];        /* 0x003DFEC0 */
extern int32_t  r1e_pairs3DFEA0[8];    /* 0x003DFEA0 four slot pairs */
extern int32_t  r1c_tbl3DFA68[0x10E];  /* 0x003DFA68 */
extern int32_t  rtc_g3DFED0;           /* 0x003DFED0 */
extern int32_t  r1e_g3DFED4;           /* 0x003DFED4 */
extern int32_t  rtc_blk3DFEE0[0x3F];   /* 0x003DFEE0 */
extern int32_t  rtc_g3DF9B4;           /* 0x003DF9B4 */
extern int32_t  a30_g3DF9B8;           /* 0x003DF9B8 stage mode */
extern int32_t  a30_g3DF9BC;           /* 0x003DF9BC */
extern int32_t  rtc_tex3DF9C0;         /* 0x003DF9C0 */
extern int32_t  rtc_tex3DF9C4;         /* 0x003DF9C4 */
extern int32_t  rtc_tex3DF9C8[24];     /* 0x003DF9C8 */
extern int32_t  rtc_tex3DF1D0;         /* 0x003DF1D0 */
extern int32_t  rtc_tex3DF1E0[2];      /* 0x003DF1E0 */
extern int32_t  rtc_tex3DFA38[9];      /* 0x003DFA38 */
extern int32_t  rtc_tex3DF9A8;         /* 0x003DF9A8 */
extern int32_t  rtc_tex3DF9AC;         /* 0x003DF9AC */
extern void    *a4c_g3DFA5C;           /* 0x003DFA5C stage block (freed through 0x00053880; r1c_stage3DFA5C) */
extern RtcStageEnt r2b_stages2E7D58[]; /* 0x002E7D58 */
extern RtcModes r2_modes3EDB60;        /* 0x003EDB60 */

/* ---------------------------------------------------------------- callees */
void  sub_0001BEE0(void *a, void *b);
void  sub_0001C160(void *a, void *b);
void *sub_000380A0(void *ctx, int x, int y, int z, void *size, int colour,
                   float sx, float sy, int ch);
void *r6d_TextDraw(void *ctx, void *t);                    /* 0x000770B0 */
void *r6d_TextDrawAlpha(void *ctx, void *t, int alpha);    /* 0x00077110 */
void  sub_000486F0(int v);
void *sub_00047390(void *heap, int size, const void *file, int line);
void *sub_00047450(void *heap, int size, const void *file, int line);
void *a6b_HeapAlloc(int slot, int align, int size, int line, const void *file);    /* 0x0007F480 */
void *a12_Table_Get(void *t, int i);                       /* 0x0001D220 */
int   r4b_Get8(void *p);                                   /* 0x001BBDD0 */
void  r1b_RecDetachNodes(RtcObj *n);                       /* 0x0001EB80 */
void  r1_NodeHide(RtcObj *n);                              /* 0x0001D700 */
int   sub_00037FD0(int v);
int   sub_0019A900(int h);
void  sub_000D2A50(PlayerStats *s, int a);
void  sub_000E8A50(int a, int b);
void  r2d_StageLinkFree(void *a, int b);                   /* 0x000E14C0 */
void  sub_000E1F30(void *a, int b);
void *afc_DispatchByType(void *o);                         /* 0x000F5F80 */
void  afc_SetBothAnims(void *o, int anim);                 /* 0x000F62F0 */
void  sub_000F3F00(void *o, float v);
void  sub_0019A0E0(int id);
int   sub_001AA520(int h);
void  sub_001ADE10(float *m, const float *a, const float *b, const float *c, const float *d);
void *r4_FogEmit(void *o, void *a);                        /* 0x001B1E10 */

void *r1c_PktTexBase(void *p);                             /* 0x0001ED90 */
void  sub_00048D70(int on);
void  r4_ModelSetPartValue(void *m, void *v);               /* 0x001B14E0 */
void  r4b_MeshSetC8(void *m, void *v);                      /* 0x001B3070 */
const char *sub_000133B0(const char *name);
int   r4_TexFindNamed(const char *name);                   /* 0x001BA7C0 */
int   r4b_TexWithGroup(void *t);                           /* 0x001BA7F0 */
void *sub_000904F0(float a, float b, float c, float d);
void  r6e_RampSet(void *r, float a, float b, float c, float d);    /* 0x00090420 */
int a5b_SndPause(void);                                  /* 0x00054040 */
void  r4d_TrackPause(int h);                               /* 0x0019AB40 */
int a5b_ShockPlay(int a, int b);                         /* 0x0005EB10 */
void  sub_00019350(int a, int b);
void  rtc_RecSetAnim(int i, int anim);                     /* 0x00192380 */
void  b1b_EnemyMarkParts(void *a, void *b);                /* 0x00113A40 */
void  r2d_NodesScale(void *n, float k);                    /* 0x000EE660 */
void  sub_00178860(void *a, void *b);
RtcObj *sub_001133E0(void *o, int i);
void  r6_Mat1ADB40(void *m, void *b);                      /* 0x001ADB40 */
void  sub_000408B0(int v);
void  sub_000408C0(int v);
void  sub_0019E810(int v);

void  r4b_EmitSetReleaseAll(void *e);                      /* 0x001B6270 */
void  r4_EmitSetFlag8(void *e);                            /* 0x001B6130 */
void  r1c_NodeFreeChain(void *c);                          /* 0x00033A70 */
void  r1d_NodeFree(void *n);                               /* 0x00033560 */
void  sub_00036B10(void *o);
void  r4b_SetFactor(float f);                              /* 0x001BBD70 */
void  sub_0003E410(void *b, int v);
void  sub_00018610(void);
void  a5b_ChansReset(void);                                /* 0x0005EB50 */
int r6e_TaskSendAll(void *list, int o);                /* 0x0008C1F0 */
void  sub_0008B400(void *p);
int r6e_TaskFreeList(void *list);                        /* 0x0008BF70 */
int   r6b_ReturnZero();                                    /* 0x000AD090 xor eax; ret: any args */
void  sub_0008FB80(void *p);
void  sub_000D1930(RtcStats *s);
void  sub_00023BC0(int v);
void  abc_SetState(RtcStats *s, int st);                   /* 0x000BD4D0 */
void  sub_000C5B10(void);
void  sub_0019BE90(int v);
void  sub_000E8920(int a, int b);
void  sub_00019000(void *o, int v);
void  sub_0001AB00(void *o, int a, int b, int c, int d);
void  sub_000F4CA0(void);
void  sub_000F3D10(RtcActor *a, RtcActor *b, int v);
void  r1b_RecSyncVisible(void *r);                         /* 0x0001D720 */
void  r1b_RecHideAll(void *r);                             /* 0x0001D7A0 */
int   sub_00199850(int i);
void  sub_001AAA00(int h, int v);
int   sub_00199DE0(int v);
int   sub_0019A1D0(int v);

void *sub_0002CF80(void *x);
void *sub_000720D0(void *x, float l, float t, float w, float h, int z,
                   uint32_t c0, uint32_t c1, uint32_t c2, uint32_t c3);
void  r6c_CamMarkersPlace(void);                           /* 0x00086EF0 */
void  sub_00085DE0(void);
void  sub_000D1D00(PlayerStats *s);
void  sub_0019BEB0(int ev);
int   sub_000DFC00(void);
void  a5b_Clear3E6040(void);                               /* 0x0005BBC0 */
int   af0_GetVar3F0738(void);                              /* 0x000DFD00 */
void  r2b_ScriptTick(void);                                /* 0x000E0570 */
void  sub_000DE9E0(int v);
void  sub_00038960(void);
int a1a_GroupAdd(void *x, int g, int n, void (*fn)(void), int a, int size); /* 0x001A1030 */
int a1a_GroupReleaseOne(void *x, int g);                 /* 0x001A1060 */
void  sub_0004D3E0(void);
void  sub_0004E9E0(void);
void  sub_0004E890(void);
void  sub_00048620(int v);
void  sub_000325A0(int v);
void  sub_000D5200(RtcSwitch *o);
int   sub_000E70C0(int page);
int   r1c_GetRecThunk(int h);                              /* 0x000482B0 */
void  sub_0003FC10(void *w);
void *r6d_MsgGet(void *table, int id);                       /* 0x0003FA70 */

void  sub_000EC320(void);
void  sub_000E66F0(RtcMenu *m);
void  sub_000D0200(RtcStats *s, int a, int id);
void  sub_000E1060(RtcActor *p, int id, int a, int b);
void  r2d_StageStart(void *o);                             /* 0x000E4870 */
void  sub_000E63A0(int v);
void  sub_000E8690(int a, int b);
void  r2b_TrackMarkBefore(void *s, int a, int pos, int b); /* 0x000E0B70 */
void  r2d_StageStreamStop(void *s);                        /* 0x000E3BA0 */
void  sub_000E0780(void);

int   sub_001C7EE1(void);                                  /* CRT rand */
void  sub_001AEDF0(RtcAnimPart *p, int frame);
int   sub_00199E70(int i);
void  sub_001AAD40(int id, int a, int b, int i);
void  sub_000EE0C0(void);
int   sub_000EE240(void);
void  r1_KeyReleaseD(int a, int b);                        /* 0x000489A0 */
int   r1_KeyQuery2D(int a, int b);                         /* 0x000489D0 */
void  r1e_StagePlace(int v);                               /* 0x00047A80 */
int   sub_00047B10(int v);
void  sub_00047B30(int v);
int   sub_00047B50(int v);
int   r6c_StreamReleaseStep(void);                         /* 0x00086C60 */
void  r6c_EvJump(int ev);                                  /* 0x00087030 */

int   sub_00048B20(int id, int b);
int   sub_000F6B80(void *part);
void  sub_00100020(int phase);
void  sub_000FBA00(int phase);
void  sub_000FE2E0(int phase);
float sub_000CBB70(RtcCamUser *o);
float r1c_CamValue(void);                                  /* 0x0003B150 */
void  r1e_CamApplyFirst(void);                             /* 0x0003B0E0 */
void  sub_000CC070(RtcCamUser *o);

int   r2b_TakeButtons(uint16_t b);                         /* 0x000D7090 b=EAX */
int   r2b_PairB(int i);                                    /* 0x000D9000 */
void  af0_ClearVar3EE6C0(void);                            /* 0x000DFE10 */
void  sub_001A5380(int busy);
void  sub_0004F700(int slot);
void  sub_0004F730(int on);
void  r6e_ProcFinish(void *proc, int slot);                /* 0x0008D250 */
int   sub_0008CD90(void *proc);
void  r6b_ProcStep(void *proc);                            /* 0x0008D1C0 */
void  sub_0008CD80(void *proc);

int   sub_0001CFD0(void);
void *a5b_AllocCur(int size, const void *file, int line);  /* 0x00053AB0 */
void  a3c_Clear16(void *p);                                /* 0x0003D860 */
void  sub_000AA2E0(int ev);
float r4_DistanceXZ(const float *a, const float *b);       /* 0x001B2770 */

void  sub_000253D0(int a, int b);
void  sub_000C85C0(void);
void  sub_000A8B80(void);
void  sub_00025D50(int a, int b);

void  sub_0013A120(void *a, int n, const void *list);
void  r1b_RecFreeRes(void *a);                             /* 0x0001D190 */
void  r2d_PListPrune(void *b);                             /* 0x001134B0 */
void *r1c_ObjPlayMotion(void *a, int motion, int b);       /* 0x00035D80 */
int aab_Effect494D0(int id, const void *at, int b);      /* 0x000494D0 */
void *b1b_NodeRenew(void *c, int id);                      /* 0x00113430 */

void  sub_001AC680(void);
void  r1b_PktOp();                                     /* 0x00102FA0 */
void  r4e_SoundInit(void);                                 /* 0x0019B500 */
void  sub_0019B5C0(int cue);
int   r4d_CuePoll(int cue);                                /* 0x00199CA0 */
void  sub_0019AE90(void);
void  r4d_CueStartAll(int cue);                            /* 0x00199EB0 */
void  r1c_ClearWork42CE80(void);                           /* 0x00017D30 */
int r4b_TexFree(int h);                                  /* 0x001B9FC0 */
void  b1b_CmdRun(int cmd);                                 /* 0x0004F5D0 */
int   a5b_GetVideoMode(void);                              /* 0x000529F0 */
void  a5b_HeapOp47640(void *p);                            /* 0x00053880 */

/* Float to int truncation (cvttss2si in the original; portable fallback). */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define RTC_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define RTC_FTOI(x) ((int)(x))
#endif

#endif
