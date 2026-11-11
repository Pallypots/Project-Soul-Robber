/* Area r1b, group 2: token parsing helpers 0x000131C0..0x00013370 (kept apart from their callees). Names inferred. */
#include "r1b.h"

/* 0x00013240: parse the next token as a float (0.0 when missing). */
float r1b_ParseFloat(char *s)
{
    float v = 0.0f;
    char *t = r1b_NextToken(&s);
    if (t) r1b_sscanf(t, r1b_fmtF, &v);
    return v;
}

/* 0x00013280: parse the next token as an int (0 when missing). */
int r1b_ParseInt(char *s)
{
    int v = 0;
    char *t = r1b_NextToken(&s);
    if (t == 0) return 0;
    r1b_sscanf(t, r1b_fmtD, &v);
    return v;
}

/* 0x000131C0: find the token equal to key; returns the text after it, or 0. */
char *r1b_FindKey(char *s, const char *key)
{
    char *t = r1b_NextToken(&s);
    while (t) {
        if (strcmp(key, t) == 0) return s;
        t = r1b_NextToken(&s);
    }
    return 0;
}

/* 0x00013370: return the last '/'-separated segment of a path.
   calls 0x00013300 with EDX=&path */
char *r1b_PathTail(char *path)
{
    char *t;
    r1b_name37B160[0] = 0;
    while ((t = r1b_NextSegment(&path)) != 0) strcpy(r1b_name37B160, t);
    return r1b_name37B160;
}


/* 0x000132C0: parse the next token as hexadecimal (0 when missing). */
int r1b_ParseHex(char *s)
{
    int v = 0;
    char *t = r1b_NextToken(&s);
    if (t == 0) return 0;
    r1b_sscanf(t, r1b_fmtX, &v);
    return v;
}
