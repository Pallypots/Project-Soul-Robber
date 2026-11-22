/* Area m1, group 301: 0x0007E720. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct { uint8_t _0[0x8C]; int32_t kind8c; uint8_t _90[0xC0 - 0x90]; int32_t nc0; } M1Md301;
typedef struct { uint8_t _0[0x14]; void *f14; void *f18; } M1Sk301;
typedef struct {
    uint8_t _0[0x20]; M1Md301 *m20; uint8_t _24[0xC]; M1Sk301 *s30;
    uint8_t _34[0x14C - 0x34]; int32_t type14c;
} M1Ob301;
typedef struct { int32_t _0; int32_t f4; int32_t _8; int32_t fc; int32_t _10; int32_t f14; } M1Fx301;

extern void *m1_scene42C8E4;
void *a6b_GetHeap(int k);
void  sub_00053710(void *heap);
void  m1_StubAD090(int a, int b);
void  sub_00022380(M1Ob301 *o, void *arg, void *scene);
void  sub_00053740(void);
void *sub_00053AB0(int size, int a, int line);
void  sub_0007F1E0(void *p, int v, int size);
void  r4e_NodeInit(void *p);
void  m1_NodesInit1AEA00(void *nodes, void *root, int n);
void  sub_00083160(M1Sk301 *s, M1Md301 *m);
void  sub_0001E9B0(void *scene, M1Ob301 *o, int type, int a, int b);
M1Fx301 *sub_00039810(int k);

/* 0x0007E720: build o's skeleton node buffers on the effect heap and register
   it with the scene (type 7 also starts a fade). Returns 0, or -1 when o has no
   model or skeleton. Regargs: o=EBX. */
int32_t m1_ObjBuild7E720(M1Ob301 *o, void *arg)
{
    volatile int32_t res;
    void *scene;
    M1Sk301 *s;
    int32_t n, k, sz;
    M1Fx301 *fx;

    scene = m1_scene42C8E4;
    n = 0;
    res = 0;
    sub_00053710(a6b_GetHeap(6));
    m1_StubAD090(0, 0);
    sub_00022380(o, arg, scene);
    if (o->m20 == 0) {
        res = -1;
        sub_00053740();
        return res;
    }
    s = o->s30;
    if (s == 0) {
        res = -1;
        sub_00053740();
        return res;
    }
    k = o->m20->kind8c;
    switch (k) { case 1: case 9:
        n = o->m20->nc0; }
    if (s->f14 == 0) {
        s->f14 = sub_00053AB0(0xE0, 0, 0x856);
        sub_0007F1E0(s->f14, 0, 0xE0);
        r4e_NodeInit(s->f14);
    }
    if (s->f18 == 0) {
        sz = n * 0x130;
        s->f18 = sub_00053AB0(sz, 0, 0x862);
        sub_0007F1E0(s->f18, 0, sz);
    }
    m1_NodesInit1AEA00(s->f18, s->f14, n);
    sub_00083160(o->s30, o->m20);
    sub_0001E9B0(scene, o, o->type14c, 5, 0x11);
    if (o->type14c == 7) {
        fx = sub_00039810(1);
        fx->f4 = 3;
        fx->fc = 0xFF;
        fx->f14 = 10;
    }
    sub_00053740();
    return res;
}

typedef struct {
    uint8_t _0[8]; uint32_t f8; uint8_t _c[0x140 - 0xC]; uint8_t v140[0x164 - 0x140]; float f164;
    uint8_t _168[0x178 - 0x168]; float t178; uint8_t _17c[4]; int32_t n180; int32_t h184;
} M1Bs301;
typedef struct {
    uint8_t _0[0xF8]; int32_t mode0f8; uint8_t _fc[8]; uint8_t *p104;
    uint8_t _108[0x278 - 0x108]; M1Bs301 *s278;
} M1Ba301;
typedef struct { uint8_t _0[0x20]; void *p20; uint8_t _24[0x128 - 0x24]; uint8_t b128; } M1Bo301;

extern float m1_frameRate42C85C;
void sub_00145F70(void *a, void *b);
void sub_000F5D40(void *dst, void *src);
int  r1c_GetRecThunk(int32_t h);
void rbi_Shapes135900(void);
int  sub_00135E10(void);
void sub_00137690(M1Bo301 *o, M1Ba301 *a);
int  sub_0019BE60(int bit);
void r3_Raise135E60(M1Ba301 *a);                 /* regargs: a=EAX */
void sub_0019BE90(int bit);
void a80_ModeSetFlag4(void);

/* 0x00137800: per-frame update of a character's power state: copy its
   position, drop a dead sound handle, build up charge, run the cooldown, and
   raise the power once enough charge has been gathered. */
void m1_PowerTick137800(M1Bo301 *o, M1Ba301 *a)
{
    M1Bs301 *s = a->s278;
    uint32_t f, c;
    float fr, v, t;

    sub_00145F70(o->p20, o->p20);
    if (a->mode0f8 == 1)
        sub_000F5D40(s->v140, a->p104 + 0x60);
    else if (a->mode0f8 == 2)
        sub_000F5D40(s->v140, &a->p104);
    s->f8 &= ~0x100;
    if (s->h184 != -1 && !r1c_GetRecThunk(s->h184)) {
        s->h184 = -1;
        rbi_Shapes135900();
    }
    f = s->f8;
    if (!(f & 4)) {
        fr = m1_frameRate42C85C;
        v = fr * fr * 294.0f;
        if (!(o->b128 & 0x18))
            s->f164 = v + s->f164;
    }
    c = f & 1;
    if (c) {
        t = s->t178 - m1_frameRate42C85C;
        s->t178 = t;
        if (0.0f > t)
            s->t178 = 0.0f;
    }
    if (c && !(f & 0x40) && sub_00135E10() < 4)
        sub_00137690(o, a);
    if ((s->f8 & 1) && !sub_0019BE60(0x10000)) {
        r3_Raise135E60(a);
        if (s->n180 >= 0x14) {
            sub_0019BE90(0x10000);
            s = a->s278;
            if (s->f8 & 0x80000) {
                s->f8 &= ~0x80000;
                a80_ModeSetFlag4();
            }
        }
    }
}

typedef struct {
    uint8_t _0[0xC]; uint32_t fc; uint8_t _10[0x50 - 0x10];
    float f50, f54, f58, f5c, f60, f64, f68, f6c, f70, f74, f78, f7c;
    uint8_t _80[0xA4 - 0x80]; float fa4; uint8_t _a8[8]; float fb0, fb4;
    uint8_t _b8[0xD0 - 0xB8]; int32_t hd0; uint8_t _d4[0x124 - 0xD4]; int32_t f124;
} M1So301;
typedef struct { uint8_t _0[8]; int32_t kind8; } M1Sc301;
typedef struct {
    uint8_t _0[0x10]; uint32_t f10; uint8_t _14[4]; float f18, f1c; int32_t f20;
    void *cb24, *cb28, *cb2c; uint8_t _30[0xC]; M1So301 *o3c; M1Sc301 *c40;
} M1Ev301;

extern float m1_scl319D64[12];
M1Ev301 *sub_0001D960(M1So301 *o, int k);
void sub_000F3B00(M1So301 *o, int f);
int32_t sub_0001BC40(M1So301 *o);
void sub_000EE270(M1Ev301 *e);
void sub_0010F010(void);
void sub_0010F090(void);
void sub_00111AD0(void);

/* 0x00111EB0: set up a spawned shard: reset its motion, scale it by the
   spawner kind (1, 14 or 15) and attach its event with the three callbacks.
   Regargs: o=ESI c=EBX. */
void m1_ShardInit111EB0(M1So301 *o, M1Sc301 *c)
{
    M1Ev301 *e;
    float k, y;

    e = sub_0001D960(o, 0xD);
    o->fc = (o->fc & ~2u) | 0x201;
    sub_000F3B00(o, 0xC0);
    switch (c->kind8) {
    case 1:  k = m1_scl319D64[0]; break;
    case 14: k = m1_scl319D64[4]; break;
    case 15: k = m1_scl319D64[8]; break;
    }
    o->f68 = 0.0f; o->f64 = 0.0f; o->f60 = 0.0f;
    o->f58 = 0.0f; o->f54 = 0.0f; o->f50 = 0.0f;
    o->fc &= ~0xC0u;
    o->f6c = 1.0f; o->f5c = 1.0f;
    o->f78 = k; o->f74 = k; o->f70 = k;
    o->f7c = 1.0f;
    o->f124 = 1;
    o->hd0 = sub_0001BC40(o);
    o->fb0 = k * 6.5f;
    o->fb4 = k * -50.0f;
    y = k * 0.0f;
    o->fa4 = y;
    sub_000EE270(e);
    e->f18 = y;
    e->f10 |= 0x80000000u;
    e->cb24 = (void *)sub_0010F010;
    e->cb28 = (void *)sub_0010F090;
    e->cb2c = (void *)sub_00111AD0;
    e->f20 = 0;
    e->f1c = k * -10.0f;
    e->o3c = o;
    e->c40 = c;
}

typedef struct { float x, y, z, w; } M1Pt301;
typedef struct { uint8_t _0[0x60]; M1Pt301 pos60; } M1Wk301;
extern M1Pt301 r3_points31F0E0[];
float r4_DistanceXZ(M1Pt301 *a, M1Pt301 *b);

/* 0x00169BA0: index of o's n-th nearest waypoint among the 11 main points
   (or, for n < 0, the nearest of the two extra points 11 and 12).
   Regargs: o=ECX. */
int32_t m1_NthNearest169BA0(M1Wk301 *o, int32_t n)
{
    float d[12];
    float best;
    volatile int32_t neg, vcnt, start;
    int32_t cnt, i, j;
    M1Pt301 *p;

    best = 3.40282347e+38f;
    neg = 0;
    if (n < 0) {
        vcnt = 2;
        n = 1;
        start = 11;
        neg = 1;
    } else {
        vcnt = 11;
        start = 0;
    }
    p = &r3_points31F0E0[start];
    for (i = 0; i < vcnt; i++, p++)
        d[i] = r4_DistanceXZ(&o->pos60, p);
    cnt = vcnt;
    j = 0;
    for (; n > 0; n--) {
        for (i = 0; i < cnt; i++) {
            if (best > d[i]) {
                best = d[i];
                j = i;
            }
        }
        d[j] = 3.40282347e+38f;
        best = 3.40282347e+38f;
    }
    if (neg) j += 11;
    return j;
}

typedef struct { uint8_t _0[0x30]; int32_t h30; uint8_t _34[0x54 - 0x34]; float rot54;
    uint8_t _58[0x88 - 0x58]; float f88; uint8_t _8c[0x128 - 0x8C]; uint8_t b128; } M1Sp301;
typedef struct { uint8_t _0[0x54]; int32_t st54; uint8_t _58[0x74 - 0x58]; uint32_t *flags74; } M1Ss301;

extern float m1_frameTime42C858;
void b16_PlayAnim(M1Sp301 *o, M1Ss301 *a, int k);
void sub_001671D0(M1Sp301 *o, M1Ss301 *a, int st);
int32_t sub_000833E0(int32_t h);
int sub_001C7EE1(void);                                   /* rand */

/* 0x0016B150: spin attack: pick a random spin direction, turn 2 degrees per
   frame unit (doubled while flags 6 are set) until the clip ends, then lift
   off and land, and pick the next state (0x10 one time in 8, else 0xE). */
void m1_SpinAttack16B150(M1Sp301 *o, M1Ss301 *a)
{
    uint32_t *fp = a->flags74;
    uint32_t f;
    float v;
    volatile int32_t m;
    switch (a->st54) {
    case 0:
        b16_PlayAnim(o, a, 1);
        f = *fp;
        if (sub_001C7EE1() & 1) f |= 0x4000;
        else f &= ~0x4000u;
        *fp = f;
        a->st54++;
    case 1:
        if (sub_000833E0(o->h30)) {
            b16_PlayAnim(o, a, 2);
            a->st54++;
            return;
        }
        f = *fp;
        if (o->b128 & 6) f |= 0x2000;
        else f &= ~0x2000u;
        *fp = f;
        if (f & 0x4000)
            v = m1_frameTime42C858 * 0.0349065848f;
        else
            v = 0.0f - m1_frameTime42C858 * 0.0349065848f;
        if (f & 0x2000)
            v = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(v), _mm_set_ss(2.0f)));
        o->rot54 = o->rot54 + v;
        return;
    case 2:
        o->f88 = 0.0f - m1_frameRate42C85C * 22.0f;
        if (sub_000833E0(o->h30) && (o->b128 & 0x18)) {
            b16_PlayAnim(o, a, 3);
            a->st54++;
        }
        return;
    case 3:
        if (sub_000833E0(o->h30)) {
            m = -(int32_t)((sub_001C7EE1() & 7) != 0);
            sub_001671D0(o, a, (m & -2) + 0x10);
        }
        return;
    }
}

typedef struct {
    uint8_t _0[0x6C]; int32_t f6c; uint8_t _70[0x8C - 0x70]; uint8_t *p8c;
    uint8_t _90[0xC0 - 0x90]; int32_t fc0; uint8_t _c4[0xF8 - 0xC4]; int32_t stf8; float tfc;
} M1Hp301;

extern M1Hp301 *m1_helper3F611C;
void sub_000FE2E0(int k);
void sub_000FBA00(int k);
void sub_00100020(int k);
void sub_000FC6F0(int k);                                   /* regargs: k=EAX */
int  sub_000494D0(int id, void *p, int f);

/* 0x000FC740: helper combo chain: after the step's delay (1 s, then 0.18 s
   twice) run the next combo step and play its sound; 2 s after the last step
   reset the chain. Skipped while idle or in mode 9. */
void m1_ComboChainFC740(void)
{
    M1Hp301 *h = m1_helper3F611C;
    int32_t *p = &h->stf8;
    float *t;
    if (h->stf8 == 0 || h->f6c == 9) return;
    switch (h->stf8) {
    case 1:
        t = &h->tfc;
        if (*t > 1.0f) {
            sub_000FE2E0(6);
            *p = 2;
            *t = 0.0f;
            sub_000494D0(0x171, h->p8c + 0x60, 1);
        }
        break;
    case 2:
        t = &h->tfc;
        if (*t > 0.18f) {
            sub_000FBA00(6);
            *p = 3;
            *t = 0.0f;
            sub_000494D0(0x166, h->p8c + 0x60, 1);
        }
        break;
    case 3:
        t = &h->tfc;
        if (*t > 0.18f) {
            sub_00100020(6);
            *p = 4;
            *t = 0.0f;
            sub_000494D0(0x16B, h->p8c + 0x60, 1);
        }
        break;
    case 4:
        if (h->tfc > 2.0f) {
            h->tfc = 0.0f;
            *p = 0;
            sub_000FC6F0(2);
            h->fc0 = 0;
        }
        break;
    }
    h->tfc = h->tfc + m1_frameRate42C85C;
}
