/* Area r6h: attack hit test against the player (r6h_16). Names inferred. */
#include "r6h.h"

/* 0x000A1220: test whether the attack box of a (centre = position + offset,
   half sizes from a) overlaps the hit box b (its centre transformed by its
   node, its two sizes). On a hit, the direction from the player to a's body
   is passed with a's body to the player hit handler; a handled hit by kind
   0x1F requests 0x00135EB0(1). Returns 1 on a hit, else 0. */
int r6h_HitTestPlayer(R6hHitter *a, R6hHitBox *b)
{
    R6hVec4 centre = { 0.0f, 0.0f, 0.0f, 1.0f };
    R6hVec4 size = { 0.0f, 0.0f, 0.0f, 1.0f };
    R6hVec4 bc = { 0.0f, 0.0f, 0.0f, 1.0f };
    R6hVec4 half = { 0.0f, 0.0f, 0.0f, 1.0f };
    R6hVec4 dir, out;
    uint8_t *node = b->node;

    sub_000F5D40(&half, a->radius);
    sub_000F5D40(&centre, &a->pos);
    centre.x += a->off[0];
    centre.y += a->off[1];
    centre.z += a->off[2];
    size.x = b->size[0];
    size.y = b->size[1];
    /* 0x001ADAF0: 4-float vector add bc = centre + node[0x70] */
    sub_001ADAF0((float *)&bc, (const float *)&b->centre, (const float *)(node + 0x70));
    if (sub_000A2890(&half, &centre, &size, &bc) <= 0)
        return 0;
    sub_001AD9F0(&dir, (uint8_t *)g_playerObj + 0x60, &a->body->pos);
    dir.w = 1.0f;
    if (sub_000D3BF0(&g_stats, a->body, 0, &out, &dir) == 1 && a->kind == 0x1F)
        sub_00135EB0(1);
    return 1;
}
