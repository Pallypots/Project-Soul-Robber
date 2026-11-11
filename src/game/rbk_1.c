/* Area rbk: Jack's own actions (0x000D0000..0x000D5FFF). Names inferred. */
#include "rbk.h"

/* 0x000D3BF0: Jack is hit by src (damage looked up by src's two ids and the hit kind).
   Returns -1 when the hit is ignored (global flag 0x10000, Jack flags 0x80080010, already
   recovering, or mode 4/5) and 2 when Jack is invulnerable. Normally the knock-back amount
   (field 1) is applied (0x000D21E0) and a stun (field 2) recorded with flag 0x10000. While
   carrying (flag 0x2000, actions 0x1D/0x1E) the held object is dropped with message 0x2D,
   Jack is knocked back instead (2 s recovery). The damage (field 0) is then taken; at no
   health the death event runs. Unless carrying, the last hit is remembered. The point
   argument is not used. Called with stack args (j src kind point dir). */
int rbk_JackHit0D3BF0(RbkJack *j, RbkAttacker *src, int kind, RbjVec4 *point, RbjVec4 *dir)
{
    RbkMsg msg;
    RbjVec4 zero;
    int n;

    if (sub_0019BE60(0x10000) != 0)
        return -1;
    if (j->flags150 & 0x80080010)
        return -1;
    if (j->hurtD2C != 0 || j->modeD4 == 4 || j->modeD4 == 5)
        return -1;
    if (j->flagsD60 & 1)
        return 2;
    if (!(j->flags150 & 0x2000)) {
        sub_000D21E0(j, src, dir, sub_00171EB0(src->idA04, src->idB08, kind, 1));
        n = sub_00171EB0(src->idA04, src->idB08, kind, 2);
        if (n != 0) {
            j->flags150 |= 0x10000;
            j->stunD48 = (float)n;
        }
    } else if (j->stateD8 == 0x1D || j->stateD8 == 0x1E) {
        if (j->linkD5C != 0) {
            zero.x = 0.0f;
            zero.y = 0.0f;
            zero.z = 0.0f;
            zero.w = 1.0f;
            msg.id00 = 0x2D;
            msg.f0C = 0.0f;
            msg.a08 = 0;
            msg.a04 = 0;
            sub_000F5D40(&msg.v10, &zero);
            sub_000F5D40(&msg.v20, &zero);
            sub_000EE010(j->linkD5C, &msg);
            j->linkD5C = 0;
        }
        sub_000D1930(j);
        sub_000BD4A0(j, -1, -1.0f);
        sub_000CFE00(j, src, dir);
        j->linkD5C = src;
        j->hurtD2C = 1;
        j->hurtTimeD30 = 2.0f;
    }
    n = sub_00171EB0(src->idA04, src->idB08, kind, 0);
    if (Player_TakeDamage((PlayerStats *)j, n) < 0)
        rtc_PlayerEventB(j);
    if (!(j->flags150 & 0x2000)) {
        j->lastDamageD34 = n;
        j->lastSrcAD38 = src->idA04;
        j->lastSrcBD3C = src->idB08;
        j->lastKindD40 = kind;
    }
    return 1;
}

/* 0x000D21E0: knock Jack back. Hit kinds 3..9 play a flinch animation on the model
   (0x39, 0x58, 0x56, 0x57) and some a voice (0x29B, 0x2F0, 0x309, 0x2FA). While guarding or
   in the air (flags 0x200040) every kind except 1 and 9 becomes kind 1. Jack's current
   action is cancelled (0x000D1930, 0x000BD4A0) and the kind's reaction runs (0x000CFC80
   push, 0x000CFE00 knock-down or 0x000CFF10); kind 9 also cuts the knock speed to 0.2.
   Jack then recovers for 2 s with src remembered. Called with stack args (j src dir kind). */
void rbk_Knock0D21E0(RbkJack *j, RbkAttacker *src, RbjVec4 *dir, int kind)
{
    RbkKnockFn react[10];
    int anim, voice;

    react[0] = sub_000CFC80;
    react[1] = sub_000CFE00;
    react[2] = sub_000CFF10;
    react[3] = sub_000CFE00;
    react[4] = sub_000CFC80;
    react[5] = sub_000CFC80;
    react[6] = sub_000CFC80;
    react[7] = sub_000CFC80;
    react[8] = sub_000CFC80;
    react[9] = sub_000CFE00;
    voice = -1;
    switch (kind) {
    case 3:
        anim = 0x39;
        voice = 0x29B;
        goto play;
    case 4:
        voice = 0x2F0;
        goto big;
    case 5:
        anim = 0x56;
        goto play;
    case 6:
        anim = 0x57;
        goto play;
    case 7:
        voice = 0x309;
        goto big;
    case 8:
        voice = 0x2FA;
    case 9:
    big:
        anim = 0x58;
    play:
        if (j->modelFD8 != 0 && j->modelFD8->xf20 != 0)
            sub_00036750(j->modelFD8, anim);
        if (voice >= 0)
            rbj_Sound(voice, &j->modelFD8->pos60, 0);
        break;
    }
    if ((j->flags150 & 0x200040) && kind != 1 && kind != 9)
        kind = 1;
    sub_000D1930(j);
    sub_000BD4A0(j, -1, -1.0f);
    react[kind](j, src, dir);
    if (kind == 9) {
        j->knockD50 = j->knockD50 * 0.2f;
        j->knockD54 = j->knockD54 * 0.2f;
    }
    j->linkD5C = src;
    j->hurtD2C = 1;
    j->hurtTimeD30 = 2.0f;
}

/* 0x000D1490: Jack's floor test. Clears the on-floor flag 0x400000. While rising (vertical
   speed < 0) or with flag 0x2000000 the node just moves by the speed. Otherwise a probe
   from the node's position lifted by the floor probe height down to the position moved by
   the speed (plus a 5 unit step-up unless flag 0x80) looks for a floor: a floor without
   the mask bits 0xF00 snaps the node onto it, zeroes both speeds, sets 0x400000 and returns
   1; its 0xF00 bits are kept in +0xEEC. The floor material comes from 0x000A47A0 or, when
   that has none, from a second probe 10 units further down (or the first floor).
   Called with stack args (node a b mask); a and b are not used. */
int rbk_Floor0D1490(RbjNode *node, int a, int b, int *mask)
{
    RbjVec4 to, from;
    RbkFloor *f, *g;
    int landed, set, kind;
    float d;

    to.x = 0.0f;
    to.y = 0.0f;
    to.z = 0.0f;
    to.w = 1.0f;
    from.x = 0.0f;
    from.y = 0.0f;
    from.z = 0.0f;
    from.w = 1.0f;
    RBK_JACK->flags150 &= ~0x400000u;
    if (0.0f > RBK_JACK->fallSpeed14C || (RBK_JACK->flags150 & 0x2000000)) {
        node->pos60.y = node->pos60.y + RBK_JACK->fallSpeed14C;
        return 0;
    }
    sub_000F5D40(&to, &node->pos60);
    d = RBK_JACK->fallSpeed14C;
    if ((int8_t)RBK_JACK->flags150 >= 0)
        d = d + 5.0f;
    to.y = d + to.y;
    sub_000F5D40(&from, &node->pos60);
    from.y = RBK_JACK->prev1A8.y;
    f = sub_0001B490(&from, &to, mask, node->unk118 + 4);   /* node +0x11C */
    if (f != 0) {
        landed = sub_00080D80(f, 0xF00);
        RBK_JACK->floorBitsEEC = sub_00080D90(f) & 0xF00;
        if (landed == 0) {
            node->pos60.y = f->y44;
            RBK_JACK->f148 = 0.0f;
            RBK_JACK->fallSpeed14C = 0.0f;
            RBK_JACK->flags150 |= 0x400000;
            landed = 1;
            goto material;
        }
    }
    node->pos60.y = node->pos60.y + RBK_JACK->fallSpeed14C;
    landed = 0;
material:
    kind = sub_000A47A0();
    if (kind == -1) {
        set = sub_00080970();
        to.y = to.y + 10.0f;
        sub_000824F0(((RbkScene *)rbj_scene42C8E4)->world5C, set, &from, &to, 0, 0);
        g = sub_00080CB0(set, &from, &to);
        if (g != 0)
            kind = sub_00080D60(g);
        else if (f != 0)
            kind = sub_00080D60(f);
        else
            return landed;
    }
    if (kind >= 0)
        RBK_JACK->floorKindEE8 = kind;
    return landed;
}

/* 0x000D3E10: Jack takes a fixed amount of damage with a given knock-back kind (no attacker).
   Same guards and results as 0x000D3BF0; while carrying the held object is dropped with
   message 0x2D and Jack is knocked down instead. The hit is not remembered.
   Called with stack args (j dir kind damage). */
int rbk_JackHurt0D3E10(RbkJack *j, RbjVec4 *dir, int kind, int damage)
{
    RbkMsg msg;
    RbjVec4 zero;

    if (sub_0019BE60(0x10000) != 0)
        return -1;
    if (j->flags150 & 0x80080010)
        return -1;
    if (j->hurtD2C != 0 || j->modeD4 == 4 || j->modeD4 == 5)
        return -1;
    if (j->flagsD60 & 1)
        return 2;
    if (!(j->flags150 & 0x2000)) {
        sub_000D21E0(j, 0, dir, kind);
    } else if (j->stateD8 == 0x1D || j->stateD8 == 0x1E) {
        if (j->linkD5C != 0) {
            zero.x = 0.0f;
            zero.y = 0.0f;
            zero.z = 0.0f;
            zero.w = 1.0f;
            msg.id00 = 0x2D;
            msg.f0C = 0.0f;
            msg.a08 = 0;
            msg.a04 = 0;
            sub_000F5D40(&msg.v10, &zero);
            sub_000F5D40(&msg.v20, &zero);
            sub_000EE010(j->linkD5C, &msg);
            j->linkD5C = 0;
        }
        sub_000D1930(j);
        sub_000BD4A0(j, -1, -1.0f);
        sub_000CFE00(j, 0, dir);
        j->linkD5C = 0;
        j->hurtD2C = 1;
        j->hurtTimeD30 = 2.0f;
    }
    if (Player_TakeDamage((PlayerStats *)j, damage) < 0)
        rtc_PlayerEventB(j);
    return 1;
}

/* 0x000D3FA0: Jack is hit by src with the damage looked up by explicit ids (idA idB kind).
   Like 0x000D3BF0, but the attacker is passed to the knock-back only for knock kind 2 and
   not remembered while carrying. Called with stack args (j src idA idB kind dir). */
int rbk_JackHitBy0D3FA0(RbkJack *j, RbkAttacker *src, int idA, int idB, int kind, RbjVec4 *dir)
{
    RbkMsg msg;
    RbjVec4 zero;
    int n;

    if (sub_0019BE60(0x10000) != 0)
        return -1;
    if ((j->flags150 & 0x80080010) || j->hurtD2C != 0 || j->modeD4 == 4 || j->modeD4 == 5)
        return -1;
    if (j->flagsD60 & 1)
        return 2;
    if (!(j->flags150 & 0x2000)) {
        n = sub_00171EB0(idA, idB, kind, 1);
        if (n == 2)
            sub_000D21E0(j, src, dir, n);
        else
            sub_000D21E0(j, 0, dir, n);
        n = sub_00171EB0(idA, idB, kind, 2);
        if (n != 0) {
            j->flags150 |= 0x10000;
            j->stunD48 = (float)n;
        }
    } else if (j->stateD8 == 0x1D || j->stateD8 == 0x1E) {
        if (j->linkD5C != 0) {
            zero.x = 0.0f;
            zero.y = 0.0f;
            zero.z = 0.0f;
            zero.w = 1.0f;
            msg.id00 = 0x2D;
            msg.f0C = 0.0f;
            msg.a08 = 0;
            msg.a04 = 0;
            sub_000F5D40(&msg.v10, &zero);
            sub_000F5D40(&msg.v20, &zero);
            sub_000EE010(j->linkD5C, &msg);
            j->linkD5C = 0;
        }
        sub_000D1930(j);
        sub_000BD4A0(j, -1, -1.0f);
        sub_000CFE00(j, 0, dir);
        j->linkD5C = 0;
        j->hurtD2C = 1;
        j->hurtTimeD30 = 2.0f;
    }
    n = sub_00171EB0(idA, idB, kind, 0);
    if (Player_TakeDamage((PlayerStats *)j, n) < 0)
        rtc_PlayerEventB(j);
    if (!(j->flags150 & 0x2000)) {
        j->lastDamageD34 = n;
        j->lastSrcAD38 = src->idA04;
        j->lastSrcBD3C = src->idB08;
        j->lastKindD40 = kind;
    }
    return 1;
}
