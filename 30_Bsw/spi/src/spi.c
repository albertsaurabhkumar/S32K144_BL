#include "common.h"
#include "spi.h"

/** SPI1 PINS **/
/* MISO - PD1  */
/* MOSI - PE0  */
/* SCLK - PD0  */
/* CSB  - PD3  */
/* RSTB - PD15 */
/***************/

/** SPI0 PINS **/
/* MOSI - PB1  */
/* MISO - PB3  */
/* SCLK - PB2  */
/* CSB  - PB0  */
/***************/

/* Declare Variables Starts Here  */

const SPIConfig_t spiConfig[SPI_INSTANCES] = {
    
    /* LPSPI-0 Configuration*/
    {
      .SPI = SPI0,
      .SPI_ADD = LPSPI0,
      .Spi_Pins.CSB = {
                    .gpio = PTB,
                    .pin  = PIN0
                  },
      .Spi_Pins.MOSI = {
                    .gpio = PTB,
                    .pin  = PIN1
                  },
      .Spi_Pins.SCK = {
                    .gpio = PTB,
                    .pin  = PIN2
                  },
      .Spi_Pins.MISO = {
                    .gpio = PTB,
                    .pin  = PIN3
                  },
      .FrameSize = 15,
      .Master = true,
      .CLKPHASE = true,
      .CLKPOLARITY = false,
      .CLKDIV = 3
    },

    /* LPSPI-1 Configuration*/
    {
      .SPI = SPI1,
      .SPI_ADD = LPSPI1,
      .Spi_Pins.CSB = {
                    .gpio = PTD,
                    .pin  = PIN3
                  },
      .Spi_Pins.MOSI = {
                    .gpio = PTE,
                    .pin  = PIN0
                  },
      .Spi_Pins.SCK = {
                    .gpio = PTD,
                    .pin  = PIN0
                  },
      .Spi_Pins.MISO = {
                    .gpio = PTD,
                    .pin  = PIN1
                  },
      .FrameSize = 15,
      .Master = true,
      .CLKPHASE = true,
      .CLKPOLARITY = false,
      .CLKDIV = 4
    }
};

/* Declare Variables Ends Here  */

void SPI_GetVersion(uint32_t* version) {
     *version = LPSPI_VERID_FEATURE(LPSPI0->VERID)|LPSPI_VERID_MINOR(LPSPI0->VERID)|LPSPI_VERID_MAJOR(LPSPI0->VERID);
}

void SPI_GetFIFOSize(uint32_t* version) {
     *version = LPSPI_PARAM_TXFIFO(LPSPI0->PARAM)|LPSPI_PARAM_RXFIFO(LPSPI0->PARAM);
}

void SPI_FlushFIFOs() {
     LPSPI0->CR |= LPSPI_CR_RRF_MASK | LPSPI_CR_RTF_MASK;
}

void SPI_GetStatus(uint32_t* status) {
     *status = (uint32_t)LPSPI0->SR;
}

STD_RETYPE SPI_Init(const SPIConfig_t* spi) {
    if(spi != NULL) {
        CLK_Enable(spi->SPI);
        
        DataDirectionGPIO(spi->Spi_Pins.CSB.gpio,spi->Spi_Pins.CSB.pin);            /* Chip Select Pin */
        DataDirectionGPIO(spi->Spi_Pins.MOSI.gpio,spi->Spi_Pins.MOSI.pin);          /* Serial Out Pin (MOSI) */
        DataDirectionGPIO(spi->Spi_Pins.SCK.gpio,spi->Spi_Pins.SCK.pin);            /* Serial Clock Signal */
        if(spi->SPI == SPI1) {
          DataDirectionGPIO(PTD,PIN15);            /* Set as output pin for HSD Swich device */
        }
        
        PORT_SpiPins(spi->SPI);                                                     /* Enable the AF for the SPI pins */

        /*****************************Congif the SPI*********************************/

        spi->SPI_ADD->CFGR1 |= LPSPI_CFGR1_MASTER(spi->Master);                     /* Config SPI0 as master */  

        spi->SPI_ADD->TCR = LPSPI_TCR_FRAMESZ(spi->FrameSize)|LPSPI_TCR_CPHA(spi->CLKPHASE)
                  |LPSPI_TCR_PRESCALE(spi->CLKDIV)|LPSPI_TCR_CPOL(spi->CLKPOLARITY); /* No of bits per frame */
    
        spi->SPI_ADD->CCR |= LPSPI_CCR_SCKPCS(2)|LPSPI_CCR_PCSSCK(2)
                  |LPSPI_CCR_DBT(2)|LPSPI_CCR_SCKDIV(4);                            /* Config the CCR register */
    
        spi->SPI_ADD->FCR = LPSPI_FCR_TXWATER(3);                                   /* Set the watermark for the SPI */

        spi->SPI_ADD->CR |= LPSPI_CR_MEN(1)|LPSPI_CR_DBGEN_MASK;                    /* Enable the SPI in Debug Mode */
        
        return OK;
    } else {
        return NOT_OK;
    }
}

void SPI_Reset() {
    SPI_FlushFIFOs();
    LPSPI0->CR = LPSPI_CR_RST_MASK;
    LPSPI0->CR = (uint32_t) 0x0;
}

void SPI_Disable() { 
    LPSPI0->CR &= ~LPSPI_CR_MEN(1);                                             /* Enable the SPI */
}

uint8_t SPI_IsBusy() {
    return ((LPSPI0->SR & LPSPI_SR_MBF_MASK) >> LPSPI_SR_MBF_SHIFT); 
}

uint16_t SPI_TxRxHalfWord(volatile LPSPI_Type * spi, uint16_t data) {
    uint16_t recieve = 0;
    /* Tx */
    while((spi->SR & LPSPI_SR_TDF_MASK)>>LPSPI_SR_TDF_SHIFT==0);             /* Wait for Tx FIFO available */
    spi->TDR = data;                                                         /* Transmit data */

    /* Rx */
    while((spi->SR & LPSPI_SR_RDF_MASK)>>LPSPI_SR_RDF_SHIFT==0);             /* Wait at least one RxFIFO entry */
    recieve|= spi->RDR;                                                      /* Read received data */
    spi->SR |= LPSPI_SR_RDF_MASK|LPSPI_SR_TDF_MASK;                          /* Clear TDF and RDF flag */
    return recieve;                                                             /* Return received data */
}




