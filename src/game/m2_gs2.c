/* Area m2, file gs2: security-cookie functions (compiled with /GS). Names inferred. */
#include <stdint.h>

typedef struct M2Spr2 { uint8_t unk00[0x24]; uint32_t flags24; uint8_t unk28[0x1C]; void *h44; uint8_t unk48[0x54]; } M2Spr2;
typedef struct M2Hud2 { uint8_t unk00[0x968]; uint8_t layout968[0x20]; void *res988; } M2Hud2;
extern int a1b_i3816D0;
extern M2Hud2 *r1_hud;
extern uint32_t m1_wipe381400[0xB1];
extern const char *m2_names2826FC[2];
extern void *m2_h3813E8[2];
extern void *r1b_handles3813F4[2];
extern const char *m2_name282710;
extern void *m2_bank3816C8;
extern M2Spr2 m2_spr381454[4];
extern const char *m2_fmt282714;
extern int r1b_v3816CC;
extern int r1_curHudId;
void  m1_SndBank0243B0(int a, int b);
void  sub_000252A0(int a, int b);
void  aab_Add24D30(int a, int b);
void  r1g_CounterRequest(int a, int b);
void  sub_000253D0(int a, int b);
int   a5b_GetVideoMode(void);
int   m1_FileBusy04F6D0(int id);
int   m1_FileSize04F680(int id);
void *a50_Alloc(int heap, int size, int a, int b);
void  r1e_MovieStartA(int id, void *mem);
int   sub_0004F4D0(void);
int   sub_00053CA0(int a);
void *m1_PathOp53D70(const char *name);
void *sub_00084C00(void *h, int a);
void  r1d_AnimBankFixup(void *bank);
void  r1e_SpriteInit(M2Spr2 *s, void *bank, void *h);
void  r1b_StepperSet(M2Spr2 *s, int a, int b, int c, int d);
int   sub_00038070(int a);
void  m1_Stub102FA0();
void  sub_00075F00(M2Hud2 *h);
void  sub_0003FAB0(void *layout, M2Hud2 *h);
const char *a50_GetVideoModeName(void);
int   a6b_Printf3(char *buf, int size, const char *fmt, ...);
void *a50_Sub53D50(const char *path, int a);
void  r1b_ApplyLayout(void *layout, int a);
void  r1_HudSelect(void);
void  sub_00023BC0(int a);
void  sub_000325A0(int a);

/* 0x2CC20: HUD start-up step: 0 resets the sound banks and counters, 2 starts the intro movie for the video mode, 3 waits for loading, 100 allocates the HUD and clears the wipe table, 101 (when ready) loads the HUD sprite banks and layout, builds the four HUD sprites and selects the HUD (state 10000). Returns 1 until finished. Security-cookie function. */
int m2_HudStartup2CC20(void) {
    char path[0x80];
    int i, k;
    switch (a1b_i3816D0) {
    case 0:
        m1_SndBank0243B0(0, 0);
        m1_SndBank0243B0(0, 0);
        sub_000252A0(0, 0);
        aab_Add24D30(0, 0);
        r1g_CounterRequest(0, 0);
        sub_000253D0(0, 0);
        a1b_i3816D0 = 2;
        break;
    case 2:
        k = a5b_GetVideoMode() + 0xC3;
        if (m1_FileBusy04F6D0(k) == 0) r1e_MovieStartA(k, a50_Alloc(4, m1_FileSize04F680(k), 0, 0));
        a1b_i3816D0 = 3;
        break;
    case 3:
        if (sub_0004F4D0() == 0) a1b_i3816D0 = 100;
        break;
    case 100:
        r1_hud = (M2Hud2 *)a50_Alloc(4, 0x98C, 0, 0);
        for (i = 0; i < 0xB1; i++) m1_wipe381400[i] = 0;
        a1b_i3816D0 = 101;
    case 101:
        if (sub_00053CA0(1) != 0) break;
        for (i = 0; i < 2; i++) {
            m2_h3813E8[i] = m1_PathOp53D70(m2_names2826FC[i]);
            r1b_handles3813F4[i] = sub_00084C00(m2_h3813E8[i], 0);
        }
        m2_bank3816C8 = m1_PathOp53D70(m2_name282710);
        r1d_AnimBankFixup(m2_bank3816C8);
        r1e_SpriteInit(&m2_spr381454[0], m2_bank3816C8, r1b_handles3813F4[0]);
        m2_spr381454[0].h44 = r1b_handles3813F4[1];
        r1b_StepperSet(&m2_spr381454[0], 0, 0, 0, 0);
        m2_spr381454[1] = m2_spr381454[0];
        m2_spr381454[2] = m2_spr381454[0];
        m2_spr381454[3] = m2_spr381454[0];
        *(uint32_t volatile *)&m2_spr381454[1].flags24 |= 4;
        *(uint32_t volatile *)&m2_spr381454[2].flags24 |= 4;
        r1b_v3816CC = sub_00038070(1);
        m1_Stub102FA0();
        sub_00075F00(r1_hud);
        sub_0003FAB0(r1_hud->layout968, r1_hud);
        a6b_Printf3(path, 0x7F, m2_fmt282714, a50_GetVideoModeName(), a50_GetVideoModeName());
        r1_hud->res988 = a50_Sub53D50(path, 0);
        r1b_ApplyLayout(r1_hud->layout968, 0);
        r1_curHudId = -1;
        r1_HudSelect();
        sub_00023BC0(1);
        sub_000325A0(0);
        a1b_i3816D0 = 10000;
        break;
    }
    return a1b_i3816D0 != 10000;
}

typedef struct M2FSlot2 { int32_t rect0[4]; float f10[4]; int32_t kind20; void *tex24; int32_t i28; float f2C; int32_t i30, i34; uint8_t unk38[0x10]; } M2FSlot2;
extern uint8_t *r2d_ctx;
extern const char m2_fmtFilter26F568[];
extern const char r1b_fmtF[];
extern const char r1b_fmtD[];
char *r1b_NextToken(char **s);
int   r1b_sscanf(const char *s, const char *fmt, ...);
void *rtc_TexFindOrLoad(const char *path);
int   sub_000376D0(M2FSlot2 *s);

/* 0x7A610: script command: add a screen filter slot: texture name, value, two integers, a rectangle (four floats, stored whole), an integer and up to four optional colour floats; retries until the 10-entry list has room. Stops quietly when a required token is missing. Security-cookie function. */
void m2_CmdFilter7A610(char *s) {
    float r[4];
    M2FSlot2 sl;
    char path[0x100];
    char *t;
    if ((t = r1b_NextToken(&s)) == 0) return;
    a6b_Printf3(path, 0xFF, m2_fmtFilter26F568, *(int *)(r2d_ctx + 0x20C), *(int *)(r2d_ctx + 0x210), t);
    sl.tex24 = rtc_TexFindOrLoad(path);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &sl.f2C);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtD, &sl.i30);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtD, &sl.i34);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &r[3]);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &r[2]);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &r[0]);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtF, &r[1]);
    if ((t = r1b_NextToken(&s)) == 0) return;
    r1b_sscanf(t, r1b_fmtD, &sl.i28);
    if ((t = r1b_NextToken(&s)) != 0) r1b_sscanf(t, r1b_fmtF, &sl.f10[0]);
    if ((t = r1b_NextToken(&s)) != 0) r1b_sscanf(t, r1b_fmtF, &sl.f10[1]);
    if ((t = r1b_NextToken(&s)) != 0) r1b_sscanf(t, r1b_fmtF, &sl.f10[2]);
    if ((t = r1b_NextToken(&s)) != 0) r1b_sscanf(t, r1b_fmtF, &sl.f10[3]);
    sl.rect0[0] = (int)r[3];
    sl.rect0[1] = (int)r[2];
    sl.rect0[2] = (int)r[0];
    sl.rect0[3] = (int)r[1];
    sl.kind20 = 1;
    while (sub_000376D0(&sl) == -1) ;
}

#include <string.h>
#include <intrin.h>
typedef struct M2Str16 { uint32_t w[4]; } M2Str16;
#pragma pack(push, 1)
typedef struct M2Str5 { uint32_t w; uint8_t b; } M2Str5;
typedef struct M2Str4 { uint32_t w; } M2Str4;
#pragma pack(pop)
typedef struct M2Stream2 { int32_t busy0; const char *name4; uint8_t unk08[4]; int32_t rawC; int32_t size10; int32_t pos14; void *buf18; int32_t state1C; } M2Stream2;
extern int a50_streamState;
extern int r1e_mId3E0DBC;
extern M2Stream2 m1_streams2C8900[0x21E];
extern int a50_streamHandle;
extern void *r1e_mArg3E0DC4;
extern void *r1e_m3E0DC8;
extern M2Stream2 *a30_curSlot;
extern const M2Str16 m2_strStmDir26B83C;
extern const M2Str5 m2_strStm26B834;
int  sub_001A8210(const char *path, int mode);
void r4b_FileSeek(int fd, int pos, int whence);
int  r4b_FileReadPoll(int fd, int a, int *st);
void r4b_FileReadAsync(int fd, void *buf, int size);
void r4b_FileClose(int fd);
void *a5b_AllocCur(int size, int a, int tag);

/* 0x50C80: step the streamed-data loader for the current stream entry: open "host0:stm_data/<name>.stm" (entries already loaded return 0), get a buffer (the caller's or a new one rounded up to 2 KB), seek, wait, read, wait, close, then mark the entry loaded (2) and make it current. Returns 1 while busy, 0 when done. Security-cookie function. */
int m2_StmLoad50C80(void) {
    char path[0x100];
    int st;
    M2Stream2 *e = &m1_streams2C8900[r1e_mId3E0DBC];
    switch (a50_streamState) {
    case 0x00: {
        char *d;
        *(M2Str16 *)path = m2_strStmDir26B83C;
        strcat(path, e->name4);
        if (e->busy0 != 0) return 0;
        for (d = path; *d; d++) ;
        *(M2Str5 *)d = m2_strStm26B834;
        a50_streamHandle = sub_001A8210(path, 0x8001);
    }
    case 0x0A: {
        void *m = r1e_mArg3E0DC4;
        if (m == 0) { int volatile q = (e->size10 + 0x7FF) / 0x800; m = a5b_AllocCur(q << 11, 0, 0xCB3); }
        e->buf18 = m;
        r1e_m3E0DC8 = m;
        a50_streamState = 0x14;
        return 1;
    }
    case 0x14:
        r4b_FileSeek(a50_streamHandle, e->pos14, 0);
        a50_streamState = 0x1E;
    case 0x1E:
        if (r4b_FileReadPoll(a50_streamHandle, 1, &st) != 0) return 1;
        a50_streamState = 0x28;
    case 0x28: {
        int size = e->size10;
        void *buf = e->buf18;
        int fd = a50_streamHandle;
        m1_Stub102FA0(0);
        r4b_FileReadAsync(fd, buf, size);
        a50_streamState = 0x32;
    }
    case 0x32:
        if (r4b_FileReadPoll(a50_streamHandle, 1, &st) != 0) return 1;
        a50_streamState = 0x3C;
        r4b_FileClose(a50_streamHandle);
        a50_streamHandle = -1;
    case 0x3C:
        e->state1C = 2;
        { int volatile id = r1e_mId3E0DBC; if (id >= 0 && id < 0x21E) a30_curSlot = &m1_streams2C8900[id]; }
        return 0;
    }
    return 1;
}

/* 0x50560: same loader as 0x50C80 for the raw (unrounded) size at +0xC (allocation tag 0xB53); the entry is marked loaded with state 1. Returns 1 while busy, 0 when done. Security-cookie function. */
int m2_StmLoadRaw50560(void) {
    char path[0x100];
    int st;
    M2Stream2 *e = &m1_streams2C8900[r1e_mId3E0DBC];
    switch (a50_streamState) {
    case 0x00: {
        char *d;
        *(M2Str16 *)path = m2_strStmDir26B83C;
        strcat(path, e->name4);
        if (e->busy0 != 0) return 0;
        for (d = path; *d; d++) ;
        *(M2Str5 *)d = m2_strStm26B834;
        a50_streamHandle = sub_001A8210(path, 0x8001);
    }
    case 0x0A: {
        void *m = r1e_mArg3E0DC4;
        if (m == 0) m = a5b_AllocCur(e->rawC, 0, 0xB53);
        e->buf18 = m;
        r1e_m3E0DC8 = m;
        a50_streamState = 0x14;
        return 1;
    }
    case 0x14:
        r4b_FileSeek(a50_streamHandle, e->pos14, 0);
        a50_streamState = 0x1E;
    case 0x1E:
        if (r4b_FileReadPoll(a50_streamHandle, 1, &st) != 0) return 1;
        a50_streamState = 0x28;
    case 0x28: {
        int size = e->rawC;
        void *buf = e->buf18;
        int fd = a50_streamHandle;
        m1_Stub102FA0(0);
        r4b_FileReadAsync(fd, buf, size);
        a50_streamState = 0x32;
    }
    case 0x32:
        if (r4b_FileReadPoll(a50_streamHandle, 1, &st) != 0) return 1;
        a50_streamState = 0x3C;
        r4b_FileClose(a50_streamHandle);
        a50_streamHandle = -1;
    case 0x3C:
        e->state1C = 1;
        { int volatile id = r1e_mId3E0DBC; if (id >= 0 && id < 0x21E) a30_curSlot = &m1_streams2C8900[id]; }
        return 0;
    }
    return 1;
}

typedef struct M2MotRec2 { char name0[8]; int32_t id8; float speedC; int32_t frames10, mode14, flags18, loop1C; } M2MotRec2;
typedef struct M2MotFile2 { uint8_t unk00[4]; int32_t n4; uint8_t unk08[8]; M2MotRec2 r[1]; } M2MotFile2;
typedef struct M2MotAnim2 { int32_t id0, idx4, flags8; void *motC; float speed10; int32_t frames14, mode18, loop1C; struct M2MotAnim2 *next20; int32_t i24; } M2MotAnim2;
typedef struct M2MotSet2 { uint8_t unk00[0xC]; int32_t nC; M2MotAnim2 *list10; } M2MotSet2;
extern const M2Str5 m2_strPmt25FDC8;
char *sub_001C7DB0(char *d, const char *s, int n);
void *sub_00037570(const char *path, int flags);

/* 0x83820: load a motion library: read the list file, then for every entry load "<dir of list><name>.pmt" and append an animation record (id, speed, frames, mode, flags, loop) to the set. Returns how many motions loaded (0 when the list is missing). Security-cookie function. */
int m2_MotLibLoad83820(M2MotSet2 *set, const char *path) {
    int n = 0, i, len;
    M2MotFile2 *d;
    M2MotRec2 *r;
    char nm[0x10];
    char dir[0x100];
    char full[0x100];
    d = (M2MotFile2 *)sub_00037570(path, 0x40);
    if (d == 0) return 0;
    len = (int)strlen(path);
    for (; len >= 0; len--) if (path[len] == '/') break;
    __stosd((unsigned long *)dir, 0, sizeof(dir) / 4);
    sub_001C7DB0(dir, path, len + 1);
    r = d->r;
    for (i = 0; i < d->n4; i++, r++) {
        char *e;
        void *m;
        M2MotAnim2 *a, *p;
        memset(nm, 0, sizeof(nm));
        sub_001C7DB0(nm, r->name0, 8);
        for (e = nm; *e; e++) ;
        *(M2Str5 *)e = m2_strPmt25FDC8;
        strcpy(full, dir);
        strcat(full, nm);
        m = sub_00037570(full, 0x40);
        if (m == 0) continue;
        a = (M2MotAnim2 *)a5b_AllocCur(0x28, 0, 0x127);
        a->id0 = n; a->idx4 = n; a->flags8 = 0; a->motC = m; a->speed10 = 1.0f;
        a->frames14 = 10; a->mode18 = 2; a->loop1C = 0; a->next20 = 0; a->i24 = 0;
        if (set->list10 == 0) set->list10 = a;
        else {
            for (p = set->list10; p->next20 != 0; p = p->next20) ;
            p->next20 = a;
        }
        set->nC++;
        a->id0 = r->id8;
        a->speed10 = r->speedC;
        a->frames14 = r->frames10;
        a->mode18 = r->mode14;
        a->flags8 = r->flags18;
        a->loop1C = r->loop1C;
        n++;
    }
    return n;
}
