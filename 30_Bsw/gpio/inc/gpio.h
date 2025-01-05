#ifndef GPIO_H
#define GPIO_H

#include "common.h"

typedef enum GPIO_PORT_t {
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E
} GPIO_PORT_t;

typedef enum {
PIN0=0,PIN1,PIN2,
PIN3,PIN4,PIN5,
PIN6,PIN7,PIN8,
PIN9,PIN10,PIN11,
PIN12,PIN13,PIN14,
PIN15,PIN16,PIN17,
PIN18,PIN19,PIN20,
PIN21,PIN22,PIN23,
PIN24,PIN25,PIN26,
PIN27,PIN28,PIN29,
PIN30,PIN31
} GPIO_PIN_t;

typedef struct {
    GPIO_Type * gpio;
    GPIO_PIN_t pin;
} GPIO_PORTPIN_t;



typedef enum {
    SPI0,
    SPI1,
    ADC_1
} PERI;

void ToggleGPIO(GPIO_Type * const GPIOAddr, GPIO_PIN_t Pin);
void SetGPIO(GPIO_Type * const GPIOAddr,GPIO_PIN_t Pin);
void ClearGPIO(GPIO_Type * const GPIOAddr,GPIO_PIN_t Pin);
void DataDirectionGPIO(GPIO_Type * const GPIOAddr,GPIO_PIN_t Pin);;
void DataOutGPIO(GPIO_Type * const GPIOAddr,uint32_t Data);

#endif