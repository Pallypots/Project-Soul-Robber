/* Area r6h: texture animation table loader, tex_ex.c (r6h_7). Names inferred. */
#include "r6h.h"

/* 0x00075220: build an "@TXA" texture animation table from the text file
   (a, b) for texture handle tex: count the non-empty lines, allocate a header
   and one 16-byte frame per line (tag 0x23C), then read every non-empty line
   again: tokens 3 and 4 are the pixel position (divided by the texture width
   and height), token 7 the frame time. Returns 0 when the file has no lines. */
R6hTxa *r6h_TexAnimLoad(void *a, void *b, int tex)
{
    char *cur2, *cur1, *line;
    float frame, x, y, w, h;
    R6hTexSize *sz;
    R6hTxaFrame *f;
    R6hTxa *t;
    int count;

    sub_00013040();
    cur1 = cur2 = sub_000134C0(a, b);
    count = 0;
    for (line = sub_00012FA0(&cur1); line; line = sub_00012FA0(&cur1)) {
        if (sub_00013140(&line))
            count++;
    }
    if (count == 0)
        return 0;
    t = sub_00053AB0((count + 1) * 16, 0, 0x23C);
    t->count = count;
    t->magic[0] = '@';
    t->magic[1] = 'T';
    t->magic[2] = 'X';
    t->magic[3] = 'A';
    t->unk8 = 0;
    t->unkC = 0;
    f = t->frames;
    cur2 = sub_000134C0(a, b);
    sz = ((R6hTexEnt *)sub_001B9650(tex))->size;
    w = (float)sz->w;
    h = (float)sz->h;
    for (line = sub_00012FA0(&cur2); line; line = sub_00012FA0(&cur2)) {
        if (!sub_00013140(&line))
            continue;
        sub_00013140(&line);
        sub_00013140(&line);
        sub_001C7C70(sub_00013140(&line), r1b_fmtF, &x);
        sub_001C7C70(sub_00013140(&line), r1b_fmtF, &y);
        sub_00013140(&line);
        sub_00013140(&line);
        sub_001C7C70(sub_00013140(&line), r1b_fmtF, &frame);
        f->frame = frame;
        f->u = x / w;
        f->v = y / h;
        f->pad = 0;
        f++;
    }
    sub_00012F90();
    sub_000130C0();
    return t;
}
