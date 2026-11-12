/* Area m1, file 14: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1TextArg {
    int32_t f00;
    const char *text04;        /* +0x04 */
} M1TextArg;
int sub_0005BBB0(int a);

/* 0x000DD880: 0x5BBB0(0) when the text is non-empty, else 0x5BBB0(-1); returns 0x2001. */
int m1_TextSelectDD880(M1TextArg *a)
{
    if (*a->text04 != 0) {
        sub_0005BBB0(0);
        return 0x2001;
    }
    sub_0005BBB0(-1);
    return 0x2001;
}
