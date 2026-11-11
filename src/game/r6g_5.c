/* Area r6g: present models (r6g_5). Names inferred. */
#include "r6g.h"

/* Load one present model record: pack list, kind 13, its index, then finish it. */
#define R6G_PRESENT_LOAD(i, path)                       \
    sub_00022630(&r6g_presents41CEBC[i], path);         \
    r6g_presents41CEBC[i].kind = 0xD;                   \
    r6g_presents41CEBC[i].index = i;                    \
    sub_00036790(&r6g_presents41CEBC[i])

/* 0x000C9460: load the twelve present models (three each of three styles and
   three of the last style, which share one pack list) and continue with
   0x000C87B0 (tail call). */
void r6g_PresentsLoad(void)
{
    sub_000C6920();
    R6G_PRESENT_LOAD(0, r6g_prsnt0000_276FF4);
    R6G_PRESENT_LOAD(1, r6g_prsnt0001_276FC8);
    R6G_PRESENT_LOAD(2, r6g_prsnt0002_276F9C);
    R6G_PRESENT_LOAD(3, r6g_prsnt0100_276F70);
    R6G_PRESENT_LOAD(4, r6g_prsnt0101_276F44);
    R6G_PRESENT_LOAD(5, r6g_prsnt0102_276F18);
    R6G_PRESENT_LOAD(6, r6g_prsnt0200_276EEC);
    R6G_PRESENT_LOAD(7, r6g_prsnt0201_276EC0);
    R6G_PRESENT_LOAD(8, r6g_prsnt0202_276E94);
    R6G_PRESENT_LOAD(9, r6g_prsnt03_277020);
    R6G_PRESENT_LOAD(10, r6g_prsnt03_277020);
    R6G_PRESENT_LOAD(11, r6g_prsnt03_277020);
    sub_000C87B0();
}
