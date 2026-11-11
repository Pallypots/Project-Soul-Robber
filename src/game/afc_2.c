/* Area afc, group 2: actor helpers 0x000F5CD0-0x000F6B80. Names inferred. */
#include "afc.h"

/* 0x000F5CD0: true when fields +4/+8 equal (a, b). */
int afc_MatchPair(int32_t *o, int a, int b)
{
    if (o != 0 && o[1] == a && o[2] == b)
        return 1;
    return 0;
}

/* 0x000F5D00: model control bit 2 set and model flag bit 2 clear. */
int afc_NodeActive(AfcActor *o)
{
    if (o != 0 && (sub_001AEE50(o->node->model, 0) & 2) && !(o->node->model->flagsBC & 2))
        return 1;
    return 0;
}

/* 0x000F5D60: set launch vector +0xA0 scaled by k, and speeds +0xB0/+0xB4. */
void afc_SetLaunch(AfcActor *o, float k, float a, float b, AfcVec4 *v)
{
    if (o == 0)
        return;
    o->vD0 = sub_0001BC40(o);
    o->fB0 = k * b;
    o->fB4 = k * a;
    o->vecA0 = *v;
    sub_001ADB60(&o->vecA0, &o->vecA0, k);
}

/* 0x000F5DD0: set push vector +0xD8 scaled by k, magnitude +0xE8. */
void afc_SetPush(AfcActor *o, float k, float a, AfcVec4 *v)
{
    if (o == 0)
        return;
    o->vEC = 0;
    o->fE8 = k * a;
    o->vecD8 = *v;
    sub_001ADB60(&o->vecD8, &o->vecD8, k);
}

/* 0x000F5EA0: compute direction vector, flatten y/w, normalise. */
void afc_FlatDirection(AfcVec4 *d, void *a, void *b)
{
    sub_001AD9F0(d, a, b);
    d->w = 0.0f;
    d->y = 0.0f;
    sub_001AD7E0(d, d);
}

/* 0x000F5ED0: wrap an angle into [-pi, pi]. */
void afc_WrapAngle(float *a)
{
    if (a == 0)
        return;
    if (*a > 3.14159274f)
        *a -= 6.28318548f;
    else if (*a < -3.14159274f)
        *a += 6.28318548f;
}

/* 0x000F5F10: vector length. */
float afc_VecLength(AfcVec4 *v)
{
    return sub_001A3F50(v->x * v->x + v->y * v->y + v->z * v->z);
}

/* 0x000F5F50: horizontal (x/z) vector length. */
float afc_VecLengthXZ(AfcVec4 *v)
{
    return sub_001A3F50(v->x * v->x + v->z * v->z);
}

/* 0x000F5F80: dispatch by actor type to the type-specific handler. */
AfcActor *afc_DispatchByType(AfcActor *o)
{
    if (o != 0 && o->type != 3) {
        if (o->type == 4)
            return sub_00100110();
        if (o->type == 5)
            return sub_000FBAF0();
    }
    return sub_000FE3D0();
}

/* 0x000F62C0: set boss sub-state and clear +0xBC. */
void afc_SetSubState(AfcActor *o, int s)
{
    if (o == 0)
        return;
    sub_000F3D10(o->part8C, o, s);
    o->wBC = 0;
}

/* 0x000F62F0: set the same animation on both parts. */
void afc_SetBothAnims(AfcActor *o, int anim)
{
    if (o == 0)
        return;
    sub_000832D0(o->part8C->node, anim);
    sub_000832D0(o->part90->node, anim);
}

/* 0x000F63D0: clamp a value to 140/fps. */
void afc_ClampStep(float *p)
{
    if (p != 0) {
        float lim = 140.0f / aec_fps42C964;
        if (*p > lim)
            *p = lim;
    }
}

/* 0x000F6400: set +0xA4 and toggle part flags 0x44/0x220. */
void afc_SetVisible(void *p, int16_t on)
{
    AfcActorA4 *o = (AfcActorA4 *)p;
    if (o == 0)
        return;
    o->wA4 = on;
    if (on) {
        o->part8C->flags |= 0x44;
        o->part8C->flags &= ~0x220;
    } else {
        o->part8C->flags &= ~0x44;
        o->part8C->flags |= 0x220;
    }
}

/* 0x000F6B40: state is 7-10, 12, 14 or 15. */
int afc_StateIsActiveA(AfcActor *o)
{
    if (o == 0)
        return 0;
    switch (o->state) {
    case 7: case 8: case 9: case 10: case 12: case 14: case 15:
        return 1;
    }
    return 0;
}

/* 0x000F6B80: state is 7-10, 12 or 14. */
int afc_StateIsActiveB(AfcActor *o)
{
    if (o == 0)
        return 0;
    switch (o->state) {
    case 7: case 8: case 9: case 10: case 12: case 14:
        return 1;
    }
    return 0;
}
