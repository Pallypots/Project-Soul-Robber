/* Area r1i, group 7: camera follow and framing 0x000196D0, 0x00019820.
   Names inferred. */
#include "r1i.h"

/* 0x000196D0: start view 2 from view 1, then (when the camera is on and
   the player exists) place it behind the player: the horizontal direction
   from the focus point (the focus target 10 units lower, else the old look
   row) to the player, scaled by the distance in view 1 (+0xE8) and raised
   by its height (+0xE4), is added to the player or (flag 0x2000) to the
   focus point; the view then looks at the focus point. */
void r1i_CamFollow(R1iCam *c)
{
    float d[4], p[4], f[4];
    R1iActor *pl, *t;
    R1iCamView *v = &c->view[2];
    *v = c->view[1];
    if (!r1i_g42C8F8)
        return;
    pl = r1i_player420E98;
    if (!pl)
        return;
    t = sub_000192C0(c);
    if (t) {
        sub_000F5D40(p, t->pos);
        p[1] -= 10.0f;
    } else {
        sub_000F5D40(p, v->m[2]);
    }
    sub_001AD9F0(d, pl->pos, p);
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    sub_001ADBA0(d, d, c->view[1].m[3][2]);
    d[1] = c->view[1].m[3][1];
    if (c->cfg->flags & 0x2000)
        sub_001ADAF0(v->m[3], p, d);
    else
        sub_001ADAF0(v->m[3], pl->pos, d);
    v->m[3][3] = 1.0f;
    sub_001AD9F0(f, p, v->m[3]);
    f[3] = 1.0f;
    sub_001AD7E0(v->m[2], f);
    sub_001ADA60(v->m[0], v->m[1], v->m[2]);
}

/* 0x00019820: start view 2 from view 1, then (camera on, player present)
   aim at the player 17 units below his position (flag 2), widen the field
   of view so that points 25 below and 5 above the player stay in view
   (flag 4, at most 60 degrees), and tilt the look direction by the
   configured amounts scaled by tan(fov / 2) (flag 2). */
void r1i_CamFrame(R1iCam *c)
{
    float d[4], p[4], dir[4];
    R1iMat m;
    float a, t;
    int i;
    R1iActor *pl;
    R1iCamView *v = &c->view[2];
    *v = c->view[1];
    if (!r1i_g42C8F8)
        return;
    pl = r1i_player420E98;
    if (!pl)
        return;
    if (c->cfg->flags & 2) {
        sub_000F5D40(p, pl->pos);
        p[1] -= 17.0f;
        sub_001AD9F0(d, p, v->m[3]);
        d[3] = 0.0f;
        sub_001AD7E0(v->m[2], d);
    }
    if (c->cfg->flags & 4) {
        sub_001AD7E0(d, v->m[2]);
        for (i = 0; i < 2; i++) {
            sub_000F5D40(p, pl->pos);
            p[1] = r1i_camHeights25FB3C[i] + p[1];
            sub_001AD9F0(p, p, v->m[3]);
            sub_001AD7E0(p, p);
            a = sub_001AD9D0(d, p);
            if (-1.0f > a || a > 1.0f)
                a = 1.0f;
            a = sub_001A3F20(a) * 114.59165f;
            if (a > v->fov)
                v->fov = a;
        }
        if (v->fov > 60.0f)
            v->fov = 60.0f;
    }
    if (c->cfg->flags & 2) {
        sub_000385D0(m, v->m);
        sub_000F5D40(m[3], r1i_vec3781A8);
        sub_000F5D40(dir, r1i_vec378198);
        t = sub_001A3EF0(v->fov * 0.0087266443f);
        dir[1] = dir[1] - t * c->cfg->tiltY;
        dir[0] = dir[0] - t * c->cfg->tiltX * 1.1428572f;
        sub_001AD7E0(dir, dir);
        sub_001AD9B0(v->m[2], m, dir);
    }
}
