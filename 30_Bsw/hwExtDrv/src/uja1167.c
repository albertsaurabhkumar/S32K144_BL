#include "uja1167.h"
#include "spi.h"

#define DUMMY_BYTE 0x00
#define NORMAL_MODE 0x07

uint16_t uja1167_GetID(){
    uint16_t tempData;
    uint8_t cmd = IDFCN << 1 | 0x1;
    tempData = cmd << 8 | DUMMY_BYTE;
    tempData = SPI_TxRxHalfWord(LPSPI0,tempData);
    return tempData;
}

uint16_t uja1167_GetStatus(){
    uint16_t tempData;
    uint8_t cmd = MAINSTS << 1 | 0x1;
    tempData = cmd << 8 | DUMMY_BYTE;
    tempData = SPI_TxRxHalfWord(LPSPI0,tempData);
    return tempData;
}

uint16_t uja1167_GetMode(){
    uint16_t tempData;
    uint8_t cmd = MODCTL << 1 | 0x1;
    tempData = cmd << 8 | DUMMY_BYTE;
    tempData = SPI_TxRxHalfWord(LPSPI0,tempData);
    return tempData;
}

uint16_t uja1167_SetMode(){
    uint16_t tempData;
    uint8_t cmd = MODCTL << 1 & 0xFE;
    tempData = cmd << 8 | NORMAL_MODE;
    tempData = SPI_TxRxHalfWord(LPSPI0,tempData);
    return tempData;
}