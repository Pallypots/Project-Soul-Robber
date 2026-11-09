/* Area a4c, group 1: block helpers and sound-slot wrappers 0x000470C0..0x00048B20. Names inferred. */
#include "a4c.h"

/* 0x000470C0: size of a memory block, rounded up to 64 bytes when in use. */
int a4c_BlockSize(A4cBlock *b)
{
    if (b == 0) return 0;
    if (b->used) return ((int)(b->end - (uint8_t *)b) + 0x3F) & ~0x3F;
    return b->size;
}
/* 0x00047920: finish a pending operation; 1 when nothing is pending. */
int a4c_PollPending(void)
{
    if (a4c_g3DFFF8 && sub_00057E90()) { sub_0019AE90(); return 0; }
    a4c_g3DFFF8 = 0;
    return 1;
}
/* 0x000479F0: true when none of channels 3,4,9,5,6,8 is busy. */
int a4c_AllChannelsIdle(void)
{
    if (sub_0019A040(3) || sub_0019A040(4) || sub_0019A040(9) ||
        sub_0019A040(5) || sub_0019A040(6)) return 0;
    return sub_0019A040(8) == 0;
}
/* 0x00047A50: select mode 5 for 0, 6 for 1, otherwise the value itself. */
int a4c_SelectMode(int a, int b, int mode)
{
    if (mode == 0) return sub_0019A180(5);
    if (mode == 1) mode = 6;
    return sub_0019A180(mode);
}
/* 0x00047BB0: query the current stream through the API matching its kind. */
int a4c_StreamQueryA(void)
{
    if (a30_g3DFECC < 0) return -1;
    if (a30_g3DFEC0 < 2) return sub_00199880(a30_g3DFECC);
    if (a30_g3DFEC0 < 3) return sub_0019A810(a30_g3DFECC);
    return sub_0019A930(a30_g3DFECC);
}
/* 0x00047BF0: reset requests and stop the current stream. */
void a4c_StreamStop(int a)
{
    a30_g3DFEC4 = a4c_g3DFEC8 = -1;
    if (a30_g3DFECC < 0) return;
    if (a30_g3DFEC0 < 2) sub_00199A40(a30_g3DFECC, a);
    else if (a30_g3DFEC0 < 3) sub_0019A8B0(a30_g3DFECC, a);
    else sub_0019AA00(a30_g3DFECC, a);
}
/* 0x00047C50: pause the current stream. */
void a4c_StreamPause(void)
{
    if (a30_g3DFECC < 0) return;
    if (a30_g3DFEC0 < 2) sub_00199980(a30_g3DFECC, 0);
    else if (a30_g3DFEC0 >= 3) sub_0019AB40(a30_g3DFECC);
}
/* 0x00047EE0: stream status through the API matching its kind. */
int a4c_StreamStatus(void)
{
    if (a30_g3DFECC < 0) return -1;
    if (a30_g3DFEC0 < 2) return sub_00199850(a30_g3DFECC);
    if (a30_g3DFEC0 < 3) return sub_0019A7E0(a30_g3DFECC);
    return sub_0019A900(a30_g3DFECC);
}
/* 0x00047F60: true when the current stream has finished. */
int a4c_StreamFinished(void)
{
    if (a30_g3DFECC >= 0) {
        if (a30_g3DFEC0 < 2) {
            int r = sub_00199850(a30_g3DFECC);
            if (r > 0 && r != 2) return 0;
        } else if (a30_g3DFEC0 < 3) {
            if (sub_0019A7E0(a30_g3DFECC) > 0) return 0;
        } else if (sub_0019A900(a30_g3DFECC) > 0) return 0;
    }
    return 1;
}
/* 0x00048110: set a value on channels 1,2,3,4,9,5,6,10. */
void a4c_SetAllChannelsA(int v)
{
    sub_0019A5A0(1, v); sub_0019A5A0(2, v); sub_0019A5A0(3, v); sub_0019A5A0(4, v);
    sub_0019A5A0(9, v); sub_0019A5A0(5, v); sub_0019A5A0(6, v); sub_0019A5A0(10, v);
}
/* 0x00048160: same as above without channel 5. */
void a4c_SetChannelsNo5A(int v)
{
    sub_0019A5A0(1, v); sub_0019A5A0(2, v); sub_0019A5A0(3, v); sub_0019A5A0(4, v);
    sub_0019A5A0(9, v); sub_0019A5A0(6, v); sub_0019A5A0(10, v);
}
/* 0x000481B0: set a second value on channels 1,2,3,4,9,5,6,10. */
void a4c_SetAllChannelsB(int v)
{
    sub_0019A640(1, v); sub_0019A640(2, v); sub_0019A640(3, v); sub_0019A640(4, v);
    sub_0019A640(9, v); sub_0019A640(5, v); sub_0019A640(6, v); sub_0019A640(10, v);
}
/* 0x00048200: same as above without channel 5. */
void a4c_SetChannelsNo5B(int v)
{
    sub_0019A640(1, v); sub_0019A640(2, v); sub_0019A640(3, v); sub_0019A640(4, v);
    sub_0019A640(9, v); sub_0019A640(6, v); sub_0019A640(10, v);
}
/* 0x00048270: reset channels 1,2,3,4,9,5,6,8. */
void a4c_ResetChannels(void)
{
    sub_0019A6A0(1); sub_0019A6A0(2); sub_0019A6A0(3); sub_0019A6A0(4);
    sub_0019A6A0(9); sub_0019A6A0(5); sub_0019A6A0(6); sub_0019A6A0(8);
}
/* 0x000482C0: apply every parameter of a sound (ids 0x30..0x214) to its playback handle. */
void a4c_SoundApplyParams(int i)
{
    A4cSoundSlot *s = &a4c_soundSlots[i];
    if (s->id >= 0x30 && s->id < 0x215) {
        int n = sub_0019ADE0(s->id), j;
        for (j = 0; j < n; j++)
            sub_0019AC20(s->handle, j, sub_0019AD10(s->id, j));
    }
}
/* 0x00048330: stop a sound slot and free it. */
void a4c_SoundFree(int i, int a)
{
    if (a4c_soundSlots[i].handle >= 0) sub_0019AA00(a4c_soundSlots[i].handle, a);
    a4c_soundSlots[i].id = -1;
    a4c_soundSlots[i].handle = -1;
}
/* 0x00048370: pause every active sound slot. */
void a4c_SoundPauseAll(void)
{
    int i;
    for (i = 0; i < A4C_SOUND_SLOTS; i++)
        if (a4c_soundSlots[i].handle >= 0) sub_0019AB40(a4c_soundSlots[i].handle);
}
/* 0x000483A0: set a value on every active sound slot. */
void a4c_SoundSetAll(int v)
{
    int i;
    for (i = 0; i < A4C_SOUND_SLOTS; i++)
        if (a4c_soundSlots[i].handle >= 0) sub_0019B800(a4c_soundSlots[i].handle, v);
}
/* 0x00048A60: pause the stream if it is the requested one, else remember the request. */
void a4c_StreamPauseIfCurrent(void)
{
    if (a30_g3DFEC0 == a30_g3DFEC4) {
        if (a30_g3DFECC < 0) return;
        if (a30_g3DFEC0 < 2) sub_00199980(a30_g3DFECC, 0);
        else if (a30_g3DFEC0 >= 3) sub_0019AB40(a30_g3DFECC);
    } else {
        a4c_g3DFEC8 = a30_g3DFEC4;
    }
}
/* 0x00048AF0: start sound i with default parameters. */
void a4c_SoundStartDefault(int i)
{
    sub_0019B690(i, sub_0019A480(i), 0x5A, 0x80, 0x80, 0x80);
}
