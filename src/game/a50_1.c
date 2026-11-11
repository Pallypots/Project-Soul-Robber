/* Streaming start, video timing, table helpers (0x00050FA0-0x00052CEF).
 * Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a50.h"

/* 0x00050FA0: poll the stream: start it when idle, then report readiness. */
int a50_StreamPoll(void)
{
    int out;

    switch (a50_streamState) {
    case 0:
        sub_001A8330(a50_streamHandle);
        a50_streamState = 10;
        return 1;
    case 10:
        if (sub_001A8500(a50_streamHandle, 1, &out))
            return 1;
        return 0;
    case 20:
        return 0;
    }
    return 1;
}

/* 0x00051000: restart the stream. */
int a50_StreamRestart(void)
{
    sub_001A8330(a50_streamHandle);
    return 0;
}

/* 0x00052A00: set the video mode, returning the previous one. */
int a50_SetVideoMode(int mode)
{
    int old = a50_videoMode;
    a50_videoMode = mode;
    return old;
}

/* 0x00052A10: name of the current video mode. */
const char *a50_GetVideoModeName(void)
{
    return a50_videoModeNames[a50_videoMode];
}

/* 0x00052A20: initialise frame timing from the display rate. */
void a50_InitTiming(void)
{
    float secs;

    sub_000527B0();
    a50_frameCounter0 = 0;
    a50_frameCounter1 = 0;
    secs = 1.0f / a50_rateHz[g_videoRateMode];
    a50_frameUnits = secs * 60.0f;
    a50_timeScale = 1.0f;
    a50_frameSeconds = secs;
    a50_framesPerSecond = 1.0f / secs;
    sub_001BBD70(a50_frameUnits);
    a50_videoMode = 1;
}

/* 0x00052AA0: clear the key of every cache entry (17 entries of 0x14 bytes). */
void a50_ClearCache(void)
{
    int i;
    for (i = 0; i < 17; i++)
        a50_cacheEntries[i * 5 + 2] = 0;
}

/* 0x00052AD0: find the entry with the given id in a table. */
A50TableEntry *a50_TableFind(A50Table *t, int id)
{
    A50TableEntry *e;
    uint32_t i = 0, n;
    if (t == 0)
        return 0;
    e = t->entries;
    n = t->count;
    if (n != 0) {
        for (; i < n; i++, e++)
            if (e->id == id)
                break;
    }
    return i < n ? e : 0;
}

/* 0x00052B00: rebase a loaded table blob's offsets into pointers, once. */
void a50_BlobRebase(A50Blob *b)
{
    A50Table *t;
    A50TableEntry *e;
    int32_t *p;
    int i;

    if (b->flags != 0)
        return;
    b->tableA += (int32_t)b; /* XBOX32: loaded blob stores 32-bit offsets rebased in place to 32-bit pointers */
    b->tableB += (int32_t)b; /* XBOX32: loaded blob stores 32-bit offsets rebased in place to 32-bit pointers */
    t = (A50Table *)b->tableA; /* XBOX32: loaded blob stores 32-bit offsets rebased in place to 32-bit pointers */
    for (i = t->count, e = t->entries; i > 0; i--, e++)
        e->ptr += (int32_t)b; /* XBOX32: loaded blob stores 32-bit offsets rebased in place to 32-bit pointers */
    t = (A50Table *)b->tableB; /* XBOX32: loaded blob stores 32-bit offsets rebased in place to 32-bit pointers */
    for (i = t->count, e = t->entries; i > 0; i--, e++) {
        e->ptr += (int32_t)b; /* XBOX32: loaded blob stores 32-bit offsets rebased in place to 32-bit pointers */
        p = (int32_t *)e->ptr; /* XBOX32: loaded blob stores 32-bit offsets rebased in place to 32-bit pointers */
        if (p[0] != 0)
            p[1] += (int32_t)p; /* XBOX32: loaded blob stores 32-bit offsets rebased in place to 32-bit pointers */
    }
    b->flags |= 1;
}

/* 0x00052CB0: copy a blob's table-A entry pointers into a counted list
 * allocated from the shared heap. */
int32_t *a50_BlobListEntries(A50Blob *b)
{
    A50Table *t = (A50Table *)b->tableA; /* XBOX32: loaded blob stores 32-bit offsets rebased in place to 32-bit pointers */
    int n = t->count;
    int32_t *list = a50_Alloc(10, n * 4 + 4, 0, 0);
    int i;

    list[0] = n;
    for (i = 0; i < n; i++)
        list[i + 1] = t->entries[i].ptr;
    return list;
}
