#include "hsd6500.h"
#include "spi.h"

#define READ 0
#define WRITE 1

static bool TxToggleFlag;

uint16_t hsd6500_TxRx(uint8_t cmd, uint16_t data, bool RW) {
    if(RW) {
        data = ((cmd << 12) & 0xF000) | (data & 0x07FF) | ((!TxToggleFlag << 11) & 0x0800) ;
        data = SPI_TxRxHalfWord(LPSPI1, data);
    } else {
        data = ((cmd << 12) & 0xF000) | (data & 0x0FFF);
        data = SPI_TxRxHalfWord(LPSPI1, data);
    }
    return data;
}

uint16_t hsd6500_Init(){
    uint16_t tempData;
    ClearGPIO(PTD, PIN15);                  /* Enable pin for HSD Swich device */
    SetGPIO(PTD, PIN15);                  /* Enable pin for HSD Swich device */
    //DataOutGPIO(PTD, (uint32_t) 1 << PIN15);                  /* Enable pin for HSD Swich device */

    /* tempData = hsd6500_TxRx(0xF,0x0,WRITE);      test mode */
    tempData = hsd6500_TxRx(0x0,0x0,WRITE);
    tempData = hsd6500_TxRx(0x1,0x0,WRITE);
    return tempData;
}

uint16_t hsd6500_GetID(){
    uint16_t tempData;
    tempData = hsd6500_TxRx(0x9,0x0,READ);
    return tempData;
}

uint16_t hsd6500_GetStatus(){
    uint16_t tempData;
    tempData = hsd6500_TxRx(0x7,0x0,READ);
    return tempData;
}