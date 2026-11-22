/* Area m1, file 360: second enemy type's knock-down, get-up and recovery states. Names
   inferred. Types come from m1_enemy.h. */
#include "m1_enemy.h"

/* 0x15CF20: when the get-up animation ends leave into state 0x18 (stand-up trigger), or
   cue the helper and leave into 4 (one time in 8) or 2. */
void m1_AiGetUp15CF20(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s = e->st;
    uint32_t f;
    if (!sub_000833E0(o->anim))
        return;
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    s->flags |= M1ES_HELPER_CUE;
    sub_00147FD0(s->helper, 2);
    if (sub_001C7EE1() & 7) {
        M1_STANDUP2_EXIT(2);
        return;
    }
    M1_STANDUP2_EXIT(4);
}


/* 0x15A550: take a hit (second enemy type): dead or flagged enemies ignore it; store the
   hit and subtract the damage (death flags the body); react with the state 0x1550E0 picks
   (0x25 only counts a damaging hit), then tell the helper whether it died and pass on a
   pending cue. Returns 1 for kind-1 hits, else -1. */
int m1_TakeHit15A550(M1Actor *o, M1EnemyAi *e, M1Hit *hit) {
    M1Enemy2State *s;
    volatile int f;
    float v;
    int k, r;
    if (o->bodyFlags & 8)
        return 0;
    s = e->st;
    if (s->flags & M1ES_DEAD)
        return 0;
    s->lastHit = *hit;
    v = e->hp - s->lastHit.damage;
    e->hp = v;
    if (0.0f >= v) {
        e->hp = 0.0f;
        o->bodyFlags |= 8;
        s->flags |= M1ES_DEAD;
    }
    k = sub_001550E0();
    r = sub_00146030(s->lastHit.kind) == 1 ? 1 : -1;
    if (k == 0x25) {
        if (s->lastHit.damage > 0.0f)
            s->hits++;
    } else {
        sub_0015A270(o, k);
    }
    if (s->helper) {
        f = 0;
        if (s->flags & M1ES_DEAD)
            f = 1;
        sub_00147FD0(s->helper, f);
        if (s->flags & M1ES_HELPER_CUE) {
            s->flags &= ~M1ES_HELPER_CUE;
            sub_00147FD0(s->helper, 3);
        }
    }
    return r;
}


/* 0x15D1F0: when the get-up animation ends leave into state 0x18 (stand-up trigger); a
   flagged enemy reacts with state 9 instead; otherwise leave into 4 (one time in 8) or 2. */
void m1_AiGetUpB15D1F0(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s;
    uint32_t f;
    if (!sub_000833E0(o->anim))
        return;
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    if (e->aiFlags & 1) {
        sub_0015A270(o, 9);
        return;
    }
    if (sub_001C7EE1() & 7) {
        M1_STANDUP2_EXIT(2);
        return;
    }
    M1_STANDUP2_EXIT(4);
}


/* 0x161C90: (must be in mode 10, else hang) when the get-up animation ends leave into 0x13
   or 1 for a flagged enemy (bit 0x10000 picks), else into 0x15. */
void m1_AiGetUpC161C90(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s;
    uint32_t f, g;
    if (e->phase != 10)
        for (;;);
    if (!sub_000833E0(o->anim))
        return;
    g = e->aiFlags;
    if (g & 1) {
        if (g & 0x10000) {
            M1_STANDUP2_EXIT(0x13);
            return;
        }
        M1_STANDUP2_EXIT(1);
        return;
    }
    M1_STANDUP2_EXIT(0x15);
}



/* 0x15E300: when the get-up animation ends leave into 0x18 (stand-up trigger); an enemy
   without flag 0x10000 leaves into 6; otherwise react with state 9 when 0x185420 reports 3,
   else leave into 0xD. */
void m1_AiGetUpD15E300(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s;
    uint32_t f;
    if (!sub_000833E0(o->anim))
        return;
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    if (!(e->aiFlagByte[2] & 1)) {
        M1_STANDUP2_EXIT(6);
        return;
    }
    if (sub_00185420(o) == 3) {
        sub_0015A270(o, 9);
        return;
    }
    M1_STANDUP2_EXIT_SND(0xD);
}

/* 0x164EE0: (mode 0 only) when the get-up animation ends leave into 0x18 (stand-up
   trigger); with flag 0x10000 react with state 9 (flag 1) or leave into 2, else into 1. */
void m1_AiGetUpE164EE0(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s;
    uint32_t f, g;
    if (e->phase != 0)
        return;
    if (!sub_000833E0(o->anim))
        return;
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    g = e->aiFlags;
    if (g & 0x10000) {
        if (g & 1) {
            sub_0015A270(o, 9);
            return;
        }
        M1_STANDUP2_EXIT(2);
        return;
    }
    M1_STANDUP2_EXIT(1);
}



/* 0x163FB0: knocked flat. A grabbed enemy (flag 0x20) only runs the grab update. Phase 0
   waits for a ground contact (body bits 0x18); phase 1 sets the knocked state, zeroes the
   speeds, plays sound 0x10E and starts a half-second timer; phase 2 waits for the timer,
   then leaves into 0 (dead), 0x18 (stand-up trigger) or 0x38. */
void m1_AiKnockedFlat163FB0(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s = e->st;
    uint32_t f, g;
    g = s->flags;
    if (g & M1ES_GRABBED) {
        sub_00185540(o);
        sub_000ED780(o);
        return;
    }
    switch (e->phase) {
    case 0:
        if (o->contact & 0x18)
            e->phase = 1;
        return;
    case 1:
        m1_AiSetState1456E0(o, e, 0x45, 0);
        s->vel[2] = 0.0f;
        s->vel[1] = 0.0f;
        s->vel[0] = 0.0f;
        s->velScale = 1.0f;
        s->f10 = 0.0f;
        s->fall = m1_frameTime42C858 * 0.005f;
        sub_00036750(o, 6);
        sub_000494D0(0x10E, o->pos, 0);
        e->timer = 0.5f;
        (e->phase)++;
        return;
    case 2:
        if (0.0f >= e->timer) {
            if (g & M1ES_DEAD) {
                M1_STANDUP2_EXIT(0);
                return;
            }
            if (sub_00156040()) {
                M1_STANDUP2_EXIT(0x18);
                return;
            }
            M1_STANDUP2_EXIT(0x38);
        }
        return;
    }
}


/* 0x15B300: getting up from a fall. When the animation ends leave into 0x18 (stand-up trigger);
   a flagged enemy reacts with state 9 (0x185420 reports 3) or leaves into 0xD with sound
   0x10F; otherwise into 2 (or 4 one time in 4). Every frame, within 14 units of the landing
   spot, notify 0x113190. */
void m1_AiFallGetUp15B300(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s;
    uint32_t f;
    if (sub_000833E0(o->anim)) {
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
        } else if (e->aiFlags & 1) {
            if (sub_00185420(o) == 3) {
                sub_0015A270(o, 9);
            } else {
                M1_STANDUP2_EXIT_SND(0xD);
            }
        } else if (sub_001C7EE1() & 3) {
            M1_STANDUP2_EXIT(2);
        } else {
            M1_STANDUP2_EXIT(4);
        }
    }
    if (sub_00145780(o, 14.0f))
        sub_00113190(o, e, 1);
}

/* 0x163290: getting up after a knock-down. A grabbed enemy only runs the grab update. When
   the animation ends leave into 0 (dead), 0x18 (stand-up trigger), state 9 or 2 (flag
   0x10000, picked by flag 1), else 6. */
void m1_AiKnockGetUp163290(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s = e->st;
    uint32_t f, g;
    if (s->flags & M1ES_GRABBED) {
        sub_00185540(o);
        sub_000ED780(o);
        return;
    }
    if (!sub_000833E0(o->anim))
        return;
    if (s->flags & M1ES_DEAD) {
        M1_STANDUP2_EXIT(0);
        return;
    }
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    g = e->aiFlags;
    if (g & 0x10000) {
        if (g & 1) {
            sub_0015A270(o, 9);
            return;
        }
        M1_STANDUP2_EXIT(2);
        return;
    }
    M1_STANDUP2_EXIT(6);
}

/* 0x1648B0: tumble. Phases: wait for the animation, set the tumble state (0x38); wait,
   set the landing state (0x39) and zero the speeds; wait, then leave into 0x18 (stand-up
   trigger), state 9 or 2 (flag 0x10000, picked by flag 1), else 6. During the first three
   phases the side speeds bleed off by 5% per frame unit. */
void m1_AiTumble1648B0(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s = e->st;
    uint32_t f, g;
    switch (e->phase) {
    case 0:
        if (!sub_000833E0(o->anim))
            break;
        e->phase++;
    case 1:
        m1_AiSetState1456E0(o, e, 0x38, 0);
        e->phase++;
        break;
    case 2:
        if (!sub_000833E0(o->anim))
            break;
        e->phase++;
    case 3:
        m1_AiSetState1456E0(o, e, 0x39, 0);
        s->vel[2] = 0.0f;
        s->vel[1] = 0.0f;
        s->vel[0] = 0.0f;
        s->velScale = 1.0f;
        s->f10 = 0.0f;
        s->fall = m1_frameTime42C858 * 0.005f;
        s->moveFlags &= ~7u;
        e->phase++;
        break;
    case 4:
        if (!sub_000833E0(o->anim))
            break;
        e->phase++;
    case 5:
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        g = e->aiFlags;
        if (g & 0x10000) {
            if (g & 1) {
                sub_0015A270(o, 9);
                return;
            }
            M1_STANDUP2_EXIT(2);
            return;
        }
        M1_STANDUP2_EXIT(6);
        return;
    }
    if (e->phase <= 2) {
        s->vel[0] = (1.0f - m1_frameTime42C858 * 0.05f) * s->vel[0];
        s->vel[2] = (1.0f - m1_frameTime42C858 * 0.05f) * s->vel[2];
    }
}

/* 0x15EAB0: recover. When the animation ends leave into 0x18 (stand-up trigger); with flag
   0x10000 into 5 (flag 1) or 2; otherwise into 1 (or 6 one time in 8). */
void m1_AiRecover15EAB0(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s;
    uint32_t f, g;
    if (!sub_000833E0(o->anim))
        return;
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    g = e->aiFlags;
    if (g & 0x10000) {
        if (g & 1) {
            M1_STANDUP2_EXIT(5);
            return;
        }
        M1_STANDUP2_EXIT(2);
        return;
    }
    if (sub_001C7EE1() & 7) {
        M1_STANDUP2_EXIT(1);
        return;
    }
    M1_STANDUP2_EXIT(6);
}

/* 0x161750: down and getting up. A grabbed enemy only runs the grab update. Phase 0 waits
   for the animation; phase 1 leaves into 0 (dead), 0x18 (stand-up trigger), 5 or 2 (flag
   0x10000, picked by flag 1), else 6 or 1 (picked by flag 1). */
void m1_AiDownGetUp161750(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s = e->st;
    M1Enemy2State *s0 = s;
    uint32_t f, g;
    if (s->flags & M1ES_GRABBED) {
        sub_00185540(o);
        sub_000ED780(o);
        return;
    }
    switch (e->phase) {
    case 0:
        if (!sub_000833E0(o->anim))
            return;
        e->phase++;
    case 1:
        if (s0->flags & M1ES_DEAD) {
            M1_STANDUP2_EXIT(0);
            return;
        }
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        g = e->aiFlags;
        if (g & 0x10000) {
            if (g & 1) {
                M1_STANDUP2_EXIT(5);
                return;
            }
            M1_STANDUP2_EXIT(2);
            return;
        }
        if (g & 1) {
            M1_STANDUP2_EXIT(6);
            return;
        }
        M1_STANDUP2_EXIT(1);
        return;
    }
}


/* 0x15C7A0: recovering on the ground. Until the animation ends the enemy heals 0.05% of its
   maximum per frame (capped at full). Then: 0x18 (stand-up trigger); on stage 8, 0xF at half
   health or less, else 0x11 (coin flip) or state 9/7 by flag 1; flagged enemies react with
   state 9 (0x185420 reports 3) or leave into 0xD with sound 0x10F; otherwise 2 (or 4 one time
   in 8). */
void m1_AiRecoverHeal15C7A0(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s;
    uint32_t f;
    int d;
    float v;
    if (!sub_000833E0(o->anim)) {
        v = e->hpMax * 0.0005f + e->hp;
        e->hp = v;
        if (v > e->hpMax)
            e->hp = e->hpMax;
        return;
    }
    d = sub_000CF4F0(m1_stats41FEC0);
    if (sub_00156040()) {
        M1_STANDUP2_EXIT(0x18);
        return;
    }
    if (d == 8) {
        if (0.5f >= e->hp / e->hpMax) {
            M1_STANDUP2_EXIT(0xF);
            return;
        }
        if (sub_001C7EE1() & 1) {
            M1_STANDUP2_EXIT(0x11);
            return;
        }
        if (e->aiFlags & 1) {
            sub_0015A270(o, 9);
            return;
        }
        sub_0015A270(o, 7);
        return;
    }
    if (e->aiFlags & 1) {
        if (sub_00185420(o) == 3) {
            sub_0015A270(o, 9);
            return;
        }
        M1_STANDUP2_EXIT_SND(0xD);
        return;
    }
    if (sub_001C7EE1() & 7) {
        M1_STANDUP2_EXIT(2);
        return;
    }
    M1_STANDUP2_EXIT(4);
}


/* 0x161100: down after a combo. Like 0x161750, but on getting up an enemy hit 10+ times (or
   5+ times, one time in 8) arms an angry dash (flag 4, speed 288 or 216) and leaves into
   0x1A. */
void m1_AiComboDown161100(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s = e->st;
    uint32_t f, g;
    float v;
    if (s->flags & M1ES_GRABBED) {
        sub_00185540(o);
        sub_000ED780(o);
        return;
    }
    switch (e->phase) {
    case 0:
        if (!sub_000833E0(o->anim))
            return;
        e->phase++;
    case 1:
        if (s->hits >= 10) {
            v = 288.0f;
            goto arm;
        }
        if (s->hits >= 5 && !(sub_001C7EE1() & 7)) {
            v = 216.0f;
arm:
            s->flags |= M1ES_ANGRY;
            s->dashSpeed = v;
        }
        if (s->flags & M1ES_DEAD) {
            M1_STANDUP2_EXIT(0);
            return;
        }
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        if (s->flags & M1ES_ANGRY) {
            M1_STANDUP2_EXIT(0x1A);
            return;
        }
        g = e->aiFlags;
        if (g & 0x10000) {
            if (g & 1) {
                M1_STANDUP2_EXIT(5);
                return;
            }
            M1_STANDUP2_EXIT(2);
            return;
        }
        if (g & 1) {
            M1_STANDUP2_EXIT(6);
            return;
        }
        M1_STANDUP2_EXIT(1);
        return;
    }
}

/* 0x161F40: landing from a throw (phase 0x28) or a slam (phase 0x1E); any other phase hangs.
   Throw: when the animation ends leave into 0x18 (stand-up trigger), 5 or 2 (flag 0x10000,
   picked by flag 1), else 1. Slam: 0x11 when within 30 units, else 0x13 or 0x12 (flag
   0x10000, picked by flag 1), else 6. */
void m1_AiLand161F40(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s = e->st;
    M1Enemy2State *s0 = s;
    uint32_t f, g;
    switch (e->phase) {
    default:
        for (;;);
    case 0x28:
        if (!sub_000833E0(o->anim))
            return;
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        g = e->aiFlags;
        if (g & 0x10000) {
            if (g & 1) {
                M1_STANDUP2_EXIT(5);
                return;
            }
            M1_STANDUP2_EXIT(2);
            return;
        }
        M1_STANDUP2_EXIT(1);
        return;
    case 0x1E:
        if (!sub_000833E0(o->anim))
            return;
        if (30.0f >= s0->landDist) {
            M1_STANDUP2_EXIT(0x11);
            return;
        }
        g = e->aiFlags;
        if (g & 0x10000) {
            if (g & 1) {
                M1_STANDUP2_EXIT(0x13);
                return;
            }
            M1_STANDUP2_EXIT(0x12);
            return;
        }
        M1_STANDUP2_EXIT(6);
        return;
    }
}



/* 0x162740: launched upward. A grabbed enemy only runs the grab update. Phases: wait, switch
   the flight animation (0x34 -> 0x35, 0x37 -> 0x38, else hang) and mark airborne; wait for a
   ground contact (clears body flag 0x10); wait, switch the landing animation (0x35 -> 0x36,
   0x38 -> 0x39) and zero the speeds; wait, then leave into 0 (dead), 0x18 (stand-up
   trigger), state 9 or 2 (flag 0x10000, picked by flag 1), else 6. In the first four
   phases the side speeds bleed off and gravity (147) pulls the body down. */
void m1_AiLaunched162740(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s = e->st;
    M1Enemy2State *s0 = s;
    int32_t an;
    uint32_t f, g;
    float fr;
    if (s->flags & M1ES_GRABBED) {
        sub_00185540(o);
        sub_000ED780(o);
        return;
    }
    switch (e->phase) {
    case 0:
        if (!sub_000833E0(o->anim))
            break;
        e->phase++;
    case 1:
        an = e->animId;
        if (an == 0x34)
            m1_AiSetState1456E0(o, e, 0x35, 0);
        else if (an == 0x37)
            m1_AiSetState1456E0(o, e, 0x38, 0);
        else
            for (;;);
        s->moveFlags |= 8;
        e->phase++;
        break;
    case 2:
        if (o->contact & 0x18) {
            o->bodyFlags &= ~0x10u;
            e->phase++;
        }
        break;
    case 3:
        if (!sub_000833E0(o->anim))
            break;
        e->phase++;
    case 4:
        an = e->animId;
        if (an == 0x35)
            m1_AiSetState1456E0(o, e, 0x36, 0);
        else if (an == 0x38)
            m1_AiSetState1456E0(o, e, 0x39, 0);
        else
            for (;;);
        s->vel[2] = 0.0f;
        s->vel[1] = 0.0f;
        s->vel[0] = 0.0f;
        s->velScale = 1.0f;
        s->f10 = 0.0f;
        s->fall = m1_frameTime42C858 * 0.005f;
        s->moveFlags &= ~7u;
        e->phase++;
        break;
    case 5:
        if (!sub_000833E0(o->anim))
            break;
        e->phase++;
    case 6:
        if (s0->flags & M1ES_DEAD) {
            M1_STANDUP2_EXIT(0);
            return;
        }
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        g = e->aiFlags;
        if (g & 0x10000) {
            if (g & 1) {
                sub_0015A270(o, 9);
                return;
            }
            M1_STANDUP2_EXIT(2);
            return;
        }
        M1_STANDUP2_EXIT(6);
        return;
    }
    if (e->phase <= 3) {
        s->vel[0] = (1.0f - m1_frameTime42C858 * 0.05f) * s->vel[0];
        s->vel[2] = (1.0f - m1_frameTime42C858 * 0.05f) * s->vel[2];
        fr = m1_frameRate42C85C;
        s->vel[1] = fr * fr * 147.0f + s->vel[1];
    }
}

/* 0x162C90: knocked back. A grabbed enemy only runs the grab update. Phases (each waiting
   step falls straight into the next): wait, switch the flight animation (0x34 -> 0x35,
   0x37 -> 0x38, else hang); wait, switch the landing animation (0x35 -> 0x36, 0x38 -> 0x39)
   and zero the speeds; wait, then leave into 0 (dead), 0x18 (stand-up trigger), 0x1A
   (angry, flag 0x20000), state 9 or 2 (flag 0x10000, picked by flag 1), else 6. During the
   first three phases the side speeds bleed off by 5% per frame unit. */
void m1_AiKnockBack162C90(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s = e->st;
    M1Enemy2State *s0 = s;
    int32_t an;
    uint32_t f, g;
    if (s->flags & M1ES_GRABBED) {
        sub_00185540(o);
        sub_000ED780(o);
        return;
    }
    switch (e->phase) {
    case 0:
        if (!sub_000833E0(o->anim))
            break;
        e->phase++;
    case 1:
        an = e->animId;
        if (an == 0x34)
            m1_AiSetState1456E0(o, e, 0x35, 0);
        else if (an == 0x37)
            m1_AiSetState1456E0(o, e, 0x38, 0);
        else
            for (;;);
        e->phase++;
    case 2:
        if (!sub_000833E0(o->anim))
            break;
        e->phase++;
    case 3:
        an = e->animId;
        if (an == 0x35)
            m1_AiSetState1456E0(o, e, 0x36, 0);
        else if (an == 0x38)
            m1_AiSetState1456E0(o, e, 0x39, 0);
        else
            for (;;);
        s->vel[2] = 0.0f;
        s->vel[1] = 0.0f;
        s->vel[0] = 0.0f;
        s->velScale = 1.0f;
        s->f10 = 0.0f;
        s->fall = m1_frameTime42C858 * 0.005f;
        s->moveFlags &= ~7u;
        e->phase++;
        break;
    case 4:
        if (!sub_000833E0(o->anim))
            break;
        e->phase++;
    case 5:
        if (s0->flags & M1ES_DEAD) {
            M1_STANDUP2_EXIT(0);
            return;
        }
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        g = e->aiFlags;
        if (g & 0x10000) {
            if (s0->flags & M1ES_ANGRY_READY) {
                s0->dashSpeed = 0.0f;
                M1_STANDUP2_EXIT(0x1A);
                return;
            }
            if (g & 1) {
                sub_0015A270(o, 9);
                return;
            }
            M1_STANDUP2_EXIT(2);
            return;
        }
        M1_STANDUP2_EXIT(6);
        return;
    }
    if (e->phase <= 2) {
        s->vel[0] = (1.0f - m1_frameTime42C858 * 0.05f) * s->vel[0];
        s->vel[2] = (1.0f - m1_frameTime42C858 * 0.05f) * s->vel[2];
    }
}




/* 0x160650: counter attack. Phase 0 waits for the animation and goes to phase 10; phase 1
   resets the state; phase 2 goes to phase 10 while 0x185420 reports under 3. Phase 10 sets
   the counter state (0x22), zeroes the speeds and sets two spin channels; phase 11 lands
   (within 14 units sets flag 1) and moves to phase 20 when the animation ends; phase 20
   sets state 5; phase 21 waits for the animation (notifying 0x113190 near the landing
   spot), then leaves into 0x18 (stand-up trigger), 0x22 with sound 0x10F (target is a
   type-0xD body with flag 1), else 5 or 2 (flag 1). */
void m1_AiCounter160650(M1Actor *o, M1EnemyAi *e) {
    M1Enemy2State *s = e->st;
    M1Spin *p;
    M1Actor *t;
    uint32_t f;
    switch (e->phase) {
    case 0:
        if (sub_000833E0(o->anim))
            e->phase = 10;
        return;
    case 1:
        m1_AiSetState1456E0(o, e, 0, 0);
        e->phase++;
        return;
    case 2:
        if (sub_00185420(o) < 3)
            e->phase = 10;
        return;
    case 10:
        m1_AiSetState1456E0(o, e, 0x22, 0);
        s->fall = m1_frameTime42C858 * 0.005f;
        s->vel[2] = 0.0f;
        s->vel[1] = 0.0f;
        s->vel[0] = 0.0f;
        s->velScale = 1.0f;
        s->f10 = 0.0f;
        sub_00147710(e, 1, 0.08726647f, -0.08726647f, m1_frameTime42C858 * 0.15707964f, 0);
        p = m1_Quest113400(e, 5);
        p->a = 9.0f;
        p->b = 1.0f;
        p->c = 0.0f;
        p->d = 0.0f;
        e->phase++;
        return;
    case 11:
        if (sub_00145780(o, 14.0f))
            sub_00113480(e, 1);
        if (sub_000833E0(o->anim)) {
            m1_gF3F7504 = 3.0f;
            e->phase = 20;
        }
        return;
    case 20:
        m1_AiSetState1456E0(o, e, 5, 0);
        e->phase++;
        return;
    case 21:
        if (sub_00145780(o, 14.0f))
            sub_00113190(o, e, 1);
        if (!sub_000833E0(o->anim))
            return;
        if (sub_00156040()) {
            M1_STANDUP2_EXIT(0x18);
            return;
        }
        t = e->target;
        if (e->targetKind == 1 && (t->drawFlags & 1) && t->kind == 0xD) {
            M1_STANDUP2_EXIT_SND(0x22);
            return;
        }
        if (e->aiFlags & 1) {
            M1_STANDUP2_EXIT(5);
            return;
        }
        M1_STANDUP2_EXIT(2);
        return;
    }
}
