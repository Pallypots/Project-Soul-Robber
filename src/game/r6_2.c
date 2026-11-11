/* Area r6: thin wrappers that pick a message-handler id (r6_2). Names inferred. */
#include "r6.h"

/* 0x000B2790: message handler 0 of 0x0B18D0. Stack args (msg st); calls 0x000B18D0 with EAX=msg ESI=st EDI=id. */
int r6_MsgB2790(int msg, R6MsgState *st) { return sub_000B18D0(msg, st, 0); }

/* 0x000B27B0: message handler 1 of 0x0B18D0. Stack args (msg st); calls 0x000B18D0 with EAX=msg ESI=st EDI=id. */
int r6_MsgB27B0(int msg, R6MsgState *st) { return sub_000B18D0(msg, st, 1); }

/* 0x000B27D0: message handler 2 of 0x0B18D0. Stack args (msg st); calls 0x000B18D0 with EAX=msg ESI=st EDI=id. */
int r6_MsgB27D0(int msg, R6MsgState *st) { return sub_000B18D0(msg, st, 2); }

/* 0x000B27F0: message handler 3 of 0x0B18D0. Stack args (msg st); calls 0x000B18D0 with EAX=msg ESI=st EDI=id. */
int r6_MsgB27F0(int msg, R6MsgState *st) { return sub_000B18D0(msg, st, 3); }

/* 0x000B2810: message handler 0 of 0x0B1B30. Stack args (msg st); calls 0x000B1B30 with EAX=msg EDI=st EBX=id. */
int r6_MsgB2810(int msg, R6MsgState *st) { return sub_000B1B30(msg, st, 0); }

/* 0x000B2830: message handler 1 of 0x0B1B30. Stack args (msg st); calls 0x000B1B30 with EAX=msg EDI=st EBX=id. */
int r6_MsgB2830(int msg, R6MsgState *st) { return sub_000B1B30(msg, st, 1); }

/* 0x000B2850: message handler 2 of 0x0B1B30. Stack args (msg st); calls 0x000B1B30 with EAX=msg EDI=st EBX=id. */
int r6_MsgB2850(int msg, R6MsgState *st) { return sub_000B1B30(msg, st, 2); }

/* 0x000B2870: message handler 3 of 0x0B1B30. Stack args (msg st); calls 0x000B1B30 with EAX=msg EDI=st EBX=id. */
int r6_MsgB2870(int msg, R6MsgState *st) { return sub_000B1B30(msg, st, 3); }

/* 0x000B2890: message handler 4 of 0x0B1B30. Stack args (msg st); calls 0x000B1B30 with EAX=msg EDI=st EBX=id. */
int r6_MsgB2890(int msg, R6MsgState *st) { return sub_000B1B30(msg, st, 4); }

/* 0x000B28B0: message handler 5 of 0x0B1B30. Stack args (msg st); calls 0x000B1B30 with EAX=msg EDI=st EBX=id. */
int r6_MsgB28B0(int msg, R6MsgState *st) { return sub_000B1B30(msg, st, 5); }

/* 0x000B3AD0: message handler 0 of 0x0B34F0. Stack args (msg st); calls 0x000B34F0 with EAX=msg ESI=st EDI=id. */
int r6_MsgB3AD0(int msg, R6MsgState *st) { return sub_000B34F0(msg, st, 0); }

/* 0x000B3AF0: message handler 1 of 0x0B34F0. Stack args (msg st); calls 0x000B34F0 with EAX=msg ESI=st EDI=id. */
int r6_MsgB3AF0(int msg, R6MsgState *st) { return sub_000B34F0(msg, st, 1); }

/* 0x000B3B10: message handler 2 of 0x0B34F0. Stack args (msg st); calls 0x000B34F0 with EAX=msg ESI=st EDI=id. */
int r6_MsgB3B10(int msg, R6MsgState *st) { return sub_000B34F0(msg, st, 2); }

/* 0x000B3B30: message handler 3 of 0x0B34F0. Stack args (msg st); calls 0x000B34F0 with EAX=msg ESI=st EDI=id. */
int r6_MsgB3B30(int msg, R6MsgState *st) { return sub_000B34F0(msg, st, 3); }

/* 0x000B48F0: message handler 14 sound 0xEB of 0x0B4010. Stack args (msg st); calls 0x000B4010 with ECX=msg EAX=st EDI=id snd=stack. */
int r6_MsgB48F0(int msg, R6MsgState *st) { return sub_000B4010(msg, st, 14, 0xEB); }

/* 0x000B4910: message handler 11 sound 0xE8 of 0x0B4010. Stack args (msg st); calls 0x000B4010 with ECX=msg EAX=st EDI=id snd=stack. */
int r6_MsgB4910(int msg, R6MsgState *st) { return sub_000B4010(msg, st, 11, 0xE8); }

/* 0x000B4930: message handler 15 sound 0xEC of 0x0B4010. Stack args (msg st); calls 0x000B4010 with ECX=msg EAX=st EDI=id snd=stack. */
int r6_MsgB4930(int msg, R6MsgState *st) { return sub_000B4010(msg, st, 15, 0xEC); }

/* 0x000B4950: message handler 12 sound 0xE9 of 0x0B4010. Stack args (msg st); calls 0x000B4010 with ECX=msg EAX=st EDI=id snd=stack. */
int r6_MsgB4950(int msg, R6MsgState *st) { return sub_000B4010(msg, st, 12, 0xE9); }

/* 0x000B4970: message handler 16 sound 0xED of 0x0B4010. Stack args (msg st); calls 0x000B4010 with ECX=msg EAX=st EDI=id snd=stack. */
int r6_MsgB4970(int msg, R6MsgState *st) { return sub_000B4010(msg, st, 16, 0xED); }

/* 0x000B4990: message handler 13 sound 0xEA of 0x0B4010. Stack args (msg st); calls 0x000B4010 with ECX=msg EAX=st EDI=id snd=stack. */
int r6_MsgB4990(int msg, R6MsgState *st) { return sub_000B4010(msg, st, 13, 0xEA); }

/* 0x000B49B0: message handler 17 sound 0xEE of 0x0B4010. Stack args (msg st); calls 0x000B4010 with ECX=msg EAX=st EDI=id snd=stack. */
int r6_MsgB49B0(int msg, R6MsgState *st) { return sub_000B4010(msg, st, 17, 0xEE); }

/* 0x000B48C0: start handler 10 (sound 0xE7) on st, then run 0xB40A0 on it; returns 1.
   Calls 0x000B4010 with ECX=msg EAX=st EDI=10 snd=stack and 0x000B40A0 with EDI=st. */
int r6_MsgB48C0(int msg, R6MsgState *st)
{
    sub_000B4010(msg, st, 10, 0xE7);
    sub_000B40A0(st);
    return 1;
}
