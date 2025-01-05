/*
**  Processor: S32K144
**  Author: Saurabh Kumar
**  GCC Version: 12.3
**  
**  Main program file for the GCC Compiler
*/

/*   PortPCR(PORTA,PIN11);
  PortPCR(PORTB,PIN4);
  DataDirectionGPIO(PTB,PIN4);
  DataDirectionGPIO(PTA,PIN11); */

#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "port.h"
#include "wdog.h"
#include "spi.h"
#include "uja1167.h"
#include "hsd6500.h"
#include "analogInp.h"

extern SPIConfig_t spiConfig[SPI_INSTANCES];

volatile PORT_Type * PortBView = PORTD;
volatile PORT_Type * PortEView = PORTE;

volatile uint16_t adcResult;

#define APP_ADD 0x00010004 /* After 64KB of Bootloader */
#define VectorAdd 0x00010000
#define NEW_MSP 0x20007000 /* Start of SRAM UPPER Bank */

typedef void (*voidFunc)(void);

uint32_t dlyCnt;
volatile uint32_t counter;

__attribute__ (( always_inline )) inline void __set_MSP(uint32_t topOfMainStack)
{
  __asm__ volatile ("MSR msp, %0\n" : : "r" (topOfMainStack));
}

void delay(uint32_t a) {
  while(a>0){
    a--;
    dlyCnt=a;
  }
}

void JumpToApp() {
  uint32_t* jumpAddress = (uint32_t*)(APP_ADD);
  uint32_t* jumpAdd = (uint32_t*)(*jumpAddress);
  voidFunc jmpFn = (voidFunc)jumpAdd;
  S32_SCB->VTOR = (uint32_t)(0x10000);
  __set_MSP(NEW_MSP);
  jmpFn();
}

int main(void) {
  STD_RETYPE ret;
  
  uint16_t rx_16bits;

  DisableWDOG();
  initClk();

  ret = SPI_Init(&spiConfig[SPI0]);
  ret = SPI_Init(&spiConfig[SPI1]);
  ret = ADC_Init();

/* SPI0 */
  rx_16bits = uja1167_GetID();
  rx_16bits = uja1167_GetStatus();

/* SPI1 */
  // rx_16bits = hsd6500_Init();
  rx_16bits = hsd6500_GetID();
  rx_16bits = hsd6500_GetStatus();
  

  PortPCR(PORTA,PIN11);
  DataDirectionGPIO(PTA,PIN11);

  while(1)
  {
    adcResult = GetAnalogVal(AN_PIN0);
    adcResult = GetAnalogVal(AN_PIN1);
    adcResult = GetAnalogVal(AN_PIN2);
    
    ToggleGPIO(PTA,PIN11);
    delay(950000);
  }

  return 0;
}