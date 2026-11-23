/* Area m1, file 364: register-argument revisits (written with normal parameters). Names inferred. */
#include <stdint.h>
#include "m1_slots.h"
#include "m1_enemy.h"

extern int32_t m1_plMode420078;
extern M1BoneSlot m1_ents41C7C0[];
void *a12_List_FindId(void *o, int id);
/* 0xCEC90 takes the object in eax and a flag in ecx plus one stack argument; 0xCDBE0 takes the bone in eax. Written as ordinary parameters. */
int  m1_BoneSetCEC90(void *o, int flag, int id);
void sub_000CDBE0(M1BoneSlot *s, int bone);

/* 0xCEE40: fade in the player's attachment for item id (blend 1) when both the id and the item are given. */
void m1_AttachFadeIn0CEE40(int id, int item) {
    int i; M1BoneSlot *s;
    if (m1_plMode420078 == 2) return;
    i = m1_BoneSetCEC90(a12_List_FindId(g_playerObj, 0), 0, id);
    if (i < 0 || id == 0 || item == 0) return;
    s = &m1_ents41C7C0[i];
    s->blend = 1.0f;
    sub_000CDBE0(s, s->bone);
}

/* 0x18A280: size an enemy: its scale (passed in xmm0, with the state in ecx and the body in eax; written as ordinary parameters) sets its upward speed and three collision sizes. */
void m1_EnemyScale18A280(float s, M1Enemy2State *st, M1Actor *o) {
    st->vel[1] = s * -4.0f;
    o->colRadius = s * 5.0f;
    o->colHeight = s * -30.0f;
    o->colReach = s * 12.0f;
}
