/* Area r6g: text table loader (r6g_14). Names inferred. */
#include "r6g.h"

/* 0x000755B0: parse a text table (lines of eight columns, the third ignored and
   the last read as a float) into a newly allocated "@TXA" record. Returns 0
   when the text has no non-empty line. */
R6gTxa *r6g_TxaLoad(void *a, void *b)
{
    char *cur, *line, *tok;
    int n = 0;
    R6gTxa *r;
    R6gTxaEnt *e;

    sub_00013040();
    cur = sub_000134C0(a, b);
    line = sub_00012FA0(&cur);
    while (line) {
        if (sub_00013140(&line))
            n++;
        line = sub_00012FA0(&cur);
    }
    if (!n)
        return 0;
    r = (R6gTxa *)sub_00053AB0(n * 32 + 16, 0, 0x36B);
    r->count = n;
    r->tag[0] = '@';
    r->tag[1] = 'T';
    r->tag[2] = 'X';
    r->tag[3] = 'A';
    r->i08 = 0;
    r->i0C = 0;
    e = r->ent;
    cur = sub_000134C0(a, b);
    line = sub_00012FA0(&cur);
    while (line) {
        tok = sub_00013140(&line);
        if (tok) {
            sub_001C7C70(tok, r1b_fmtD, &e->v[0]);
            sub_001C7C70(sub_00013140(&line), r1b_fmtD, &e->v[1]);
            sub_00013140(&line);
            sub_001C7C70(sub_00013140(&line), r1b_fmtD, &e->v[2]);
            sub_001C7C70(sub_00013140(&line), r1b_fmtD, &e->v[3]);
            sub_001C7C70(sub_00013140(&line), r1b_fmtD, &e->v[4]);
            sub_001C7C70(sub_00013140(&line), r1b_fmtD, &e->v[5]);
            sub_001C7C70(sub_00013140(&line), r1b_fmtF, &e->f00);
            e++;
        }
        line = sub_00012FA0(&cur);
    }
    sub_00012F90();
    sub_000130C0();
    return r;
}
