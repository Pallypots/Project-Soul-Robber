/* Area aac, group 3: string tidy, peer record queries, thread table and vector helpers (0x1ACDF0-0x1AF640). Names inferred. */
#include "aac.h"

/* 0x001ACDF0: thiscall; release a short-string buffer and reset to empty. */
void __fastcall aac_StrTidy(AacStr *s)
{
    if (s->cap >= 16)
        sub_001C885F(s->u.ptr);
    s->cap = 15;
    s->size = 0;
    s->u.buf[0] = 0;
}

/* 0x001ACF00: thiscall; peer state is 3. */
int __fastcall aac_PeerIsState3(AacPeer *p) { return p->state == 3; }
/* 0x001ACF10: thiscall; peer state is non-zero. */
int __fastcall aac_PeerHasState(AacPeer *p) { return p->state != 0; }
/* 0x001ACF20: thiscall; peer value at +0xB0. */
int __fastcall aac_PeerValue(AacPeer *p) { return p->value; }

/* 0x001AD3A0: true unless the calling thread has an entry whose state is not 3. */
int aac_ThreadDoneOrMissing(void)
{
    int tid = sub_001BD50A();
    AacThreadRec *r;
    for (r = aac_g40EDD8; r != aac_g40EDD8 + 32; r++) {
        if (r->id == tid)
            return r->state == 3;
    }
    return 1;
}

/* 0x001AD4F0: resume the thread entry with this id; returns the id. */
int aac_ResumeThread(int id)
{
    AacThreadRec *r;
    for (r = aac_g40EDD8; r != aac_g40EDD8 + 32; r++) {
        if (r->id == id)
            break;
    }
    if (r == aac_g40EDD8 + 32)
        r = 0;
    sub_001BD2B6(r->handle);
    return id;
}

/* 0x001AD6B0: suspend every other thread in the table. */
void aac_SuspendOthers(void)
{
    int tid = sub_001BD50A();
    AacThreadRec *r;
    for (r = aac_g40EDD8; r != aac_g40EDD8 + 32; r++) {
        if (r->handle && r->id != tid)
            sub_001BD290(r->handle);
    }
}

/* 0x001AD6E0: run 0x1AD520 unless the calling thread has an entry whose state is not 3. */
void aac_CheckThread(void)
{
    int tid = sub_001BD50A();
    AacThreadRec *r;
    for (r = aac_g40EDD8; r != aac_g40EDD8 + 32; r++) {
        if (r->id == tid) {
            if (r->state == 3)
                sub_001AD520();
            return;
        }
    }
    sub_001AD520();
}

/* 0x001AD7C0: library call forwarder with the last two arguments swapped. */
void aac_Call_1AD7C0(void *a, const void *b, const void *c) { sub_001E522D(a, c, b); }

/* 0x001AD8B0: build a 64-byte block with 0x1E4C33 from c, then pass it to 0x1E522D. */
void aac_Build1_1AD8B0(void *a, const void *b, float c)
{
    uint8_t m[0x40];
    sub_001E4C33(m, c);
    sub_001E522D(a, b, m);
}
/* 0x001AD8E0: build a 64-byte block with 0x1E4CAD from c, then pass it to 0x1E522D. */
void aac_Build2_1AD8E0(void *a, const void *b, float c)
{
    uint8_t m[0x40];
    sub_001E4CAD(m, c);
    sub_001E522D(a, b, m);
}
/* 0x001AD910: build a 64-byte block with 0x1E4D28 from c, then pass it to 0x1E522D. */
void aac_Build3_1AD910(void *a, const void *b, float c)
{
    uint8_t m[0x40];
    sub_001E4D28(m, c);
    sub_001E522D(a, b, m);
}

/* 0x001AD9A0: library call forwarder. */
void aac_Call_1AD9A0(void *a, const void *b) { sub_001E4BC6(a, b); }
/* 0x001AD9B0: library call forwarder with the last two arguments swapped. */
void *aac_Call_1AD9B0(void *out, const void *m, const void *v) { return sub_001E4B2D(out, v, m); }

/* 0x001AD9D0: dot product of two 3-vectors. */
float aac_Dot3(const AacVec3 *a, const AacVec3 *b)
{
    return a->z * b->z + a->y * b->y + a->x * b->x;
}

/* 0x001ADB40: copy a 3-vector. */
void aac_Copy3(AacVec3 *d, const AacVec3 *s)
{
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
}

/* 0x001ADB60: scale a 3-vector. */
void aac_Scale3(AacVec3 *d, const AacVec3 *s, float k)
{
    d->x = s->x * k;
    d->y = s->y * k;
    d->z = s->z * k;
}

/* 0x001AE8C0: address of chunk i from the header's offset table at +0x20 (-1 = none). */
uint8_t *aac_ChunkAt(uint8_t *base, int i)
{
    if (i == -1)
        return 0;
    return base + ((int32_t *)(base + 0x20))[i];
}

/* 0x001AE950: header is an 'EDGE' block of version 1. */
int aac_IsEdgeV1(const uint8_t *p)
{
    if (*(const uint32_t *)p != 0x45444745)
        return 0;
    return *(const uint16_t *)(p + 4) == 1;
}

/* 0x001AEDD0: set float at +0xC4. */
void aac_SetC4(uint8_t *o, float v) { *(float *)(o + 0xC4) = v; }

/* 0x001AF3B0: run 0xF5D40 with block 0x40F130. */
void aac_Apply40F130(float *a) { a19_VecOp(a, aac_g40F130); }
/* 0x001AF3D0: run 0xF5D40 with block 0x40F140. */
void aac_Apply40F140(float *a) { a19_VecOp(a, aac_g40F140); }

/* 0x001AF640: run 0x1AEBF0(a, b, 0). */
void aac_Run_1AF640(void *a, void *b) { sub_001AEBF0(a, b, 0); }
