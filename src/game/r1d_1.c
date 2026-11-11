/* Area r1d, group 1: packet templates, line reader and pools 0x00012010..0x00017DE0. Names inferred. */
#include "r1d.h"

/* 0x00012010: fill a sprite packet template with its default GS registers
   and the texture registers of texture `tex`. */
void r1d_SprTplInit(R1dSprTpl *p, int tex)
{
    R1dTex *t = sub_001B9650(tex);
    p->ent[0].id = 0x42;
    p->ent[0].lo = 0x44;
    p->ent[0].hi = 0;
    p->ent[1].id = 0x3B;
    p->ent[1].lo = 0x8080;
    p->ent[1].hi = 0x40;
    p->ent[2].id = 0x47;
    p->ent[2].lo = 0x5000D;
    p->ent[2].hi = 0;
    p->texLo = t->reg[0];
    p->texHi = t->reg[1];
    p->ent[3].id = 0x14;
    p->ent[3].lo = t->reg[2];
    p->ent[3].hi = t->reg[3];
    p->ent[4].id = 0x34;
    p->ent[4].lo = t->reg[4];
    p->ent[4].hi = t->reg[5];
    p->ent[5].id = 0x36;
    p->ent[5].lo = t->reg[6];
    p->ent[5].hi = t->reg[7];
    p->ent[6].id = 8;
    p->ent[6].lo = t->reg[8];
    p->ent[6].hi = t->reg[9];
    p->b = 0x80;
    p->g = 0x80;
    p->r = 0x80;
    p->a = 0x80;
    p->col80 = 0xFFFFF0;
    p->w84[7] = 0;
    p->w84[6] = 0;
    p->w84[5] = 0;
    p->w84[4] = 0;
    p->w84[3] = 0;
    p->w84[2] = 0;
    p->w84[1] = 0;
    p->w84[0] = 0;
}

/* 0x00012FA0: copy the next line of the current file into the line buffer
   (record 0's name), dropping ';' comments, then skip the line break.
   Returns the buffer, or 0 at the end of the file with an empty line. */
char *r1d_ReadLine(char **pp)
{
    int n = 0;
    int comment = 0;
    char c;
    char *line = r1d_files4326A0[0].name;
    if (**pp != '\r') {
        do {
            c = **pp;
            if (c == '\n') break;
            if (*pp >= r1d_files4326A0[0].end) break;
            if (*pp == 0) break;
            if (c == ';')
                comment = 1;
            else if (!comment)
                line[n++] = c;
            (*pp)++;
            if (n > 0x1FE) break;
        } while (**pp != '\r');
    }
    line[n] = 0;
    while (**pp == '\r' || **pp == '\n') {
        if (*pp >= r1d_files4326A0[0].end) goto at_end;
        if (*pp == 0) break;
        (*pp)++;
    }
    if (*pp < r1d_files4326A0[0].end) return line;
at_end:
    if (line[0] == 0) return 0;
    return line;
}

#define R1D_HW(a) (*(volatile uint32_t *)(uintptr_t)(a))

/* 0x00013A30: start a DMA transfer of qwc quadwords at addr once the
   channel is idle and the FIFO has room.  regargs: addr=stack qwc=EDX */
void r1d_DmaKick(uint32_t addr, uint32_t qwc)
{
    uint32_t tag, head, room;
    while (R1D_HW(0x1000D000) & 0x100)
        ;
    R1D_HW(0x1000D080) = addr;
    R1D_HW(0x1000D020) = qwc;
    qwc <<= 4;
    for (;;) {
        tag = R1D_HW(0x1000A030);
        r1d_dmaTag37B550 = tag;
        if (tag == 0) continue;
        head = R1D_HW(0x1000D010);
        r1d_dmaHead37B4A8 = head;
        if (tag == head)
            room = 0x100;
        else
            room = (tag - head) & 0xF0;
        r1d_dmaFree37B394 = room;
        if (room > qwc) break;
    }
    R1D_HW(0x1000D000) |= 0x100;
}

/* 0x00014DA0: relocate an animation bank in place ("ANB" -> "ANT"):
   turn its table offsets into pointers. Hangs on an unknown tag. */
void r1d_AnimBankFixup(R1dAnimBank *h)
{
    int i;
    uint32_t magic = h->m.magic;
    if (magic == 0x544E41) return;
    if (magic != 0x424E41) for (;;) ;
    h->elems = (char *)h + (intptr_t)h->elems;
    h->lists = (int32_t **)((char *)h + (intptr_t)h->lists);
    h->keys = (R1dKey **)((char *)h + (intptr_t)h->keys);
    h->m.tag[0] = 'A';
    h->m.tag[1] = 'N';
    h->m.tag[2] = 'T';
    h->m.tag[3] = 0;
    for (i = 0; i < h->n14; i++)
        h->lists[i] = (int32_t *)((char *)h + (intptr_t)h->lists[i]);
    for (i = 0; i < h->n18; i++)
        h->keys[i] = (R1dKey *)((char *)h + (intptr_t)h->keys[i]);
}

/* 0x00017DE0: find cmd[1] consecutive free pool slots, mark them used and
   step the request to its next command.  regargs: r=ESI */
void r1d_PoolAlloc(R1dPoolReq *r)
{
    uint32_t *cmd = r->cmd;
    uint32_t n;
    int i;
    R1dPoolSlot *s;
    for (i = 0; i < 0x80; i++) {
        s = &r1d_pool42CE80[i];
        if (s->flags & 1) continue;
        r->slots = s;
        for (n = 0; n < cmd[1]; n++, s++) {
            if (s->flags & 1) {
                i += n;
                break;
            }
        }
        if (n == cmd[1]) break;
    }
    for (n = 0; n < cmd[1]; n++)
        r->slots[n].flags |= 1;
    r->count = cmd[1];
    r->d08 = 0;
    r->cmd = r->cmd + 2;
    r->next = r->cmd;
}
