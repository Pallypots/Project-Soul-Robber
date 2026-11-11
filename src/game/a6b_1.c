/* Area a6b, group 1: 0x0007E070..0x0007F70A leaf helpers (y_camera.c,
 * y_character.c and the keyframe/tree/interpolator utilities). Names inferred. */
#include <stdarg.h>
#include "a6b.h"

/* 0x0007E070: varargs front end of 0x0007DAF0. */
int a6b_Printf3(char *buf, int size, const char *fmt, ...)
{
    va_list ap;
    int r;
    va_start(ap, fmt);
    r = sub_0007DAF0(buf, size, fmt, &ap);
    va_end(ap);
    return r;
}

/* 0x0007E0A0: varargs front end of 0x0007DAF0 with b fixed at 10000. */
int a6b_Printf2(char *buf, const char *fmt, ...)
{
    va_list ap;
    int r;
    va_start(ap, fmt);
    r = sub_0007DAF0(buf, 10000, fmt, &ap);
    va_end(ap);
    return r;
}

/* 0x0007E190: add a reference to a camera animation. */
void a6b_CamAnim_AddRef(A6bCamAnim *c)
{
    c->set.refs++;
}

/* 0x0007E2B0: set two words at +4/+8. */
void a6b_SetPair(int32_t *o, int a, int b)
{
    o[1] = a;
    o[2] = b;
}

/* 0x0007E2D0: create the character resource handle if it is missing. */
void a6b_Char_EnsureRes(A6bChar *ch, int a)
{
    if (ch->res != 0 && ch->res->handle == 0)
        ch->res->handle = sub_000538A0(a, a6b_srcYCharacter, 0x291);
}

/* 0x0007E310: end a temporary slot if the character resource has a handle. */
void a6b_Char_EndTemp(A6bChar *ch, int slot)
{
    if (ch->res != 0 && ch->res->handle != 0)
        a50_SlotEndTemp(slot);
}

/* 0x0007E340: add a reference (byte at +0x1A). */
void a6b_AddRef1A(A6bRef1A *o)
{
    o->refs++;
}

/* 0x0007E490: apply a scaled value to every active part through 0x001B1190. */
int a6b_Model_ScaleParts(A6bModel *m, float s)
{
    A6bPart *p;
    for (p = m->parts; p != 0; p = p->next) {
        A6bPartObj *o;
        A6bPartInfo *info;
        if (!(p->flags & 1))
            break;
        o = p->obj;
        info = sub_00083120(o, o->id);
        if (info != 0 && info->valid != 0)
            sub_001B1190(o->inst, info->value * s);
    }
    return 0;
}

/* 0x0007E4F0: convert each active part's per-frame value to per-second through 0x001AEDD0. */
void a6b_Model_RateParts(A6bModel *m)
{
    A6bPart *p;
    for (p = m->parts; p != 0; p = p->next) {
        A6bPartObj *o;
        A6bPartInfo *info;
        if (!(p->flags & 1))
            break;
        o = p->obj;
        info = sub_00083120(o, o->id);
        if (info != 0 && info->valid != 0)
            sub_001AEDD0(o->inst, info->value * 60.0f * 0.016666668f);
    }
}

/* 0x0007E560: store a scaled value at +0xDC of every active part instance. */
void a6b_Model_SetPartsDC(A6bModel *m, float s)
{
    A6bPart *p;
    for (p = m->parts; p != 0; p = p->next) {
        A6bPartObj *o;
        A6bPartInfo *info;
        if (!(p->flags & 1))
            break;
        o = p->obj;
        info = sub_00083120(o, o->id);
        if (info != 0 && info->valid != 0)
            *(float *)(o->inst + 0xDC) = info->value * s;
    }
}

/* 0x0007E670: store v through the pointer at +0x1C. */
int a6b_StoreVia1C(uint8_t *o, int v)
{
    **(int32_t **)(o + 0x1C) = v;
    return 0;
}

/* 0x0007E880: free a record chain (recursively from the tail). */
void a6b_Rec_FreeList(A6bRec *r)
{
    if (r == 0)
        return;
    a6b_Rec_FreeList(r->next);
    if (r->pC != 0)
        r->pC = 0;
    sub_00053880(r);
}

/* 0x0007EEB0: clear a track. */
int a6b_Track_Clear(A6bTrack *t)
{
    return sub_0007F1E0(t, 0, sizeof(A6bTrack));
}

/* 0x0007EED0: free owned keys and clear a track. */
int a6b_Track_Free(A6bTrack *t)
{
    if (t == 0)
        return 0;
    if (t->flags & 1)
        sub_0008BCC0(t->keys);
    return sub_0007F1E0(t, 0, sizeof(A6bTrack));
}

/* 0x0007EFB0: eval function of constant tracks: 0. */
float a6b_Track_EvalZero(A6bTrack *t, float x)
{
    return 0.0f;
}

/* 0x0007EFC0: step track: value of the key at or before x. */
float a6b_Track_EvalStep(A6bTrack *t, float x)
{
    float *k;
    if (t == 0)
        return 0.0f;
    k = sub_0007EF30(t, x);
    if (k != 0)
        return k[1];
    return 0.0f;
}

/* 0x0007F120: length function of constant tracks: -1. */
float a6b_Track_LengthNone(A6bTrack *t)
{
    return -1.0f;
}

/* 0x0007F130: time of the last key (-1 when there are no keys). */
float a6b_Track_Length(A6bTrack *t)
{
    float last = 0.0f;
    float *k;
    int stride;
    if (t == 0 || t->keys == 0)
        return -1.0f;
    k = t->keys;
    if (*k >= 0.0f) {
        stride = a6b_trackTypes[t->type].stride;
        do {
            last = *k;
            k += stride;
        } while (*k >= 0.0f);
    }
    return last;
}

/* 0x0007F180: attach serialized keys {type, keys..., terminator}; returns the data after them. */
float *a6b_Track_Load(A6bTrack *t, float *data)
{
    float *k;
    int size;
    if (t == 0)
        return 0;
    t->type = *(int32_t *)data;
    t->keys = data + 1;
    k = t->keys;
    while (*k >= 0.0f)
        k += a6b_trackTypes[t->type].stride;
    size = (int)((char *)(k + a6b_trackTypes[t->type].stride) - (char *)t->keys);
    if (size < 0)
        return 0;
    return (float *)((char *)t->keys + size);
}

/* 0x0007F2B0: unlink a node from its siblings and parent; returns its old next. */
A6bNode *a6b_Node_Unlink(A6bNode *n)
{
    A6bNode *next, *prev, *parent;
    if (n == 0)
        return 0;
    next = n->next;
    prev = n->prev;
    parent = n->parent;
    n->next = 0;
    n->prev = 0;
    n->parent = 0;
    if (next != 0)
        next->prev = prev;
    if (prev != 0)
        prev->next = next;
    if (parent != 0 && parent->child == n)
        parent->child = next;
    return next;
}

/* 0x0007F300: next sibling. */
A6bNode *a6b_Node_Next(A6bNode *n)
{
    if (n == 0)
        return n;
    return n->next;
}

/* 0x0007F310: previous sibling. */
A6bNode *a6b_Node_Prev(A6bNode *n)
{
    if (n == 0)
        return n;
    return n->prev;
}

/* 0x0007F320: first child. */
A6bNode *a6b_Node_Child(A6bNode *n)
{
    if (n == 0)
        return n;
    return n->child;
}

/* 0x0007F330: first sibling. */
A6bNode *a6b_Node_First(A6bNode *n)
{
    if (n == 0)
        return 0;
    while (n->prev != 0)
        n = n->prev;
    return n;
}

/* 0x0007F350: last sibling. */
A6bNode *a6b_Node_Last(A6bNode *n)
{
    if (n == 0)
        return 0;
    while (n->next != 0)
        n = n->next;
    return n;
}

/* 0x0007F370: root of the tree. */
A6bNode *a6b_Node_Root(A6bNode *n)
{
    if (n == 0)
        return 0;
    while (n->parent != 0)
        n = n->parent;
    return n;
}

/* 0x0007F390: step i siblings forward (stays 0 past the end). */
A6bNode *a6b_Node_Nth(A6bNode *n, int i)
{
    if (n == 0)
        return n;
    for (; i != 0; i--)
        if (n != 0)
            n = n->next;
    return n;
}

/* 0x0007F480: allocate from a heap slot (align and source location unused). */
void *a6b_HeapAlloc(int slot, int align, int size, int line, const char *file)
{
    return a50_Alloc(slot, size, a6b_empty2608A2, 0);
}

/* 0x0007F4A0: set the heap id for a kind. */
void a6b_SetHeap(int kind, int heap)
{
    a6b_heaps428F00[kind] = heap;
}

/* 0x0007F4B0: heap id for a kind. */
int a6b_GetHeap(int kind)
{
    return a6b_heaps428F00[kind];
}

/* 0x0007F4F0: 0 when 0x000374C0 succeeds, -1 when it returns -1. */
int a6b_Check374C0(const void *a)
{
    return sub_000374C0(a) != -1 ? 0 : -1;
}

/* 0x0007F540: take the value at +0x10 and clear +0x10/+0x14. */
void a6b_Take10(int32_t *o, int32_t *out)
{
    *out = o[4];
    o[4] = 0;
    o[5] = 0;
}

/* 0x0007F5E0: string copy that tolerates null pointers. */
char *a6b_StrCopy(char *dst, const char *src)
{
    char *d;
    if (dst == 0)
        return dst;
    if (src == 0)
        return 0;
    d = dst;
    while (*src != 0)
        *d++ = *src++;
    *d = 0;
    return dst;
}

/* 0x0007F610: set up an interpolator of the given kind between a and b. */
int a6b_Lerp_Init(A6bLerp *l, int kind, float a, float b)
{
    if (l == 0)
        return -1;
    l->flags |= 3;
    l->a = a;
    l->kind = kind;
    l->b = b;
    return 0;
}

/* 0x0007F670: constant interpolation. */
float a6b_Lerp_Const(A6bLerp *l, float t)
{
    return l->a;
}

/* 0x0007F680: linear interpolation. */
float a6b_Lerp_Linear(A6bLerp *l, float t)
{
    return (l->b - l->a) * t + l->a;
}

/* 0x0007F6A0: ease-out (sine of t * pi/2). */
float a6b_Lerp_SinOut(A6bLerp *l, float t)
{
    float s = sub_001A3ED0(t * 1.5707964f);
    return (l->b - l->a) * s + l->a;
}

/* 0x0007F6D0: ease-in (cosine of t * pi/2, from b back to a). */
float a6b_Lerp_CosIn(A6bLerp *l, float t)
{
    float s = sub_001A3EE0(t * 1.5707964f);
    return (l->a - l->b) * s + l->b;
}

/* 0x0007F700: zero interpolation. */
float a6b_Lerp_Zero(A6bLerp *l, float t)
{
    return 0.0f;
}
