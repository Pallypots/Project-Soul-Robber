#ifndef R6_H
#define R6_H
#include "oogie.h"
/* Area r6: register-argument functions in 0x00060000..0x000D0000. All names inferred.
   Register mappings of callees are in the comments and in config/function_states_r6.csv. */

/* Two- or three-word state blocks driven by message handlers (msg 0 = clear, 1 = start...). */
typedef struct R6MsgState { uint32_t flags; int32_t step; int32_t extra; } R6MsgState;

/* Message handlers: return 1 when handled. Register inputs given per handler. */
int sub_000ABBF0(int msg, R6MsgState *st, int id);           /* msg=EAX st=ESI id=ECX */
int sub_000AD8C0(int msg, R6MsgState *st, int id);           /* msg=EAX st=ESI id=EDI */
int sub_000B18D0(int msg, R6MsgState *st, int id);           /* msg=EAX st=ESI id=EDI */
int sub_000B1B30(int msg, R6MsgState *st, int id);           /* msg=EAX st=EDI id=EBX */
int sub_000B34F0(int msg, R6MsgState *st, int id);           /* msg=EAX st=ESI id=EDI */
int sub_000B4010(int msg, R6MsgState *st, int id, int snd);  /* msg=ECX st=EAX id=EDI snd=stack */
void sub_000B40A0(R6MsgState *st);                           /* st=EDI */
int sub_000B6300(int msg, R6MsgState *st, int id);           /* msg=EAX st=ESI id=EDI */
int sub_000B8800(int msg, R6MsgState *st, int id);           /* msg=EAX st=ESI id=EDI */
int sub_000BA6F0(int msg, R6MsgState *st, int id, int snd);  /* msg=EAX st=EDI id=ESI snd=stack */
int sub_000BB1C0(int msg, R6MsgState *st, int id);           /* msg=EAX st=ESI id=EDI */
/* Object with a list of items whose targets get its transform (0x0007A980). */
typedef struct R6Target { uint8_t unk00[0x30]; float mat30[3]; float f3C; } R6Target;
typedef struct R6ListItem { uint8_t unk00[0x20]; R6Target *target20; } R6ListItem;
typedef struct R6ListNode { struct R6ListNode *next; uint8_t unk04[8]; R6ListItem *item0C; } R6ListNode;
typedef struct R6List { uint32_t unk00; R6ListNode *first04; } R6List;
typedef struct R6ListOwner {
    uint8_t unk000[0x184];
    float   mat184[32];      /* +0x184 */
    R6List *list204;         /* +0x204 */
} R6ListOwner;
void r6_Mat1ADB40(float *dst, const float *src);             /* 0x001ADB40 */
void r6_ObjRefreshList(R6ListOwner *obj);                    /* 0x0007A980 obj=EBX */
#endif
