/* Area rbg: stage timeline functions in 0x000E0000..0x000EFFFF kept apart from their callees
   (rbg_5). Names inferred. */
#include "rbg.h"

/* 0x000E6D80: per-frame update of the current stage timeline. Jack's death (state 6) forces
   mode 6 and stops music and effects; then the tracks of the current mode are advanced to the
   play position (track 0 camera, 1 events, 2 and 5 cues, 6 ending, 7 page items), the stage
   effects and fades are updated, and outside mode 6 tracks 3 and 4 follow.
   calls 0x000E4DD0 with EAX=pos; 0x000E2C20/0x000E2C70/0x000E2CC0/0x000E2D10 with EDI=stage;
   0x000E2E70 with ESI=stage EAX=cursor ECX=pos; 0x000E6910/0x000E26B0/0x000E48C0/0x000E1CD0
   with ESI=stage; 0x000E4C00 with EBX=stage; 0x000E1A60 with EAX=stage; 0x000E4E90 with
   EDI=key EBX=3; 0x000E2D60 with ESI=stage EAX=pos */
void rbg_StageUpdate0E6D80(void)
{
    RbgPage *st = &r2e_stage3F0758;
    uint32_t pos;

    if (!st->on320)
        return;
    sub_000E3C90(st);
    pos = st->len2F0;
    if (PlayerObj_GetState(&g_stats) == 6 && st->mode324 != 6) {
        st->mode324 = 6;
        if (st->rec31C >= 0) {
            sub_00048330(st->rec31C, 0x64);
            st->rec31C = -1;
        }
        if (st->strm2FC >= 0)
            sub_0019AA00(st->strm2FC, 0x64);
        sub_000E0E40(0);
        r2c_FxResetAll();
    }
    switch (st->mode324) {
    case 0:
        st->layers0C[0].cur10 = sub_000E4DD0(st, st->layers0C[0].cur10, pos);
        st->layers0C[1].cur10 = sub_000E2C20(st, pos);
        break;
    case 1:
        st->layers0C[0].cur10 = sub_000E4DD0(st, st->layers0C[0].cur10, pos);
        st->layers0C[1].cur10 = sub_000E2C20(st, pos);
        if (st->active408) {
            st->layers0C[7].cur10 = rbg_PageNext0E2E70(st, st->layers0C[7].cur10, pos);
            sub_000E6910(st);
        }
        break;
    case 2:
        if (st->active408)
            st->layers0C[2].cur10 = sub_000E2C70(st, pos);
        st->layers0C[0].cur10 = sub_000E4DD0(st, st->layers0C[0].cur10, pos);
        st->layers0C[1].cur10 = sub_000E2C20(st, pos);
        if (st->active408)
            sub_000E6910(st);
        break;
    case 3:
        if (st->active408)
            st->layers0C[5].cur10 = sub_000E2CC0(st, pos);
        st->layers0C[0].cur10 = sub_000E4DD0(st, st->layers0C[0].cur10, pos);
        if (st->active408)
            sub_000E26B0(st, pos);
        break;
    case 4:
        if (st->active408) {
            st->layers0C[2].cur10 = sub_000E2C70(st, pos);
            sub_000E6910(st);
            r2_SeqStep(st);
        }
        if (st->id00 == 6) {
            st->layers0C[1].cur10 = sub_000E2C20(st, pos);
            st->layers0C[6].cur10 = sub_000E2D10(st, pos);
        }
        break;
    case 5:
        if (st->active408) {
            st->layers0C[6].cur10 = sub_000E2D10(st, pos);
            r2_SeqStep(st);
        }
        break;
    case 6:
        if (PlayerObj_GetState(&g_stats) == 6)
            st->layers0C[0].cur10 = sub_000E4DD0(st, st->layers0C[0].cur10, pos);
        if (st->id00 == 6)
            sub_000E4C00(st);
        break;
    }
    sub_000EC730();
    sub_000E4160(st);
    sub_000E44E0(st);
    sub_000E4A20(st);
    sub_000E17A0(st);
    sub_000E1A60(st);
    sub_000E1CD0(st);
    if (st->mode324 != 6) {
        st->layers0C[3].cur10 = sub_000E4E90(st, pos, st->layers0C[3].cur10, sub_000E2420(st), 3);
        st->layers0C[4].cur10 = sub_000E2D60(st, pos, st->layers0C[4].cur10);
    }
}
