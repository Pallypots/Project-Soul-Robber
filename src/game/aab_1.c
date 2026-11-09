/* Area aab, group 1: slot table helpers (0x000A2CA0..0x000A5460). Names inferred. */
#include "aab.h"

/* 0x000A2CA0: OR bits into slot i's flags. */
void aab_SlotSetFlags(int i, uint32_t m) { AabSlot *s = &aab_slots[i]; if (s) s->flags |= m; }

/* 0x000A2CC0: clear bits in slot i's flags. */
void aab_SlotClearFlags(int i, uint32_t m) { AabSlot *s = &aab_slots[i]; if (s) s->flags &= ~m; }

/* 0x000A2CE0: nonzero when any of the bits are set in slot i's flags. */
int aab_SlotTestFlags(int i, uint32_t m)
{
    AabSlot *s = &aab_slots[i];
    if (!s) return 0;
    return (s->flags & m) != 0;
}

/* 0x000A2D10: OR bits into the attached actor's +0x0C flags. */
void aab_ActorSetFlagsC(int i, uint32_t m) { AabActor *o = aab_slots[i].obj120; if (o) o->flags0C |= m; }

/* 0x000A2D40: clear bits in the attached actor's +0x0C flags. */
void aab_ActorClearFlagsC(int i, uint32_t m) { AabActor *o = aab_slots[i].obj120; if (o) o->flags0C &= ~m; }

/* 0x000A2D70: OR bits into the attached actor's +0x10 flags. */
void aab_ActorSetFlags10(int i, uint32_t m) { AabActor *o = aab_slots[i].obj120; if (o) o->flags10 |= m; }

/* 0x000A2DA0: clear bits in the attached actor's +0x10 flags. */
void aab_ActorClearFlags10(int i, uint32_t m) { AabActor *o = aab_slots[i].obj120; if (o) o->flags10 &= ~m; }

/* 0x000A2DD0: create handle k (via 0x00036750) if not present. */
void aab_SlotAttach(int i, int a, int k)
{
    AabSlot *s = &aab_slots[i];
    if (!s->h14C[k]) s->h14C[k] = aab_Attach36750(s->obj120, a);
}

/* 0x000A2E10: free handle k with 0x00033A40. */
void aab_SlotFreeA(int i, int k)
{
    AabSlot *s = &aab_slots[i];
    if (s->h14C[k]) { aab_Free33A40(s->h14C[k]); s->h14C[k] = 0; }
}

/* 0x000A2E50: free handle k with 0x00033A70. */
void aab_SlotFreeB(int i, int k)
{
    AabSlot *s = &aab_slots[i];
    if (s->h14C[k]) { aab_Free33A70(s->h14C[k]); s->h14C[k] = 0; }
}

/* 0x000A2E90: combine the actor position with b and pass the result on. */
void aab_SlotPosOp(AabSlot *s, const void *b)
{
    float v[4];
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    aab_Vec1AD9F0(v, s->obj120->vec60, b);
    aab_Use82D70(v);
}

/* 0x000A2EF0: same, between two actors' positions. */
void aab_ActorPosOp(AabSlot *s, AabActor *b)
{
    float v[4];
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    aab_Vec1AD9F0(v, s->obj120->vec60, b->vec60);
    aab_Use82D70(v);
}

/* 0x000A3480: set float k (0..3) of slot i. */
void aab_SlotSetF(int i, float v, unsigned k)
{
    AabSlot *s = &aab_slots[i];
    if (s && k <= 3) s->f100[k] = v;
}

/* 0x000A34B0: set int k (0..3) of slot i. */
void aab_SlotSetI(int i, int v, unsigned k)
{
    AabSlot *s = &aab_slots[i];
    if (s && k <= 3) s->i110[k] = v;
}

/* 0x000A34E0: float k of slot i, -1 when out of range. */
float aab_SlotGetF(int i, unsigned k)
{
    AabSlot *s = &aab_slots[i];
    if (!s || k > 3) return -1.0f;
    return s->f100[k];
}

/* 0x000A3510: int k of slot i, -1 when out of range. */
int aab_SlotGetI(int i, unsigned k)
{
    AabSlot *s = &aab_slots[i];
    if (!s || k > 3) return -1;
    return s->i110[k];
}

/* 0x000A3540: zero +0x54 and set +0x58 of the slot's linked 0x134 record. */
void aab_SlotSetRecPair(int i, float v)
{
    AabRec134 *r = &aab_rec134[aab_slots[i].i110[0]];
    r->f54 = 0.0f;
    r->f58 = v;
}

/* 0x000A3570: run 0x000A32A0 on the linked record and the actor position. */
void aab_SlotRecOp(int i, int a, int b)
{
    AabSlot *s = &aab_slots[i];
    aab_Rec32A0(&aab_rec134[s->i110[0]], s->obj120->vec60, a, b);
}

/* 0x000A3620: forward the attached actor to 0x0001F070. */
void aab_SlotActor1F070(int i)
{
    AabSlot *s = &aab_slots[i];
    if (s && s->obj120) aab_Actor1F070(s->obj120);
}

/* 0x000A3650: show or hide the attached actor. */
void aab_SlotShow(int i, int on)
{
    AabActor *o = aab_slots[i].obj120;
    if (o) {
        if (!on) aab_Hide1B3F0(o);
        else aab_Show1B3A0(o);
    }
}

/* 0x000A3740: release handle k (-1 = none). */
void aab_SlotRelease(int i, int k)
{
    AabSlot *s = &aab_slots[i];
    if (s->h154[k] != -1) { aab_Release48250(s->h154[k]); s->h154[k] = -1; }
}

/* 0x000A4010: start an animation on the slot's actor. */
void aab_SlotPlayAnim(AabSlot *s, int anim)
{
    AabActor *o = s->obj120;
    if (o) {
        aab_SetAnim832D0(o->anim30, anim);
        aab_Model1D7F0(o->model3C, anim, 0);
        o->anim30->cur08 = -1;
        s->anim48 = anim;
    }
}

/* 0x000A4180: nonzero when the actor's animation has finished. */
int aab_SlotAnimDone(AabSlot *s)
{
    AabActor *o = s->obj120;
    AabAnimCtl *c = o->anim30->ctl14;
    if (c->busyC8 == 0 && (aab_Ctl1AEE50(c, 0) & 2) && !(o->anim30->ctl14->flagsBC & 2))
        return 1;
    return 0;
}

/* 0x000A41F0: set the actor's +0x60 vector when the slot is active. */
void aab_SlotSetPos(int i, const float *v)
{
    AabSlot *s = &aab_slots[i];
    if ((s->flags & 1) && s->obj120) aab_Vec4Copy(s->obj120->vec60, v);
}

/* 0x000A4220: set the actor's +0x50 vector when the slot is active. */
void aab_SlotSetVec50(int i, const float *v)
{
    AabSlot *s = &aab_slots[i];
    if ((s->flags & 1) && s->obj120) aab_Vec4Copy(s->obj120->vec50, v);
}

/* 0x000A4250: copy slot i's +0x70 vector out. */
void aab_SlotGetVec70(int i, float *out) { aab_Vec4Copy(out, aab_slots[i].vec70); }

/* 0x000A4270: copy slot i's +0x80 vector out. */
void aab_SlotGetVec80(int i, float *out) { aab_Vec4Copy(out, aab_slots[i].vec80); }

/* 0x000A42C0: the slot holding actor o, or NULL. */
AabSlot *aab_FindSlotByActor(AabActor *o)
{
    AabSlot *s;
    for (s = aab_slots; s < aab_slots + 32; s++)
        if (s->obj120 == o) return s;
    return 0;
}

/* 0x000A42F0: start an animation on slot i's actor. */
void aab_SlotPlayAnimI(int i, int anim) { aab_SlotPlayAnim(&aab_slots[i], anim); }

/* 0x000A4340: call 0x000A4050 on slot i with (a, 0, 0). */
void aab_SlotA4050I(int i, int a) { aab_SlotA4050(&aab_slots[i], a, 0, 0); }

/* 0x000A4370: nonzero when slot i's animation has finished. */
int aab_SlotAnimDoneI(int i) { return aab_SlotAnimDone(&aab_slots[i]); }

/* 0x000A43C0: change slot i's state, resetting its timer on change. */
void aab_SlotSetState(int i, int st)
{
    AabSlot *s = &aab_slots[i];
    if (s->state != st) { s->state = st; s->timer = 0; }
}

/* 0x000A43F0: nonzero when slot i's state is -1. */
int aab_SlotStateNone(int i) { return aab_slots[i].state == -1; }

/* 0x000A44C0: index of slot s, or -1. */
int aab_SlotIndex(AabSlot *s)
{
    int i;
    for (i = 0; i < 32; i++)
        if (&aab_slots[i] == s) return i;
    return -1;
}

/* 0x000A4950: call 0x000A4870 on slot i. */
void aab_SlotA4870I(int i) { aab_SlotA4870(&aab_slots[i]); }

/* 0x000A5440: call 0x000A4DE0 when the slot is active. */
void aab_SlotA4DE0IfActive(AabSlot *s) { if (s->flags & 1) aab_SlotA4DE0(s); }

/* 0x000A5450: same, by index. */
void aab_SlotA4DE0IfActiveI(int i)
{
    AabSlot *s = &aab_slots[i];
    if (s->flags & 1) aab_SlotA4DE0(s);
}

/* 0x000A4410: hide or show slot i's actor and clear its done bit. */
void aab_SlotSetVisible(int i, int on)
{
    AabSlot *s = &aab_slots[i];
    if (!on) { aab_Hide1D700(s->obj120); s->flags |= 0x20000000; }
    else { aab_Show1D610(s->obj120); s->flags &= ~0x20000000; }
    s->flags &= ~0x40000000;
}

/* 0x000A44F0: hide or show every active slot with the given id. */
void aab_SlotSetVisibleById(int id, int on)
{
    AabSlot *s;
    for (s = aab_slots; s < aab_slots + 32; s++) {
        if ((s->flags & 1) && s->id == id) {
            if (!on) { aab_Hide1D700(s->obj120); s->flags |= 0x20000000; }
            else { aab_Show1D610(s->obj120); s->flags &= ~0x20000000; }
            s->flags &= ~0x40000000;
        }
    }
}

/* 0x000A4610: free both 0x00033A40 handles of every active slot with the given id. */
void aab_SlotFreeAllById(int id)
{
    AabSlot *s;
    int k;
    for (s = aab_slots; s < aab_slots + 32; s++) {
        if ((s->flags & 1) && s->id == id) {
            for (k = 0; k < 2; k++)
                if (s->h14C[k]) { aab_Free33A40(s->h14C[k]); s->h14C[k] = 0; }
        }
    }
}
