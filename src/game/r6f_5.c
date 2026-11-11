/* Area r6f: model record lists around 0x0008FAF0-0x00090067 (r6f_5). Names inferred. */
#include "r6f.h"

/* 0x0008FAF0: format the name of a model record (stage id, model id and size) into buf.
   regargs: o=EAX buf=stack */
void r6f_ModelRecName(char *buf, R6fModelRec *o)
{
    int id, size;
    id = sub_000894D0(o->models ? sub_0001D220(o->models, 0) : 0);
    size = sub_001BBDD0(o->models ? sub_0001D220(o->models, 0) : 0);
    sub_0007E0A0(buf, r6f_fmt2707A0, ((R6eProcRef *)sub_00089390())->i04, id, size, id, size);
}

/* 0x0008FB80: free every model record of a list (handles, model, record). */
void r6f_ModelListFree(void *list)
{
    void *it, *end, *nx;
    R6fModelRec *rec;
    end = sub_0008F8F0(list);
    it = (void *)sub_000894D0(list);
    if (!sub_0008F960(&it, &end)) {
        do {
            nx = sub_0008F950(&it);
            rec = (R6fModelRec *)sub_0008FF80(&it);
            sub_0008F920(list);
            if (rec->h0C)
                sub_00020170(rec->h0C);
            if (rec->models) {
                sub_0001D030(sub_0007AA50(r6f_ctx42C8E4), rec->models);
                sub_00020170(rec->models);
            }
            a8c_Release102FA0(rec);
            sub_00053880(rec);
            it = nx;
        } while (!sub_0008F960(&it, &end));
    }
}

/* 0x00090020: set up the four growable key arrays (16-byte records, 4-byte keys). */
void r6f_KeyArraysInit(R6eArr *a)
{
    int i;
    for (i = 0; i < 4; i++) {
        a[i].keyLen = 4;
        a[i].data = (uint8_t *)sub_00053AB0(0x100, 0, 0x40);
        a[i].stride = 0x10;
        a[i].cap = 0x10;
        a[i].count = 0;
    }
}
