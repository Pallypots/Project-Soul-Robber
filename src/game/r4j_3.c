/* Area r4j: blend presets by texture format (0x001A69C0). Names inferred. */
#include "r4j.h"

/* 0x001A69C0: under the render lock mark the texture stage dirty, set
   render-state shadow 0x001E2190 to 6 and pick the blend states from the
   64-bit texture format (blend op 0x40350, source 0x40344, destination
   0x40348; 0x88 also sets 0x40300 on and 0x40304 off). Unknown formats
   change nothing more. Stack arg (fmt, 64-bit as two dwords). 0x001D4350 is
   fastcall (ECX EDX). */
void r4j_BlendByFormat(uint64_t fmt)
{
    RtlEnterCriticalSection(g_renderLock);
    a1a_g1E2148 |= 0x800;
    r4f_rs1E2190 = 6;
    switch (fmt) {
    case 0x44:
        sub_001D4350(0x40350, 0x8006);
        r4f_rs1E2478 = 0x8006;
        sub_001D4350(0x40344, 0x302);
        r4f_rs1E2448 = 0x302;
        sub_001D4350(0x40348, 0x303);
        r4f_rs1E244C = 0x303;
        break;
    case 0x48:
        sub_001D4350(0x40350, 0x8006);
        r4f_rs1E2478 = 0x8006;
        sub_001D4350(0x40344, 0x302);
        r4f_rs1E2448 = 0x302;
        sub_001D4350(0x40348, 1);
        r4f_rs1E244C = 1;
        break;
    case 0x42:
        sub_001D4350(0x40350, 0x800B);
        r4f_rs1E2478 = 0x800B;
        sub_001D4350(0x40344, 0x302);
        r4f_rs1E2448 = 0x302;
        sub_001D4350(0x40348, 1);
        r4f_rs1E244C = 1;
        break;
    case 0x4A:
        sub_001D4350(0x40350, 0x8006);
        r4f_rs1E2478 = 0x8006;
        sub_001D4350(0x40344, 1);
        r4f_rs1E2448 = 1;
        sub_001D4350(0x40348, 0);
        r4f_rs1E244C = 0;
        break;
    case 0x88:
        sub_001D4350(0x40300, 1);
        aac_g1E2440 = 1;
        sub_001D4350(0x40304, 0);
        aac_g1E243C = 0;
        /* fall through */
    case 0x0A:
        sub_001D4350(0x40350, 0x8006);
        r4f_rs1E2478 = 0x8006;
        sub_001D4350(0x40344, 0x302);
        r4f_rs1E2448 = 0x302;
        sub_001D4350(0x40348, 0);
        r4f_rs1E244C = 0;
        sub_001D4350(0x40348, 0x303);
        r4f_rs1E244C = 0x303;
        break;
    }
    RtlLeaveCriticalSection(g_renderLock);
}
