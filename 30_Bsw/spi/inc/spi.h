#ifndef SPI_H
#define SPI_H

#include "gpio.h"
#include "port.h"
#include "clock.h"

#define SPI_INSTANCES 2

/* Define Datatypes for SPI */

typedef struct {
    GPIO_PORTPIN_t MISO;
    GPIO_PORTPIN_t MOSI;
    GPIO_PORTPIN_t CSB;
    GPIO_PORTPIN_t SCK;
} SPIPins_t;

typedef struct {
    /* configuration for the SPI */
    PERI SPI;
    LPSPI_Type* SPI_ADD;
    SPIPins_t Spi_Pins;
    uint8_t FrameSize;
    bool Master;
    bool CLKPHASE;
    bool CLKPOLARITY;
    bool CLKDIV;
} SPIConfig_t;


/* Functions prototype for SPI */

void SPI_GetVersion(uint32_t*);
void SPI_GetFIFOSize(uint32_t*);
void SPI_Reset();
void SPI_Disable();
void SPI_GetStatus(uint32_t *);
STD_RETYPE SPI_Init(const SPIConfig_t *);
uint8_t SPI_IsBusy();
uint16_t SPI_TxRxHalfWord(volatile LPSPI_Type *, uint16_t );
void SPI_FlushFIFOs();

#endif