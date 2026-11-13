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
void  sub_00048250(int h);

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


typedef struct M1Rec150 {
    uint8_t  unk000[8];
    int32_t  kind008;          /* +0x008 */
    uint32_t flags00C;         /* +0x00C */
    uint8_t  unk010[0x150 - 0x10];
} M1Rec150;
typedef struct M1Boss5 {
    uint8_t unk00[0x4C];
    int32_t f4C;               /* +0x4C */
    uint8_t unk50[0xDC - 0x50];
    void   *resDC;             /* +0xDC */
} M1Boss5;
extern uint8_t m1_snd3E1270[];     /* 0x003E1270 */
M1Boss5 *sub_0001D960B(M1Rec150 *o, int kind);   /* 0x0001D960 */
void sub_00039820(int v);
void sub_00033A70(void *r);
void sub_000192B0(void *s, int v);
int  sub_000F3140(int kind);
void sub_0001EB80R(M1Rec150 *r);                  /* 0x0001EB80 */
void sub_000EE270(void *c);
void sub_000F3AA0(void *c);
void sub_0001D910B(M1Rec150 *o, void *c);         /* 0x0001D910 */

/* 0x00107490: boss teardown: stops its music, frees its resource, hides every part
 * record, shuts down components 0xD and 5 and detaches them. Returns 1. */
int m1_BossTeardown107490(M1Rec150 *o)
{
    M1Boss5 *c = sub_0001D960B(o, 5);
    M1Boss5 *d;
    int i;
    if (o == 0)
        for (;;) ;
    sub_00039820(0);
    if (c->resDC != 0)
        sub_00033A70(c->resDC);
    sub_000192B0(m1_snd3E1270, 0);
    for (i = 0; i < sub_000F3140(o->kind008); i++) {
        if (o[i].flags00C & 1) {
            o[i].flags00C &= ~1u;
            sub_0001EB80R(&o[i]);
        }
    }
    d = sub_0001D960B(o, 0xD);
    c = sub_0001D960B(o, 5);
    sub_000EE270(d);
    sub_000F3AA0(c);
    c->f4C = 0;
    sub_0001D910B(o, c);
    sub_0001D910B(o, d);
    return 1;
}

typedef struct M1Comp5E4 { uint8_t unk00[0xE4]; int32_t sndE4; } M1Comp5E4;
typedef struct M1Hit68 { uint8_t unk00[0x68]; float dmg68; } M1Hit68;
M1Comp5E4 *sub_0001D960E(void *o, int kind);   /* 0x0001D960 */
void sub_0010FD50(void *o);                    /* regargs: o=EAX */

/* 0x001108A0: on a hit of at least 2.0, stops the kind-5 component's sound and runs
 * the hit reaction 0x10FD50. */
void m1_HitStrong1108A0(void *o, M1Hit68 *h)
{
    M1Comp5E4 *c;
    if (!(h->dmg68 >= 2.0f))
        return;
    c = sub_0001D960E(o, 5);
    if (c->sndE4 >= 0) {
        sub_00048250(c->sndE4);
        c->sndE4 = -1;
    }
    sub_0010FD50(o);
}
