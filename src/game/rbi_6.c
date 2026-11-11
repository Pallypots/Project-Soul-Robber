/* Area rbi: hit shapes placed from bone positions (rbi_6). Names inferred. */
#include "rbi.h"

/* 0x00114E90: place the hit shapes of an enemy from its bones: the offset of part 3 from the
   object position gives the horizontal centre of the body shape (radius 5.5, height of part
   10 above the object minus 5), of the second shape (y -8, radius 6) and of the vertical
   segment (y -5 at both ends).
   regargs: o=ESI */
void rbi_Shapes114E90(RbiShapeObj *o)
{
    RbiVec4 d, m[4];

    rbi_PartMatrix145F40(o, 3, m);
    rbi_VecSub(&d, &m[3], &o->pos60);
    rbi_PartMatrix145F40(o, 10, m);
    o->cA0.x = d.x;
    o->cA0.y = 0.0f;
    o->cA0.z = d.z;
    o->cA0.w = 1.0f;
    o->hB4 = m[3].y - o->pos60.y - 5.0f;
    o->rB0 = 5.5f;
    o->cD8.x = d.x;
    o->cD8.y = -8.0f;
    o->cD8.z = d.z;
    o->cD8.w = 1.0f;
    o->rE8 = 6.0f;
    o->aF8.x = d.x;
    o->aF8.y = -5.0f;
    o->aF8.z = d.z;
    o->aF8.w = 1.0f;
    o->b108.x = d.x;
    o->b108.y = 0.0f;
    o->b108.z = d.z;
    o->b108.w = 1.0f;
}

/* 0x00135900: the same for another enemy (body radius 4, height minus 7, second shape y -6.5,
   radius 4.5).
   regargs: o=ESI */
void rbi_Shapes135900(RbiShapeObj *o)
{
    RbiVec4 d, m[4];

    rbi_PartMatrix145F40(o, 3, m);
    rbi_VecSub(&d, &m[3], &o->pos60);
    rbi_PartMatrix145F40(o, 10, m);
    o->cA0.x = d.x;
    o->cA0.y = 0.0f;
    o->cA0.z = d.z;
    o->cA0.w = 1.0f;
    o->hB4 = m[3].y - o->pos60.y - 7.0f;
    o->rB0 = 4.0f;
    o->cD8.x = d.x;
    o->cD8.y = -6.5f;
    o->cD8.z = d.z;
    o->cD8.w = 1.0f;
    o->rE8 = 4.5f;
    o->aF8.x = d.x;
    o->aF8.y = -5.0f;
    o->aF8.z = d.z;
    o->aF8.w = 1.0f;
    o->b108.x = d.x;
    o->b108.y = 0.0f;
    o->b108.z = d.z;
    o->b108.w = 1.0f;
}

/* 0x0012DEC0: the shapes of 0x00114E90 for another enemy, with the segment start height
   -0.5 * 10 per frame unit instead of a fixed -5.
   regargs: o=ESI */
void rbi_Shapes12DEC0(RbiShapeObj *o)
{
    RbiVec4 d, m[4];

    rbi_PartMatrix145F40(o, 3, m);
    rbi_VecSub(&d, &m[3], &o->pos60);
    rbi_PartMatrix145F40(o, 10, m);
    o->cA0.x = d.x;
    o->cA0.y = 0.0f;
    o->cA0.z = d.z;
    o->cA0.w = 1.0f;
    o->hB4 = m[3].y - o->pos60.y - 5.0f;
    o->rB0 = 5.5f;
    o->cD8.x = d.x;
    o->cD8.y = -8.0f;
    o->cD8.z = d.z;
    o->cD8.w = 1.0f;
    o->rE8 = 6.0f;
    o->aF8.x = d.x;
    o->aF8.z = d.z;
    o->aF8.w = 1.0f;
    o->b108.x = d.x;
    o->b108.y = 0.0f;
    o->b108.z = d.z;
    o->b108.w = 1.0f;
    o->aF8.y = a50_frameUnits * -0.5f * 10.0f;
}
