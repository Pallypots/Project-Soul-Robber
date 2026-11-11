/* Area r4e: image, mesh and vector helpers around 0x001AE8E0-0x001AF294 (r4e_15). Names inferred. */
#include "r4e.h"

/* 0x001AE8E0: address of entry k of an image's level table: after the 0x20-byte
   header, f18 words and the block-rounded size words. Stack args (img k). */
int32_t *r4e_ImgLevelPtr(R4eImgHdr *img, int k)
{
    int n = (img->w10 + 3) / 4 + (img->h0C + 3) / 4 + k * 5;
    return (int32_t *)img + img->f18 + n * 4 + 8;
}

/* 0x001AE920: the mesh block that follows mesh: count vertices of 3 words plus one
   per optional array flag of the model, plus the 16-byte header. Stack args (m mesh). */
R4eMesh *r4e_MeshNext(R4eModel *m, R4eMesh *mesh)
{
    uint32_t f = m->flags04;
    int n = (f & 1) ? 4 : 3;
    if (f & 2)
        n++;
    if (f & 4)
        n++;
    return (R4eMesh *)((uint8_t *)mesh + (mesh->count00 * n + 1) * 16);
}

/* 0x001AF260: out = b + (a - b) * k. regargs: a=EAX b=ESI; stack args (out k). */
void r4e_VecLerp(float *out, float k, const float *a, const float *b)
{
    float t[4];
    r4c_VecSub(t, a, b);
    r4c_Vec4Scale(t, t, k);
    r4c_VecAdd(out, t, b);
}
