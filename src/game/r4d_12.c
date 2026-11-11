/* Area r4d: temporary data slot and small list helpers around 0x001A1AC0-0x001A24CC (r4d_12). Names inferred. */
#include "r4d.h"

/* 0x001A1AC0: save the three cached data blocks (1/0, 13/0, 1/255) and open the temporary slot. No inputs. */
void r4d_TempSave(void)
{
    void *p;
    if (!r4d_g4046CC || r4d_tempOn4046D0)
        return;
    p = sub_000532B0(1, 0);
    if (p)
        r4d_blob4046C0 = sub_00052CB0(p);
    else
        r4d_blob4046C0 = 0;
    p = sub_000532B0(0x0D, 0);
    if (p)
        r4d_blob4046C4 = sub_00052CB0(p);
    else
        r4d_blob4046C4 = 0;
    p = sub_000532B0(1, 0xFF);
    if (p)
        r4d_blob4046C8 = sub_00052CB0(p);
    else
        r4d_blob4046C8 = 0;
    sub_0004F620(0x5F);
    sub_000539C0(1, r4d_g4046CC, r4d_g4046BC);
    r4d_tempOn4046D0 = 1;
}

/* 0x001A1B90: close the temporary slot and put the three saved blocks back (or reacquire them). No inputs. */
void r4d_TempRestore(void)
{
    void *p;
    if (!r4d_g4046CC || !r4d_tempOn4046D0)
        return;
    sub_00053A00(1);
    sub_000512D0(0x5F, r4d_g4046CC);
    p = sub_000532B0(1, 0);
    if (p && r4d_blob4046C0) {
        sub_00052B00(p);
        sub_00052CF0(p, r4d_blob4046C0);
        sub_00053880(r4d_blob4046C0);
    } else {
        sub_000535F0(-1, 1, 0);
    }
    p = sub_000532B0(0x0D, 0);
    if (p && r4d_blob4046C4) {
        sub_00052B00(p);
        sub_00052CF0(p, r4d_blob4046C4);
        sub_00053880(r4d_blob4046C4);
    } else {
        sub_000535F0(-1, 0x0D, 0);
    }
    p = sub_000532B0(1, 0xFF);
    if (p && r4d_blob4046C8) {
        sub_00052B00(p);
        sub_00052CF0(p, r4d_blob4046C8);
        sub_00053880(r4d_blob4046C8);
    } else {
        sub_000535F0(-1, 1, 0xFF);
    }
    sub_00034370();
    r4d_tempOn4046D0 = 0;
}

/* 0x001A1F50: append a 16-byte entry to a list of at most 8. Stack args (l v). */
void r4d_List8Add(R4dList8 *l, const R4dVec16 *v)
{
    if (l->n < 8) {
        l->e[l->n] = *v;
        l->n++;
    }
}

/* 0x001A2480: send the 0x180-byte matrix blocks selected by l (from obj+0xFC) to GPU constants 0x40+4k.
   Stack args (obj l); XDK callee 0x001D24F0 is fastcall. */
void r4d_UploadBones(uint8_t *obj, R4dIdxList *l)
{
    uint32_t k;
    for (k = 0; k < l->n; k++)
        sub_001D24F0(0x40 + 4 * k, obj + l->idx[k] * 0x180 + 0xFC);
}
