/* Effect path building and the streamed sound channel (0x00053140-0x000541A5),
 * second pass. Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include <string.h>
#include "a5b.h"

/* 0x00053140: build a demo effect (.efa) path for `kind` (0x12 = "bg",
 * 10 = hex number) into `dst`. */
void a5b_BuildDemoEfaPath(char *dst, int kind, int num)
{
    char name[4];
    int demo = sub_0008CDA0(sub_0008CD60());
    if (kind == 0x12)
        memcpy(name, a5b_strBg, 3);
    else if (kind == 10)
        a6b_Printf3(name, 3, a5b_strHex2, kind);
    else
        for (;;) ;
    a6b_Printf3(dst, 0xFF, a5b_strDemoEfa, demo, demo, demo, name, num);
}

/* 0x00053F20: start channel `ch` (or restart the current one). */
void a5b_SndStart(int ch)
{
    if (a5b_sndChannel < 0)
        a5b_sndChannel = ch;
    else if (a5b_sndChannel != ch)
        return;
    a5b_sndCount = 0;
    a5b_sndLevel = 0;
    sub_000771E0(a5b_sndChannel, 2, 0);
    sub_001A8650();
}

/* 0x00053FD0: channel callback; counts wraps of the matching voice. */
int a5b_SndCallback(int id)
{
    int ch = a5b_sndChannel;
    int want = -1;
    switch (ch) {
    case 0: want = 9; break;
    case 1: want = 10; break;
    }
    if (id == want) {
        a5b_sndCount++;
        a60_ChannelSetC00(ch);
    }
    return 0;
}

/* 0x00054010: begin playback on the current channel. */
void a5b_SndBegin(void)
{
    sub_001A8720();
    a60_ChannelStart(a5b_sndChannel, a5b_SndCallback);
    sub_000773A0(a5b_sndChannel, 0);
}

/* 0x00054040: pause the current channel. */
int a5b_SndPause(void)
{
    int r = sub_001A8680();
    a60_ChannelLevel(a5b_sndChannel);
    a60_ChannelStop(a5b_sndChannel);
    sub_001A8760();
    return r;
}

/* 0x00054070: stop and release the current channel. */
void a5b_SndRelease(void)
{
    sub_001A8650();
    sub_001A8680();
    a60_ChannelLevel(a5b_sndChannel);
    a60_ChannelStop(a5b_sndChannel);
    sub_001A8760();
    a5b_sndChannel = -1;
    a5b_sndCount = 0;
    a5b_sndLevel = 0;
}

/* 0x00054160: setter for 0x003E3944. */
void a5b_Set3E3944(int v) { a5b_g3E3944 = v; }

/* 0x00054170: setter for 0x003E393C. */
void a5b_Set3E393C(int v) { a5b_g3E393C = v; }

/* 0x00054180: getter for 0x003E3910. */
int a5b_Get3E3910(void) { return a5b_g3E3910; }

/* 0x00054190: getter for 0x003E3F4C. */
int a5b_Get3E3F4C(void) { return a5b_g3E3F4C; }

/* 0x000541A0: getter for 0x003E3F48. */
int a5b_Get3E3F48(void) { return a5b_g3E3F48; }
