/* Area r6d: cutscene audio hand-over sequences around 0x000882F0-0x00088ED2 (r6d_19). Names inferred.
   "In" sequences pause the music tracks and start the cutscene voice; "Out" sequences
   resume the tracks and stop it. Every wait is a busy loop on the sound driver. */
#include "r6d.h"

/* Start voice v and wait until it reports state 2. */
static void r6d_VoiceStart(int v)
{
    sub_00047A80(v);
    while (sub_00047B10(v) != 2)
        ;
}

/* Release voice v and wait until it is idle. */
static void r6d_VoiceRelease(int v)
{
    sub_00047B30(v);
    while (sub_00047B50(v))
        ;
}

/* Stop voice v and wait until it is idle. */
static void r6d_VoiceStop(int v)
{
    sub_00047B70(v);
    while (sub_00047B90(v))
        ;
}

/* Send key (a, b, 1) through the three-step handshake. */
static void r6d_KeySend(int a, int b)
{
    sub_000487F0(a, b, 1);
    while (sub_00048820(a, b, 1) != 2)
        ;
    sub_00048860(a, b, 1);
    while (sub_00048890(a, b, 1))
        ;
}

/* 0x000882F0: cutscene audio in, layout A (voice 0x0E). */
void r6d_CsAudioInA(void)
{
    int a = a30_g41316C;
    int b = a30_g413170;
    sub_00053710(4);
    sub_000ED4C0(2);
    sub_000ED4C0(5);
    while (sub_000ED520(2, 0x0B))
        ;
    while (sub_000ED520(2, 0))
        ;
    while (sub_000ED520(2, 0x0E))
        ;
    sub_000ED590(2, 0x0B);
    sub_000ED590(5, 0x20);
    sub_000ED590(2, 0);
    sub_000ED590(2, 0x0E);
    sub_000ED5D0(2);
    sub_000ED5D0(5);
    sub_000488C0(a, b, 1);
    r6d_VoiceStart(0x0E);
    r6d_VoiceStart(5);
    r6d_VoiceRelease(0x0E);
    r6d_VoiceRelease(5);
    sub_00053740();
}

/* 0x00088490: cutscene audio out, layout A. */
void r6d_CsAudioOutA(void)
{
    int a = a30_g41316C;
    int b = a30_g413170;
    sub_00033BF0(2, -1);
    sub_00033BF0(5, -1);
    while (!sub_000EE240())
        ;
    sub_000ED600(2);
    sub_000ED600(5);
    sub_000ED560(2);
    sub_000ED4F0(2);
    sub_000ED4F0(5);
    r6d_VoiceStop(0x0E);
    r6d_VoiceStop(5);
    r6d_KeySend(a, b);
}

/* 0x00088560: cutscene audio in, layout B (voices 0x0F and 9). */
void r6d_CsAudioInB(void)
{
    int a = a30_g41316C;
    int b = a30_g413170;
    sub_00053710(4);
    sub_000ED4C0(2);
    while (sub_000ED520(2, 0x0C))
        ;
    while (sub_000ED520(2, 5))
        ;
    while (sub_000ED520(2, 0x0F))
        ;
    sub_000ED590(2, 0x0C);
    sub_000ED590(2, 5);
    sub_000ED590(2, 0x0F);
    sub_000ED5D0(2);
    sub_000488C0(a, b, 1);
    r6d_VoiceStart(0x0F);
    r6d_VoiceStart(9);
    r6d_VoiceRelease(0x0F);
    r6d_VoiceRelease(9);
    sub_00053740();
}

/* 0x00088650: cutscene audio out, layout B. */
void r6d_CsAudioOutB(void)
{
    int a = a30_g41316C;
    int b = a30_g413170;
    sub_00033BF0(2, -1);
    while (!sub_000EE240())
        ;
    sub_000ED600(2);
    sub_000ED560(2);
    sub_000ED4F0(2);
    r6d_VoiceStop(0x0F);
    r6d_VoiceStop(9);
    r6d_KeySend(a, b);
}

/* 0x000888C0: cutscene audio in, layout C (voice 0x10). */
void r6d_CsAudioInC(void)
{
    int a = a30_g41316C;
    int b = a30_g413170;
    sub_00053710(4);
    sub_000ED4C0(2);
    sub_000ED4C0(5);
    while (sub_000ED520(2, 0x0D))
        ;
    while (sub_000ED520(2, 1))
        ;
    sub_000ED590(2, 0x0D);
    sub_000ED590(5, 0x21);
    sub_000ED590(2, 1);
    sub_000ED590(5, 0);
    sub_000ED5D0(2);
    sub_000ED5D0(5);
    sub_000488C0(a, b, 1);
    r6d_VoiceStart(0x10);
    r6d_VoiceStart(5);
    r6d_VoiceRelease(0x10);
    r6d_VoiceRelease(5);
    sub_00053740();
}

/* 0x000889C0: cutscene audio out, layout C. */
void r6d_CsAudioOutC(void)
{
    int a = a30_g41316C;
    int b = a30_g413170;
    sub_00033BF0(2, -1);
    sub_00033BF0(5, -1);
    while (!sub_000EE240())
        ;
    sub_000ED600(2);
    sub_000ED600(5);
    sub_000ED560(2);
    sub_000ED4F0(2);
    sub_000ED4F0(5);
    r6d_VoiceStop(0x10);
    r6d_VoiceStop(5);
    r6d_KeySend(a, b);
}

/* 0x00088A90: cutscene event A: play cue 0x0D on track 2 until flag 4, then end. */
void r6d_CsEventA(R6dCsEvent *e)
{
    R6dCsData *d;
    if (!(e->flags & 1))
        return;
    switch (e->state) {
    case 0:
        sub_000D2A50(&g_stats, 1);
        sub_000DE330(1);
        d = *e->data;
        sub_000ED630(2, 0x0D, d->a, d->a10, d->a20);
        e->state = 10;
    case 10:
        if (e->flags & 4)
            e->state = 20;
        break;
    case 20:
        sub_000D2A50(&g_stats, 0);
        sub_000DE330(0);
        e->flags = (e->flags & ~5) | 2;
        e->state = 0;
        break;
    }
}

/* 0x00088B20: send the stage key through the two-argument handshake. */
void r6d_CsKeyWait(void)
{
    int a;
    int b;
    sub_00053710(4);
    b = a30_g413170;
    a = a30_g41316C;
    sub_000488F0(a, b);
    while (sub_00048910(a, b) != 2)
        ;
    sub_00048940(a, b);
    while (sub_00048970(a, b))
        ;
    sub_00053740();
}

/* 0x00088C30: cutscene event B: cue chosen by stage (5 or 0x0B) on track 3. */
void r6d_CsEventB(R6dCsEvent *e)
{
    R6dCsData *d;
    if (!(e->flags & 1))
        return;
    switch (e->state) {
    case 0:
        sub_000D2A50(&g_stats, 1);
        sub_000DE330(1);
        d = *e->data;
        if (a30_g41316C == 5)
            sub_000ED630(3, 0x0F, d->a, d->a10, d->a20);
        else if (a30_g41316C == 0x0B)
            sub_000ED630(3, 0x0E, d->b24, d->b34, d->b44);
        e->state = 10;
    case 10:
        if (e->flags & 4)
            e->state = 20;
        break;
    case 20:
        sub_000D2A50(&g_stats, 0);
        sub_000DE330(0);
        e->flags = (e->flags & ~5) | 2;
        e->state = 0;
        break;
    }
}

/* 0x00088CF0: cutscene audio in, layout D (voice 8). */
void r6d_CsAudioInD(void)
{
    sub_00053710(4);
    sub_000ED4C0(2);
    sub_000ED4C0(5);
    while (sub_000ED520(2, 3))
        ;
    while (sub_000ED520(2, 4))
        ;
    sub_000ED590(2, 3);
    sub_000ED590(5, 2);
    sub_000ED590(2, 4);
    sub_000ED590(5, 3);
    sub_000ED5D0(2);
    sub_000ED5D0(5);
    r6d_VoiceStart(8);
    r6d_VoiceRelease(8);
    sub_00053740();
}

/* 0x00088DB0: cutscene audio out, layout D. */
void r6d_CsAudioOutD(void)
{
    sub_00033BF0(2, -1);
    sub_00033BF0(5, -1);
    while (!sub_000EE240())
        ;
    sub_000ED600(2);
    sub_000ED600(5);
    sub_000ED560(2);
    sub_000ED4F0(2);
    sub_000ED4F0(5);
    r6d_VoiceStop(8);
}

/* 0x00088E10: cutscene event C: cues 3 and 4 on track 2, end when tracks 2 and 5 are done. */
void r6d_CsEventC(R6dCsEvent *e)
{
    R6dCsData *d;
    if (!(e->flags & 1))
        return;
    switch (e->state) {
    case 0:
        sub_000D2A50(&g_stats, 1);
        sub_000DE330(1);
        d = *e->data;
        sub_000ED630(2, 3, d->a, d->a10, d->a20);
        sub_000ED630(2, 4, d->b24, d->b34, d->b44);
        e->state = 10;
    case 10:
        if (sub_000EDAD0(2, -1) <= 0 && sub_000EDAD0(5, -1) <= 0)
            e->state = 20;
        break;
    case 20:
        sub_000D2A50(&g_stats, 0);
        sub_000DE330(0);
        e->flags = (e->flags & ~1) | 2;
        e->state = 0;
        break;
    }
}
