/* Area m2, file 15. Names inferred. */
#include <stdint.h>

typedef struct M2Ent15 { int8_t k0, k1; uint8_t unk02[2]; int32_t bit4; int8_t b8, b9, bA; uint8_t unk0B; int8_t nearC; uint8_t unk0D[3]; float pos10[3]; float yaw1C; } M2Ent15;
typedef struct M2EList15 { uint8_t unk00[8]; int32_t n8; uint8_t unk0C[4]; M2Ent15 e[1]; } M2EList15;
typedef struct M2Cand15 { struct M2Cand15 *next0; uint8_t unk04[8]; M2Ent15 *entC; float d10; } M2Cand15;
typedef struct M2CList15 { uint8_t unk00[4]; M2Cand15 *first4; } M2CList15;
typedef struct M2Tm15 { void *obj0; float t4; } M2Tm15;
extern M2EList15 *m1_addEnemy3ED1B0;
extern M2CList15 a8c_list3ED1B4;
extern M2Tm15 *r6c_timed;
extern M2Cand15 m2_slots3ECCB0[65];
extern uint8_t *aab_player;
extern uint8_t g_stats[];
void  a3c_VecCopy(float *d, const float *s);
void  sub_000CF2C0(void *stats, float *out);
void  a3c_Clear16(void *list);
void  a4c_ListAppend(void *list, void *node);
void  a4c_ListRemove(void *node);
int   r2b_TestBit(int bit);
float rbj_Distance(const float *a, const float *b);
void  rbj_VecSub(float *d, const float *a, const float *b);
float sub_001B27C0(const float *a, const float *b);

/* 0x84F00: pick the enemy spawn point to use: among enabled points whose timer has run out, keep those 30..60 units from the player, -50..50 units above, and within 45 degrees of the view direction (at most 65); remove and return the nearest one's entry, or 0 when there is none. */
M2Ent15 *m2_PickSpawn84F00(void) {
    float d, ang, p[4], pp[4], t[4], view[4];
    float best = 1000000.0f;
    M2Cand15 *bc = 0, *c;
    M2EList15 *h = m1_addEnemy3ED1B0;
    M2Ent15 *e;
    int i, n = 0;
    if (h == 0) return 0;
    e = h->e;
    a3c_VecCopy(pp, (float *)(aab_player + 0x60));
    sub_000CF2C0(g_stats, view);
    a3c_Clear16(&a8c_list3ED1B4);
    for (i = 0; i < h->n8; i++, e++) {
        if (r2b_TestBit(e->bit4) == 0) continue;
        if (!(0.0f >= r6c_timed[i].t4)) continue;
        p[0] = e->pos10[0]; p[1] = e->pos10[1]; p[2] = e->pos10[2]; p[3] = 1.0f;
        d = rbj_Distance(pp, p);
        if (!(d >= 30.0f)) continue;
        if (!(60.0f >= d)) continue;
        { float dy = p[1] - pp[1];
          if (!(dy >= -50.0f)) continue;
          if (!(50.0f >= dy)) continue; }
        rbj_VecSub(t, p, pp);
        ang = sub_001B27C0(view, t);
        if (!(ang >= -0.78539819f)) continue;
        if (!(0.78539819f >= ang)) continue;
        m2_slots3ECCB0[n].entC = e;
        m2_slots3ECCB0[n].d10 = d;
        a4c_ListAppend(&a8c_list3ED1B4, &m2_slots3ECCB0[n]);
        n++;
        if (n > 64) break;
    }
    if (n == 0) return 0;
    for (c = a8c_list3ED1B4.first4; c != 0; c = c->next0)
        if (best > c->d10) { best = c->d10; bc = c; }
    a4c_ListRemove(bc);
    return bc->entC;
}

int   sub_00086250(int a, int b);
void *rbi_Spawn0ED630(int a, int b, float *pos, float *rot, int c);
void  sub_000EDF30(void *o, int k, int v);
void  sub_000EDF90(void *o);
M2Ent15 *sub_00084F00(void);

/* 0x85110: try up to count spawn points (nearest suitable first, see 0x84F00): spawn the enemy of each allowed kind facing the player (near points) or its stored yaw, remember it with an 8-second timer and set its two parameters. Returns how many were spawned. */
int m2_SpawnEnemies85110(int count) {
    float rot[4], pos[4], d[4], down[4];
    int spawned = 0, tries = 0;
    M2Ent15 *e;
    void *o;
    down[0] = 0.0f; down[1] = 0.0f; down[2] = -1.0f; down[3] = 1.0f;
    e = sub_00084F00();
    if (count <= 0) return 0;
    do {
        if (e == 0) break;
        if (sub_00086250(e->k0, e->k1) != 0) {
            pos[0] = e->pos10[0]; pos[1] = e->pos10[1]; pos[2] = e->pos10[2]; pos[3] = 1.0f;
            rot[0] = 0.0f; rot[2] = 0.0f; rot[3] = 0.0f;
            if (e->nearC == 0) {
                rot[1] = e->yaw1C;
            } else {
                rbj_VecSub(d, (float *)(aab_player + 0x60), pos);
                rot[1] = sub_001B27C0(down, d);
            }
            o = rbi_Spawn0ED630(e->k0, e->k1, pos, rot, e->b8);
            if (o != 0) {
                int i = e - m1_addEnemy3ED1B0->e;
                r6c_timed[i].obj0 = o;
                r6c_timed[i].t4 = 8.0f;
                sub_000EDF30(o, 0, e->b9);
                sub_000EDF30(o, 1, e->bA);
                sub_000EDF90(o);
                spawned++;
            }
        }
        tries++;
        e = 0;
        if (m1_addEnemy3ED1B0 != 0) {
            float best = 1000000.0f;
            M2Cand15 *c, *bc = 0;
            for (c = a8c_list3ED1B4.first4; c != 0; c = c->next0)
                if (best > c->d10) { best = c->d10; bc = c; }
            if (bc != 0) { a4c_ListRemove(bc); e = bc->entC; }
        }
    } while (tries < count);
    return spawned;
}
