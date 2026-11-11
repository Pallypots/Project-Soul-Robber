/* Area r4: scene-node lists and small setters around 0x001B1430-0x001B2A2A (r4_3). Names inferred.
   All functions here take ordinary stack arguments (the `mov edi,edi` fillers are not register reads). */
#include "r4.h"

/* 0x001B1430: store c in *p and return b. */
int r4_StoreRet(int *p, int b, int c)
{
    *p = c;
    return b;
}

/* 0x001B14E0: set the model's +0xC8 value and copy it into every part. */
void r4_ModelSetPartValue(R4Model *m, int v)
{
    uint32_t i;
    R4Part *p = m->parts;
    m->iC8 = v;
    for (i = 0; i < m->count; i++, p++)
        p->i17C = v;
}

/* 0x001B1530: set the model's +0xCC field. */
void r4_ModelSetCC(R4Model *m, int v)
{
    m->iCC = v;
}

/* 0x001B1540: set the model's +0xE8/+0xEC pair. */
void r4_ModelSetE8(R4Model *m, int a, int b)
{
    m->iE8 = a;
    m->iEC = b;
}

/* 0x001B1560: apply each enabled part's bone matrix. */
void r4_ModelApplyBones(R4Model *m)
{
    int i;
    R4Part *p = m->parts;
    for (i = 0; i < (int)m->count; i++, p++) {
        if (p->i17C)
            sub_001ADA40(p, (const float *)(p->ownerB8->skel->mats + p->boneB4 * 0x130));
    }
}

/* 0x001B16E0: create the built-in texture from the embedded DDS image. */
void r4_CreateBuiltinTexture(void)
{
    void *tex = sub_001BA7F0(r4_g367EA8);
    uint8_t *d = sub_001B9650(tex);
    *(int32_t *)(d + 0x48) = 5;
    r4_g40F1B0 = tex;
    *(int32_t *)(d + 0x4C) = 0;
}

/* 0x001B1710: bind the built-in texture. */
int r4_BindBuiltinTexture(int a)
{
    return sub_001B9CA0(a, r4_g40F1B0);
}

/* 0x001B1DB0: reset a fog/range block. */
void r4_FogInit(R4Fog *f)
{
    f->f04 = 256.0f;
    f->f00 = 0.0f;
    f->f08 = 1.0f;
    f->f0C = 0.0f;
    f->f20 = 0.0f;
    f->f1C = 0.0f;
    f->f18 = 0.0f;
    f->f14 = 0.0f;
    f->f30 = 0.0f;
    f->f2C = 0.0f;
    f->f28 = 0.0f;
    f->f24 = 0.0f;
    f->cmd34 = 0;
}

/* 0x001B1E10: compute the fog factors and emit a 4-word command; returns the next command slot. */
uint32_t *r4_FogEmit(R4Fog *f, uint32_t *cmd)
{
    float k = 0.0f - (f->f04 - f->f00) / (f->f0C - f->f08);
    f->cmd34 = cmd;
    f->f30 = k;
    f->f20 = 0.0f - f->f0C * k;
    cmd[1] = (uint32_t)(uintptr_t)&f->f14;
    cmd[0] = 0x30000002;
    cmd[2] = 0x1000101;
    cmd[3] = 0x6C02000E;
    return cmd + 4;
}

/* 0x001B1F40: set a 4-float vector. */
void r4_Vec4Set(float *v, float x, float y, float z, float w)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

/* 0x001B1F70: copy the three rotation rows of a matrix and clear the translation. */
void r4_MatCopyRotation(float *d, const float *s)
{
    sub_001AD7E0(d, s);
    sub_001AD7E0(d + 4, s + 4);
    sub_001AD7E0(d + 8, s + 8);
    d[12] = 0.0f;
    d[13] = 0.0f;
    d[14] = 0.0f;
    d[15] = 1.0f;
}

/* 0x001B2020: link child under parent (append to the end of the child list). */
void r4_NodeAttach(R4Node *parent, R4Node *child)
{
    R4Node *n;
    child->parent = parent;
    n = parent->child;
    if (n == child)
        return;
    if (!n) {
        parent->child = child;
        child->next = 0;
        return;
    }
    for (; n->next; n = n->next)
        if (n->next == child)
            return;
    n->next = child;
    child->next = 0;
}

/* 0x001B2080: unlink a node from its parent. */
void r4_NodeDetach(R4Node *node)
{
    R4Node *p, *n;
    if (!node)
        return;
    p = node->parent;
    if (!p)
        return;
    n = p->child;
    if (n == node) {
        p->child = node->next;
    } else {
        for (; n; n = n->next) {
            if (n->next == node) {
                n->next = node->next;
                break;
            }
        }
    }
    node->next = 0;
    node->parent = 0;
}

/* 0x001B20F0: set the upper limit, not below the lower limit. */
void r4_SetUpperLimit(float v)
{
    float lo = r4_g40F1C4;
    r4_g377F48 = v;
    if (lo > v)
        r4_g377F48 = lo;
}

/* 0x001B2120: set the lower limit, not above the upper limit. */
void r4_SetLowerLimit(float v)
{
    float hi = r4_g377F48;
    r4_g40F1C4 = v;
    if (v > hi)
        r4_g40F1C4 = hi;
}

/* 0x001B2150: clear three words. */
void r4_Clear3(int32_t *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
}

/* 0x001B2160: push a hook at the head of the +0xA8 list. */
void r4_HookPushA8(R4Node *n, R4Hook *h)
{
    if (!n->hooksA8) {
        n->hooksA8 = h;
        return;
    }
    h->next = n->hooksA8;
    n->hooksA8 = h;
}

/* 0x001B2190: remove a hook from the +0xA8 list. */
void r4_HookRemoveA8(R4Node *n, R4Hook *h)
{
    R4Hook *e = n->hooksA8;
    if (e == h) {
        n->hooksA8 = h->next;
        return;
    }
    for (; e; e = e->next) {
        if (e->next == h) {
            e->next = h->next;
            return;
        }
    }
}

/* 0x001B21D0: append a hook at the tail of the +0xAC list. */
void r4_HookAppendAC(R4Node *n, R4Hook *h)
{
    R4Hook *e = n->hooksAC;
    if (!e) {
        n->hooksAC = h;
        return;
    }
    while (e->next)
        e = e->next;
    e->next = h;
}

/* 0x001B2200: remove a hook from the +0xAC list. */
void r4_HookRemoveAC(R4Node *n, R4Hook *h)
{
    R4Hook *e = n->hooksAC;
    if (e == h) {
        n->hooksAC = h->next;
        return;
    }
    for (; e; e = e->next) {
        if (e->next == h) {
            e->next = h->next;
            return;
        }
    }
}

/* 0x001B2240: run every hook of the +0xA8 list. */
void r4_HookRunA8(R4Node *n)
{
    R4Hook *e;
    for (e = n->hooksA8; e; e = e->next)
        if (e->fn)
            e->fn(n, e);
}

/* 0x001B2490: repeat the 0x001B2270 pass over p until a full round changes nothing. */
void r4_RunPasses(void *p)
{
    r4_g40F1BC = 0;
    do {
        r4_g40F1C0 = 1;
        if (p)
            while (sub_001B2270(p))
                ;
        r4_g40F1BC++;
    } while (!r4_g40F1C0);
}

/* 0x001B2660: build a matrix with 0x001ADEE0 and set its w to 1. */
void r4_MatBuildW1(float *m, int a, int b, int c)
{
    sub_001ADEE0(m, a, b, c);
    m[15] = 1.0f;
}

/* 0x001B26A0: select b (0x001A7280) and remember it; returns a. */
int r4_Select40F208(int a, int b)
{
    sub_001A7280(b);
    r4_g40F208 = b;
    return a;
}

/* 0x001B2730: distance between two points. */
float r4_Distance(const float *a, const float *b)
{
    float d[4];
    sub_001AD9F0(d, a, b);
    return sub_001A3F50(sub_001AD9D0(d, d));
}

/* 0x001B2770: distance between two points in the x/z plane. */
float r4_DistanceXZ(const float *a, const float *b)
{
    float d[4];
    sub_001AD9F0(d, a, b);
    return sub_001A3F50(d[2] * d[2] + d[0] * d[0]);
}

/* 0x001B29F0: clear two words. */
void r4_Clear2(int32_t *p)
{
    p[0] = 0;
    p[1] = 0;
}

/* 0x001B2A10: remember b; returns a. */
int r4_Set40F324(int a, int b)
{
    r4_g40F324 = b;
    return a;
}

/* 0x001B2A20: remember a. */
void r4_Set40F328(int a)
{
    r4_g40F328 = a;
}
