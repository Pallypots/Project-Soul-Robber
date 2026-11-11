/* Area r6h: title screen drawing (r6h_3). Names inferred. */
#include "r6h.h"

/* 0x0006C750: add the title screen to the draw list cmd and return the new end.
   Pages 0, 2 and 3 draw the five animated title letters, pages 1 and 4 the
   full-screen background quad; any other page draws a black screen and stops.
   Page 4, sub-page 3 adds the 0x0006E960 overlay. Then, when the particle
   texture is loaded, every particle of the page's kind is moved, faded by its
   lifetime (sine of the remaining life) and drawn, and respawned when its
   lifetime has run out (calls 0x0006C270 with EAX=i ECX=alt EDX=kind). */
void *r6h_TitleDraw(void *cmd)
{
    R6hQuad q;
    R6hFx *p;
    int kind, alt, i;

    switch (r6g_b428F80[0]) {
    case 0:
    case 2:
    case 3:
        for (i = 0; i < 5; i++) {
            R6hSprite *s = &r6h_titleSpr42C27C[i];
            s->x = r6h_titlePos42C588[i].x + r6h_titleOff2DF140[i].x;
            s->y = r6h_titlePos42C588[i].y + r6h_titleOff2DF140[i].y;
            s->sx = r6h_titleScl42C5B0[i].x;
            s->sy = r6h_titleScl42C5B0[i].y;
            cmd = sub_00017AE0(cmd, s);
        }
        break;
    case 1:
    case 4:
        q.col[0] = 0x80808080;
        q.col[1] = 0x80808080;
        q.col[2] = 0x80808080;
        q.col[3] = 0x80808080;
        q.x = 0.0f;
        q.y = 0.0f;
        q.w = 512.0f;
        q.h = 448.0f;
        q.u0 = 0.0f;
        q.v0 = 0.0f;
        q.u1 = 512.0f;
        q.v1 = 448.0f;
        q.tex = a60_h42C6F0;
        q.z = 0;
        cmd = sub_00072420(cmd, &q);
        break;
    default:
        return sub_000720D0(cmd, -256.0f, -224.0f, 512.0f, 448.0f, 0,
                            0x80000000, 0x80000000, 0x80000000, 0x80000000);
    }

    if (r6g_b428F80[0] == 4 && r6g_b428F80[1] == 3)
        cmd = sub_0006E960(cmd);
    if (a60_v3E68A8 == -1)
        return cmd;

    alt = 0;
    kind = 0;
    switch (r6g_b428F80[0]) {
    case 0:
    case 1:
    case 2:
    case 3:
        alt = 0;
        kind = 0;
        break;
    case 4:
        alt = 1;
        kind = 1;
        break;
    }
    r6h_fxSpr428FB4.mode = r6h_fxKinds2DF0C8[kind].sprite;
    p = r6h_fx3E6628;
    for (i = 0; i < r6h_fxKinds2DF0C8[kind].count; i++, p++) {
        float inv, scale;

        p->x += p->vx;
        r6h_fxSpr428FB4.x = p->x;
        p->y += p->vy;
        r6h_fxSpr428FB4.y = p->y;
        inv = 1.0f / r6h_fxKinds2DF0C8[kind].life;
        scale = (r6h_fxKinds2DF0C8[kind].life - p->life) * r6h_fxKinds2DF0C8[kind].fade * inv + 1.0f;
        r6h_fxSpr428FB4.sx = scale;
        r6h_fxSpr428FB4.sy = scale;
        r6h_fxSpr428FB4.color = ((uint32_t)(int)(sub_001A3ED0(inv * 180.0f * p->life * 0.017453292f)
                                                 * r6h_fxKinds2DF0C8[kind].alpha) << 24)
                              | r6h_fxKinds2DF0C8[kind].color;
        cmd = sub_00017C00(cmd, &r6h_fxSpr428FB4);
        sub_000720A0(&p->life, 0);
        if (0.0f >= p->life)
            sub_0006C270(i, alt, kind);
    }
    return cmd;
}
