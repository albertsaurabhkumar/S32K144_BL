#ifndef HSD6500_H
#define HSD6500_H

#include "common.h"
/* HSD Control over SPI */
#endif

uint16_t hsd6500_TxRx(uint8_t, uint16_t , bool );
uint16_t hsd6500_Init();
uint16_t hsd6500_GetID();
uint16_t hsd6500_GetStatus();
