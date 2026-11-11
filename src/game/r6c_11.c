/* Area r6c: streamed sound waits and event camera around 0x00086890-0x00087C70 (r6c_11). Names inferred. */
#include "r6c.h"

/* 0x00086890: start the current stream and wait until it has played out. */
void r6c_StreamPlayWait(void)
{
    int h = r6c_strH3ED200;
    r6c_busy3ED204 = 1;
    sub_000488C0(r6c_strA3ED1F8, r6c_strB3ED1FC, 1);
    sub_00047A80(h);
    while (sub_00047B10(h) != 2)
        sub_000580D0();
    sub_00047B30(h);
    while (sub_00047B50(h))
        sub_000580D0();
    r6c_busy3ED204 = 0;
}

/* 0x00086920: stop the current stream, then load and settle the next one. */
void r6c_StreamSwitchWait(void)
{
    int a = r6c_strA3ED1F8;
    int b = r6c_strB3ED1FC;
    r6c_busy3ED204 = 1;
    sub_00047B70(r6c_strH3ED200);
    sub_000487F0(a, b, 1);
    while (sub_00048820(a, b, 1) != 2)
        sub_000580D0();
    sub_00048860(a, b, 1);
    while (sub_00048890(a, b, 1))
        sub_000580D0();
    r6c_busy3ED204 = 0;
}

/* 0x00086C60: step the stream release job: 0 when finished, 1 while busy. */
int r6c_StreamReleaseStep(void)
{
    switch (r6c_step3ED1EC) {
    case 0:
        if (sub_00057EA0()) {
            sub_000867F0(0);
            r6c_step3ED1EC = 0;
            return 0;
        }
        r6c_step3ED1EC = 10;
        /* fall through */
    case 10:
        if (sub_00057E90())
            return 1;
        sub_00058540((void (*)(void))sub_000867F0, 0);
        r6c_step3ED1EC = 20;
        /* fall through */
    case 20:
        if (sub_00057E90())
            return 1;
        r6c_step3ED1EC = 0;
        return 0;
    }
    return 1;
}

/* 0x00086EF0: place every event camera marker at its position and yaw. */
void r6c_CamMarkersPlace(void)
{
    R6cCamEnt *e;
    int i;
    if (!r6c_camSet3ED210)
        return;
    e = r6c_camSet3ED210->ents;
    for (i = 0; i < r6c_camSet3ED210->count; i++, e++) {
        R6cVec4 pos, rot;
        pos.x = e->x;
        pos.y = e->y;
        pos.z = e->z;
        pos.w = 1.0f;
        rot.x = 0.0f;
        rot.y = e->yaw;
        rot.z = 0.0f;
        rot.w = 0.0f;
        sub_000A57C0(e->id, &pos, &rot);
    }
}

/* 0x00087030: run event jump handler i when the event camera is on. */
void r6c_EvJump(int i)
{
    if (r6c_on3ED214)
        r6c_jumpFns[i](i);
}

/* 0x00087050: current event camera position, direction and id; 0 when there is none. */
int r6c_CamGet(R6cVec4 *pos, R6cVec4 *dir, int *id)
{
    R6cCamRec *c;
    if (!r6c_on3ED214 || !(c = r6c_cam3ED218))
        return 0;
    pos->x = c->pos[0];
    pos->y = c->pos[1];
    pos->z = c->pos[2];
    pos->w = 1.0f;
    dir->x = c->dir[0];
    dir->y = c->dir[1];
    dir->z = c->dir[2];
    dir->w = 1.0f;
    *id = c->i1C;
    return 1;
}

/* 0x00087310: reset the event camera and run its init hooks. */
void r6c_CamReset(void)
{
    int i;
    r6c_target3ED224.x = 0.0f;
    r6c_target3ED224.y = 0.0f;
    r6c_target3ED224.z = 0.0f;
    r6c_state3ED21C = 0;
    r6c_v3ED220 = 1;
    r6c_v3ED248 = 0;
    r6c_target3ED224.w = 1.0f;
    r6c_v3ED234 = -1;
    r6c_v3ED240 = 0;
    r6c_v3ED238 = 0;
    r6c_v3ED23C = -1;
    r6c_step3ED244 = 0;
    for (i = 0; i < 6; i++)
        if (r6c_initFns[i])
            r6c_initFns[i]();
}

/* 0x000873A0: run the event camera state handler, then its tick hooks. */
void r6c_CamTick(void)
{
    int i;
    r6c_stateFns[r6c_state3ED21C]();
    for (i = 0; i < 6; i++)
        if (r6c_tickFns[i])
            r6c_tickFns[i]();
}

/* 0x00087450: aim the event camera at the player (head height from the model). */
void r6c_CamFollowPlayer(void)
{
    R6cPlayer *p = (R6cPlayer *)g_playerObj;
    R6cPlBody *body = (R6cPlBody *)(p->sub->pC4 + 0x300);
    sub_000F5D40(&r6c_target3ED224, &p->pos);
    r6c_target3ED224.y = body->height;
    r6c_state3ED21C = 2;
    r6c_v3ED234 = -1;
    r6c_v3ED240 = 0;
    r6c_v3ED238 = 0;
}

/* 0x00087C70: begin an event scene (lock the player unless the group is already done) and pick the mode. */
void r6c_EvSceneBegin(void)
{
    r6c_v3ED270 = 0;
    r6c_v3ED250 = 0;
    r6c_v3ED24C = 0;
    if (!r6c_grp3ED254->done) {
        sub_000D2A50(&g_stats, 1);
        sub_00048A00(0, 1000);
        sub_000DE330(1);
        sub_000EDA10();
    }
    switch (r6c_v3ED25C) {
    case 0:
        r6c_v3ED274 = 2;
        break;
    case 1:
        r6c_v3ED274 = 3;
        break;
    }
}
