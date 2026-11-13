/* Area m1, file 39: removing an object's kind-12 component. Names inferred. */
#include <stdint.h>

typedef struct M1Comp12 {
    uint8_t unk00[0x10];
    int (*canRemove10)(void *o);   /* +0x10 */
} M1Comp12;
typedef struct M1ObjR {
    uint8_t  unk000[0xC];
    uint32_t flags0C;          /* +0x00C */
    uint8_t  unk010[0x134 - 0x10];
    void    *res134;           /* +0x134 */
    uint8_t  unk138[4];
    void    *res13C;           /* +0x13C */
} M1ObjR;
extern uint8_t m1_list3F59C0[];      /* 0x003F59C0 */
M1Comp12 *sub_0001D960(M1ObjR *o, int kind);
void *sub_0003DBC0(void *list, int z, M1ObjR *o);
void  sub_0003D8C0(void *node);
void  sub_0003D860(void *node);
void  sub_0001D910(M1ObjR *o, M1Comp12 *c);
void  sub_0001EB80(M1ObjR *o);
void  sub_000362B0(M1ObjR *o);
void  sub_00033C20(void *h);
void  sub_0005BC50(void *h);

/* 0x000EC670: if o has a kind-12 component that allows it, unlinks o from list
 * 0x3F59C0, removes the component, clears bit 0, and frees both resources. 1 when
 * removed, else 0. */
int m1_RemoveComp12EC670(M1ObjR *o)
{
    M1Comp12 *c = sub_0001D960(o, 0xC);
    void *n;
    if (c == 0 || !c->canRemove10(o))
        return 0;
    n = sub_0003DBC0(m1_list3F59C0, 0, o);
    if (n != 0) {
        sub_0003D8C0(n);
        sub_0003D860(n);
    }
    sub_0001D910(o, c);
    o->flags0C &= ~1u;
    sub_0001EB80(o);
    sub_000362B0(o);
    if (o->res134 != 0) {
        sub_00033C20(o->res134);
        o->res134 = 0;
    }
    if (o->res13C != 0) {
        sub_0005BC50(o->res13C);
        o->res13C = 0;
    }
    return 1;
}

