/* Area r4b: type-5 node helpers around 0x001BB810-0x001BBA1C (r4b_9). Names inferred. */
#include "r4b.h"

/* 0x001BB810: initialise a type-5 node; returns n. Stack args. */
R4bNode5 *r4b_NodeInitType5(R4bNode5 *n)
{
    n->type8C = 5;
    sub_001B25B0(n);
    n->flags90 |= 0x100;
    n->iB0 = 0;
    n->iB4 = 0;
    n->iB8 = 0;
    n->srcBC = 0;
    n->count = 0;
    n->items = 0;
    n->iDC = 0;
    n->iE4 = 0;
    n->colC8[0] = 128.0f;
    n->colC8[1] = 128.0f;
    n->colC8[2] = 128.0f;
    n->colC8[3] = 128.0f;
    n->iD8 = 0x44;
    n->iE0 = 0x5000D;
    return n;
}

/* 0x001BB8B0: set the sources of a type-5 node. Stack args (n a b unused unused src). */
void r4b_Node5SetSource(R4bNode5 *n, int a, int b, int unused1, int unused2, R4bNode5Src **src)
{
    n->iB4 = a;
    n->iB8 = b;
    n->srcBC = src;
    n->count = (*src)->i08;
}

/* 0x001BB930: apply the blend state of a type-5 node; returns cmd. Stack args (cmd n). */
uint32_t *r4b_Node5Apply(uint32_t *cmd, R4bNode5 *n)
{
    if (n->flags90 & 0x100) {
        sub_001A69C0(n->iD8, n->iDC);
        if (n->iE0 == 0x51001 && n->iE4 == 0) {
            sub_001A6E80(0);
            return cmd;
        }
        sub_001A6E80(1);
    }
    return cmd;
}

/* 0x001BBA00: set +0xE0/+0xE4. Stack args. */
void r4b_Node5SetE0(R4bNode5 *n, int a, int b)
{
    n->iE0 = a;
    n->iE4 = b;
}

/* 0x001BBBA0: attach item array base to a type-5 node and link the root item (items become type 6). Stack args (base n). */
void r4b_Node5AttachItems(R4bNode5Item *base, R4bNode5 *n)
{
    int i;
    int root;
    R4bNode5Item *p;
    n->items = base;
    for (i = 0; i < n->count; i++) {
        base[i].type8C = 6;
        sub_001B25B0(&base[i]);
        base[i].flags90 |= 0x140;
    }
    root = (*n->srcBC)->root0C;
    sub_001BBA20(n, n->items, root);
    p = &base[root];
    n->child88 = p;
    p->parent80 = n;
}

/* 0x001BBC40: emit a type-6 node, re-sending texture and matrix state only when it differs from the previous node. Stack args (cmd n). */
uint32_t *r4b_Node6Emit(uint32_t *cmd, R4bNode6 *n)
{
    int changed;
    R4bNode6 *prev;
    if (!n->itemsC4)
        return cmd;
    changed = 0;
    if (n->texC8 && r4_g40F324 != n->texC8) {
        cmd = r4_Set40F324(cmd, n->texC8);
        changed = 1;
    }
    if (n->selCC && r4_g40F208 != n->selCC)
        cmd = r4_Select40F208(cmd, n->selCC);
    prev = n->prevA0;
    if (!prev)
        changed |= 2;
    else if (prev->type8C != 6)
        changed |= 4;
    else if (!prev->itemsC4)
        changed |= 8;
    else {
        if (prev->texD0 != n->texD0)
            changed |= 0x10;
        if (prev->modelC0 != n->modelC0)
            changed |= 0x20;
    }
    if (changed & 0x1E)
        cmd = sub_001B9CA0(cmd, n->texD0);
    if (!(n->flags90 & 0x100))
        sub_001A69C0(n->iF8, n->iFC);
    if (changed & 0x2F)
        cmd = r4b_MatUpload(n->modelC0->m40, cmd);
    sub_001A2EB0(n);
    r4b_g41312C += n->modelC0->infoBC->subs[n->subB4].size0C;
    return cmd;
}

/* 0x001BBD70: set the global factor at 0x00412F34. Stack args. */
void r4b_SetFactor(float f)
{
    r4b_g412F34 = f;
}

/* 0x001BBD80: the global factor at 0x00412F34 (x87 result). No inputs. */
float r4b_GetFactor(void)
{
    return r4b_g412F34;
}

/* 0x001BBD90: reset the renderer globals. No inputs. */
void r4b_RenderReset(void)
{
    r4b_g412F34 = 1.0f;
    r4b_TexSetGroup(0xFFFF);
    r4b_NodeBucketsClear();
    r4b_g412F30 = 0;
    r4_Set40F328(0);
}

/* 0x001BBDD0: field +8. Stack args. */
int r4b_Get8(const int32_t *p)
{
    return p[2];
}

/* 0x001BC030: true if p is a 'P2OD' header of version 0x80. Stack args. */
int r4b_IsP2od(const R4bP2od *p)
{
    if (p->magic != 0x444F3250)
        return 0;
    return p->w4 == 0x80;
}

/* 0x001BC050: address of chunk i of an offset-table blob. Stack args. */
uint8_t *r4b_BlobChunk(uint8_t *base, int i)
{
    return base + ((int32_t *)base)[i + 1];
}

/* 0x001BC060: stop the four voices and free every voice buffer. Stack args (unused s). */
void r4b_VoiceSetFree(int unused, R4bVoiceSet *s)
{
    int i;
    sub_001D3AB0(0, 0);
    sub_001D3AB0(1, 0);
    sub_001D3AB0(2, 0);
    sub_001D3AB0(3, 0);
    for (i = 0; i < s->count; i++) {
        if (s->bufs[i].buf[0]) {
            sub_001BD587(s->hnd[i][0].h);
            sub_001C885F(s->bufs[i].buf[0]);
            s->bufs[i].buf[0] = 0;
        }
        if (s->bufs[i].buf[1]) {
            sub_001BD587(s->hnd[i][1].h);
            sub_001C885F(s->bufs[i].buf[1]);
            s->bufs[i].buf[1] = 0;
        }
        if (s->bufs[i].buf[2]) {
            sub_001BD587(s->hnd[i][2].h);
            sub_001C885F(s->bufs[i].buf[2]);
            s->bufs[i].buf[2] = 0;
        }
        if (s->bufs[i].buf[3]) {
            sub_001BD587(s->hnd[i][3].h);
            sub_001C885F(s->bufs[i].buf[3]);
            s->bufs[i].buf[3] = 0;
        }
    }
}

/* 0x001BC130: allocate one voice resource and its 128-byte aligned physical buffer; returns 1 on success. Stack args. */
int r4b_VoiceAlloc(int a, int b, int fmt, void **res, void **mem, int32_t *data, int32_t *size)
{
    void *r;
    void *phys;
    int n;
    int32_t tmp;
    r = sub_001C8864(0x14);
    if (!r)
        return 0;
    n = sub_002039CA(a, b, 1, fmt, 0, 0, r, 0, 0);
    n = ((n + 0x7F) >> 7) << 7;
    phys = sub_001BD517(n, -1, 0x80, 4);
    if (!phys) {
        sub_001C885F(r);
        return 0;
    }
    sub_001D6030(r, phys);
    *data = a;
    *res = r;
    *mem = phys;
    *size = n;
    sub_001D6210(r, 0, &tmp, 0, 0);
    *data = tmp;
    return 1;
}
