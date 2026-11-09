/* Chapter grading (results screen). Reference build OOGIE-XBOX-US-RETAIL.
 * Names inferred. Records: docs/functions/grade.md */
#include "oogie.h"

/* 0x00041480 */
void Grade_AddBestCombo(int combo)
{
    if (g_grade.bestCombo < combo)
        g_grade.bestCombo = combo;
}

/* 0x000414A0 */
void Grade_AddExclamations(int amount)
{
    g_grade.exclaim += amount;
    sub_00025FD0(1, 0x78);
    if (g_grade.exclaim < 0)
        g_grade.exclaim = 0;
    else if (g_grade.exclaim > 999)
        g_grade.exclaim = 999;
}

/* 0x000414F0 */
void Grade_AddDamage(int amount)
{
    int v = g_grade.damage + amount;
    g_grade.damage = v;
    if (v < 0)
        g_grade.damage = 0;
    else if (v > 999)
        g_grade.damage = 999;
}

/* 0x00040C10. The original takes `chapter` in EAX (a whole-program
 * optimised convention); an out-of-range chapter hangs on purpose. */
void Grade_CommitChapter(int chapter)
{
    GradeBlock *rec;
    int sum;

    if (chapter < 1 || chapter > 24)
        for (;;)
            ;   /* deliberate hang (an assert in the original build, Hypothesis) */
    rec = &g_chapterRecords[chapter];
    if (rec->grade == -1) {
        *rec = g_grade;
        return;
    }
    if (rec->time > g_grade.time) {
        rec->time = g_grade.time;
        rec->rank[0] = g_grade.rank[0];
    }
    if (rec->bestCombo < g_grade.bestCombo) {
        rec->bestCombo = g_grade.bestCombo;
        rec->rank[1] = g_grade.rank[1];
    }
    if (rec->damage > g_grade.damage) {
        rec->damage = g_grade.damage;
        rec->rank[2] = g_grade.rank[2];
    }
    if (rec->exclaim < g_grade.exclaim) {
        rec->exclaim = g_grade.exclaim;
        rec->rank[3] = g_grade.rank[3];
    }
    sum = rec->rank[2] + rec->rank[3] + rec->rank[1] + rec->rank[0];
    if (sum >= 16)
        rec->grade = 4;
    else if (sum >= 12)
        rec->grade = 3;
    else if (sum >= 8)
        rec->grade = 2;
    else
        rec->grade = sum >= 4;
}
