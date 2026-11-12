/* Area m1, part f: save/system data helpers. Names inferred. */
#ifndef M1F_H
#define M1F_H
#include "oogie.h"
void sub_001A8920(int *a, int *b, int *c, int *d, int *e, int *f);   /* fills six values (looks like a date/time) */
void sub_00054700_m1(uint16_t *rec);        /* 0x00054700 regargs: rec=ESI */
void sub_00054770_m1(uint8_t *p);            /* 0x00054770 regargs: p=EAX */
extern uint8_t *m1_ioBuf3E397C;              /* 0x003E397C */
void m1_StampTime54CC0(void);                /* 0x00054CC0 */
typedef int (*M1PollFn)(void);
void    *sub_001AD560(void);                 /* returns the current thread handle (compared with g_job.thread) */
int      a1a_MsgClearCb_m1(int which);       /* 0x001A85D0 */
int      a1a_MsgSetCb_m1(int which);         /* 0x001A8600 */
M1PollFn sub_001A85C0(M1PollFn fn);          /* swaps the poll callback, returns the old one */
int      a1a_Get40B0EC_m1(void);             /* 0x001A5390 */
void     sub_001A53F0(void);
void     sub_00102FA0();                     /* empty debug stub */
void     Frame_Present(void);                /* 0x001A7BA0 */
int      a50_JobPoll(void);                  /* 0x00057EE0 */
extern M1PollFn m1_savedPoll3E3F8C;          /* 0x003E3F8C */
int m1_JobFrame586E0(void);                  /* 0x000586E0 */
uint32_t sub_0004ECE0(int pad);
uint32_t sub_0004ED20(int pad);
void     sub_00048AF0(int sound);
extern int32_t   m1_ynDone3E3988;            /* 0x003E3988 1 once answered */
extern int32_t   m1_ynSel3E3964;             /* 0x003E3964 0 = yes, 1 = no */
extern uint8_t  *m1_save3E3934;              /* 0x003E3934 */
extern uint32_t *m1_padMasks2C4AE8;          /* 0x002C4AE8 [0] confirm, [1] cancel */
#endif
