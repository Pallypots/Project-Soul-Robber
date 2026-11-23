/* Area m1, file 363: register-argument revisits (written with normal parameters). Names inferred. */
#include <stdint.h>
#include "m1_player.h"

void m1_SlotTickCD860(M1Player *p, int k);
/* 0xCC510 and 0xCC6E0 take the player in esi, a in edi and b in edx; written as ordinary parameters. */
int sub_000CC510(M1Player *p, int a, int b);
int sub_000CC6E0(M1Player *p, int a, int b);

/* 0xCD8D0: try a slot action: -1 while locked; 1 if the first test passes; otherwise 1 or -1 from the second test. */
int m1_SlotTry0CD8D0(M1Player *p, int a, int b) {
    if (p->stateFlags & 0x800) return -1;
    m1_SlotTickCD860(p, 0);
    if (sub_000CC510(p, a, b) > 0) return 1;
    return sub_000CC6E0(p, a, b) > 0 ? 1 : -1;
}

#include "m1_slots.h"
extern int32_t m1_plMode420078;
extern void *g_playerObj;
extern M1BoneSlot m1_ents41C7C0[];
void *a12_List_FindId(void *o, int id);
/* 0xCDAB0 takes the object in eax and a kind in esi; 0xCDBE0 takes the bone in eax. Written as ordinary parameters. */
int  m1_FindEntryCDAB0(void *o, int kind);
void m1_BonesClearCDBA0(void);
void m1_BonesRestoreCDB50(void);
void sub_000CDBE0(M1BoneSlot *s, int bone);

/* Twins: find the player's attachment slot, set or clear its hidden bit, refresh the bones and reset the slot pose. */
#define M1_SLOTVIS363(name, hide, refresh) \
void name(void) { \
    int i; M1BoneSlot *s; \
    if (m1_plMode420078 == 2) return; \
    i = m1_FindEntryCDAB0(a12_List_FindId(g_playerObj, 0), 1); \
    if (i < 0) return; \
    s = &m1_ents41C7C0[i]; \
    if (hide) s->flags |= 2; else s->flags &= ~2u; \
    refresh(); \
    s->frame = 0; s->blend = 0.0f; \
    sub_000CDBE0(s, s->bone); \
}

/* 0xCEEA0: show the attachment. */
M1_SLOTVIS363(m1_AttachShow0CEEA0, 0, m1_BonesClearCDBA0)
/* 0xCEF00: hide the attachment. */
M1_SLOTVIS363(m1_AttachHide0CEF00, 1, m1_BonesRestoreCDB50)
