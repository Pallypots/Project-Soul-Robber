/* Area r1j, group 14: save data load steps 0x00057370.
   Names inferred. */
#include "r1j.h"

/* 0x00057370: one step of loading the save data. Step 0 allocates and
   clears the 0x8A0-byte work buffer and starts the read (0x001A9740).
   Step 1 runs the fade object 0x00428F40: wait for it to finish, then for
   the read (0x00056E10 == 1), fade back in over 8 frames, and when done
   advance. The last step copies the 0x800-byte record at +0x80 into a
   new block (r1j_saveRec42C7A0) when the read succeeded (0x003E3910 == 1),
   applies it when its mode is 1 or 2 (0x000408E0(0), flag bit 1 of
   0x00413160), frees the work buffer and resets the step. */
void r1j_SaveLoadStep(void)
{
    switch (r1j_ioStep3E3954) {
    case 0:
        r1j_ioBuf3E397C = sub_00053820(1, 0x8A0, 0, 0);
        r1j_Zero32(r1j_ioBuf3E397C, 0x8A0 / 4);
        sub_001A9740(r1j_ioBuf3E397C);
        r1j_ioStep3E3954++;
        /* fall through */
    case 1:
        switch (r1j_fadeState428F20) {
        case 0:
            r1j_fadeState428F20 = 1;
            /* fall through */
        case 1:
            if (sub_00072FA0(r1j_fade428F40) != 0)
                return;
            r1j_fadeState428F20 = 2;
            return;
        case 2:
            if (sub_00056E10() != 1)
                return;
            sub_00072F30(r1j_fade428F40, 0, 8.0f, 0, 0);
            r1j_fadeState428F20 = 3;
            return;
        case 3:
            if (sub_00072FA0(r1j_fade428F40) == 0)
                r1j_ioStep3E3954++;
            return;
        }
        return;
    }
    if (r1j_readOk3E3910 == 1) {
        r1j_saveRec42C7A0 = sub_00053820(8, 0x800, 0, 0);
        *r1j_saveRec42C7A0 = r1j_ioBuf3E397C->rec;
        if (r1j_saveRec42C7A0->mode == 1 || r1j_saveRec42C7A0->mode == 2) {
            sub_000408E0(0);
            r1j_flags413160 |= 2;
        }
    }
    sub_00053880(r1j_ioBuf3E397C);
    r1j_ioBuf3E397C = 0;
    r1j_mode3E3950 = 3;
    r1j_ioStep3E3954 = 0;
}
