/* Area r6d: stream stop at 0x000867F0 (r6d_17). Names inferred. */
#include "r6d.h"

/* 0x000867F0: stop both streaming voices that are still busy and wait until they are idle
   (job entry point; the argument is unused). */
void r6d_StreamsStop(int unused)
{
    int i;
    (void)unused;
    for (i = 0; i < 2; i++) {
        if (a8c_handles3ED1DC[i] != -1 && !sub_000480F0(a8c_handles3ED1DC[i])) {
            sub_00047A80(a8c_handles3ED1DC[i]);
            while (sub_00047B10(a8c_handles3ED1DC[i]) != 2)
                ;
            sub_00047B30(a8c_handles3ED1DC[i]);
            while (sub_00047B50(a8c_handles3ED1DC[i]))
                ;
        }
    }
}
