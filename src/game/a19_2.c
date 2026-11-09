/* Area a19, 0x001940A0-0x00194D81: component-7 accessors. Names inferred. */
#include "a19.h"

/* 0x001940A0: clear component-7 work +0x18. */
void a19_C7_Clear18(void *obj)
{
    a19_Actor *c;
    if (obj != 0) {
        c = sub_0001D960(obj, 7);
        if (c != 0)
            *(int32_t *)&A19_F18(c->work) = 0;
    }
}

/* 0x00194CA0: set component-7 work +0x00 when obj and value are nonzero. */
void a19_C7_Set0(void *obj, int value)
{
    a19_Actor *c = sub_0001D960(obj, 7);
    if (obj != 0 && value != 0)
        c->work->f0 = value;
}

/* 0x00194CD0 */
void a19_C7_Set88(void *obj, int16_t v)
{
    if (obj != 0)
        sub_0001D960(obj, 7)->work->s88 = v;
}

/* 0x00194D00 */
void a19_C7_Set8A(void *obj, int16_t v)
{
    if (obj != 0)
        sub_0001D960(obj, 7)->work->s8A = v;
}

/* 0x00194D30: pass component 7 of obj to 0x00189DA0. */
void a19_C7_Apply(void *obj, int arg)
{
    if (obj != 0)
        sub_00189DA0(obj, sub_0001D960(obj, 7), arg);
}

/* 0x00194D60: component-7 work +0x18, or a default when obj is null. */
float a19_C7_Get18(void *obj)
{
    if (obj == 0)
        return 0.0f;
    return A19_F18(sub_0001D960(obj, 7)->work);
}

