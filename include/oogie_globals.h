/* Globals referenced by recovered functions. Addresses are for reference build
 * OOGIE-XBOX-US-RETAIL (default.xbe SHA-1 667c5bd8...). Names are INFERRED. */
#ifndef OOGIE_GLOBALS_H
#define OOGIE_GLOBALS_H
#include <stdint.h>

typedef void (*JobFunc)(void *arg);

/* 0x003E3F64: background job record (see docs/provenance.md, REVERSE_ENGINEERING.md) */
typedef struct BackgroundJob {
    int32_t state;        /* +0x00  0 idle, 1 loading, 2 started (inferred) */
    void   *thread;       /* +0x04 */
    uint8_t unk08[0x10];  /* +0x08 .. +0x17 not analysed */
    JobFunc func;         /* +0x18  non-NULL while the job runs */
    void   *arg;          /* +0x1C */
} BackgroundJob;

extern BackgroundJob g_job;                 /* 0x003E3F64 */
extern int32_t       g_chapterExclamations; /* 0x0041318C, grading block +0xC */
extern void         *g_renderLock;          /* 0x0040B0E0, RTL_CRITICAL_SECTION* */
extern void         *g_presentEvent;        /* 0x0040B0E4, waitable handle */
#endif
