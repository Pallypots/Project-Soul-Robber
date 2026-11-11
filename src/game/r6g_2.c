/* Area r6g: status screen textures and outlined text (r6g_2). Names inferred. */
#include "r6g.h"

/* 0x00065F00: load the textures of the current texture set (r6d_texSet3E6538):
   up to four big textures from the work block (handles in r6g_tex3E6528, -1 when
   unused) and up to three sprites whose layers use those handles. */
void r6g_StatusLoadTextures(void)
{
    int i;
    r6g_tex3E6528[0] = -1;
    r6g_tex3E6528[1] = -1;
    r6g_tex3E6528[2] = -1;
    r6g_tex3E6528[3] = -1;
    for (i = 0; i < 4; i++) {
        if (r6d_texSets[r6d_texSet3E6538].big[i])
            r6g_tex3E6528[i] = sub_00084C00(a60_work42C5E8 + i * 0x20080 + 0x40080, 0);
    }
    for (i = 0; i < 3; i++) {
        R6gSprite *s;
        const uint8_t *sel;
        if (!r6d_texSets[r6d_texSet3E6538].small[i])
            continue;
        sub_00014DA0(a60_work42C5E8 + i * 0x2800 + 0xC0280);
        s = &r6g_sprites429530[i];
        sub_00014D00(s, a60_work42C5E8 + i * 0x2800 + 0xC0280,
                     r6g_tex3E6528[r6d_texSets[r6d_texSet3E6538].sel[i][0]]);
        sel = r6d_texSets[r6d_texSet3E6538].sel[i];
        s->tex[0] = r6g_tex3E6528[sel[1]];
        s->tex[1] = r6g_tex3E6528[sel[2]];
        s->tex[2] = r6g_tex3E6528[sel[3]];
        sub_00014E30(s, 0, 0, 0, 0);
    }
}

/* 0x00076E30: draw the text of t four times, offset by d diagonally, as an
   outline of the given alpha; the position, the first word and both sprite
   colours/modes are restored afterwards. Returns ctx.
   regargs: t=EAX alpha=ESI ctx=EBX (d on the stack); calls 0x000768D0 with EDI=t. */
void *r6g_TextDrawOutline(R6gText *t, uint32_t alpha, void *ctx, int d)
{
    int x = t->x;
    int y = t->y;
    uint32_t flags = t->flags;
    uint32_t c8CC = t->spr8CC.color;
    uint32_t c830 = t->spr830.color;
    int m8CC = t->spr8CC.mode;
    int m830 = t->spr830.mode;
    uint32_t c;

    sub_00038060(alpha);
    c = ((((alpha & 0xFE) << 16) | (alpha & 0xFE00)) << 7)
      | (((alpha & 0xFE0000) | (alpha >> 16)) >> 9);
    t->spr8CC.color = c;
    t->spr830.color = c;
    t->spr8CC.mode = 1;
    t->spr830.mode = 1;
    t->x = (int16_t)(x - d);
    t->y = (int16_t)(y - d);
    sub_000768D0(t, ctx, sub_00038380, alpha);
    t->x = (int16_t)(x - d);
    t->y = (int16_t)(y + d);
    sub_000768D0(t, ctx, sub_00038380, alpha);
    t->x = (int16_t)(x + d);
    t->y = (int16_t)(y - d);
    sub_000768D0(t, ctx, sub_00038380, alpha);
    t->x = (int16_t)(x + d);
    t->y = (int16_t)(y + d);
    sub_000768D0(t, ctx, sub_00038380, alpha);
    t->x = (int16_t)x;
    t->y = (int16_t)y;
    t->flags = flags;
    t->spr8CC.color = c8CC;
    t->spr830.color = c830;
    t->spr8CC.mode = m8CC;
    t->spr830.mode = m830;
    sub_00038060(-1);
    return ctx;
}
