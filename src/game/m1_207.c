/* Area m1, file 207: frame draw helpers. Names inferred. */
#include <stdint.h>

extern int32_t b3b_mode42CAFC;
extern uint8_t af0_var3EE6A8[];
extern uint8_t *g_acb_table;
extern uint8_t aec_3EDD20[];
int   af0_GetVar3EDCBC(void);
void  sub_00033250(void);
void *sub_000325E0(void *dl);
int   af0_GetVar3EDCF8(void);
void *rtc_DrawPanelOrText(void *dl);
void  sub_0002C7A0(void);
void  a19_Signal402FE4(void);
void  m1_PlayerResume0D3680(void);
void  adc_SetChannels1(void);
void  af0_SetVar3EDCF8(int v);
void  sub_0003FCE0(void *layer);
void *sub_0003FBD0(void *dl, void *layer);

/* 0xDFB00: end-of-frame draw: the optional overlay, the panel or text pass (finishing a closing scene in states 3/4), then the four extra layers and the HUD layer. */
void *m1_FrameDraw0DFB00(void *dl) {
    int i;
    if (b3b_mode42CAFC != 9999 && af0_GetVar3EDCBC() == 1) { sub_00033250(); dl = sub_000325E0(dl); }
    if (af0_GetVar3EDCF8()) {
        dl = rtc_DrawPanelOrText(dl);
        if (af0_GetVar3EDCF8() == 3 || af0_GetVar3EDCF8() == 4) {
            sub_0002C7A0();
            if (af0_GetVar3EDCF8() == 4) a19_Signal402FE4();
            m1_PlayerResume0D3680();
            adc_SetChannels1();
            af0_SetVar3EDCF8(0);
        }
    }
    sub_0003FCE0(af0_var3EE6A8);
    dl = sub_0003FBD0(dl, af0_var3EE6A8);
    if (g_acb_table != 0)
        for (i = 0; i < 0x80; i += 0x20) {
            sub_0003FCE0(g_acb_table + i);
            dl = sub_0003FBD0(dl, g_acb_table + i);
        }
    sub_0003FCE0(aec_3EDD20);
    return sub_0003FBD0(dl, aec_3EDD20);
}

typedef struct M1CsC207 { uint8_t unk00[0x10]; uint32_t f10; int32_t i14; uint8_t unk18[0xC]; void *cb24; void *cb28; void *cb2C; } M1CsC207;
typedef struct M1CsB207 { uint8_t unk00[4]; int32_t kind4; int32_t sub8; uint32_t fC; uint32_t f10; } M1CsB207;
typedef struct M1CsP207 {
    uint8_t unk00[0x54]; float t54, t58; uint8_t unk5C[0x30]; M1CsB207 *body8C; void *h90, *h94, *h98;
    uint8_t unk9C[0x4C]; int32_t iE8; uint8_t unkEC[8]; float fF4; int32_t iF8; uint8_t unkFC[0x34]; float f130;
} M1CsP207;
void *rbi_Comp1D960(void *o, int comp);
void  m1_ObjDetach0F6C90(void);
void  sub_000F8EC0(void);
void  sub_000F8330(void);
void  sub_000F3B70(void *b, int k);
float sub_00171D50(int a, int b, int c);
void *a12_List_At(void *l, int i);
void  sub_0001D610(void *h);

/* 0xF90D0: wear the costume: set the body's draw flags, hook its detach/update/draw handlers, reset its timers and fetch its three parts (hanging until each exists). */
void m1_CostumeWear0F90D0(M1CsP207 *p) {
    M1CsB207 *b = p->body8C; M1CsC207 *c = rbi_Comp1D960(b, 0xD); void *volatile h0; void *volatile h1; void *volatile h2; float t;
    if (b != 0) {
        b->f10 = (b->f10 & ~0x200u) | 0x5CD;
        b->fC &= ~0xE0u;
    }
    c->f10 |= 0x80000000;
    c->cb24 = (void *)m1_ObjDetach0F6C90;
    c->cb28 = (void *)sub_000F8EC0;
    c->cb2C = (void *)sub_000F8330;
    c->i14 = 2;
    sub_000F3B70(b, 0);
    t = sub_00171D50(b->kind4, b->sub8, 0);
    p->t58 = t; p->t54 = t;
    p->h90 = a12_List_At(b, 0);
    p->h94 = a12_List_At(b, 1);
    p->h98 = h2 = a12_List_At(b, 2);
    h0 = p->h90; while (h0 == 0) ;
    h1 = p->h94; while (h1 == 0) ;
    while (h2 == 0) ;
    p->iF8 = 0;
    sub_0001D610(h2);
    p->f130 = 0.0f; p->fF4 = 0.0f; p->iE8 = 0;
}

typedef struct M1Sq207 { uint32_t flags0; uint8_t unk04[0xC]; float size10; uint8_t unk14[0xC]; int32_t st20; uint8_t unk24[0x5C]; float s80, s84, s88; uint8_t unk8C[4]; float t90; } M1Sq207;
extern float m1_frameTime42C858;
void sub_000A7B30(M1Sq207 *o);

/* 0xA58D0: squash-and-stretch pop: start at full size, then shrink width/depth by size/16 and grow height by size/8 per unit of time; after 16 units finish (0xA7B30) and flag it done. */
void m1_SquashPop0A58D0(M1Sq207 *o) {
    float d;
    switch (o->st20) {
    case 0:
        o->flags0 &= ~0xB10u;
        o->t90 = m1_frameTime42C858;
        o->s88 = o->size10; o->s84 = o->size10; o->s80 = o->size10;
        o->st20 = 1;
        return;
    case 1:
        d = o->size10 * 0.0625f;
        o->s80 -= d * m1_frameTime42C858;
        o->s88 -= d * m1_frameTime42C858;
        o->s84 += o->size10 * 0.125f * m1_frameTime42C858;
        o->t90 += m1_frameTime42C858;
        if (o->t90 >= 16.0f) {
            sub_000A7B30(o);
            o->flags0 |= 0x40000000;
            o->st20 = -1;
        }
        return;
    }
}

typedef struct M1Bx207 { uint8_t unk00[0x60]; float pos60[4]; uint8_t unk70[0x68]; float offD8[4]; } M1Bx207;
void r4c_VecAdd(float *dst, const float *a, const float *b);
void sub_0001B420(const float *hi, const float *lo, void *out);

/* 0xD11E0: query what lies in a 40-unit box centred on the object's offset point. */
void m1_BoxQuery0D11E0(M1Bx207 *o, void *out) {
    float lo[4], hi[4], c[4];
    c[0] = 0.0f; c[1] = 0.0f; c[2] = 0.0f; c[3] = 1.0f;
    hi[0] = 0.0f; hi[1] = 0.0f; hi[2] = 0.0f; hi[3] = 1.0f;
    lo[0] = 0.0f; lo[1] = 0.0f; lo[2] = 0.0f; lo[3] = 1.0f;
    r4c_VecAdd(c, o->pos60, o->offD8);
    hi[0] = c[0] + 20.0f; hi[1] = c[1] + 20.0f; hi[2] = c[2] + 20.0f; hi[3] = 1.0f;
    lo[0] = c[0] - 20.0f; lo[1] = c[1] - 20.0f; lo[2] = c[2] - 20.0f; lo[3] = 1.0f;
    sub_0001B420(hi, lo, out);
}
