/* Area r2c, group 2: component helpers (0x000EE010..0x000F0BDC). Names inferred. */
#include "r2c.h"

/* 0x000EE010: forward a hit on obj to its kind-0x0D component's callback;
   0 without the component. */
int r2c_CompHit(void *obj, void *target)
{
    R2cComp0D *c = (R2cComp0D *)sub_0001D960(obj, 0xD);
    if (!c)
        return 0;
    return c->onHit2C(obj, target);
}

/* 0x000EE040: ask the kind-0x0D component's query callback; without one,
   clear *out (when given) and return 0. */
int r2c_CompQuery(void *obj, int a, int *out)
{
    R2cComp0D *c = (R2cComp0D *)sub_0001D960(obj, 0xD);
    if (c && c->query30)
        return c->query30(obj, a, out);
    if (out)
        *out = 0;
    return 0;
}

/* 0x000EFB90: free the state component's +0xD4 effect and clear st->v104. */
void r2c_StateFreeD4(void *obj, R2cState *st)
{
    R2cComp5 *c = (R2cComp5 *)sub_0001D960(obj, 5);
    if (c->hD4) {
        sub_00033A70(c->hD4);
        c->hD4 = 0;
    }
    st->v104 = 0;
}

/* 0x000EFC90: unless st->kind70 is 0x1B..0x1D or 0x1F, free the state
   component's +0xD4 effect; always clear st->v100. */
void r2c_StateFreeD4B(void *obj, R2cState *st)
{
    int k = st->kind70;
    if (k < 0x1B || (k > 0x1D && k != 0x1F)) {
        R2cComp5 *c = (R2cComp5 *)sub_0001D960(obj, 5);
        if (c->hD4) {
            sub_00033A70(c->hD4);
            c->hD4 = 0;
        }
    }
    st->v100 = 0;
}

/* 0x000F0B10: replace the state component's +0xD4 effect with a new one of
   the given kind. regargs: obj=EDI kind=stack. */
void r2c_SetEffectD4(void *obj, int kind)
{
    R2cComp5 *c = (R2cComp5 *)sub_0001D960(obj, 5);
    if (c->hD4) {
        R2cComp5 *o = (R2cComp5 *)sub_0001D960(obj, 5);
        if (o->hD4) {
            sub_00033A70(o->hD4);
            o->hD4 = 0;
        }
    }
    c->hD4 = sub_00036750(obj, kind);
}

/* 0x000F0B70: replace the state component's +0xD8 sound with effect id
   played at part 0x11 of obj. regargs: obj=ESI id=stack1 c=stack2. */
void r2c_SetSoundD8(void *obj, int id, int c)
{
    R2cComp5 *s = (R2cComp5 *)sub_0001D960(obj, 5);
    if (s->hD8 >= 0) {
        R2cComp5 *o = (R2cComp5 *)sub_0001D960(obj, 5);
        if (o->hD8 >= 0) {
            sub_00048250(o->hD8);
            o->hD8 = -1;
        }
    }
    s->hD8 = sub_000494D0(id, (char *)sub_0001D0F0(obj, 0x11) + 0x70, c);
}
