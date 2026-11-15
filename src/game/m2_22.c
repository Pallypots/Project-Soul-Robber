/* Area m2, file 22: sphere mesh. Names inferred. */
#include <stdint.h>

extern float *r1g_batchCur3DCEFC;
void  r1g_BatchBegin(void *b, int kind, int count);
float sub_001A3ED0(float a);
float sub_001A3EE0(float a);
void  sub_0003A2A0(void *b, float rx, float ry, float rz, int nu, int nv);

/* 0x3A6B0: emit a sphere (ellipsoid radii rx, ry, rz) as two strip sets: 2*nu meridian strips over nv+2 rings, then nv latitude strips over 2*nu+1 points; each vertex's fourth word is 0 for a strip start and 0x8000 otherwise. Finishes through 0x3A2A0. */
void m2_SphereMesh3A6B0(void *b, float rx, float ry, float rz, int nu, int nv) {
    float stepU, stepV, sa, ca, sb, cb, t;
    int u, i, j, k;
    float *p;
    if (nu < 1) nu = 1;
    u = nu + nu;
    if (nv < 1) nv = 1;
    stepU = 6.2831860f / (float)u;
    stepV = 3.1415930f / (float)(nv + 1);
    r1g_BatchBegin(b, 2, (nv + 2) * u + (u + 1) * nv);
    for (i = 0; i < u; i++) {
        float a = (float)(i % u) * stepU;
        sa = sub_001A3ED0(a);
        ca = sub_001A3EE0(a);
        for (j = 0; j <= nv + 1; j++) {
            float bb = (float)j * stepV;
            sb = sub_001A3ED0(bb);
            cb = sub_001A3EE0(bb);
            p = r1g_batchCur3DCEFC;
            p[0] = sb * sa * rx;
            ((int32_t *)p)[3] = j ? 0x8000 : 0;
            p[1] = cb * ry;
            p[2] = sb * ca * rz;
            r1g_batchCur3DCEFC = (float *)((uint8_t *)r1g_batchCur3DCEFC + 0x10);
        }
    }
    for (k = 1; k <= nv; k++) {
        float bb = (float)k * stepV;
        sb = sub_001A3ED0(bb);
        cb = sub_001A3EE0(bb);
        t = cb * ry;
        for (j = 0; j <= u; j++) {
            float a = (float)(j % u) * stepU;
            float s1 = sub_001A3ED0(a) * sb;
            float c1 = sub_001A3EE0(a) * sb;
            p = r1g_batchCur3DCEFC;
            p[0] = s1 * rx;
            ((int32_t *)p)[3] = j ? 0x8000 : 0;
            p[1] = t;
            p[2] = c1 * rz;
            r1g_batchCur3DCEFC = (float *)((uint8_t *)r1g_batchCur3DCEFC + 0x10);
        }
    }
    sub_0003A2A0(b, rx, ry, rz, nu, nv);
}
