/* Area r1j, group 11: chapter grading 0x00040AB0.
   Names inferred. */
#include "r1j.h"

/* 0x00040AB0: rank grading block g against the chapter thresholds t.
   Each category gets 4..0 by the first threshold it reaches (time and
   damage at or below, best combo and exclamations at or above); the
   overall grade is 4, 3, 2, 1 or 0 for a rank sum of at least 16, 12, 8,
   4 or less. regargs: g=EAX t=ECX */
void r1j_GradeRank(GradeBlock *g, const R1jGradeThr *t)
{
    int r, sum;
    if (t->time[0] >= g->time) r = 4;
    else if (t->time[1] >= g->time) r = 3;
    else if (t->time[2] >= g->time) r = 2;
    else if (t->time[3] >= g->time) r = 1;
    else r = 0;
    g->rank[0] = (int8_t)r;
    if (g->bestCombo >= t->combo[0]) r = 4;
    else if (g->bestCombo >= t->combo[1]) r = 3;
    else if (g->bestCombo >= t->combo[2]) r = 2;
    else r = g->bestCombo >= t->combo[3];
    g->rank[1] = (int8_t)r;
    if (g->damage <= t->damage[0]) r = 4;
    else if (g->damage <= t->damage[1]) r = 3;
    else if (g->damage <= t->damage[2]) r = 2;
    else r = g->damage <= t->damage[3];
    g->rank[2] = (int8_t)r;
    if (g->exclaim >= t->exclaim[0]) r = 4;
    else if (g->exclaim >= t->exclaim[1]) r = 3;
    else if (g->exclaim >= t->exclaim[2]) r = 2;
    else r = g->exclaim >= t->exclaim[3];
    g->rank[3] = (int8_t)r;
    sum = g->rank[1] + g->rank[2] + g->rank[0] + g->rank[3];
    if (sum >= 16) g->grade = 4;
    else if (sum >= 12) g->grade = 3;
    else if (sum >= 8) g->grade = 2;
    else g->grade = sum >= 4;
}
