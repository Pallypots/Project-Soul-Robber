#ifndef R3_H
#define R3_H
#include "oogie.h"
/* Area r3: register-argument functions in 0x00130000..0x00190000. All names inferred.
   Register mappings of callees are in the comments and in config/function_states_r3.csv. */

/* Per-character work block hung off an actor at +0x278. */
typedef struct R3Work {
    uint32_t unk00;
    void    *snd04;          /* +0x04 */
    uint32_t flags08;        /* +0x08 */
    uint32_t flags0C;        /* +0x0C */
    uint32_t unk10;
    int32_t  i14;            /* +0x14 */
    uint32_t flags18;        /* +0x18 */
    float    f1C;            /* +0x1C */
    uint8_t  unk20[0x2C - 0x20];
    void    *h2C;            /* +0x2C */
    int32_t  i30;            /* +0x30 */
    void    *h34;            /* +0x34 */
    void    *p38[2];         /* +0x38 */
    uint8_t  unk40[0x50 - 0x40];
    float    f50;            /* +0x50 */
    uint8_t  unk54[0x140 - 0x54];
    int32_t  i140;           /* +0x140 */
    uint32_t unk144;
    int32_t  i148;           /* +0x148 */
    uint32_t unk14C[2];
    float    vec154[3];      /* +0x154 */
    uint32_t unk160;
    float    f164;           /* +0x164 */
    float    f168;           /* +0x168 */
    float    f16C;           /* +0x16C */
    union { int32_t i; float f; } u170; /* +0x170 */
    int32_t  i174;           /* +0x174 */
    int32_t  i178;           /* +0x178 */
    int32_t  i17C;           /* +0x17C */
    int32_t  i180;           /* +0x180 */
    float    f184;           /* +0x184 */
} R3Work;

/* Actor state block (the "act" side of the character state machine). */
typedef struct R3Actor {
    uint8_t  unk000[0x20];
    uint32_t flags20;        /* +0x020 */
    uint8_t  unk024[0x4C - 0x24];
    uint32_t flags4C;        /* +0x04C */
    int32_t  state50;        /* +0x050 current state */
    uint32_t unk54;
    int32_t  step58;         /* +0x058 sub-step inside a state */
    float    f5C;            /* +0x05C */
    uint8_t  unk060[0x6C - 0x60];
    int32_t  h6C;            /* +0x06C handle, -1 = none */
    void    *p70;            /* +0x070 */
    float    f74;            /* +0x074 */
    uint8_t  unk078[0x104 - 0x78];
    float    vec104[3];      /* +0x104 */
    uint8_t  unk110[0x270 - 0x110];
    float    f270;           /* +0x270 */
    float    f274;           /* +0x274 */
    R3Work  *work278;        /* +0x278 */
} R3Actor;

/* Character object (the "obj" side). */
typedef struct R3Obj {
    uint8_t  unk000[0x0C];
    uint32_t flags0C;        /* +0x00C */
    uint32_t flags10;        /* +0x010 */
    uint8_t  unk014[0x30 - 0x14];
    int32_t  anim30;         /* +0x030 animation handle */
    uint8_t *p34;            /* +0x034 */
    uint8_t  unk038[0x58 - 0x38];
    float    f58;            /* +0x058 */
    uint32_t unk05C;
    float    pos60[3];       /* +0x060 position (y at +0x64) */
    uint8_t  unk06C[0x90 - 0x6C];
    float    v90[4];         /* +0x090 */
    uint8_t  unk0A0[0x128 - 0xA0];
    uint32_t flags128;       /* +0x128 */
    uint8_t  unk12C[0x13C - 0x12C];
    int32_t  i13C;           /* +0x13C */
} R3Obj;

/* Callees (stack arguments unless stated). */
int  sub_000833E0(int anim);                         /* animation finished */
void sub_001134B0(R3Actor *act);
void sub_00113AA0(R3Obj *obj, R3Actor *act);
void sub_00194D30(void *snd, int a);
void sub_0001D720(R3Obj *obj);
void sub_00048250(int h);
void sub_0005BE30(int a);
void sub_00033A70(void *p);
void sub_00113040(R3Obj *obj, R3Actor *act, int state);
void sub_0012E5E0(int mode);                         /* mode=ESI */
int  sub_0012E630(R3Actor *act, R3Obj *obj);         /* act=EAX obj=stack */
int  sub_0012DC90(int table, R3Obj *obj, R3Actor *act);   /* table=EAX obj=EBX act=EDI */

void *sub_000EDC20(int a, int b);                    /* object iterator */
void *sub_0001D960(void *o, int kind);               /* component lookup */
int  sub_00145780(R3Obj *obj, float t);              /* animation passed time t */
void sub_00113480(R3Actor *act, int ev);
float sub_001B2770(const float *a, const float *b);  /* distance */
int  sub_001C7EE1(void);                             /* CRT rand (Hypothesis) */
void sub_0012D600(int a);
int  sub_001457C0(R3Obj *obj, float t0, float t1);   /* animation time in [t0,t1] */
void sub_000253D0(int id, int v);
/* Emitter-like record returned by 0x00113400. */
typedef struct R3Emit { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } R3Emit;
R3Emit *sub_00113400(R3Actor *act, int a);
extern float r3_frameUnits;                          /* 0x0042C858 */
void sub_000C56B0(R3Obj *obj);
int  sub_001456E0(R3Obj *obj, R3Actor *act, int a, int b);
void sub_0001D4E0(R3Obj *obj);
int  sub_000494D0(int id, const float *pos, int c);   /* returns the effect handle (0x0019B690 result) */
void sub_000C62A0(R3Obj *obj);
void sub_00025D50(int a, int b);

/* Condition lists: entries of 0x18 bytes, terminated by active == 0. */
typedef struct R3Cond { int32_t active; int32_t kind; uint8_t unk08[0x10]; } R3Cond;
typedef int (*R3CondFn)(R3Obj *obj, R3Actor *act, R3Cond *c);
extern R3Cond  *r3_condLists135[];                   /* 0x0031C858 */
extern R3CondFn r3_condFns135[];                     /* 0x0031C868 */

/* Leaf helpers (r3_3..). */
typedef struct R3Fsm { uint8_t unk00[0x4C]; int32_t state4C; int32_t i50; float f54; } R3Fsm;
typedef int (*R3FsmFn)(void *arg, R3Fsm *o);
extern R3FsmFn r3_fsmEnter32B1B0[11];               /* 0x0032B1B0 */
extern float   r3_points31F0E0[][4];                 /* 0x0031F0E0 */
typedef struct R3SndSlot { int16_t mode00; uint16_t unk02; void *p04; void *h08; } R3SndSlot;
typedef struct R3SndOwner { uint8_t unk00[0x20]; uint32_t flags20; uint8_t unk24[0x74 - 0x24]; R3SndSlot *slot74; } R3SndOwner;
typedef struct R3Rec4 { int32_t a; float f4; int32_t c; int32_t d; } R3Rec4;
void  sub_0018E7C0(void *p);
float sub_00082D70(void *p);
void *sub_00036750(void *o, int b);
void  sub_001AD9F0(float *dst, const float *a, const float *b);
float sub_001B27C0(const float *a, const float *b);

/* r3_4 types. */
typedef struct R3Flags74 {
    uint32_t flags;          /* +0x00 */
    float    f04, f08, f0C, f10; /* +0x04..+0x10 */
    void    *p14;            /* +0x14 */
    uint8_t  unk18[0x3C - 0x18];
    int32_t  i3C;            /* +0x3C */
} R3Flags74;
typedef struct R3Act74 { uint8_t unk00[0x74]; R3Flags74 *p74; } R3Act74;
typedef struct R3Model54 { uint8_t unk00[0x54]; int32_t i54; } R3Model54;
typedef struct R3Ent50 { uint8_t unk00[0x50]; float pos50[3]; } R3Ent50;
typedef struct R3Item150 { uint8_t unk00[0x0C]; uint8_t flags0C; uint8_t unk0D[0x150 - 0x0D]; } R3Item150;
typedef struct R3ItemList { int32_t count; uint32_t unk04; R3Item150 *items; } R3ItemList;
typedef struct R3Ctx42C8E4 { uint8_t unk000[0x1E8]; void *p1E8; } R3Ctx42C8E4;
extern R3Ctx42C8E4 *r3_ctx42C8E4;                    /* 0x0042C8E4 */
typedef struct R3Cond2 { int32_t active; int32_t kind; uint8_t unk08[0x10]; } R3Cond2;
typedef int (*R3Cond2Fn)(void *a, void *b, R3Cond2 *c);
extern R3Cond2  *r3_condLists155[];                  /* 0x0031EF60 */
extern R3Cond2Fn r3_condFns155[];                    /* 0x0031EFD8 */
int   sub_001671D0(R3Model54 *m, R3Act74 *a, int state);
void *sub_000ED630(int a, int b, int c, int d, const float *pos);
void  sub_0018C450(void *h, R3Ent50 *e, int a, int b);
void  sub_000C4DF0(void *o, int a, float b, int c, float d, float e, float f, const float *pos, float *v0, float *v1);
int   sub_000C46A0(float a, float b, float c, const float *pos, float *v0, float *v1);
void  sub_000C4D30(void *o, int a, float b, int c);
void  sub_000ED780(void *p);
void  sub_0001D030(void *a, void *b);
void  sub_00020170(void *p);

/* r3_5 types. */
typedef struct R3WorkB { uint32_t unk00; uint32_t flags04; } R3WorkB;
typedef struct R3ActorB { uint8_t unk000[0x278]; R3WorkB *work278; } R3ActorB;
typedef struct R3Spin {
    uint8_t  unk00[0x0C];
    uint32_t flags0C;        /* +0x0C */
    uint8_t  unk10[0x50 - 0x10];
    float    rot50[4];       /* +0x50 rotation, yaw at +0x54 */
    uint8_t  unk60[0x80 - 0x60];
    float    v80[4];         /* +0x80 */
} R3Spin;
typedef struct R3Cond3 { int32_t active; int32_t kind; uint8_t unk08[0x10]; } R3Cond3;
typedef int (*R3Cond3Fn)(void *a, void *b, R3Cond3 *c);
extern R3Cond3  *r3_condLists147[];                  /* 0x0031E558 */
extern R3Cond3Fn r3_condFns147[14];                  /* 0x0031E5B4 */
extern R3Cond3  *r3_condLists186[];                  /* 0x0032C288 */
extern R3Cond3Fn r3_condFns186[10];                  /* 0x0032C2C0 */
extern float r3_timer3F8410;                         /* 0x003F8410 */
extern float r3_frameDelta;                          /* 0x0042C85C */
void sub_00025C10(int a, int b);
void sub_00049700(int id, int r, int g, int b, const float *pos, int a, float size, int c);
void sub_00113190(R3Obj *obj, R3Actor *act, int a);
void sub_0018E700(void *h, int a);
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, const float *s, float a);
void sub_001AD9B0(float *dst, const float *a, const float *b);
int  r3_Count135E10(void);                           /* 0x00135E10 */

/* r3_6 */
void sub_00186470(R3Obj *obj, R3Actor *act, int state);   /* obj=EBX act=EDI state=stack */
void sub_001ADBA0(float *d, const float *s, float k);
void sub_0018D680(R3Spin *b, void *p, float k);
void sub_00189DE0(void *h, int a);
void sub_000F5D40(float *d, const float *s);
void r3_Reset18D9E0(R3Act74 *a, R3Spin *b);                /* 0x0018D9E0 a=EAX b=EDI */
void r3_Sound18E700(void *h, int on);                      /* 0x0018E700 */

/* Helpers recovered in r3_3..r3_5 that other r3 files call. */
void r3_SlotSound18E230(R3SndOwner *o, void *src, int on);       /* 0x0018E230 o=EAX */
int  r3_CheckConds186160(int table, void *a, void *b);           /* 0x00186160 table=EAX a=EBX b=EDI */
int  r3_CheckConds147270(int table, void *a, void *b);           /* 0x00147270 table=EAX a=EBX b=EDI */
int  r3_CheckConds1558F0(int table, void *a, void *b);           /* 0x001558F0 table=EAX a=EBX b=EDI */
int  r3_OtherBusy140170(void *self);                             /* 0x00140170 self=ESI */

/* r3_7..r3_9: animation controller pair (a = object, b = controller). */
typedef struct R3AnimH { uint8_t unk00[8]; int32_t cur08; } R3AnimH;
typedef struct R3Obj2 {
    uint8_t  unk00[8];
    int32_t  kind08;         /* +0x08 */
    uint32_t unk0C;
    uint32_t flags10;        /* +0x10 */
    uint8_t  unk14[0x30 - 0x14];
    R3AnimH *anim30;         /* +0x30 */
    uint8_t  unk34[0x3C - 0x34];
    void    *p3C;            /* +0x3C */
} R3Obj2;
typedef struct R3Ctl {
    uint8_t  unk00[0x50];
    int32_t  i50;            /* +0x50 */
    uint32_t unk54;
    float    f58;            /* +0x58 */
    uint32_t flags5C;        /* +0x5C */
    int32_t  anim60;         /* +0x60 current animation */
    float    f64;            /* +0x64 */
    int32_t  h68;            /* +0x68 */
    uint8_t  unk6C[0xB8 - 0x6C];
    int32_t  iB8;            /* +0xB8 */
} R3Ctl;
/* Pulsing value driver used by 0x0017C5D0/0x0017C670. */
typedef struct R3Pulse {
    R3Obj   *obj00;          /* +0x00 */
    R3Actor *act04;          /* +0x04 */
    uint8_t  unk08[0x24 - 8];
    int16_t  mode24;         /* +0x24 */
    uint16_t unk26;
    float    t28;            /* +0x28 */
    uint8_t  unk2C[0x4C - 0x2C];
    float    f4C;            /* +0x4C */
    int16_t  w50;            /* +0x50 */
} R3Pulse;
/* Record cleared by 0x0017E4D0 (0xBC bytes). */
typedef struct R3Rec17E {
    int32_t  i00[5];         /* +0x00..+0x10 */
    uint8_t  unk14[0x20 - 0x14];
    int32_t  i20, i24;       /* +0x20, +0x24 (-1 = none) */
    float    f28;            /* +0x28 */
    int32_t  i2C[6];         /* +0x2C */
    float    f44[6];         /* +0x44 */
    float    v5C[6][4];      /* +0x5C */
} R3Rec17E;
extern R3Rec17E r3_recs3FDED8[2];                    /* 0x003FDED8 */
extern R3Obj2  *r3_obj3FD7C4;                        /* 0x003FD7C4 */
extern float    r3_fps42C964;                        /* 0x0042C964 */
extern const float r3_vec32B6A8[4];                  /* 0x0032B6A8 */
int   sub_00083120(R3AnimH *h, int anim);
void  sub_000832D0(R3AnimH *h, int anim);
void  sub_0001D7F0(void *p, int anim, int c);
void  sub_00172B80(R3Obj2 *a, R3Ctl *b, int on);     /* a=EAX b=EBX on=stack */
int   sub_000CF6B0(void);
void  sub_000EE760(void *o, float v);
void  sub_0001EB80(R3Obj2 *a);
void  sub_0001E9B0(R3Ctx42C8E4 *c, R3Obj2 *a, int x, int y, int z);
void  r3_PlayAnim172C90(R3Ctl *b, R3Obj2 *a, int anim);   /* 0x00172C90 b=EAX a=ESI anim=EDI */
void  r3_Pulse17C5D0(R3Pulse *s);                         /* 0x0017C5D0 s=EAX */
void  r3_Tick17C670(R3Pulse *s);                          /* 0x0017C670 s=ESI */
void  r3_ClearRec17E4D0(R3Rec17E *r);                     /* 0x0017E4D0 r=EAX */
void  r3_SetState16C820(R3Act74 *a, R3Model54 *m, int state); /* 0x0016C820 a=EAX m=EDI */

/* Work block of the variant-D state machine (0x0017A2B0). */
typedef struct R3WorkD { uint32_t flags00; uint8_t unk04[0x18 - 4]; float f18; uint32_t unk1C; float f20; void *h24; int32_t h28; } R3WorkD;
int  sub_00048100(int h);
void r3_SetStateD(R3Obj *obj, R3Actor *act, int state);   /* 0x0017A2B0 obj=EBX act=ESI state=stack */

/* r3_1: callees with register arguments. */
void r3_SetStateA(R3Obj *obj, R3Actor *act, int state);         /* 0x00131310 obj=EBX act=EDI state=stack */
void r3_SetStateB(R3Obj *obj, R3Actor *act, int state);         /* 0x00135A70 obj=ESI act=EDI state=stack */
int  r3_CheckConds135730(int table, R3Obj *obj, R3Actor *act);  /* 0x00135730 table=EAX obj=EBX act=EDI */
#endif
