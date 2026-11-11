/* Canonical prototypes of callees shared by several recovery areas.
 * Reference build OOGIE-XBOX-US-RETAIL. Names inferred. Each signature was
 * decided from the callee's entry code (tools/xdis.py) and its callers
 * (consolidation pass 2026-11-11); pointer parameters whose pointee differs
 * between areas are void *. Area headers include this file instead of
 * redeclaring these functions. */
#ifndef SHARED_DECLS_H
#define SHARED_DECLS_H
#include "oogie.h"

void *sub_00012300(void *a, int b, int c, int d, int e); /* Writes packet header at [p1], returns p1+0x10; p2:p3 compared as a 64-bit 0x42 and p4:p5 forwarded to 0x1A69C0 as a 64-bit value (kind int). */
void sub_00014D00(void *p, void *obj, int a); /* p2 stored at +0x3C which 0x14E30/0x17AE0 dereference ([+0x3C]+0x24), so p2 is ptr not int; p3 stored at +0x40. */
void sub_00014E30(void *p, int a, float b, float c, int d); /* p2 index into [[p1+0x3C]+0x24], p3/p4 movss stored to +0/+4, p5 stored at +0x18. */
void *sub_00017AE0(void *v, void *s); /* p1 is passed through unchanged and returned (0x15150 never reads it); callers thread a command/packet pointer (r6j_2 void *p), so a is ptr; p2 track deref. */
void *sub_00017C00(void *v, void *s); /* Same shape as 0x17AE0 with 0x16B80; p1 passthrough command pointer returned, p2 track deref. */
void *sub_0001D0F0(void *a, int b); /* Returns items+idx*0x180 or idx*0x108 or 0. */
void *sub_0001D220(void *list, int i); /* Returns [p1+8]+p2*0x150 or 0. */
void *sub_0001D290(void *o, int k); /* Walks +0x3C list comparing [node] with p2; returns node. */
void *sub_0001D960(void *obj, int kind); /* Walks list at [a1+0x40] comparing [node]==a2 and returns node ptr or 0; abc int return is wrong */
int sub_0001DA90(void *k, const void *src); /* Thunk to 0x83520: a2 passed to 0x13480 as name string; a1 deref ([a1+0x10]/[a1+0xC]); returns count in esi or 0; rbg void and r6c int a2 wrong */
void sub_0001EB80(void *h); /* Walks +0x3C chain releasing +0x20/+0x28/+0x30->+0x14 objects. */
void sub_0001EE80(void *o, void *fn); /* p1 deref; p2 stored at [+4] of the found entry; every caller passes the callback 0x196B40 */
void sub_0001EEC0(void *a, float b); /* p2 loaded with movss and stored at +0x18. */
void sub_0001EFE0(void *p, void *owner, void *a); /* All three null-checked and dereferenced. */
int sub_0001F070(void *o, int k); /* p2 range 0..1 index; returns 1 or 0. */
void sub_00022380(void *c, const void *a, void *ctx); /* a1/a2 node lists deref'd and copied; a3 never read in body but all callers pass a context pointer; eax not set at ret */
int sub_00022630(void *o, const void *path); /* p2 filename to 0x53BC0/0x37570; p1 forwarded as arg1 of 0x21B00, which dereferences [p1+0x3C]; callers pass object pointers */
void sub_0002CF50(void *p1); /* Infinite loop; p1 passed to 0x1A1060 as target pointer. */
void *sub_0002E8C0(void *pkt, int p2, int p3, int p4, void *p5, void *p6, const void *fmt, ...); /* Variadic printf-style: fmt into vsnprintf(buf;0x3ff;fmt;&va) then 0x2E560(a1..a6;1.0f;2.0f;buf); a5/a6 optional out-ptrs written by 0x2E560; returns the advanced draw packet (0x3E550 returns it as its own result) */
void *sub_000324B0(void *a); /* Push-buffer cmd pointer in and returned (passthrough or from 0x17AE0 chain); callers do cmd = f(cmd); a9b int decl wrong */
int sub_000335D0(void *p1, void *p2); /* Pool-foreach callback (0x36B30 cb type takes 2 args): uses only a1 (+0x10 passed on) and returns 0; a2 unused */
void sub_00033A70(void *p); /* Recursive chain free via +0x10. */
void sub_00033C20(void *p); /* Tail jmp to 0x36B10 (eax garbage there) with p1-0x10. */
void *sub_00033DC0(void *p, int id); /* Walks [a1+4] list matching [[n+0xC]+0x10]==a2 and returns [n+0xC] or 0; r6f int first param wrong */
int sub_00034270(void *entry, void *ctx); /* Callback: a1 flags at +0x24; a2 deref'd ([a2]) when nonnull; always returns 0; a3b no-param decl wrong */
int sub_00034B50(void *p1, void *p2); /* Pool-foreach callback (0x36B30 cb type takes 2 args): uses only a1 (+0x10 to 0x33C20) and returns 0; a2 unused */
void *sub_00035D20(void *m, void *o, int from, int to, int flags); /* Returns first node (esi); p2..p5 forwarded to 0x35C60; both callers pass an object pointer as p2 (0x35D80 its obj, 0x35DD0 its void *o), so p2 is ptr not int. */
void *sub_00035DD0(void *p, void *a, int b, int c); /* Returns 0 or the R1dNode* from 0x35D20 (call;ret); DEF ret int. */
int sub_00036B30(void *base, int count, void *cb, void *z); /* p3 called indirectly (fn ptr); returns callback result or 0. */
void sub_00036C00(int a, int b, float c); /* p2 indexes 16-byte table; p3 movss. */
void sub_00036F40(float a, float b, float c, float d); /* Four movss stores. */
int sub_000374C0(const void *a); /* p1 path passed to file open; returns size or -1. */
void *sub_00037550(const void *a, void *buf); /* Returns 0x373A0(a1;0;0;a2) which returns an allocated buffer/a1 or 0; a1 passed to loader as name; a6b int kinds and r6b void wrong. Round 2: a2 is forwarded verbatim into 0x373A0's 4th slot, the destination buffer (0x373A0 tests [esp+0x10] for 0 and allocates, else loads into it and returns it), so a2 is ptr; callers pass 0 */
void *sub_00037570(const void *name, int align); /* Reads only [esp+4] and returns 0x373A0(p1,0,0,0); result is a buffer callers deref (0x22630 compares [eax] with @CPB), p1 is the filename; DEF void(int) wrong (callers push a 2nd arg it ignores). [arity kept at 2: original callers push that many args; extra args unused by the callee] */
void *sub_00037780(void); /* Returns constant address 0x42CB20; r6h int wrong */
void sub_00037BB0(int a, void *b); /* Stores a2 into table 0x3DA2D8[a1]; caller 0x89C10 pushes the address [esi+0x4C]+0x78 as a2 */
int sub_00038070(int a); /* Waits on flag then swaps global 0x2C4460 with a1 and returns old value; most decls void (callers ignore result) */
void sub_000385D0(void *dst, const void *src); /* Both args used as matrix addresses (R1eMat is an array type, decays to pointer). */
void *sub_00038F10(void *p); /* Writes packet at p1 and returns end pointer. */
void *sub_000390A0(void); /* Returns constant address 0x3DCDA8; r6h int wrong */
void *sub_000396E0(void *v); /* a1 is push-buffer pointer passed through 0x12300 encoder chain and the new pointer is returned; r1c/r1d/r1e int kinds wrong */
void *sub_0003D090(int a); /* Returns [0x3DDCC0 + a*4], the group header pointer table (a4c_groupHdr); callers compare it with object pointers and store it in pointer fields */
void *sub_0003DBC0(void *list, void *match, void *key); /* p2 callback (default 0x3DBA0); returns matching node or 0. */
void *sub_0003DC10(void *node, void *a, int key); /* Iterates [node] list from a1 calling a2 (fnptr; default 0x3DBA0) with (node;a3) and returns node; a3 compared to [n+0xC] as key */
int sub_0003ED50(void *a, int b); /* p1 menu deref; p2 flag bits; returns 0/1/-1. */
int sub_0003EF00(void *e, int v); /* a1 menu entry deref'd; a2 pad index *0x4C into 0x42CA20; returns 0 or 1 on all paths; r1h void wrong */
int sub_0003F570(void *o); /* Returns 0 or 0x3EF00 result (int). */
int sub_0003F770(void *m); /* Returns 0x3ED50(p1,0) whose p1 is dereferenced (menu struct), so p1 is ptr not int. */
void *sub_0003F780(void *ev, void *o, int mode); /* Returns p1 (draw ctx packet) or 0x3F650(p1,o) which returns 0x2E8C0's ctx; menu handlers thread ctx through it; DEF has int a and int ret. */
void *sub_0003F8B0(void *a, void *b, int c); /* a1 deref'd array header; a2 deref'd ([a2+4] fnptr); a3 stored; returns new 0x3C-byte element ptr or 0; a3c/r1h kinds wrong */
void *sub_0003F9C0(void *a, const void *b); /* Returns 0x3F8B0(a1;a2;0) which returns an element ptr; all int returns wrong; a5b/r1d first-int wrong */
void *sub_0003FA70(void *a, int b); /* Returns a1 + offset table [a1+4+a2*4] (pointer arithmetic on a1); adc/r2b/r6d 5-param decls are wrong (misparsed nested calls) */
void *sub_0003FBD0(void *a, void *p); /* Returns ctx, or tail jmp to r6d_TextDraw(ctx, [p2+8]). */
void sub_0003FCB0(void *t, void *a, int b, float c, float d); /* Calls 0x3FAF0(a1;a2;0;a3;a4;a5): a2 deref'd as byte string by 0x76330; a3 flag byte; a4/a5 read with movss; adc/r2b/r6d 2-param decls wrong */
int sub_0003FCE0(void *p); /* a1 deref'd ([a1+8]/[a1+4]); returns 0 or 1 on all paths though callers ignore it; rtc 3-param decl wrong */
void sub_00047A80(int v); /* a1 compared to ranges 3..0x18 and passed to 0x199C10/0x19B5C0; eax leftover; r1 int return wrong */
void sub_00047BF0(int a); /* p1 forwarded to void stop functions; eax otherwise -1 or garbage. */
unsigned int sub_00048530(int id); /* Returns table field or 0. */
unsigned int sub_00048560(int id); /* Returns table field or 0. */
void sub_000488F0(int a, int b); /* Stack args loaded into EBX/EDI for regarg callee 0x484B0; returns 0x47A80 whose eax is a stale arg on the <3 path, and both callers ignore it, so ret void not int. */
int sub_00048A00(int a, int b); /* a1 compared to globals; a2 forwarded to 0x47BF0; returns [0x3DFECC] or 0 or callee result; r6f_7 tests ==-1 */
int sub_00048AF0(int k); /* Returns sound handle from 0x19B690(a1;vol(a1);0x5A;0x80;0x80;0x80); callers ignore it */
int sub_000494D0(int id, const void *pos, int c); /* a1 sound id; a2 vector ptr passed to 0x1AD9F0/0x48F10; a3 int to 0x48F10; returns handle esi or 0x19B690 result; void decls wrong */
int sub_00049700(int id, int r, int g, int b, const void *pos, int a, float size, int c); /* a5 passed in eax as vec ptr to 0x48B70 and to 0x48F10; a7 float; returns -1 or handle; r3/r4c void wrong */
unsigned int sub_0004ECE0(int kind); /* Returns dword table [0x42CA38 + a1*0x4C] used as pad button bits; r4e void wrong */
int sub_0004F4E0(void); /* No args; returns 0. */
int sub_0004F680(int id); /* Arg is a range-checked index (0..0x21E) into table 0x2C890C; returns 16-aligned size or 0; r1c (void*) param and r2e ptr return are wrong */
int sub_0004FA70(int id, void *buf); /* Returns -1 or 0; p1 range-checked id; p2 stored to 0x3E0DC4, callers pass the load buffer from 0x53820/0x53AB0 */
int sub_0004FAE0(int id, void *buf); /* As 0x4FA70 (mode 4) */
int sub_000512D0(int id, void *mem); /* Arg1 is a slot index shl 5 into 0x2C8904; arg2 is a buffer (allocated if NULL then filled and stored); returns -1 on open failure else 0 and a caller tests !result */
void *sub_00052840(void *p); /* Never touches its arg except to return it in eax (after 16 calls to 0x1B29F0); the only caller passes the address 0x402788 */
int sub_00052A00(int lang); /* Stores p1 and returns previous mode. */
int sub_000535F0(int a, int b, int c); /* ECX=[esp+4] slot plus stack a b into 0x53400 then returns [eax+0xC]; callers ignore result */
void *sub_00053820(int pool, int size, void *a, int b); /* heap idx -> table then tail jmp 0x47390(heap,size,file,line) returning block ptr; 0x7F480 passes string 0x2608A2 as p3 so p3 is ptr (def says int) */
void *sub_00053AB0(int size, const void *a, int line); /* call 0x47390(curheap,size,file,line) returns ptr; callers pass (0x10,0x26F090,0xA2) so p2 is file ptr (def int) */
int sub_00053CA0(int a); /* Arg is a flag (zero clears state); every path sets eax (0 or queue count) and callers loop while(result); a60/r6g void returns are wrong */
int sub_00054040(void); /* returns saved result of 0x1A8680 in esi across the pause calls; no args */
void *sub_00057E90(void); /* returns global 0x3E3F7C which callers compare against function addresses (JobFunc) */
int sub_00058540(void *fn, void *arg); /* Arg1 callback stored at 0x3E3F7C (NULL check returns 0); arg2 stored at 0x3E3F80 as callback context; returns handle 0x3E3F68 or 0 so all void decls are wrong; r1h int arg2 wrong */
int sub_000586E0(int arg); /* Never reads its stack arg (callers push 0 so cdecl unused int kept); both paths xor eax and callers compare result ==0 so returns int */
int sub_000588D0(int h); /* p1 job id to lookup 0x57F80; returns 0 or -1 */
void *sub_0005A990(void *o, void *fn, void *ctx); /* p1 goes to 0x3F8B0 which derefs it and returns slot ptr; caller passes (o->child, sub_0005D030, r1c_ctx2DD624 array) */
void sub_0005BC50(void *p); /* p1 compared against slot owners and +0x14/-0x10 passed on; null path leaves eax garbage */
void sub_0005BE30(void *a); /* p1 compared against slot owners; eax garbage on exit */
int sub_0005C430(void *p); /* Arg dereferenced ([eax+4] list head); every path ends xor eax so returns int 0; adc/r4d/rtc int param wrong */
void sub_0005CAF0(void *p); /* Arg dereferenced and initialised (16 entries at +0x150); eax is leftover from callee; a5b int return wrong */
int sub_0005D030(int p1, void *p2); /* p1 switch index 0..5, p2 deref; all paths return 0 */
int sub_0005EB10(int a, int b); /* p2 indexes table (<0x40), p1 passed to 0x5EA60 which returns -1 or slot index */
void *sub_000727E0(void *v, void *obj); /* Arg1 is a GPU command-buffer pointer passed to 0x12300 whose result flows through 0x72280/0x72180 and is returned; arg2 is dereferenced struct; callers do cmd=f(cmd obj); r1d int/int wrong */
void sub_00075F00(void *t); /* Arg spun on until non-NULL then fields at +4..+0x8CC written; no return value; a4c int param wrong */
void sub_00076060(void *h); /* clears +0x28/+0x2C/+0x82C; eax is stale p1 */
void *sub_00079480(void *v); /* Arg is a command pointer passed to 0x3FBD0 and its result (or the arg itself) returned; callers do cmd=f(cmd); r1d int and r6c void are wrong */
int sub_0007E0A0(void *buf, const void *fmt, ...); /* vsnprintf-style: 0x7DAF0(buf,10000,fmt,&va) result returned */
int sub_0007EAD0(void *n); /* recursive tree free on p1; returns 0 */
int sub_0007F1E0(void *p, int v, int n); /* memset rep stos to p1 with byte p2 count p3; returns 0 */
int sub_0007F210(void *dst, const void *src, int n); /* memcpy rep movs; returns 0 */
void *sub_0007F2B0(void *o); /* unlinks p1 from siblings; returns old next ptr or 0 */
void *sub_0007F3F0(void *list, void *n); /* returns n: eax = [esp+8] at entry and never rewritten; 0x8CBE0 tests the result */
void sub_0007FD30(void *a, void *b, int v); /* p2 pushed to 0x1B2160 which stores it as list head and writes [p2]=old head so p2 is ptr (def int); eax not meaningful */
void sub_0007FD60(void *a, int v); /* p1 deref +0x8C/+0xC4, p2 index; no meaningful eax */
void *sub_00080CB0(void *pool, const void *from, const void *to); /* p2/p3 are vec ptrs passed to 0x1AD9F0 via 0x80A60/0x809C0; returns nearest item ptr (esi/ebp); def p2/p3 int */
void *sub_00080CF0(void *pool, const void *pos); /* p2 vec ptr passed to 0x1B2730/0x1AD9F0 via 0x80BD0/0x80B40; returns nearest item ptr; def ret int p2 int */
float sub_00082D70(const void *v); /* Arg vector passed twice to dot product 0x1AD9D0 then 0x1A3F50 (sqrt) result left in st0; aab/r6e void returns wrong */
void *sub_00083030(void *node, int a, void *u); /* Allocates 0x24 bytes and stores arg1 (node from alloc) at +0x14 arg2 at +4 arg3 at +0x1C; returns the allocation; rbg int first param wrong */
void *sub_00083120(void *o, int id); /* Walks list at [arg1+0x10] via +0x20 comparing arg2 to [node]; returns node pointer or NULL; r3 int return wrong */
void sub_00083160(void *s, void *r); /* p2 deref +0x8C, p1 deref +0x14; tail jmp to 0x1B14E0/0x1B3070 which leave loop counter in eax */
int sub_000833E0(void *handle); /* Arg dereferenced ([esi+0x14]); returns 0 or 1; int-param decls are wrong kind */
void *sub_000847F0(void *a, int b); /* Returns [arg1+4] + arg2*0x370 + 0x24 (element address); r2d int/int and int return wrong */
void sub_00084910(void *h, float x, float y, float c4, float c8, float cc, float k); /* Arg1 list header deref; args2-3 passed with 255.0f to 0x1B1F40 and args4-7 fld'd and converted to bytes; r6f int first param wrong */
int sub_00084C00(const void *p, int a); /* Arg1 blob pointer passed to 0x1BA7F0; returns that texture index (or -1); callers store it in int handles */
void sub_000862A0(void *e); /* p1 deref +4/+8; ends with heap pop */
void sub_00086460(void *e); /* p1 deref +4/+8; eax loop garbage */
int sub_00089420(void *ref); /* Arg deref ([edi+0x20] list) and passed to 0x8C450; explicit xor eax so returns int 0; rtc int param wrong */
void sub_00089740(void *ref, void *b); /* arg1 [edi+0x4C] deref, arg2 [esi+0x28] deref; eax differs per path */
int sub_0008B680(void *list, void *ctx, void *refs); /* returns 0; arg1 +0x1C deref, arg2 passed to 0x8C350, arg3 compared with node+8 and walked */
void *sub_0008BD80(int heap, int a, int size, int tag, const void *file); /* tail jmp a6b_HeapAlloc(slot,align,size,line,void *); arg2 is the align int (caller 0x8D340 passes 4) not a ptr, and callers pass 5 args (line, file) though body reads only 3 */
int sub_0008BF70(void *o); /* xor eax at exit; arg walked as node list */
int sub_0008BFD0(void *heap, void *s); /* Arg1 is event list head walked via 0x7F300; arg2 demo deref ([ebp+0x1C]); returns -1 on NULL args else 0; r6f int first param wrong */
void *sub_0008C6E0(int type, void *a); /* arg1 indexes table 0x2E10E8, arg2 stored at node+0x1C; returns new node or 0 */
void *sub_0008C900(void *n, void *a); /* returns arg1 or 0x8C5F0 result (list head) */
int sub_0008CB90(void *o); /* recursive tree free; returns 0 or child result */
int sub_0008CC50(void *slot, void *o); /* arg2 is forwarded to ops->step(task,arg) and the only caller a80_ReleaseX24 passes an object pointer, so arg2 is ptr not int */
void *sub_0008E1B0(void *t); /* returns [[p+0x28]+0x5C]; caller a8b_2.c passes it to sub_0001EB80 which takes an object pointer */
void *sub_0008E5E0(int a, int b, int c, int d); /* Four args (arg1 tested and passed to 0x8C350 arg2-4 packed as id bits); returns 0x8C350 result or NULL; r6d single-param decl is wrong */
unsigned int sub_000AD090(); /* xor eax; ret only [any number of args: declared unprototyped] */
void sub_000BCA50(int a); /* Stores arg to global 0x41FFF8 only; r2 zero-param decl wrong */
void sub_000BD4D0(void *obj, int anim); /* arg1 deref +0xD8, arg2 stored; eax differs per path */
int sub_000C4D30(void *o, int kind, float a, int b, float c, float d, float e, const void *pos, void *v1, void *v2); /* Ten stack args (floats at 3/5/6/7 via movss; 8-10 copied as vectors by 0xF5D40; arg1 stored at +0x54); returns slot index or -1; 4-param decls (r3 r4c rbj) are wrong and r3d void return wrong */
void sub_000CED50(void *p); /* Arg passed as eax regarg to 0xCDAB0 which derefs [eax+4] and as esi to 0xCE4C0; no return; rbg int param wrong */
void sub_000CF330(void *a, const void *b, float c); /* Arg1 deref (+0x108 +0xFD8); arg2 vector to 0x1AD9F0; arg3 movss-stored to +0x10C; ac0 int third param wrong */
int sub_000D1E10(void *s, int index, int delta); /* Arg1 stats struct deref (+0xD64..); arg2 stat id switch; arg3 delta added; returns clamped value in eax; aab void return wrong */
void sub_000D45B0(void *obj, void *a, float b, float c); /* arg2 copied via 0xF5D40, args 3-4 movss */
void *sub_000E0770(); /* Returns constant address 0x3F0758 and reads no args; unprototyped because the original caller 0x6DBB0 pushes one (ignored) argument while all others push none */
void sub_000E0FB0(int v); /* only [esp+4] is read (then overwritten for tail jmp 0x3FCE0); def has 3 params, b and c are really the tail callee's own args */
void *sub_000E23F0(int a, int b); /* Returns global object 0x420E98 when arg1==1 else result of 0x1D080 lookup; callers dereference the result; r2e void return wrong */
void *sub_000E2540(int a, int i); /* Arg1 never read (kind unknown; callers pass int and ptr); arg2 switch 0..10 selecting object 0x420E98 or 0x1D080 result; returns pointer */
int sub_000ED590(int a, int b); /* Arg1 compared to type ids in table 0x278248; arg2 passed to the handler via call [edx+0x278264] whose eax is returned; void decls lose the handler result */
void *sub_000ED630(int a, int b, const void *c, const void *d, int e); /* a1 matched against type table; a3/a4 null-defaulted vec4 ptrs passed to spawn callback; a5 int; returns spawned object esi (afc/r6c/r6d void-return decls wrong; afc/r3/b7c_3 int-for-ptr wrong) */
int sub_000ED780(void *a); /* returns 0/1; arg deref +0xC */
void *sub_000EDBE0(int list, int side); /* two ints compared to node [+4]/[+8]; returns node ptr [ecx+0xc] or 0 which callers dereference (b1b/r2 int return wrong) */
void sub_000EE660(void *o, float v); /* mulss with arg2; arg1 walked list */
void sub_000EE6D0(void *m, float b); /* a1 dereferenced [esi+0x28]; a2 used in mulss; no meaningful eax (b4c int a2 wrong) */
int sub_000F3B50(void *o); /* a1 passed to 0x1D960 which derefs [a1+0x40]; returns int field [+0x50] compared to 2/3 (r3c int param wrong) */
void sub_000F3BF0(void *boss, float dmg, int flag); /* a1 object to 0x1D960; a2 addss float; a3 or'd into flags; eax leftover (acb/r2e int a2 wrong) */
int sub_000F5D00(const void *a); /* returns 0/1; arg deref +0x30 */
void sub_000F5E30(void *o, float a, const void *v1, const void *v2); /* arg2 passed as float 3rd arg of 0x1ADB60; args 3-4 are vec4 sources (def has const void* for arg2) */
float sub_000F7B80(void *a, void *pos, float c); /* fld return; arg2 passed to 0xF7720 as vector ptr; arg3 fld */
float sub_000F7C40(void *a, void *b, float c); /* arg3 forwarded as float 3rd arg of 0xF7B80 (def has int); returns float */
void *sub_000FBAF0(void); /* returns global 0x3F6114 (asserts nonzero); no args read (afc 1-param decl wrong) */
void *sub_000FE3D0(void); /* returns global 0x3F6120; no args read (afc 1-param decl wrong) */
void *sub_00100110(void); /* returns global 0x3F6128; no args read (afc 1-param decl wrong) */
void *sub_00101220(void); /* returns [g_3F6130+0x8C] which callers pass to sub_000F3B50 as object ptr (r3c int wrong) */
void sub_00113040(void *o, void *e, int anim); /* a2 deref [+0x28C] state table; a3 index; a1 forwarded to state callback; eax only leftover from callback and no caller uses it (b1b/b3b/b4c int return doubtful) */
void sub_00113090(void *o, void *e, int anim); /* a1 deref [+0x30]/[+0x3C]; a2 deref [+0x64]; a3 int id; ends with no return value (b16 int return wrong) */
void sub_001130F0(void *a, void *b, int c); /* a1 list walked via [+0x3C]; a2 deref [+0x20]/[+0x270]; a3 int flag (r2 int a2 wrong) */
void sub_00113190(void *o, void *e, int arg); /* a1 passed to 0x1D470/0x1D4B0; a2 flags [+0x20]; a3 bool; eax just holds a2 at exit (int-return decls dubious though b13 wrapper returns it) */
void *sub_00113430(void *e, int slot); /* returns node from 0x113300 or 0 */
void sub_00113CB0(void *v, float a, float b); /* subss/movss with args 2-3 */
void sub_0013DF90(void *key, int p); /* a1 deref [+4]/[+8]; a2 int switch index 0..4 (r2c ptr a2 wrong) */
int sub_001456E0(void *a, void *b, int c, int d); /* returns 0/1; arg4 never read but every caller passes a 4th 0 */
int sub_00145940(void *a, float b, float c, float d, float e); /* args 2-3 forwarded to 0x145820 angle fn, args 4-5 movss range */
int sub_001459D0(void *a, float b, float c, float d); /* returns 0/1; arg4 fld; args 2-3 to 0x145820 */
void sub_00145C90(void *dst, void *a, const void *b); /* a1 and a3 forwarded to 0x1AD9B0 with local matrix; a2 forwarded to 0x1ADA40 as matrix source; no return (r2e int a2 likely wrong) */
int sub_001671D0(void *m, void *a, int state); /* returns indirect handler result (call;add;ret) */
int sub_00184610(void); /* no args; returns 1 or 0 used in if test (b10 void wrong) */
void sub_00189510(void *p); /* a1 null-checked and dereferenced [esi]/[+0xC] (r3d int wrong) */
void sub_00196B40(void *p1, void *p2); /* arg1 is a matrix passed to 0x1ADA40/0x1ADB60, arg2 deref +0x10..+0x24; eax garbage on the early-exit path. */
void sub_00199C10(int i, int v); /* Two int args (index, cue); ends with unlock 0x1AA1F0 (LeaveCriticalSection-style import) so eax is garbage; no caller uses it. */
int sub_00199F70(int i); /* a1 int index 0..0x76; returns 0/1/flag in eax used by callers (rtc void wrong) */
void sub_0019B800(int h, int v); /* Slot index 0..2; no eax set on exit. [arity kept at 2: original callers push that many args; extra args unused by the callee] */
void sub_001A0830(void *arg); /* arg1 passed as group to 0x1A1030/0x1A1060 and deref [ecx]; tail jmp 0x58190. */
int sub_001A1030(void *g, int slot, int prio, void *fn, int a, int stack); /* arg1 deref [arg1]; all 6 args forwarded to 0x58B00 (arg4 is the job function); returns 0x58B00's result (call;add;ret), no caller uses it. */
int sub_001A1060(void *target, int ev); /* arg1 deref [ecx]; returns -1 or result of 0x588D0. */
void sub_001A1130(void *a); /* a1 dereferenced [edi] each iteration; no return (r6b ptr agrees; int decls are kind-mismatch) */
int sub_001A11B0(void *group); /* a1 dereferenced [edi]; returns xor eax eax =0 (a9c void/no-param decl wrong) */
float sub_001A3F50(float x); /* fld [esp+4]; fsqrt; result in st0 (a8c void return wrong) */
int sub_001A7E30(void); /* Returns 0 on all paths; push ecx is float scratch space, not a regarg. */
int sub_001A8210(const void *name, int flags, ...); /* CRT _open-style: a1 path to 0x1A81C0, a2 flags; optional mode arg never read (0x50440 pushes 2 args, others 3) */
int sub_001A8410(int h, void *buf, int n); /* arg1 index; arg2 (buffer) and arg3 (size) stored to 0x40B86C/0x40B870 for the read thread; returns 0 or -1. */
int sub_001A8490(int h, int pos, int whence); /* arg3 is the switch (whence), arg1 index, arg2 offset; eax = arg2 on every path. */
int sub_001A8500(int h, int which, void *out); /* Reads [esp+4] and [esp+0xC] (after push esi it is [esp+0x10]); arg3 is the bytes-out pointer passed to 0x1BC7AE, arg2 unused; def has only (idx, n) so n is in the wrong slot; callers pass (h, 1, &v). */
void *sub_001A8630(int size); /* tail-forwards size to 0x1BD517 allocator; result stored as buffer base (a5b int return wrong) */
void sub_001AA1E0(void *lock); /* pushes a1 to kernel import (enter critical section); callers pass a CS object (rtc int wrong) */
void sub_001AA1F0(void *lock); /* pushes a1 to kernel import (leave critical section); callers pass a CS object (rtc int wrong) */
int sub_001AA310(int a); /* a1 int slot 0..63; returns slot or -1 compared by caller (void decls wrong) */
int sub_001AA460(int h); /* Index arg; returns index or -1. */
void sub_001AB3D0(int a, int b); /* a1/a2 ints compared to constants; eax on exit only leftover from callees (a19 int return dubious) */
int sub_001AD440(int thread); /* Returns arg1 (esi) on both paths. */
void *sub_001AD560(void); /* jmp to 0x1BD50A which returns fs:[0x28]->+0x12C current thread ptr compared to stored thread ptrs (r1/r1c/r1e int wrong) */
void sub_001AD7C0(void *dst, const void *a, const void *b); /* cdecl wrapper forwarding all 3 args to D3DXMatrixMultiply 0x1E522D (out/a/b swapped); r6h.h float** /int kinds wrong */
void sub_001AD8E0(void *d, const void *s, float a); /* Passes arg3 as float angle to rotation 0x1E4CAD then multiplies arg2 by temp into arg1; b7c_5.c local decl (3rd void*) wrong */
void sub_001AD940(void *m); /* Writes identity floats through arg1; eax = arg1 but callers ignore it. */
void sub_001AD9B0(void *dst, const void *a, const void *b); /* cdecl wrapper forwarding 3 pointers to D3DXVec4Transform 0x1E4B2D */
float sub_001AD9D0(const void *a, const void *b); /* fld/fmul [arg1+n]*[arg2+n] dot3 returned in st0; a8c.h single-float-param decl wrong */
void sub_001ADA40(void *a, const void *p); /* rep movsd 16 dwords from arg2 to arg1; a3b.h/b13.h int kinds wrong */
void sub_001ADB60(void *dst, const void *src, float s); /* movss scale of arg2 vec3 by float arg3 into arg1; r2d.h 3rd-param ptr wrong */
void sub_001ADEE0(void *m, void *a, void *b, void *c); /* Scales vec4s from args 2/3/4 and calls 0x1AD7E0 into arg1 rows; r4.h int kinds wrong r4b.h right */
void *sub_001AE970(void *node); /* Initialises arg1 fields and returns arg1. */
void sub_001AEBF0(void *o, void *anim, int mode); /* arg1 deref +0xB0 arg2 deref +8 arg3 tested &3/&4 as flags; aac.h ints wrong and r4e.h p2 int wrong */
void sub_001AEDD0(void *inst, float v); /* movss float arg2 stored to [arg1+0xC4]; int-second-param decls (afc r2d r3b r3c rfl rtc b13) wrong */
int sub_001AEE90(void *a, int b); /* arg1 deref +0xB0/+0xB4; returns OR-mask. [arity kept at 2: original callers push that many args; extra args unused by the callee] */
int sub_001AEED0(void *t, int a); /* ORs arg2 into every part; eax = arg2 on both paths. */
int sub_001AEF10(void *s, int n); /* ANDs ~arg2 into parts; eax = arg2 on both paths. */
void sub_001B2020(void *a, void *chan); /* Links arg2 under arg1 (+0x80/+0x84/+0x88); eax garbage. */
void sub_001B2160(void *bank, void *l); /* arg1 deref +0xA8, arg2 deref [ecx]; eax garbage. */
void sub_001B32E0(void *q, void *buf, int size); /* arg2 stored at [p+0] and [p+4] as buffer base/cursor; callers pass buffers (r1e_buf3E05DC, 0x53AB0 alloc result); def has int. */
void sub_001B7100(void *p, void *a); /* arg1 used as base +0xF0/+0x130 arg2 dereferenced as floats; both decls agree at kind level except r6c type name */
void *sub_001B9650(int handle); /* Returns the address of a 0x58-byte table entry on every path. */
void *sub_001B9CA0(void *cmd, int tex); /* arg1 command buffer written; returns arg1+0x10 or arg1. */
int sub_001B9FC0(int handle); /* Index arg; returns 0 or a setne result. */
int sub_001BA0B0(int g); /* Stores 16-bit arg at +0x1C; returns the previous value or 0xFFFF. */
int sub_001BA7C0(void *h); /* arg forwarded as 2nd arg of 0x1B9BF0, which compares it byte by byte as a name string; returns callee result. */
int sub_001BA7F0(const void *a); /* arg forwarded as 2nd arg of 0x1BA6E0, which dereferences it ([ebx+0x20]); def has int; returns callee's index (edi) or -1. */
int OOG_STDCALL sub_001BC71B(void *a, void *b, void *c, void *d, int e, int f, int g); /* stdcall ret 0x1C DuplicateHandle-style wrapper passing args 2/4/7 to kernel import and returning 1/0; r4.h void return wrong */
int OOG_STDCALL sub_001BCEF9(void *h); /* stdcall ret 4 passes handle arg to kernel import (SetEvent-like) and returns 1/0; HANDLE so ptr (a1a.h int) */
int OOG_STDCALL sub_001BD2B6(void *h); /* stdcall ret 4; returns [ebp+8] out value or -1 */
void *OOG_STDCALL sub_001BD517(int size, int max, int align, int prot); /* stdcall ret 0x10 allocator calling import with size/range/align and returning the allocation in eax; a1a.h int return wrong */
int OOG_STDCALL sub_001BD59E(void *freq); /* stdcall ret 4; writes [a1] [a1+4] returns 1 */
void OOG_STDCALL sub_001D3D80(int a, int b, void *c); /* stdcall ret 0xC arg1/arg2 compared as ints arg3 dereferenced via fild [ebx]; r4c.h all-ptr decl wrong */
int OOG_STDCALL sub_001D5F50(void *p); /* D3D Release: decrements [arg1] refcount and returns count&0xFFFF or 0; all void-return decls wrong and a1a.h int param wrong */
void OOG_STDCALL sub_001D6210(void *res, int a, void *out, void *b, int c); /* stdcall ret 0x14 forwarding (arg1 0 arg2..arg5) to lock routine 0x1DAA10; r4b.h p4 int wrong (RECT* passed 0) */
void OOG_STDCALL sub_001D6ED0(int n, void *rects, int flags, int color, float z, int stencil); /* stdcall ret 0x18 Clear(count rects flags color z stencil): arg2 advanced by 0x10 per rect arg5 fld; a1a/aac p2 int wrong */
void *OOG_STDCALL sub_001E4B2D(void *out, const void *v, const void *m); /* D3DXVec4Transform stores to [arg1] and returns arg1 in eax; r4e.h void return wrong */
void *OOG_STDCALL sub_001E4BC6(void *out, const void *in); /* D3DXMatrixTranspose: arg2 read arg1 written eax=arg1 at ret; aac.h int kinds wrong */
void *OOG_STDCALL sub_001E4C33(void *out, float angle); /* Rotation matrix: fsincos of float [ebp+0xC] written to [arg1] and eax=arg1 at ret; aac.h int 2nd param and void returns wrong */
void *OOG_STDCALL sub_001E4CAD(void *out, float angle); /* Rotation matrix: fsincos of float arg2 written to arg1 returning arg1; aac.h int 2nd param wrong */
void *OOG_STDCALL sub_001E4D28(void *out, float angle); /* Rotation matrix: fsincos of float arg2 written to arg1 returning arg1; aac.h int 2nd param wrong */
void *OOG_STDCALL sub_001E522D(void *out, const void *a, const void *b); /* D3DXMatrixMultiply stdcall ret 0xC with arg1 compared against arg2/arg3 as pointers; returns pOut per D3DX convention; a1a/aac int kinds wrong */
int OOG_STDCALL sub_002039CA(int a, int b, int c, int d, int e, int f, void *g, int h, int i); /* stdcall ret 0x24; forwards to 0x20397E and returns its eax */
int OOG_STDCALL sub_002224A2(void *dev, void *o); /* DSound wrapper adjusts arg1 by -8 (COM this) passes arg2 deref'd as object to 0x223BE2 and returns its HRESULT; aac.h int p2 and void returns wrong */
int OOG_STDCALL sub_002225B2(void *dev, void *status); /* DSound wrapper returning callee HRESULT; arg2 nullable ptr dereferenced in 0x223121; aac.h int p2 and r4f void return wrong */
int OOG_STDCALL sub_002226F3(void *eng, void *m, void *out); /* Forwards 3 args to 0x224EC4 (arg2 deref'd) and returns eax; callers pass &out-handle as arg3; aac.h int p1/p3 wrong */
int OOG_STDCALL sub_00222726(void *eng, int a, int b, void *play); /* Forwards to 0x224FCE where arg2 is index cmp -1 arg3 flags and arg4 a handle object; returns HRESULT; r4f void return wrong */
int OOG_STDCALL sub_0022275D(void *eng, void *play, int on); /* Forwards to 0x224598 where arg2 becomes ECX this and arg3 a bool; returns 0; aac.h int p2 and r4f void return wrong */
void OOG_STDCALL sub_00223F9C(void); /* No stack args read and plain ret; eax left over; decls differ only in callconv macro */

#endif
