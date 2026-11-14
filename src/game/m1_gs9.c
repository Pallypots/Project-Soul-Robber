/* Area m1, /GS file 9: model loader (range revisit). Names inferred. */
#include <stdint.h>

typedef struct M1Md9 { int32_t kind0; uint8_t unk04[4]; const char *dir8; void *dataC; } M1Md9;
extern const char m1_fmtBmd25FBC8[], m1_fmtPod25FBD8[];
char *sub_001C7DB0(char *d, const char *s, unsigned n);
int   sub_0007E070(char *buf, int n, const char *fmt, ...);
void *sub_00037550(const char *path, int k);
int   sub_0001D1E0(void *ctx, const char *name);

/* 0x1DB40: load a model by its 8-character name (.bmd for kind 0, .pod for kinds 1..2) and register it. */
int m1_ModelLoad01DB40(void *ctx, const char *name, M1Md9 *d) {
    char nm[12]; char path[0x100]; volatile int k;
    sub_001C7DB0(nm, name, 8);
    nm[8] = 0;
    k = d->kind0;
    if (k == 0) sub_0007E070(path, 0xFF, m1_fmtBmd25FBC8, d->dir8, nm);
    else if (k > 0 && k <= 2) sub_0007E070(path, 0xFF, m1_fmtPod25FBD8, d->dir8, nm);
    d->dataC = sub_00037550(path, 0);
    sub_0001D1E0(ctx, nm);
    return 8;
}
