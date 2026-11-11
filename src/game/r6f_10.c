/* Area r6f: grid cell walkers around 0x000856F0-0x0008592E (r6f_10). Names inferred. */
#include "r6f.h"

/* 0x000856F0: for every cell of g, run 0x000ED4C0 on the cell and on each of
   its links; then for every cell spin 0x000ED520 on the cell and each link
   until it reports done.
   calls 0x000853B0 and 0x00085430 with EDI=g */
void r6f_GridSettle(void *g)
{
    int x = -1, y = -1, k = -1;
    int r;
    sub_00053710(4);
    sub_000853B0(&x, &y, g);
    do {
        sub_000ED4C0(x);
        for (r = sub_000EDCB0(x, y, &k); r != -1; r = sub_000EDCB0(x, y, &k))
            sub_000ED4C0(r);
    } while (sub_00085430(&x, &y, g) != -1);
    sub_000853B0(&x, &y, g);
    do {
        while (sub_000ED520(x, y))
            ;
        for (r = sub_000EDCB0(x, y, &k); r != -1; r = sub_000EDCB0(x, y, &k)) {
            while (sub_000ED520(r, k))
                ;
        }
    } while (sub_00085430(&x, &y, g) != -1);
    sub_00053740();
}

/* 0x00085820: for every cell of g, run 0x000ED590 on the cell and each of its
   links; then run 0x000ED5D0 on every cell and link.
   calls 0x000853B0 and 0x00085430 with EDI=g */
void r6f_GridRefresh(void *g)
{
    int x = -1, y = -1, k = -1;
    int r;
    sub_00053710(4);
    sub_000853B0(&x, &y, g);
    do {
        sub_000ED590(x, y);
        for (r = sub_000EDCB0(x, y, &k); r != -1; r = sub_000EDCB0(x, y, &k))
            sub_000ED590(r, k);
    } while (sub_00085430(&x, &y, g) != -1);
    sub_000853B0(&x, &y, g);
    do {
        sub_000ED5D0(x);
        for (r = sub_000EDCB0(x, y, &k); r != -1; r = sub_000EDCB0(x, y, &k))
            sub_000ED5D0(r);
    } while (sub_00085430(&x, &y, g) != -1);
    sub_00053740();
}

/* 0x00085930: reset the grid g: wait for 0x000EE240, then for every cell
   except column 8 run 0x000ED600, 0x000ED560 and 0x000ED4F0 (one pass each)
   on the cell and its links.
   calls 0x000853B0 and 0x00085430 with EDI=g */
void r6f_GridReset(void *g)
{
    int x = -1, y = -1, k = -1;
    int r;
    r6f_StubAD090(0, 0);
    while (!sub_000EE240())
        ;
    sub_000853B0(&x, &y, g);
    do {
        if (x != 8) {
            sub_000ED600(x);
            for (r = sub_000EDCB0(x, y, &k); r != -1; r = sub_000EDCB0(x, y, &k))
                sub_000ED600(r);
        }
    } while (sub_00085430(&x, &y, g) != -1);
    sub_000853B0(&x, &y, g);
    do {
        if (x != 8) {
            sub_000ED560(x);
            for (r = sub_000EDCB0(x, y, &k); r != -1; r = sub_000EDCB0(x, y, &k))
                sub_000ED560(r);
        }
    } while (sub_00085430(&x, &y, g) != -1);
    sub_000853B0(&x, &y, g);
    do {
        if (x != 8) {
            sub_000ED4F0(x);
            for (r = sub_000EDCB0(x, y, &k); r != -1; r = sub_000EDCB0(x, y, &k))
                sub_000ED4F0(r);
        }
    } while (sub_00085430(&x, &y, g) != -1);
}

/* 0x000862A0: the four grid passes of 0x000856F0/0x00085820 over an explicit
   list of cells instead of the whole grid. */
void r6f_CellListSettle(R6fCellList *l)
{
    int i, r, k;
    R6fCell *c;
    sub_00053710(4);
    for (i = 0, c = l->cells; i < l->count; i++, c++) {
        sub_000ED4C0(c->x);
        for (r = sub_000EDCB0(c->x, c->y, &k); r != -1; r = sub_000EDCB0(c->x, c->y, &k))
            sub_000ED4C0(r);
    }
    for (i = 0, c = l->cells; i < l->count; i++, c++) {
        while (sub_000ED520(c->x, c->y))
            ;
        for (r = sub_000EDCB0(c->x, c->y, &k); r != -1; r = sub_000EDCB0(c->x, c->y, &k)) {
            while (sub_000ED520(r, k))
                ;
        }
    }
    for (i = 0, c = l->cells; i < l->count; i++, c++) {
        sub_000ED590(c->x, c->y);
        for (r = sub_000EDCB0(c->x, c->y, &k); r != -1; r = sub_000EDCB0(c->x, c->y, &k))
            sub_000ED590(r, k);
    }
    for (i = 0, c = l->cells; i < l->count; i++, c++) {
        sub_000ED5D0(c->x);
        for (r = sub_000EDCB0(c->x, c->y, &k); r != -1; r = sub_000EDCB0(c->x, c->y, &k))
            sub_000ED5D0(r);
    }
    sub_00053740();
}

/* 0x00086460: reset a list of cells: 0x00033BF0(c, -1) on every cell and
   link, wait for 0x000EE240, then the 0x000ED600, 0x000ED560 and 0x000ED4F0
   passes of 0x00085930. */
void r6f_CellListReset(R6fCellList *l)
{
    int i, r, k;
    R6fCell *c;
    for (i = 0, c = l->cells; i < l->count; i++, c++) {
        sub_00033BF0(c->x, -1);
        for (r = sub_000EDCB0(c->x, c->y, &k); r != -1; r = sub_000EDCB0(c->x, c->y, &k))
            sub_00033BF0(r, -1);
    }
    while (!sub_000EE240())
        ;
    for (i = 0, c = l->cells; i < l->count; i++, c++) {
        sub_000ED600(c->x);
        for (r = sub_000EDCB0(c->x, c->y, &k); r != -1; r = sub_000EDCB0(c->x, c->y, &k))
            sub_000ED600(r);
    }
    for (i = 0, c = l->cells; i < l->count; i++, c++) {
        sub_000ED560(c->x);
        for (r = sub_000EDCB0(c->x, c->y, &k); r != -1; r = sub_000EDCB0(c->x, c->y, &k))
            sub_000ED560(r);
    }
    for (i = 0, c = l->cells; i < l->count; i++, c++) {
        sub_000ED4F0(c->x);
        for (r = sub_000EDCB0(c->x, c->y, &k); r != -1; r = sub_000EDCB0(c->x, c->y, &k))
            sub_000ED4F0(r);
    }
}
