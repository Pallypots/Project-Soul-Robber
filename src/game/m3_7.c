/* Area m3, file 7: line-of-sight probe, record table restore. Names inferred. */
#include <stdint.h>

typedef struct M3Ctx7 { uint8_t unk00[0x54]; void *col54; } M3Ctx7;
extern M3Ctx7 *m1_scene42C8E4;
void a3c_VecCopy(float *dst, const float *src);
float sub_001A3EE0(float a);
float sub_001A3ED0(float a);
void rbj_VecScale(float *d, const float *s, float k);
void r4e_VecAdd4(float *d, const float *a, const float *b);
void *r1b_Pool80970(void);
void sub_000824F0(void *col, void *q, float *from, float *to, int a, int b);
int  r6c_PickNearest(void *q, float *from, float *to);

/* 0xF6510: probe from half a unit below the object's position towards angle a at distance d; returns 1 when the collision query reports a hit, 0 for a null object. */
int m3_ProbeDirF6510(uint8_t *o, float a, float d) {
    float to[4], from[4]; void *q;
    if (o == 0) return 0;
    a3c_VecCopy(from, (float *)(o + 0x60));
    from[1] = -0.5f;
    from[3] = 1.0f;
    to[0] = sub_001A3EE0(a);
    to[2] = sub_001A3ED0(a);
    to[3] = 0.0f; to[1] = 0.0f;
    rbj_VecScale(to, to, d);
    r4e_VecAdd4(to, to, from);
    q = r1b_Pool80970();
    sub_000824F0(m1_scene42C8E4->col54, q, from, to, 0, 0);
    return r6c_PickNearest(q, from, to) != 0;
}

typedef struct M3R34 { uint32_t w[13]; } M3R34;
extern M3R34 m1_live3ED540[10];
extern M3R34 aab_rec34[10];
extern float m3_tblScaleA3ED758;
extern float m3_tblScaleB3ED75C;
extern int m3_tblSel3ED760;
extern int m3_tblCnt3ED764;

/* 0xA9DC0: reset the table settings (scale 1, scale 2, selection -1, count 0) and restore the ten 0x34-byte records from their saved copy. */
void m3_TblRestoreA9DC0(void) {
    m3_tblScaleA3ED758 = 1.0f;
    m3_tblCnt3ED764 = 0;
    m3_tblSel3ED760 = -1;
    m3_tblScaleB3ED75C = 2.0f;
    aab_rec34[0] = m1_live3ED540[0];
    aab_rec34[1] = m1_live3ED540[1];
    aab_rec34[2] = m1_live3ED540[2];
    aab_rec34[3] = m1_live3ED540[3];
    aab_rec34[4] = m1_live3ED540[4];
    aab_rec34[5] = m1_live3ED540[5];
    aab_rec34[6] = m1_live3ED540[6];
    aab_rec34[7] = m1_live3ED540[7];
    aab_rec34[8] = m1_live3ED540[8];
    aab_rec34[9] = m1_live3ED540[9];
}

typedef struct M3Flg7 { uint8_t unk00[0xC]; uint32_t fC; uint32_t f10; } M3Flg7;
typedef struct M3Mgr7 { uint8_t unk00[0x8C]; M3Flg7 *f8C; uint8_t unk90[0x14]; int16_t hA4; } M3Mgr7;
M3Mgr7 *sub_000FE3D0(void);
M3Mgr7 *r4i_GetMgr(void);
M3Mgr7 *sub_000FBAF0(void);

/* 0xF8170: put the three stage managers into their hold state: set flags 0x220 (clearing 0x14D) and 0x20 on each one's flag block, then clear their +0xA4 counter and flag 0x44. */
void m3_MgrsHoldF8170(void) {
    M3Flg7 *f; M3Mgr7 *m;
    f = sub_000FE3D0()->f8C;
    if (f) { f->f10 = (f->f10 & 0xFFFFFEB2u) | 0x220; f->fC |= 0x20; }
    f = r4i_GetMgr()->f8C;
    if (f) { f->f10 = (f->f10 & 0xFFFFFEB2u) | 0x220; f->fC |= 0x20; }
    f = sub_000FBAF0()->f8C;
    if (f) { f->f10 = (f->f10 & 0xFFFFFEB2u) | 0x220; f->fC |= 0x20; }
    m = sub_000FE3D0();
    if (m) { m->hA4 = 0; m->f8C->f10 &= ~0x44u; m->f8C->f10 |= 0x220; }
    m = r4i_GetMgr();
    if (m) { m->hA4 = 0; m->f8C->f10 &= ~0x44u; m->f8C->f10 |= 0x220; }
    m = sub_000FBAF0();
    if (m) { m->hA4 = 0; m->f8C->f10 &= ~0x44u; m->f8C->f10 |= 0x220; }
}

typedef struct M3SndCmd7 { uint8_t unk00[0xC]; int32_t bankC; int32_t slot10; int32_t mode14; } M3SndCmd7;
typedef struct M3SndOwn7 { uint8_t unk00[0x2E8]; void *tbl2E8; int32_t bankA2EC; uint8_t unk2F0[0x10]; int32_t mode300[7]; int32_t bankB31C; } M3SndOwn7;
uint8_t *sub_000E3DA0(M3SndOwn7 *o, int mode);
int  sub_0019AD10(void *tbl, int slot);
void sub_000497E0(int bank, int slot, int v, void *pos, int a, float r, int b);
void sub_00048450(int bank, int slot);
void r1c_SetRecThunk(int bank, int slot, int v);

/* 0xEA2A0: run a sound command on bank A or B of the owner: mode 0 restarts the slot with 0, mode 1 with its table value, other modes play it 3D at the mode's source object (range 1000); remember the mode per slot. */
void m3_SndCmdEA2A0(M3SndOwn7 *o, M3SndCmd7 *c) {
    int h; uint8_t *src;
    if (c == 0) return;
    if (c->bankC == 0) h = o->bankA2EC;
    else if (c->bankC == 1) h = o->bankB31C;
    else return;
    if (h < 0) return;
    switch (c->mode14) {
    default:
        src = sub_000E3DA0(o, c->mode14);
        sub_000497E0(h, c->slot10, sub_0019AD10(o->tbl2E8, c->slot10), src + 0x60, 0, 1000.0f, 1);
        break;
    case 1:
        sub_00048450(h, c->slot10);
        r1c_SetRecThunk(h, c->slot10, sub_0019AD10(o->tbl2E8, c->slot10));
        break;
    case 0:
        sub_00048450(h, c->slot10);
        r1c_SetRecThunk(h, c->slot10, 0);
        break;
    }
    o->mode300[c->slot10] = c->mode14;
}

typedef struct M3LtSlot7 { int32_t a, b; float c; } M3LtSlot7;
typedef struct M3Arena7 { uint8_t unk00[0x520]; int32_t i520; void *unit524; void *unit528; void *st52C; void *st530; M3LtSlot7 slot534[8]; } M3Arena7;
extern char m3_pathLightA277794[];
extern char m3_pathLightB27776C[];
void *r1_StateNew(int a);
void sub_0001DA10(void *s);
void r1d_LoadPack(void *s, const char *path);
void *r1g_CharUnitAlloc(int kind, int a, int b, int c, void *s);

/* 0xE1170: set up the battle arena's two light units once: create two states (hang if either fails), load the two light packs into them, allocate a kind-8 unit for each and clear the eight light slots. */
void m3_ArenaLightsE1170(M3Arena7 *o) {
    void *a, *b;
    if (o->unit524 != 0 || o->unit528 != 0) return;
    a = r1_StateNew(0);
    b = r1_StateNew(0);
    if (a == 0 || b == 0) for (;;) ;
    sub_0001DA10(a);
    sub_0001DA10(b);
    r1d_LoadPack(a, m3_pathLightA277794);
    r1d_LoadPack(b, m3_pathLightB27776C);
    o->st52C = a;
    o->st530 = b;
    o->unit524 = r1g_CharUnitAlloc(8, 0, 0, 0, a);
    o->unit528 = r1g_CharUnitAlloc(8, 0, 0, 0, b);
    o->slot534[0].a = 0; o->slot534[0].b = 0;
    o->slot534[1].a = 0; o->slot534[1].b = 0;
    o->slot534[2].a = 0; o->slot534[2].b = 0;
    o->slot534[3].a = 0; o->slot534[3].b = 0;
    o->slot534[4].a = 0; o->slot534[4].b = 0;
    o->slot534[5].a = 0; o->slot534[5].b = 0;
    o->slot534[6].a = 0; o->slot534[6].b = 0;
    o->slot534[7].a = 0; o->slot534[7].b = 0;
    o->i520 = 0;
}
