/* Shared types for the HUD panel table in area m1 (a3c_tbl3DA4A8, rows of 0x2C bytes). */
#ifndef M1_PANEL_H
#define M1_PANEL_H
#include <stdint.h>

typedef struct M1PanelRow {
    int32_t  kind;          /* +0x00  0 = text panel, 1 = icon panel */
    uint8_t  unk04[0x2C - 0x04];
} M1PanelRow;

#endif
