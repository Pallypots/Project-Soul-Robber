/* Area r1f, group 10: movie stream loaders 0x000507D0..0x00050F00. Names inferred. */
#include "r1f.h"

/* 0x000507D0: start reading part A of the current movie into the caller's
   buffer (or a new one) and make it the current slot. */
int r1f_MovieLoadA(void)
{
    void *buf = r1e_mArg3E0DC4;
    R1fMovie *m = &r1e_movies2C8900[r1e_mId3E0DBC];
    int fd, size;
    void *dst;
    if (buf == 0)
        buf = sub_00053AB0(m->sizeA, 0, 0xBA2);
    m->buf = buf;
    r1e_m3E0DC8 = buf;
    sub_001A8490(a50_streamHandle, m->pos, 0);
    size = m->sizeA;
    dst = m->buf;
    fd = a50_streamHandle;
    sub_00102FA0(0);
    sub_001A8410(fd, dst, size);
    m->mode = 1;
    if (r1e_mId3E0DBC >= 0 && r1e_mId3E0DBC < 0x21E)
        a30_curSlot = &r1e_movies2C8900[r1e_mId3E0DBC];
    return 0;
}

/* 0x00050F00: start reading part B of the current movie into the caller's
   buffer (or a new one) and make it the current slot. */
int r1f_MovieLoadB(void)
{
    void *buf = r1e_mArg3E0DC4;
    R1fMovie *m = &r1e_movies2C8900[r1e_mId3E0DBC];
    int fd, size;
    void *dst;
    if (buf == 0)
        buf = sub_00053AB0(m->sizeB, 0, 0xCFE);
    m->buf = buf;
    r1e_m3E0DC8 = buf;
    sub_001A8490(a50_streamHandle, m->pos, 0);
    size = m->sizeB;
    dst = m->buf;
    fd = a50_streamHandle;
    sub_00102FA0(0);
    sub_001A8410(fd, dst, size);
    m->mode = 2;
    if (r1e_mId3E0DBC >= 0 && r1e_mId3E0DBC < 0x21E)
        a30_curSlot = &r1e_movies2C8900[r1e_mId3E0DBC];
    return 0;
}

/* 0x00050440: open the movie archive, read its header and directory and
   fill in each named movie's part sizes and file offset.
   calls 0x0004F8E0 with EDI=entry name */
int r1f_MovieArchiveOpen(void)
{
    int fd, size, i;
    R1fArcEnt *dir, *e;
    R1fMovie *m;
    a50_streamHandle = sub_001A8210(r1e_m3E0DC0, 1);
    sub_001A8490(a50_streamHandle, 0, 0);
    fd = a50_streamHandle;
    sub_00102FA0(0);
    sub_001A8410(fd, &r1f_hdr3E0D90, 0x20);
    r1f_dirSize3E0D6C = r1f_hdr3E0D90.size;
    r1f_dir3E0D70 = (R1fArcEnt *)sub_00053AB0(r1f_hdr3E0D90.size, 0, 0xAFA);
    r1f_dirCount3E0D74 = r1f_hdr3E0D90.count;
    sub_001A8490(a50_streamHandle, 0, 0);
    size = r1f_dirSize3E0D6C;
    dir = r1f_dir3E0D70;
    fd = a50_streamHandle;
    sub_00102FA0(0);
    sub_001A8410(fd, dir, size);
    for (i = 0; i < r1f_dirCount3E0D74; i++) {
        e = &r1f_dir3E0D70[i + 1];
        m = sub_0004F8E0((const char *)e->name);
        m->sizeA = e->size;
        m->pos = e->pos;
        sub_001A8490(a50_streamHandle, m->pos, 0);
        fd = a50_streamHandle;
        sub_00102FA0(0);
        sub_001A8410(fd, &r1f_hdr3E0D90, 0x20);
        m->sizeB = r1f_hdr3E0D90.size;
        m->buf = 0;
        m->mode = 0;
    }
    return 0;
}

/* 0x00050B60: read part A of the current movie in 256 KB chunks into the
   caller's buffer (or a new one) and make it the current slot. */
int r1f_MovieLoadChunked(void)
{
    R1fMovie *m = &r1e_movies2C8900[r1e_mId3E0DBC];
    int chunks = m->sizeA / 0x40000 + 1;
    void *buf = r1e_mArg3E0DC4;
    int i, off, len, pos, fd;
    char *dst;
    if (buf == 0)
        buf = sub_00053AB0(m->sizeA, 0, 0xC61);
    m->buf = buf;
    r1e_m3E0DC8 = buf;
    for (i = 0, off = 0; i < chunks; i++, off += 0x40000) {
        dst = (char *)m->buf + off;
        pos = m->pos + off;
        if (i == chunks - 1) {
            len = m->sizeA - off;
            if (len < 0)
                len = m->sizeA;
        } else {
            len = 0x40000;
        }
        sub_001A8490(a50_streamHandle, pos, 0);
        fd = a50_streamHandle;
        sub_00102FA0(0);
        sub_001A8410(fd, dst, len);
    }
    m->mode = 1;
    if (r1e_mId3E0DBC >= 0 && r1e_mId3E0DBC < 0x21E)
        a30_curSlot = &r1e_movies2C8900[r1e_mId3E0DBC];
    return 0;
}
