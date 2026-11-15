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
