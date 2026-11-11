/* Area r1d, group 18: title jobs, camera groups and page arrows 0x0003CAB0..0x0003E5B0. Names inferred. */
#include "r1d.h"

/* 0x0003CAB0: register the title screen's three jobs and reset its
   state. */
void r1d_TitleStart(void *job)
{
    a1a_GroupAdd(job, 0, 1, sub_0003C700, 8, 0x2000);
    a1a_GroupAdd(job, 1, 1, r1d_TitleLoop, 8, 0x2000);
    a1a_GroupAdd(job, -1, 4, r1d_FrameLoop, 8, 0x2000);
    a1a_GroupReleaseOne(job, 0);
    a1a_GroupReleaseOne(job, -1);
    r1d_g3DDC80 = 0;
    r1d_g3DDC84 = 0;
    r1d_g3DDC88 = 0;
    r1d_g3DDC8C = 0;
    r1d_g3DDC90 = 0;
    r1d_g3DDC94 = 0;
    r1d_g3DDC74 = 0;
}

/* 0x0003D020: install camera group i: record its header, records and data
   and queue one node per entry (0x20 bytes of data each). */
void r1d_CamGroupInit(int i, R1dCamGrp *g)
{
    char *recs = (char *)g + 0x10;
    char *data = recs + 0xC0;
    R1dCamNode *n;
    int j;
    a4c_groupHdr[i] = g;
    a4c_groupRecs[i] = recs;
    a4c_groupData[i] = data;
    n = a4c_groupNodes[i];
    for (j = 0; j < g->count; j++, n++, data += 0x20) {
        n->data = data;
        a4c_ListAppend(a4c_groupList, n);
    }
}

/* 0x0003E550: draw the "previous page" arrow (or a blank) when the page
   list is not finished; otherwise return a. */
int r1d_PageArrowUp(int a, int b, int c, int d, int e, R1dPage *p)
{
    if (p->cur >= p->count) return a;
    return sub_0002E8C0(a, b, c, a4c_pg2C4B08[1], d, e, r1d_fmt266FC0,
                        p->first > 0 ? 0x5E : 0x20);
}

/* 0x0003E5B0: draw the "next page" arrow (or a blank) when the page list
   is not finished; otherwise return a. */
int r1d_PageArrowDown(int a, int b, int c, int d, int e, R1dPage *p)
{
    if (p->cur >= p->count) return a;
    return sub_0002E8C0(a, b, c, a4c_pg2C4B08[1], d, e, r1d_fmt266FC0,
                        p->first + p->cur < p->count ? 0x76 : 0x20);
}
