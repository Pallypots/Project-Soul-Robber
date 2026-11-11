/* Area r4e: options and game-state threads at 0x0019BED0 and 0x0019FC60 (r4e_22). Names inferred. */
#include "r4e.h"

/* 0x0019BED0: apply the saved options: video mode, sound mode (+3 when the first
   option is set), language, two volumes, screen offsets and the viewport. No inputs. */
void r4e_ApplyOptions(void)
{
    int sel = r4c_opt413145 ? 3 : 0;
    sub_00052A00((int8_t)r4c_opt413145);
    sub_0003CFC0((int8_t)r4c_opt413146 + sel);
    sub_0005EB40((int8_t)r4c_opt413142);
    sub_000479E0((int8_t)r4c_opt413147);
    sub_00048620((int8_t)r4c_opt413148 * 0x7FF);
    sub_000486F0((int8_t)r4c_opt413149 * 0x7FF);
    r4e_SetDepthRange((float)(int8_t)r4c_opt41314A, (float)(int8_t)r4c_opt41314B);
    r4e_SetSafeViewport();
    sub_001A76A0((int16_t)r4c_opt41314C);
}

/* 0x0019FC60: start the game-state threads (0x0019E990 and 0x0019FAC0) on group
   state, then reset the state timers and load 0x003374A8 into 0x00403008.
   Stack arg (state). */
void r4e_GameStateStart(int *state)
{
    state[1] = 1;
    sub_001A1030(state, 0, 1, sub_0019E990, 8, 0x20000);
    sub_001A1030(state, -1, 4, sub_0019FAC0, 8, 0x20000);
    sub_001A10F0(state);
    a19_g403004 = 0.0f;
    a19_g403120 = 0.0f;
    a19_g403128 = state;
    a19_g3374A0 = 1;
    r4c_g403130 = 0;
    a9c_g403124 = 1.0f;
    sub_0001AE70(r4e_g403008, r4e_g3374A8);
}
