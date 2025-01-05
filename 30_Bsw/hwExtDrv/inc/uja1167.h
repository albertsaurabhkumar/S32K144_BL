#ifndef UJA1167_H
#define UJA1167_H

#include "common.h"

uint16_t uja1167_GetID();
uint16_t uja1167_GetStatus();
uint16_t uja1167_GetMode();
uint16_t uja1167_SetMode();

typedef enum UJA1167_CMDS {
    WDGCTL   = 0x00,                         /*Watchdog control */
    MODCTL   = 0x01,                         /*Mode control */
    MAINSTS  = 0x03,                         /*Main status */
    SYSEVEN  = 0x04,                         /*System event enable */
    WDGSTS   = 0x05,                         /*Watchdog status */
    MEM0     = 0x06,                         /*Memory 0 GPM[7:0]*/
    MEM1     = 0x07,                         /*Memory 1 GPM[15:8]*/
    MEM2     = 0x08,                         /*Memory 2 GPM[23:16]*/
    MEM3     = 0x09,                         /*Memory 3 GPM[31:24]*/
    LKCTL    = 0x0A,                         /*Lock control*/
    V1CTL    = 0x10,                         /*V1 and INH/VEXT control */
    SUPSTS   = 0x1B,                         /*Supply status */
    SUPEVEN  = 0x1C,                         /*Supply event enable */
    CANCTL   = 0x20,                         /*CAN control */
    TRCVSTS  = 0x22,                         /*Transceiver status */
    TRCVEVEN = 0x23,                         /*Transceiver event enable*/
    WUPINSTS = 0x4B,                         /*WAKE pin status */
    WUPINEN  = 0x4C,                         /*WAKE pin enable */
    GLEVSTS  = 0x60,                         /*Global event status */
    SYSESTS  = 0x61,                         /*System event status */
    SUPESTS  = 0x62,                         /*Supply event status*/
    TRCVEST  = 0x63,                         /*Transceiver event status */
    WUPINST  = 0x64,                         /*WAKE pin event status*/
    MTPNVST  = 0x70,                         /*MTPNV status*/
    STUPCTL  = 0x73,                         /*Startup control*/
    SBCCFG   = 0x74,                         /*SBC configuration control*/
    MTPNVCTL = 0x75,                         /*MTPNV CRC control*/
    IDFCN    = 0x7E,                         /*Identification*/
} UJA1167_CMDS;

#endif