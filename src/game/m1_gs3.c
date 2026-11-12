/* Area m1, /GS file 3: world arrange file loaders. Names inferred. */
#if defined(_M_IX86)
#include <intrin.h>
#endif
#include "m1.h"

/* 0x00085300: load world area (a,b) arrange/enemy.arg and keep the pointer. */
void m1_LoadEnemyArg85300(int a, int b)
{
    char path[0x100];
    sub_0007E0A0(path, m1_fmtEnemy26F904, a, b);
    m1_enemyArg3ED1CC = sub_00037570(path, 0x40);
}

/* 0x000861A0: load world area (a,b) arrange/loadset.arg and keep the pointer. */
void m1_LoadLoadsetArg861A0(int a, int b)
{
    char path[0x100];
    sub_0007E0A0(path, m1_fmtLoadset26F95C, a, b);
    m1_loadsetArg3ED208 = sub_00037570(path, 0x40);
}

/* 0x00086E60: load world area (a,b) arrange/bgobject.arg and keep the pointer. */
void m1_LoadBgobjectArg86E60(int a, int b)
{
    char path[0x100];
    sub_0007E0A0(path, m1_fmtBgobject26F98C, a, b);
    m1_bgobjectArg3ED210 = sub_00037570(path, 0x40);
}

/* 0x00086FA0: load world area (a,b) arrange/resident.arg and keep the pointer. */
void m1_LoadResidentArg86FA0(int a, int b)
{
    char path[0x100];
    sub_0007E0A0(path, m1_fmtResident26F9BC, a, b);
    m1_residentArg3ED214 = sub_00037570(path, 0x40);
}

/* 0x000873D0: load arrange/arrange.lin for world area (a,b); mark ready on success. */
void m1_LoadArrangeLin873D0(int a, int b)
{
    char path[0x100];
    sub_0007E0A0(path, m1_fmtArrangeLin26F9EC, a, b);
    m1_arrangeLin3ED248 = sub_00037570(path, 0x40);
    if (m1_arrangeLin3ED248)
        m1_arrangeReady3ED21C = 1;
}

/* 0x00084DD0: load arrange/addenemy.arg for area (a,b); if present allocate and clear
 * 8 bytes per entry on pool 3. */
void m1_LoadAddEnemy84DD0(int a, int b)
{
    char path[0x100];
    sub_0007E0A0(path, m1_fmtAddEnemy26F8D0, a, b);
    m1_addEnemy3ED1B0 = sub_00037570(path, 0x40);
    if (m1_addEnemy3ED1B0) {
        m1_addEnemyWork3ECCA8 = sub_00053820(3, m1_addEnemy3ED1B0->count * 8, 0, 0);
        {
            uint32_t n = (uint32_t)m1_addEnemy3ED1B0->count * 8;
#if defined(_M_IX86)
            /* the original's inline memset: dwords, then the remaining bytes */
            uint8_t *p = (uint8_t *)m1_addEnemyWork3ECCA8;
            __stosd((unsigned long *)p, 0, n >> 2);
            __stosb(p + (n & ~3u), 0, n & 3);
#else
            memset(m1_addEnemyWork3ECCA8, 0, n);
#endif
        }
    }
}

