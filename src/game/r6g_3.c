/* Area r6g: player animation bank and action input (r6g_3). Names inferred. */
#include "r6g.h"

/* 0x000BCA60: switch the player's animation bank. While the player is active
   and the bank changes, the model node is detached and rebuilt with its
   animation fields cleared (mode 6), the old bank's command 0x60+bank is run,
   the new bank is loaded and the saved model fields are put back (mode 1). */
void r6g_PlayerSetAnimBank(int bank)
{
    R6gModel *m;
    int i30, i12C, i138, i130, i134, i13C;

    if (!R6G_PLAYER->active1B8)
        return;
    if (R6G_PLAYER->anim140 == bank)
        return;
    R6G_PLAYER->prev144 = R6G_PLAYER->anim140;
    R6G_PLAYER->anim140 = bank;
    m = r1e_g42C8E0;
    i12C = m->i12C;
    i138 = m->i138;
    i130 = m->i130;
    i30 = m->i30;
    i134 = m->i134;
    i13C = m->i13C;
    m->i30 = 0;
    m->mode04 = 6;
    m->i08 = 0;
    m->i12C = 0;
    m->i138 = 0;
    m->i130 = 0;
    m->i134 = 0;
    m->i13C = 0;
    sub_0001EB80((R6eModel *)m);
    sub_0001E550(m);
    sub_0004F5D0(R6G_PLAYER->prev144 + 0x60);
    sub_000BBF40(bank);
    r1e_g42C8E0->i30 = i30;
    r1e_g42C8E0->mode04 = 1;
    r1e_g42C8E0->i08 = 0;
    r1e_g42C8E0->i12C = i12C;
    r1e_g42C8E0->i138 = i138;
    r1e_g42C8E0->i130 = i130;
    r1e_g42C8E0->i134 = i134;
    r1e_g42C8E0->i13C = i13C;
}

/* 0x000CD430: pick the player's next action state from the buttons pressed this
   frame (masks per action at 0x0041CD00) and the stick direction dir, and set it
   in the action state machine when it differs from the current one. */
void r6g_PlayerActionInput(PlayerObj *p, int dir)
{
    uint32_t pressed = r4e_g42CA38;
    int st = 0;
    int cur = sub_000BC650(R6G_PLAYER->sm);
    R6gPlayer *q;

    if (pressed & r6g_keyMask41CD00[0]) {
        if ((unsigned)dir > 2) {
            if (dir == 3)
                st = 5;
            else if (dir == -1)
                st = 1;
        } else if (dir == 2) {
            st = 3;
        } else if (dir == 0) {
            st = 1;
        } else if (dir == 1) {
            st = 2;
        }
        if (st != cur)
            sub_000BC6B0(R6G_PLAYER->sm, st);
        return;
    }
    if (r6g_keyMask41CD00[1] & pressed) {
        if (cur != 0xE)
            sub_000BC6B0(R6G_PLAYER->sm, 0xE);
        return;
    }
    if (!(r6g_keyMask41CD00[8] & pressed) && !(r6g_keyMask41CD00[9] & pressed)) {
        if (r6g_keyMask41CD00[6] & pressed) {
            st = sub_000CD300(p);
            ((R6gPlayer *)p)->aim1D8 = st;
            st += 0x2E;
            if (st != cur)
                sub_000BC6B0(R6G_PLAYER->sm, st);
            return;
        }
        if ((r6g_keyMask41CD00[2] & pressed) || (r6g_keyMask41CD00[3] & pressed) ||
            (r6g_keyMask41CD00[4] & pressed) || (r6g_keyMask41CD00[5] & pressed)) {
            if (cur != 0x24)
                sub_000BC6B0(R6G_PLAYER->sm, 0x24);
        }
        return;
    }
    q = (R6gPlayer *)p;
    if (q->stateD4 == 2 || q->stateD4 == 4)
        return;
    if (q->flags150 & 0x40282006)
        return;
    if (sub_0019BE60(0x4101))
        return;
    sub_000D2440(p);
    if (cur == 0x32)
        return;
    if (r6g_keyMask41CD00[8] & pressed) {
        if (!q->can1D0)
            return;
        q->side1BC = 2;
    } else {
        if (!q->can1CC)
            return;
        q->side1BC = 1;
    }
    sub_000BC6B0(R6G_PLAYER->sm, 0x32);
}
