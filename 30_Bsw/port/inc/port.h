#ifndef PORT_H
#define PORT_H

#include "common.h"
#include "gpio.h"

void PortPCR(PORT_Type * const PortAddr,GPIO_PIN_t Pin);
void PORT_SpiPins(PERI );

#endif