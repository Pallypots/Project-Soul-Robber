/* Area m2, file gs1: security-cookie functions (compiled with /GS). Names inferred. */
#include <stdint.h>

extern void *volatile m1_poolAux3E26D0[];
extern void *m1_pools3E26A8[];
extern const char m2_strRegion26BF08[];
extern const char m2_strRegionNone26BEFC[];
int   a6b_Printf3(char *buf, int size, const char *fmt, ...);
void *sub_00047560(void *pool, const char *name, int size);
int   sub_00047740(void *p);
void  r1c_HeapSetup(void *pool, int v);

/* 0x538A0: open a memory region in pool slot (waits until the slot's saved pointer is free): name it "REGION: <name>" (or "-"), carve it from the slot's heap (slot 10 uses the heap in slot 8; other slots past 8 hang), remember the old heap and make the region the slot's heap. Returns the new heap. */
void *m2_RegionOpen538A0(int slot, const char *name, int size) {
    char buf[0x80];
    void *h, *r;
    while (m1_poolAux3E26D0[slot] != 0) ;
    if (name != 0) a6b_Printf3(buf, 0x7F, m2_strRegion26BF08, name);
    else a6b_Printf3(buf, 0x7F, m2_strRegionNone26BEFC);
    if (slot == 10) h = m1_pools3E26A8[8];
    else {
        if (slot >= 9) for (;;) ;
        h = m1_pools3E26A8[slot];
    }
    r = sub_00047560(h, buf, size);
    m1_poolAux3E26D0[slot] = m1_pools3E26A8[slot];
    m1_pools3E26A8[slot] = r;
    r1c_HeapSetup(m1_pools3E26A8[slot], sub_00047740(r));
    return m1_pools3E26A8[slot];
}

typedef struct M2Pig1 { uint8_t unk00[0x1C]; uint32_t flags1C; uint8_t unk20[0x20]; void *tex40; void *anim44; } M2Pig1;
typedef struct M2PigEnt1 { uint8_t unk00[8]; const char *dir8; uint8_t unk0C[0x1C]; M2Pig1 *pig28; } M2PigEnt1;
typedef struct M2PigCtx1 { uint8_t unk00[0x20]; void *owner20; uint8_t unk24[0x20]; void *list44; } M2PigCtx1;
extern const char m1_fmtPig25FBE8[];
extern const char m2_fmtTxa25FC40[];
char *sub_001C7DB0(char *d, const char *s, int n);
void *rtc_TexFindOrLoad(const char *path);
void *sub_00037570(const char *path, int flags);
void  a60_AttachEff6974(void *owner, void *list, void *tex, void *anim);

/* 0x1E270: load a .pig texture and its .txa animation named by the two 8-character fields of src, under the entry's directory; attach them to the entry's pig (flag 4) or, without one, to the context's owner list. Returns the record size 0x10. Security-cookie function. */
int m2_PigLoad1E270(M2PigCtx1 *c, const char *src, M2PigEnt1 *e) {
    char name[12];
    char path[0x100];
    void *tex, *anim;
    sub_001C7DB0(name, src, 8);
    name[8] = 0;
    a6b_Printf3(path, 0xFF, m1_fmtPig25FBE8, e->dir8, name);
    tex = rtc_TexFindOrLoad(path);
    sub_001C7DB0(name, src + 8, 8);
    name[8] = 0;
    a6b_Printf3(path, 0xFF, m2_fmtTxa25FC40, e->dir8, name);
    anim = sub_00037570(path, 0x40);
    if (e->pig28 == 0) {
        a60_AttachEff6974(c->owner20, c->list44, tex, anim);
    } else {
        e->pig28->flags1C |= 4;
        e->pig28->tex40 = tex;
        e->pig28->anim44 = anim;
    }
    return 0x10;
}

typedef struct M2MdlEnt1 { uint8_t unk00[8]; const char *dir8; uint8_t unk0C[0x1C]; void *pig28; void *node2C; } M2MdlEnt1;
typedef struct M2MdlCtx1 { uint8_t unk00[0x20]; void *pose20; uint8_t unk24[0xC]; void *anim30; void *lod34; } M2MdlCtx1;
extern const char m2_fmtMlb25FBF8[];
void *a5b_AllocCur(int size, int a, int tag);
void  r4e_NodeInit(void *n);
void *sub_00083030(void *node, int a, M2MdlCtx1 *c);
void *sub_0007FC60(void);
int   sub_00083820(void *anim, const char *path);
int  *sub_00083140(void *anim, int i);
void  sub_000831A0(void *anim, int id, int node);
void  rtc_ApplyValueToModel(void *anim, void *pose);

/* 0x1DFD0: load the .mlb motion library named by the record's 8-character field under the entry's directory: create the entry's node and the context's animation set, and when the entry has no pig and the library loaded, start its first animation and apply it to the pose. Returns the record size 8. Security-cookie function. */
int m2_MlbLoad1DFD0(M2MdlCtx1 *c, const char *src, M2MdlEnt1 *e) {
    char name[12];
    char path[0x100];
    int ok;
    sub_001C7DB0(name, src, 8);
    name[8] = 0;
    a6b_Printf3(path, 0xFF, m2_fmtMlb25FBF8, e->dir8, name);
    e->node2C = a5b_AllocCur(0xE0, 0, 0xDF1);
    r4e_NodeInit(e->node2C);
    c->anim30 = sub_00083030(e->node2C, 0, c);
    c->lod34 = sub_0007FC60();
    ok = sub_00083820(c->anim30, path);
    if (e->pig28 == 0 && ok != 0) {
        sub_000831A0(c->anim30, 0, *sub_00083140(c->anim30, 0));
        rtc_ApplyValueToModel(c->anim30, c->pose20);
    }
    return 8;
}

typedef struct M2HmEnt1 { uint8_t link00[0xC]; int32_t iC; uint8_t unk10[0x30]; } M2HmEnt1;
typedef struct M2HmFile1 { uint8_t unk00[8]; uint32_t n8; uint8_t unk0C[4]; M2HmEnt1 e[1]; } M2HmFile1;
extern const char m2_fmtHm266DA8[];
void a4c_ListAppend(void *list, void *node);

/* 0x3AC00: load the height-map file of world (a, b) and link all its entries (cleared) into list; -1 when the file is missing, else 0. Security-cookie function. */
int m2_HmLoad3AC00(uint8_t *list, int a, int b) {
    char path[0x80];
    M2HmFile1 *f;
    M2HmEnt1 *e;
    uint32_t i;
    a6b_Printf3(path, 0x7F, m2_fmtHm266DA8, a, b, a, b);
    f = (M2HmFile1 *)sub_00037570(path, 0x40);
    if (f == 0) return -1;
    *(int32_t *)(list + 0x10) = 0;
    for (i = 0, e = f->e; i < f->n8; i++, e++) {
        a4c_ListAppend(list, e);
        e->iC = 0;
    }
    return 0;
}

typedef struct M2TaskKey1 { uint8_t unk00[0x1A]; uint8_t kind1A; uint8_t unk1B; uint32_t packed1C; uint8_t unk20[0xC]; int32_t a2C; int32_t b30; uint8_t unk34[0xF4]; } M2TaskKey1;
void r6d_MemFill(void *d, int v, int n);
int  r6f_TaskFindMatch(void *list, M2TaskKey1 *key, int mode);

/* 0x8E5E0: look for a kind-8 task matching (a, b, c) in list: builds a cleared key with a, b and the packed id c | b << 8 | a << 20 and searches in mode 6. 0 for no list. Security-cookie function. */
int m2_TaskFind8E5E0(void *list, int a, int b, int c) {
    M2TaskKey1 k;
    uint32_t w;
    if (list == 0) return 0;
    r6d_MemFill(&k, 0, sizeof(k));
    w = k.packed1C;
    k.a2C = a;
    w ^= ((uint32_t)a << 20 ^ w) & 0x0FF00000;
    k.b30 = b;
    w ^= ((uint32_t)b << 8 ^ w) & 0x000FFF00;
    w ^= ((uint32_t)c ^ w) & 0xFF;
    k.kind1A = 8;
    k.packed1C = w;
    return r6f_TaskFindMatch(list, &k, 6);
}

typedef struct M2LgtTask1 { uint8_t unk00[0x18]; uint16_t flags18; uint8_t unk1A[2]; void *path1C; int8_t kind20; int8_t heap21; uint8_t unk22[2]; uint32_t flags24; void *res28; } M2LgtTask1;
extern uint8_t *r2d_ctx;
int   sub_0008BCD0(int k);
void  a6b_SetHeap(int a, int heap);
void  m1_PathLgt8EFB0(char *out, int a, void *path);
void *r6b_LookupSelect(const char *path, int a);
void  sub_0003D7B0(void *res, void *ctx);

/* 0x8F000: load the light resource of a kind-2 task once (flag 2): select its heap, build its .lgt path and look it up; when missing, create an empty one (flag 2 in +0x24). Clears flags 4/8. -1 for other task kinds, else 0. Security-cookie function. */
int m2_LgtLoad8F000(M2LgtTask1 *t, int a) {
    char path[0x40];
    void *m;
    if (t->kind20 != 2) return -1;
    if (!(t->flags18 & 2)) {
        a6b_SetHeap(2, sub_0008BCD0(t->heap21));
        m1_PathLgt8EFB0(path, a, t->path1C);
        t->res28 = r6b_LookupSelect(path, 0);
        if (t->res28 == 0) {
            m = a5b_AllocCur(0x8D0, 0, 0xD5);
            sub_0003D7B0(m, r2d_ctx);
            t->res28 = m;
            t->flags24 |= 2;
        }
        t->flags18 = (uint16_t)((t->flags18 & ~0xCu) | 2);
    }
    return 0;
}

typedef struct M2DfdObj1 { uint8_t unk00[0x28]; uint8_t take28[0x10]; void *res38; } M2DfdObj1;
typedef struct M2DfdTask1 { uint8_t unk00[0x18]; uint16_t flags18; uint8_t unk1A[2]; void *path1C; int8_t kind20; int8_t heap21; uint8_t unk22[2]; uint32_t flags24; uint8_t holder28[1]; } M2DfdTask1;
void m1_PathDfd8ED70(char *out, void *path);
void a6b_Take10(void *src, int *out);
void r6b_HolderSet(void *holder, int v);

/* 0x8EDC0: load the .dfd resource of a kind-2 task once (flag 2): select its heap, look it up into the object, take its value into the task's holder and mirror whether it is set in flag 2 of +0x24. Clears flags 4/8. -1 for no object or other task kinds, else 0. Security-cookie function. */
int m2_DfdLoad8EDC0(M2DfdObj1 *o, M2DfdTask1 *t) {
    int v;
    char path[0x40];
    int volatile r = 0;
    if (o == 0) return -1;
    if (t->kind20 != 2) { r = -1; return r; }
    if (!(t->flags18 & 2)) {
        a6b_SetHeap(2, sub_0008BCD0(t->heap21));
        m1_PathDfd8ED70(path, t->path1C);
        o->res38 = r6b_LookupSelect(path, 0);
        a6b_Take10(o->take28, &v);
        r6b_HolderSet(t->holder28, v);
        if (v) t->flags24 |= 2;
        else t->flags24 &= ~2u;
        t->flags18 = (uint16_t)((t->flags18 & ~0xCu) | 2);
    }
    return r;
}


typedef struct M2Demo1 { uint8_t unk00[4]; int32_t id4; uint8_t unk08[0x40]; void *models48; uint8_t *light4C; } M2Demo1;
extern const char a80_str26FA20[];
extern const char a80_str26FACC[];
extern const char m2_fmtLight26FB24[];
int   a6b_Printf2(char *buf, const char *fmt, ...);
void  sub_000902A0(void *tbl, const char *path);
void *r6b_FwdGetX04(void *list);
void *r6b_FwdListHeadRef(void *list);
int   r6b_FwdIterEqual(void **a, void **b);
void *r6b_FwdHolderData(void **it);
int   rtc_TableEntry0Get8(void *m);
void *sub_000900A0(void *tbl, int key);
void  r6f_ModelSetApply(void *m, void *light);
void  r6b_FwdIterNext(void **it);

/* 0x899C0: load the demo's light_type.txt table and give every model of the demo the light type its key selects. Security-cookie function. */
void m2_DemoLights899C0(M2Demo1 *d) {
    void *it, *end;
    char dir[0x40];
    char path[0x100];
    a6b_Printf2(dir, a80_str26FACC, a80_str26FA20, d->id4);
    a6b_Printf2(path, m2_fmtLight26FB24, dir, d->id4);
    sub_000902A0(d->light4C + 0x24, path);
    it = r6b_FwdGetX04(d->models48);
    end = r6b_FwdListHeadRef(d->models48);
    while (!r6b_FwdIterEqual(&it, &end)) {
        void *m = r6b_FwdHolderData(&it);
        r6f_ModelSetApply(m, sub_000900A0(d->light4C + 0x24, rtc_TableEntry0Get8(m)));
        r6b_FwdIterNext(&it);
    }
}


typedef struct M2SesBody1 { uint32_t w[0x114]; } M2SesBody1;
extern const char m2_fmtSes26CA4C[];
extern const char m2_fmtSes26CA6C[];
int r1d_FileWrite(const char *path, void *data, int size, int a);

/* 0x5C0E0: save a sound-effect set as a .ses file ("SES" header, version 3, then 0x450 bytes copied from src) named after world k (area 0 for world 1) and number n. -1 for no source, else the write result. Security-cookie function. */
int m2_SesSave5C0E0(const uint32_t *src, int unused, int k, int n) {
    char path[0x100];
    uint32_t *h;
    if (src == 0) return -1;
    h = (uint32_t *)a5b_AllocCur(0x460, 0, 0x365);
    if (h != 0) {
        h[0] = 0; h[1] = 0; h[2] = 0; h[3] = 0;
        h[0] = 0x534553;
        h[1] = 3;
    }
    *(M2SesBody1 *)(h + 4) = *(const M2SesBody1 *)src;
    switch (k) {
    case 1: a6b_Printf3(path, 0x7F, m2_fmtSes26CA4C, 1, n); break;
    case 3: a6b_Printf3(path, 0x7F, m2_fmtSes26CA6C, 3, k, n); break;
    default: a6b_Printf3(path, 0x7F, m2_fmtSes26CA6C, k, k, n); break;
    }
    return r1d_FileWrite(path, h, 0x460, 0);
}


typedef struct M2DtTbl1 { uint8_t unk00[0x24]; int32_t data24, size28; } M2DtTbl1;
typedef struct M2DtDemo1 { uint8_t unk00[4]; int32_t id4; uint8_t unk08[0x14]; int32_t data1C, size20; } M2DtDemo1;
extern const char m2_fmtDtt26FADC[];
void r6b_DemoTableInit(M2DtTbl1 *t);
int  r6e_TaskLookup(M2DtTbl1 *t, const char *path);
int  r6f_BlobMerge(M2DtTbl1 *dst, M2DtTbl1 *src);
void r6e_TaskReleaseHeld(M2DtTbl1 *t);

/* 0x898C0: load demo table (a, b) (.dtt) and merge it with the demo's current table; on success the merged data replaces the demo's (ownership moves out of the temporary). Both temporaries are released. Returns 0 or the first error. Security-cookie function. */
int m2_DemoTable898C0(M2DtDemo1 *d, int a, int b) {
    M2DtTbl1 cur, nw;
    char dir[0x40];
    char path[0x40];
    int r = 0, e;
    r6b_DemoTableInit(&cur);
    r6b_DemoTableInit(&nw);
    a6b_Printf2(dir, a80_str26FACC, a80_str26FA20, d->id4);
    a6b_Printf2(path, m2_fmtDtt26FADC, dir, d->id4, d->id4, b, a);
    e = r6e_TaskLookup(&nw, path);
    if (e == 0) {
        cur.data24 = d->data1C;
        cur.size28 = d->size20;
        e = r6f_BlobMerge(&cur, &nw);
        if (e == 0) {
            d->data1C = cur.data24;
            d->size20 = cur.size28;
            cur.data24 = 0;
            cur.size28 = 0;
        } else r = e;
    } else r = e;
    r6e_TaskReleaseHeld(&cur);
    r6e_TaskReleaseHeld(&nw);
    return r;
}

typedef struct M2SecRec1 { struct M2SecRec1 *next0; uint32_t w[0x11B]; } M2SecRec1;
typedef struct M2SecList1 { int32_t n0; M2SecRec1 *first4; uint8_t unk08[8]; int32_t v10, v14; } M2SecList1;
extern const char m2_fmtSec26CC68[];

/* 0x5C6D0: save the sound-effect placement list as a .sec file ("SEC" header, version 4, count, every 0x470-byte record, the two list values and two zero words) named after world (a, b). -1 when out of memory, else the write result. Security-cookie function. */
int m2_SecSave5C6D0(M2SecList1 *l, int a, int b) {
    char path[0x100];
    int size = l->n0 * 0x470 + 0x20;
    int32_t *h, *p;
    M2SecRec1 *e;
    h = (int32_t *)a5b_AllocCur(size, 0, 0x56C);
    if (h == 0) return -1;
    h[0] = 0; h[1] = 0; h[2] = 0; h[3] = 0;
    h[0] = 0x434553;
    h[1] = 4;
    h[2] = l->n0;
    p = h + 4;
    for (e = l->first4; e != 0; e = e->next0) {
        *(M2SecRec1 *)p = *e;
        p += 0x470 / 4;
    }
    p[0] = l->v10;
    p[1] = l->v14;
    p += 2;
    p[0] = 0;
    p[1] = 0;
    a6b_Printf3(path, 0x7F, m2_fmtSec26CC68, a, b);
    return r1d_FileWrite(path, h, size, 0);
}

typedef struct M2ShObj1 { uint8_t unk00[0xC]; uint32_t flagsC; uint8_t unk10[0x18]; void *node28; uint8_t unk2C[0x20]; void *tex4C; } M2ShObj1;
typedef struct M2ShEnt1 { uint8_t unk00[0x28]; void *pig28; } M2ShEnt1;
extern const char m2_strCubeShdw25FCF8[];
extern const char m2_strCirShdw25FD40[];
extern const char r1g_srcCharUnit25FC08[];
extern int m2_g37C4BC;
uint8_t *a5b_CurHeapOp47560(const char *file, int line);
uint8_t *sub_001B2DA0(void *dst, uint8_t *heap, void *model, int flags);
void  a5b_HeapShrink(uint8_t *p, int size);
void  r4e_Node1Init(void *n);
void  r4b_Node5SetSource(void *n, void *a, int b, int c, int d, void *src);
void  sub_0001FE70(M2ShObj1 *o, void *model, void *node, int a, float scale);

/* 0x22040: set up a character's shadow: load the shadow cube model and circle texture, build the model in the current heap (shrunk to fit), make a node using it and, for entries without a pig, attach it at scale 1. Always 0. Security-cookie function. */
int m2_ShadowInit22040(M2ShObj1 *o, int unused, M2ShEnt1 *e) {
    char path[0x100];
    void *mdl, *m;
    uint8_t *h;
    a6b_Printf3(path, 0xFF, m2_strCubeShdw25FCF8);
    mdl = sub_00037570(path, 0x40);
    a6b_Printf3(path, 0xFF, m2_strCirShdw25FD40);
    o->tex4C = rtc_TexFindOrLoad(path);
    m = a5b_AllocCur(0x30, 0, 0xE83);
    o->node28 = a5b_AllocCur(0xF0, 0, 0xE84);
    h = a5b_CurHeapOp47560(r1g_srcCharUnit25FC08, 0xE89);
    a5b_HeapShrink(h, sub_001B2DA0(m, h, mdl, m2_g37C4BC) - h);
    r4e_Node1Init(o->node28);
    r4b_Node5SetSource(o->node28, 0, 0, 0, 0, m);
    o->flagsC |= 0x10;
    if (e->pig28 == 0) sub_0001FE70(o, m, o->node28, 0, 1.0f);
    return 0;
}

extern const char m2_strDome25FCC8[];

/* 0x22150: same as 0x22040 with the dome shadow model (allocation tags 0xEAC/0xEAD/0xEB2). Always 0. Security-cookie function. */
int m2_DomeShadowInit22150(M2ShObj1 *o, int unused, M2ShEnt1 *e) {
    char path[0x100];
    void *mdl, *m;
    uint8_t *h;
    a6b_Printf3(path, 0xFF, m2_strDome25FCC8);
    mdl = sub_00037570(path, 0x40);
    a6b_Printf3(path, 0xFF, m2_strCirShdw25FD40);
    o->tex4C = rtc_TexFindOrLoad(path);
    m = a5b_AllocCur(0x30, 0, 0xEAC);
    o->node28 = a5b_AllocCur(0xF0, 0, 0xEAD);
    h = a5b_CurHeapOp47560(r1g_srcCharUnit25FC08, 0xEB2);
    a5b_HeapShrink(h, sub_001B2DA0(m, h, mdl, m2_g37C4BC) - h);
    r4e_Node1Init(o->node28);
    r4b_Node5SetSource(o->node28, 0, 0, 0, 0, m);
    o->flagsC |= 0x10;
    if (e->pig28 == 0) sub_0001FE70(o, m, o->node28, 0, 1.0f);
    return 0;
}

extern const char m2_strCscm25FF28[];
extern const char m2_strCscl25FF20[];
extern const char m2_fmtSysPod25FF08[];

/* 0x21EE0: set up a character's shadow from a size record {kind, scale}: kinds 0-1 use the medium shadow model and kind 2 the large one (kind 0 at half scale); otherwise as 0x22040 (tags 0xE5A/0xE5B/0xE60). Returns the record size 8. Security-cookie function. */
int m2_SizedShadowInit21EE0(M2ShObj1 *o, int32_t *p, M2ShEnt1 *e) {
    struct { float scale; const char *names[3]; } v;
    char path[0x100];
    void *mdl, *m;
    uint8_t *h;
    v.names[0] = m2_strCscm25FF28;
    v.names[1] = m2_strCscm25FF28;
    v.names[2] = m2_strCscl25FF20;
    v.scale = ((float *)p)[1];
    if (p[0] == 0) v.scale *= 0.5f;
    a6b_Printf3(path, 0xFF, m2_fmtSysPod25FF08, v.names[p[0]]);
    mdl = sub_00037570(path, 0x40);
    a6b_Printf3(path, 0xFF, m2_strCirShdw25FD40);
    o->tex4C = rtc_TexFindOrLoad(path);
    m = a5b_AllocCur(0x30, 0, 0xE5A);
    o->node28 = a5b_AllocCur(0xF0, 0, 0xE5B);
    h = a5b_CurHeapOp47560(r1g_srcCharUnit25FC08, 0xE60);
    a5b_HeapShrink(h, sub_001B2DA0(m, h, mdl, m2_g37C4BC) - h);
    r4e_Node1Init(o->node28);
    r4b_Node5SetSource(o->node28, 0, 0, 0, 0, m);
    o->flagsC |= 0x10;
    if (e->pig28 == 0) sub_0001FE70(o, m, o->node28, 0, v.scale);
    return 8;
}

typedef struct M2EdgNode1 { uint8_t unk00[0xC0]; int32_t nC0; } M2EdgNode1;
typedef struct M2EdgCtx1 { uint8_t unk00[0x20]; void *mats20; uint8_t unk24[4]; M2EdgNode1 *node28; void *bones2C; } M2EdgCtx1;
extern const char m2_fmtEdg25FC30[];
extern uint8_t m2_g42C980[];
void r4b_NodeInitType12(void *n);
uint8_t *sub_001B8800(void *dst, uint8_t *heap, void *model, int flags);
void sub_001B85B0(void *bones, M2EdgNode1 *n);
void r4b_NodeCSetMats(M2EdgNode1 *n, void *mats);

/* 0x1E110: load the .edg edge model named by the record's 8-character field: build its node in the current heap (shrunk to fit) and, for entries without a pig, give it bone matrices (0x110 bytes each) bound to the context's matrices. Returns the record size 8 (also when the file is missing). Security-cookie function. */
int m2_EdgLoad1E110(M2EdgCtx1 *c, const char *src, M2ShEnt1 *e) {
    char name[12];
    char path[0x100];
    void *mdl, *m, *k;
    uint8_t *h;
    sub_001C7DB0(name, src, 8);
    name[8] = 0;
    a6b_Printf3(path, 0xFF, m2_fmtEdg25FC30, *(const char **)((uint8_t *)e + 8), name);
    mdl = sub_00037570(path, 0x40);
    if (mdl == 0) return 8;
    c->node28 = (M2EdgNode1 *)a5b_AllocCur(0xF0, 0, 0xE2D);
    r4b_NodeInitType12(c->node28);
    m = a5b_AllocCur(0x30, 0, 0xE2F);
    h = a5b_CurHeapOp47560(r1g_srcCharUnit25FC08, 0xE32);
    a5b_HeapShrink(h, sub_001B8800(m, h, mdl, m2_g37C4BC) - h);
    r4b_Node5SetSource(c->node28, m2_g42C980, 0, 0, 0, m);
    if (e->pig28 == 0) {
        k = a5b_AllocCur(c->node28->nC0 * 0x110, 0, 0xE3B);
        sub_001B85B0(k, c->node28);
        r4b_NodeCSetMats(c->node28, c->mats20);
        c->bones2C = k;
    }
    return 8;
}
