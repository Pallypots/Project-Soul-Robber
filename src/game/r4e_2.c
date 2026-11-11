/* Area r4e: sound system initialisation at 0x0019B500 (r4e_2). Names inferred. */
#include "r4e.h"

/* 0x0019B500: (re)initialise the sound system: recreate the lock, start the driver,
   clear the voice, stream, music and track tables and reset the volumes. No inputs. */
void r4e_SoundInit(void)
{
    if (r4c_g402778) {
        sub_001AA1D0(r4c_g402778);
        r4c_g402778 = 0;
    }
    r4c_g402778 = r4d_AllocPersist();
    r4e_g402758 = 0x1800;
    sub_001AB3D0(4, 0x1800);
    r4e_g40275C = 0x3FFF;
    r4e_Trace102FA0(0x3FFF);
    r4e_g402760 = sub_001AB610();
    R4E_ZERO(r4c_voices401B30, sizeof(r4c_voices401B30));
    R4E_ZERO(r4d_streams401D70, sizeof(r4d_streams401D70));
    R4E_ZERO(r4e_music401AF8, sizeof(r4e_music401AF8));
    R4E_ZERO(r4d_tracks4019D8, sizeof(r4d_tracks4019D8));
    r4c_g402764 = 0x3FFF;
    r4d_g402768 = 0x3FFF;
    r4d_g402770 = 0x3FFF;
    r4d_g402774 = 0x3FFF;
    r4e_g40276C = 0x7FFF;
    sub_001995A0();
}
