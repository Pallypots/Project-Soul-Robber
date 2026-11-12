/* Area m1, part i: scene render-buffer setup (types from r1c). Names inferred. */
#ifndef M1I_H
#define M1I_H
#include "r1c.h"
int sub_00022630(void *o, const void *path);
extern R1cRBuf *m1_rbA41CEB8, *m1_rbB41CEB0, *m1_rbC41CFF8, *m1_rbD41D000;
extern void    *m1_rbAData41CEBC, *m1_rbBData41D008, *m1_rbCData41CFFC, *m1_rbDData41E290;
extern const char m1_strChkaz2770A8[];       /* 0x002770A8 "host0:data/char/01/model/chkaz00_pk.txt" */
void m1_SetupBufsC6920(void);                /* 0x000C6920 */
void m1_SetupBufsC7B00(void);                /* 0x000C7B00 */
extern R1cRBuf *m1_rbE41D004, *m1_rbF41E294;
extern uint8_t *m1_rbEData41CEB4;            /* 0x0041CEB4 */
extern void    *m1_rbFData41E298;            /* 0x0041E298 */
extern const char m1_strPk277078[], m1_strPk277050[];
void m1_SetupBufsC72C0(void);                /* 0x000C72C0 */
#endif
