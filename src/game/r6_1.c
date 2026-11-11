/* Area r6: thin wrappers that pick a message-handler id (r6_1). Names inferred. */
#include "r6.h"

/* 0x000ACF20: message handler 0 of 0x0ABBF0. Stack args (msg st); calls 0x000ABBF0 with EAX=msg ESI=st ECX=id. */
int r6_MsgACF20(int msg, R6MsgState *st) { return sub_000ABBF0(msg, st, 0); }

/* 0x000ACF40: message handler 3 of 0x0ABBF0. Stack args (msg st); calls 0x000ABBF0 with EAX=msg ESI=st ECX=id. */
int r6_MsgACF40(int msg, R6MsgState *st) { return sub_000ABBF0(msg, st, 3); }

/* 0x000AE790: message handler 0 of 0x0ABBF0. Stack args (msg st); calls 0x000ABBF0 with EAX=msg ESI=st ECX=id. */
int r6_MsgAE790(int msg, R6MsgState *st) { return sub_000ABBF0(msg, st, 0); }

/* 0x000AE7B0: message handler 4 of 0x0ABBF0. Stack args (msg st); calls 0x000ABBF0 with EAX=msg ESI=st ECX=id. */
int r6_MsgAE7B0(int msg, R6MsgState *st) { return sub_000ABBF0(msg, st, 4); }

/* 0x000AE7D0: message handler 6 of 0x0AD8C0. Stack args (msg st); calls 0x000AD8C0 with EAX=msg ESI=st EDI=id. */
int r6_MsgAE7D0(int msg, R6MsgState *st) { return sub_000AD8C0(msg, st, 6); }

/* 0x000AE7F0: message handler 7 of 0x0AD8C0. Stack args (msg st); calls 0x000AD8C0 with EAX=msg ESI=st EDI=id. */
int r6_MsgAE7F0(int msg, R6MsgState *st) { return sub_000AD8C0(msg, st, 7); }

/* 0x000AE810: message handler 8 of 0x0AD8C0. Stack args (msg st); calls 0x000AD8C0 with EAX=msg ESI=st EDI=id. */
int r6_MsgAE810(int msg, R6MsgState *st) { return sub_000AD8C0(msg, st, 8); }

/* 0x000AE830: message handler 9 of 0x0AD8C0. Stack args (msg st); calls 0x000AD8C0 with EAX=msg ESI=st EDI=id. */
int r6_MsgAE830(int msg, R6MsgState *st) { return sub_000AD8C0(msg, st, 9); }
