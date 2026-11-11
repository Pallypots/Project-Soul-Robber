/* Area r4b: scene node helpers around 0x001B0E00-0x001B2723 (r4b_1). Names inferred. */
#include "r4b.h"

/* 0x001B0E00: apply the owner's +0xC4 value to node a (0x001B05E0). Stack args. */
void r4b_SkinRefApply(R4bSkinRef *a)
{
    sub_001B05E0(a, a->ownerB4->iC4);
}

/* 0x001B1190: reset skin s and set every bone to time t. Stack args. */
void r4b_SkinSetTime(R4bSkin *s, float t)
{
    int i;
    sub_001AEF10(s, 2);
    sub_001AEED0(s, 4);
    s->fC4 = 0.0f;
    s->fD8 = t;
    for (i = 0; i < s->count; i++)
        sub_001B0E20(&s->bones[i], t);
}

/* 0x001B1360: attach part array base to node n and link the root part. Stack args (base n). */
void r4b_NodeAttachParts(R4bPart *base, R4bNode *n)
{
    int i;
    int root;
    R4bPart *p;
    n->parts = base;
    for (i = 0; i < n->count; i++) {
        base[i].type8C = 10;
        sub_001B25B0(&base[i]);
    }
    root = ((R4bSkel *)*(void **)n->pBC)->root1C;
    sub_001B1200(n, n->parts, root);
    p = &base[root];
    n->child = (R4bNode *)p;
    ((R4bNode *)p)->parent = n;
}

/* 0x001B1440: initialise a type-9 node; returns n. Stack args. */
R4bNode *r4b_NodeInitType9(R4bNode *n)
{
    n->type8C = 9;
    sub_001B25B0(n);
    n->iB0 = 0;
    n->texB4 = 0;
    n->selB8 = 0;
    n->pBC = 0;
    n->count = 0;
    n->parts = 0;
    n->iC8 = 0;
    n->iE4 = 0;
    n->iEC = 0;
    n->iCC = 0;
    n->colD0[0] = 128.0f;
    n->colD0[1] = 128.0f;
    n->colD0[2] = 128.0f;
    n->colD0[3] = 128.0f;
    n->iE0 = 0x44;
    n->iE8 = 0x5000D;
    return n;
}

/* 0x001B15D0: emit the draw commands of a type-9 node into cmd; returns the new end. Stack args. */
uint32_t *r4b_NodeEmit(uint32_t *cmd, R4bNode *n)
{
    uint32_t *p;
    R4bPart *part;
    int i;
    if (n->texB4 && r4_g40F324 != n->texB4)
        r4_Set40F324(cmd, n->texB4);
    if (n->selB8 && r4_g40F208 != n->selB8)
        r4_Select40F208(cmd, n->selB8);
    p = sub_001B9CA0(cmd, n->iCC);
    for (i = 0, part = n->parts; i < n->count; i++, part++) {
        float *fc = part->mFC;
        float *w = fc - 0x2F;     /* part->m40 */
        sub_001AD7C0(fc, w, w + 0x1F);
        r4_MatCopyRotation(fc + 0x10, fc);
    }
    sub_001A69C0(n->iE0, n->iE4);
    p[0] = n->iE8;
    p[1] = n->iEC;
    p[2] = 0x47;
    p[3] = 0;
    r4b_g41312C += ((R4bTexInfo *)n->pBC)->size0C;
    sub_001A32F0(n, r4b_g40F334->m1F0);
    return p + 4;
}

/* 0x001B1FC0: clear both node bucket tables. No inputs. */
void r4b_NodeBucketsClear(void)
{
    int i;
    for (i = 0; i < 0x33; i++)
        r4_g412F80[i] = 0;
    for (i = 0; i < 0x33; i++)
        r4_g413060[i] = 0;
}

/* 0x001B1FE0: unlink the bucket chain of every node in 0x00412F80. No inputs. */
void r4b_NodeBucketsUnlink(void)
{
    unsigned i;
    for (i = 0; i < 0x33; i++)
        if (r4_g412F80[i])
            r4_g412F80[i]->linkA4 = 0;
}

/* 0x001B24E0: run the hooks and per-type functions of every node in 0x00413060; returns arg. Stack args. */
int r4b_NodeRunAll(int arg)
{
    unsigned i;
    R4bNode *n;
    R4bHook *h;
    R4bNodeFn *fp;
    r4_g40F208 = 0;
    r4b_g40F330 = 0;
    r4b_g40F388 = 0;
    for (i = 0; i < 0x33; i++) {
        for (n = r4_g413060[i]; n; n = n->linkA4) {
            for (h = n->hooksA8; h; h = h->next)
                if (h->fn)
                    h->fn(arg, n, h);
            for (fp = n->fns9C; *fp; fp++)
                (*fp)(arg, n);
            for (h = n->hooksAC; h; h = h->next)
                if (h->fn)
                    h->fn(arg, n, h);
        }
    }
    return arg;
}

/* 0x001B25B0: reset node links and matrices and pick the per-type tables. Stack args. */
void r4b_NodeReset(R4bNode *n)
{
    int t;
    n->i90 = 0;
    n->child = 0;
    n->next = 0;
    n->parent = 0;
    n->iA0 = 0;
    n->linkA4 = 0;
    n->hooksA8 = 0;
    n->hooksAC = 0;
    sub_001AD940(n->m40);
    sub_001AD940(n->m00);
    t = n->type8C;
    if ((unsigned)t < 18)
        n->p98 = r4b_g377FA8[t];
    else
        n->p98 = r4b_g377FA8[0];
    if ((unsigned)t < 18)
        n->fns9C = r4b_g378040[t];
    else
        n->fns9C = r4b_g378040[0];
    n->f94 = 16770000.0f;
}

/* 0x001B26C0: decompose matrix of n, reset its world matrix to the default; returns n. Stack args. */
R4bNode *r4b_NodeRebuild(R4bNode *n)
{
    float tmp[16];
    sub_001AD940(tmp);
    sub_001ADEE0(n, tmp, tmp + 4, tmp + 8);
    n->m00[15] = 1.0f;
    sub_001ADE10(n->m40, r4b_g40F20C, r4b_g40F20C, r4b_g40F20C, r4b_g40F20C);
    n->parent = 0;
    return n;
}
