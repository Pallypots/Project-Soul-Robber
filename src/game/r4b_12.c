/* Area r4b: file slot helpers around 0x001A8330-0x001A8584 (r4b_12). Names inferred. */
#include "r4b.h"

/* 0x001A8330: close file slot idx (1..64); returns 0, or -1 on error. Stack args. */
int r4b_FileClose(int idx)
{
    R4bOverlapped *ov;
    if (idx <= 0 || idx > 0x40 || !r4b_g40B210[idx] || !sub_001BC6FD(r4b_g40B210[idx]))
        return -1;
    ov = &r4b_g40B320[idx];
    ov->pos = 0;
    ov->event = 0;
    ov->status = 0;
    ov->done = 0;
    ov->posHigh = 0;
    r4b_g40B210[idx] = 0;
    r4b_g40B318--;
    return 0;
}

/* 0x001A83A0: background read thread: read the pending request (up to five tries) and exit. Thread argument unused. */
void r4b_FileReadThread(void *arg)
{
    int i;
    int err;
    if (r4b_g40B864) {
        for (i = 0; i < 5; i++) {
            if (sub_001BCC81(r4b_g40B210[r4b_g40B868], r4b_g40B86C, r4b_g40B870, &r4b_g40B320[r4b_g40B868], 0))
                break;
            err = sub_001BC741();
            if (err == 0x26 || err == 0x3E5)
                break;
        }
        sub_001A7A70();
        r4b_g40B864 = 0;
    }
    sub_001BD345(0);
}

/* 0x001A8410: start a background read of size bytes from slot idx into buf; returns 0, or -1 on a bad slot. Stack args. */
int r4b_FileReadAsync(int idx, void *buf, uint32_t size)
{
    void *h;
    if (idx < 0 || idx > 0x40 || !r4b_g40B210[idx])
        return -1;
    if (r4b_g40B874)
        sub_001BC6FD(r4b_g40B874);
    r4b_g40B864 = 1;
    r4b_g40B868 = idx;
    r4b_g40B86C = buf;
    r4b_g40B870 = size;
    r4b_g40B874 = 0;
    h = sub_001BD49C(0, 0, r4b_FileReadThread, 0, 0, 0);
    r4b_g40B874 = h;
    sub_001BD23E(h, 2);
    return 0;
}

/* 0x001A8490: move the file position of slot idx (whence 0 set, 1 current, 2 end); returns off. Stack args. */
int r4b_FileSeek(int idx, int off, int whence)
{
    switch (whence) {
    case 0:
        r4b_g40B320[idx].pos = off;
        break;
    case 1:
        r4b_g40B320[idx].pos += off;
        break;
    case 2:
        r4b_g40B320[idx].pos = sub_001BCCD2(r4b_g40B210[idx], 0) + off;
        break;
    }
    return off;
}

/* 0x001A8500: poll a read on slot idx; returns 1 busy, 0 done, -1 error (the 15th error runs 0x001A7A70). Stack args (idx n). */
int r4b_FileReadPoll(int idx, uint32_t *n)
{
    R4bOverlapped *ov;
    int err;
    int r;
    if (r4b_g40B864)
        return 1;
    ov = &r4b_g40B320[idx];
    sub_001BC7AE(r4b_g40B210[idx], ov, n, 0);
    if (ov->status != 0x103)
        return 0;
    err = sub_001BC741();
    if (err == 0x26)
        return 0;
    if (err > 0x3E3 && err <= 0x3E5)
        return 1;
    r = -1;
    if (++r4b_g40B878 >= 0xF)
        sub_001A7A70();
    return r;
}
