/* Area m1, file 217: handler-block dispatch. Names inferred. */
#include <stdint.h>

typedef struct M1Obj { uint8_t p[0xC]; uint8_t flags; } M1Obj;
typedef struct M1Hnd M1Hnd;
struct M1Hnd {
    uint8_t p00[0x50]; int32_t idx50; uint8_t p54[8]; float f5C; float f60; uint8_t p64[0x4C];
    void (*fnB0)(M1Obj *, M1Hnd *); uint8_t pB4[4];
    void (*fnB8)(M1Obj *, M1Hnd *); uint8_t pBC[4];
    void (*fnC0)(M1Obj *, M1Hnd *); void (*fnC4)(M1Obj *, M1Hnd *);
    void (**tabC8)(M1Obj *, M1Hnd *);
};
M1Hnd *sub_0001D960(M1Obj *o, int kind);
extern float a50_frameSeconds;   /* 0x0042C85C */

/* 0x00166CE0: run the handler block's setup, per-frame and optional step handlers on o (hang if the block is missing). */
void m1_HandlerRun166CE0(M1Obj *o) {
    M1Hnd *h = sub_0001D960(o, 9);
    void (*f)(M1Obj *, M1Hnd *);
    if (!h) for (;;) ;
    h->fnB8(o, h);
    h->fnC0(o, h);
    if (o->flags & 1) {
        f = h->tabC8[h->idx50];
        if (!f) for (;;) ;
        f(o, h);
        if (o->flags & 1) {
            h->fnC4(o, h);
            h->f5C -= a50_frameSeconds;
            h->f60 += a50_frameSeconds;
            h->fnB0(o, h);
        }
    }
}
