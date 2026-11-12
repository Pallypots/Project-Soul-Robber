/* Area m1, file 6: save data stamp. Names inferred. */
#include "m1f.h"

/* 0x00054CC0: read six values from 0x1A8920 (looks like the date and time), store them
 * as 16-bit words at buffer+0x200, then run 0x54700 on that record (ESI) and 0x54770 on buffer+0x280. */
void m1_StampTime54CC0(void)
{
    int v[6];
    uint16_t *w = (uint16_t *)(m1_ioBuf3E397C + 0x200);
    sub_001A8920(&v[0], &v[1], &v[2], &v[3], &v[4], &v[5]);
    w[0] = (uint16_t)v[0];
    w[1] = (uint16_t)v[1];
    w[2] = (uint16_t)v[2];
    w[3] = (uint16_t)v[3];
    w[4] = (uint16_t)v[4];
    w[5] = (uint16_t)v[5];
    sub_00054700_m1(w);
    sub_00054770_m1(m1_ioBuf3E397C + 0x280);
}

/* 0x000586E0: called from another thread while the background job runs: present one
 * frame with the job poll callback installed (state 1 -> 2). On the job's own thread
 * it only runs 0x1A53F0 when 0x1A5390 reports nothing. */
int m1_JobFrame586E0(void)
{
    int cleared, set;
    M1PollFn old;
    if (g_job.thread != sub_001AD560()) {
        g_job.state = 1;
        sub_00102FA0(0);
        cleared = a1a_MsgClearCb_m1(2);
        old = sub_001A85C0(0);
        if (old != a50_JobPoll)
            m1_savedPoll3E3F8C = old;
        sub_001A85C0(a50_JobPoll);
        if (cleared)
            a1a_MsgSetCb_m1(2);
        set = a1a_MsgSetCb_m1(2);
        Frame_Present();
        if (!set)
            a1a_MsgClearCb_m1(2);
        g_job.state = 2;
        return 0;
    }
    if (!a1a_Get40B0EC_m1())
        sub_001A53F0();
    return 0;
}


/* 0x00056740: apply a loaded save: keep the console language, copy the options and the
 * 0x2D4-byte body into globals, restore the sub-blocks, chapter time and health. */
int m1_ApplySave56740(M1Save *s)
{
    int hp;
    s->opt4E4[1] = m1_lang413145;
    m1_opt413140 = s->opt4E0;
    m1_opt413144 = *(int32_t *)s->opt4E4;
    m1_opt413148 = s->opt4E8;
    m1_opt41314C = s->opt4EC;
    m1_opt413147 = sub_001AB610();
    sub_0019BED0();
    m1_body413160 = s->body;
    sub_000CFB50(s->unk2D8);
    sub_000D9BB0(s->unk460);
    Clock_SetChapterTime(m1_clock413180);
    sub_0019C190(m1_v41317C);
    hp = Stats_Get(&g_stats, 0);
    Stats_Set(&g_stats, 1, hp);
    sub_00026280(hp, hp);
    return 0;
}

void sub_000CFA60(void *p);
void sub_000D9BD0(void *p);
extern int32_t a5b_g3E393C;                  /* 0x003E393C */
extern float   m1_playTime41317C;            /* 0x0041317C (same word as m1_v41317C) */

/* 0x00054770: build a save record (inverse of 0x56740): store both clocks, copy the
 * 0x2D4-byte body, save the sub-blocks, header word, capped count and options.
 * regargs: s=EAX */
void m1_BuildSave54770(M1Save *s)
{
    int n;
    m1_clock413180 = Clock_GetChapterTime();
    m1_playTime41317C = Clock_GetPlayTime();
    s->body = m1_body413160;
    sub_000CFA60(s->unk2D8);
    sub_000D9BD0(s->unk460);
    s->unk000 = a5b_g3E393C;
    n = m1_body413160.w[1];
    if (n > 0x18)
        n = 0x18;
    s->body.w[1] = n;
    s->opt4E0 = m1_opt413140;
    *(int32_t *)s->opt4E4 = m1_opt413144;
    s->opt4E8 = m1_opt413148;
    s->opt4EC = m1_opt41314C;
}
