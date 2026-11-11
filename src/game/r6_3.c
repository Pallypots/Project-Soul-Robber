/* Area r6: thin wrappers that pick a message-handler id (r6_3). Names inferred. */
#include "r6.h"

/* 0x000B64B0: message handler 0 of 0x0B6300. Stack args (msg st); calls 0x000B6300 with EAX=msg ESI=st EDI=id. */
int r6_MsgB64B0(int msg, R6MsgState *st) { return sub_000B6300(msg, st, 0); }

/* 0x000B64D0: message handler 1 of 0x0B6300. Stack args (msg st); calls 0x000B6300 with EAX=msg ESI=st EDI=id. */
int r6_MsgB64D0(int msg, R6MsgState *st) { return sub_000B6300(msg, st, 1); }

/* 0x000B64F0: message handler 2 of 0x0B6300. Stack args (msg st); calls 0x000B6300 with EAX=msg ESI=st EDI=id. */
int r6_MsgB64F0(int msg, R6MsgState *st) { return sub_000B6300(msg, st, 2); }

/* 0x000B6510: message handler 3 of 0x0B6300. Stack args (msg st); calls 0x000B6300 with EAX=msg ESI=st EDI=id. */
int r6_MsgB6510(int msg, R6MsgState *st) { return sub_000B6300(msg, st, 3); }

/* 0x000B6530: message handler 4 of 0x0B6300. Stack args (msg st); calls 0x000B6300 with EAX=msg ESI=st EDI=id. */
int r6_MsgB6530(int msg, R6MsgState *st) { return sub_000B6300(msg, st, 4); }

/* 0x000B8900: message handler 3 of 0x0B8800. Stack args (msg st); calls 0x000B8800 with EAX=msg ESI=st EDI=id. */
int r6_MsgB8900(int msg, R6MsgState *st) { return sub_000B8800(msg, st, 3); }

/* 0x000B8920: message handler 4 of 0x0B8800. Stack args (msg st); calls 0x000B8800 with EAX=msg ESI=st EDI=id. */
int r6_MsgB8920(int msg, R6MsgState *st) { return sub_000B8800(msg, st, 4); }

/* 0x000B8940: message handler 1 of 0x0B8800. Stack args (msg st); calls 0x000B8800 with EAX=msg ESI=st EDI=id. */
int r6_MsgB8940(int msg, R6MsgState *st) { return sub_000B8800(msg, st, 1); }

/* 0x000B8960: message handler 5 of 0x0B8800. Stack args (msg st); calls 0x000B8800 with EAX=msg ESI=st EDI=id. */
int r6_MsgB8960(int msg, R6MsgState *st) { return sub_000B8800(msg, st, 5); }

/* 0x000B8980: message handler 2 of 0x0B8800. Stack args (msg st); calls 0x000B8800 with EAX=msg ESI=st EDI=id. */
int r6_MsgB8980(int msg, R6MsgState *st) { return sub_000B8800(msg, st, 2); }

/* 0x000BA8C0: message handler 0 sound 0xCE of 0x0BA6F0. Stack args (msg st); calls 0x000BA6F0 with EAX=msg EDI=st ESI=id snd=stack. */
int r6_MsgBA8C0(int msg, R6MsgState *st) { return sub_000BA6F0(msg, st, 0, 0xCE); }

/* 0x000BA8E0: message handler 2 sound 0xCF of 0x0BA6F0. Stack args (msg st); calls 0x000BA6F0 with EAX=msg EDI=st ESI=id snd=stack. */
int r6_MsgBA8E0(int msg, R6MsgState *st) { return sub_000BA6F0(msg, st, 2, 0xCF); }

/* 0x000BA900: message handler 4 sound 0xD0 of 0x0BA6F0. Stack args (msg st); calls 0x000BA6F0 with EAX=msg EDI=st ESI=id snd=stack. */
int r6_MsgBA900(int msg, R6MsgState *st) { return sub_000BA6F0(msg, st, 4, 0xD0); }

/* 0x000BB750: message handler 0 of 0x0BB1C0. Stack args (msg st); calls 0x000BB1C0 with EAX=msg ESI=st EDI=id. */
int r6_MsgBB750(int msg, R6MsgState *st) { return sub_000BB1C0(msg, st, 0); }

/* 0x000BB770: message handler 1 of 0x0BB1C0. Stack args (msg st); calls 0x000BB1C0 with EAX=msg ESI=st EDI=id. */
int r6_MsgBB770(int msg, R6MsgState *st) { return sub_000BB1C0(msg, st, 1); }

/* 0x000BB790: message handler 2 of 0x0BB1C0. Stack args (msg st); calls 0x000BB1C0 with EAX=msg ESI=st EDI=id. */
int r6_MsgBB790(int msg, R6MsgState *st) { return sub_000BB1C0(msg, st, 2); }

/* 0x000BB7B0: message handler 3 of 0x0BB1C0. Stack args (msg st); calls 0x000BB1C0 with EAX=msg ESI=st EDI=id. */
int r6_MsgBB7B0(int msg, R6MsgState *st) { return sub_000BB1C0(msg, st, 3); }
