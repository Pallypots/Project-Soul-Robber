#ifndef A60_H
#define A60_H
#include "oogie.h"

/* Area a60 (0x00060000..0x0007FFFF). All names inferred. */

/* Six consecutive buffer pointers carved from one block (0x00062050). */
typedef struct A60Slices {
    int32_t  unk00;
    int32_t *s[6];          /* +0x04..+0x18 */
} A60Slices;

/* Text cursor object used by the 0x00076xxx helpers. */
typedef struct A60Text {
    uint8_t  unk00[0x28];
    int32_t  len;           /* +0x28 */
    char     buf[0x800];    /* +0x2C */
    int32_t  pos;           /* +0x82C */
} A60Text;

typedef struct A60Rect {
    int16_t  unk00[2];
    int16_t  x0, y0;        /* +0x04 */
    int16_t  x1, y1;        /* +0x08 */
} A60Rect;

typedef struct A60Timer {
    int16_t  kind;          /* +0x00 */
    int16_t  unk02;
    uint8_t  unk04[0x0C];
    float    value;         /* +0x10 */
} A60Timer;

/* Linked-list node owned by the 0x00075xxx effect lists. */
typedef struct A60Node {
    uint8_t  unk00[0x10];
    void    *data;          /* +0x10 */
    int32_t  unk14;
    int32_t  handle;        /* +0x18 */
} A60Node;

typedef struct A60Obj {
    uint8_t  unk00[0x8C];
    int32_t  type;          /* +0x8C */
} A60Obj;

extern float   a50_frameUnits;          /* 0x0042C858 */

extern int32_t a60_mode3E64C0;          /* 0x003E64C0 */
extern int32_t a60_state3E60D4;         /* 0x003E60D4 */
extern uint8_t *a60_base3E60C8;         /* 0x003E60C8 */
extern void   *a60_res3E64BC;           /* 0x003E64BC */
extern uint8_t *a60_work42C5E8;         /* 0x0042C5E8 */
extern void   *a60_res3E6540;           /* 0x003E6540 */
extern int32_t a60_h3E660C, a60_h3E6608, a60_h42C6F0;
extern int32_t a60_val3E65FC, a60_val3E6938;
extern int32_t a60_cmd3E6610, a60_arg3E661C;
extern uint8_t a60_phase428F81;
extern int32_t a60_h3E694C[2], a60_h3E6940[3];
extern uint8_t a60_list3E6994[16], a60_list3E6984[16], a60_list3E6974[16];
extern void   *a60_table3E69A4;
extern uint8_t a60_table266AD8[];
extern int32_t a60_h3E64FC[5], a60_h3E6510[4], a60_h3E6520[2], a60_h3E653C;
extern int32_t a60_flag428F78;
extern int32_t a60_v3E6620, a60_v42C5EC, a60_v428F74, a60_v3E6614, a60_v3E68A8;

void  sub_001B9FC0(int handle);
void *sub_00084C00(void *p, int a);
void  sub_0006A970(void);
void  sub_0006AB70(void);
void  sub_0006AD80(void);
void  sub_001B9720(void);
void  sub_0003D860(void *list);
void *sub_0003DBC0(void *list, int a, void *key);
void  sub_0003D8C0(void *node);
void  sub_00048250(int h);
void  sub_0006EA20(int v);
int   sub_00073A50(int a);
int   sub_00073660(int a);
int   sub_00073030(int a);
void  sub_00073FC0(void);
void  sub_00073C80(void);
void  sub_00074730(void);

/* Menu work block reached through 0x003E60CC. */
typedef struct A60Menu {
    uint8_t  unk000[0x968];
    uint8_t  anim968[8];    /* +0x968 animation player */
    A60Text *text970;       /* +0x970 */
    uint8_t  unk974[0x988 - 0x974];
    int32_t  anim988;       /* +0x988 */
} A60Menu;

/* Effect list nodes allocated in tex_ex.c (0x00075420: 0x24 bytes). */
typedef struct A60EffNode {
    uint8_t  link[0x0C];
    A60Obj  *obj;           /* +0x0C */
    int32_t  a10;           /* +0x10 */
    int32_t  a14;           /* +0x14 */
    int32_t  a18;           /* +0x18 */
    int32_t  a1C;           /* +0x1C */
    float    t20;           /* +0x20 */
} A60EffNode;

/* 0x00075150: 0x20-byte node. */
typedef struct A60EffNode20 {
    uint8_t  link[0x0C];
    A60Obj  *obj;           /* +0x0C */
    int32_t  a10;           /* +0x10 */
    int32_t  a14;           /* +0x14 */
    int32_t  a18;           /* +0x18 */
    float    t1C;           /* +0x1C */
} A60EffNode20;

typedef struct A60Model {
    uint8_t  unk000[0x44];
    int32_t  handle;        /* +0x44 */
    uint8_t  unk048[0x1B8 - 0x48];
    uint8_t  flags;         /* +0x1B8 */
    uint8_t  unk1B9[3];
    float    p1BC, p1C0, p1C4, p1C8, p1CC; /* +0x1BC..+0x1CC */
} A60Model;

typedef struct A60Save { int32_t w[0x38E]; } A60Save;

extern A60Menu *a60_menu3E60CC;          /* 0x003E60CC */
extern int32_t a60_v3E60F4, a60_v3E60D8, a60_v3E60DC, a60_v3E60E0;
extern int16_t a60_w3E60F8, a60_w3E60FA;
extern uint8_t a60_b42A026;
extern uint32_t a60_flags413428;
extern int32_t a60_hA3E64C4[3], a60_hB3E64D0[3], a60_h3E64DC, a60_hC3E64E0[3], a60_hD3E64EC[3];
extern int32_t a60_h3E68B8[32];
extern int8_t  a60_lang413145;
extern uint8_t a60_b428F45, a60_b428F80;
extern int32_t a60_chFlags[2], a60_chVol[2], a60_chId[2];
extern uint32_t *a60_chReg650[2], *a60_chReg660[2];
extern int32_t a60_v3E7398, a60_v3E7A4C, a60_h3E7500[2], a60_h3E69F0, a60_h3E69F4;
extern void   *a60_p3E6A04;
extern int32_t a60_v3E7538, a60_v3E7530, a60_v3E7508, a60_v3E750C, a60_v3E7510, a60_v3E7514;
extern uint8_t a60_buf3E75F4[1], a60_buf3E7690[1], a60_buf3E772C[1], a60_buf3E77C8[1];
extern uint32_t a60_pad3E7540[4];
extern int32_t a60_v3E74B8;
extern int32_t a60_v3E7A50, a60_v3E7A54, a60_v3E83E0, a60_v3E83E4, a60_v3E83E8;
extern uint8_t a60_anim3E7A58[0x20];
extern uint32_t a60_flags3E7A78;
extern char    a60_name3E9298[];
extern A60Save a60_save3E83F0, a60_save4326A0;
extern const char a60_srcTexEx[];       /* 0x0026F090 "\Project\nightmareXbox\app\tex_ex.c" */

void  sub_00018620(void *anim, int id);
void  a60_FlagBit2(uint32_t *f, int on);
void  sub_0003FAB0(void *anim, void *owner);
void  sub_00075F00(A60Menu *m);
void  sub_000603C0(int v);
int   sub_000D9A70(int id);
void  sub_00058540(void (*fn)(void), int a);
void  sub_00065F00(void);
int   sub_00057E90(void);
void  sub_000580D0(void);
int   sub_00079460(void);
void  sub_0006D910(void);
void  sub_00053CA0(int a);
void  sub_00079340(void);
int   sub_000E3370(void);
int   sub_000E0770(int lang);
void  sub_000E3A20(int a);
void *sub_00053AB0(int size, const void *file, int line);
void  sub_0003D880(void *list, void *node);
void *sub_0003DC10(void *node, int a, void *key);
void  sub_001A85D0(int v);
int   sub_001A8580(int v, int a, int b);
void  sub_001A85A0(int v, int id);
void  sub_001A8600(int v);
int   sub_000529F0(void);
void  sub_0004F5D0(int v);
void  sub_000150B0(void *p, int n);
uint32_t sub_001A9130(int pad);
void  sub_0019B9E0(void);
void  sub_00048590(void);
int   sub_00047950(void);
void  sub_0019B9F0(void);
void  sub_0019BEB0(int v);
void  sub_00052840(int v);
const char *sub_000133E0(int id);
int   sub_00013480(int id);
#endif
