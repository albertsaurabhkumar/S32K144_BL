#include "port.h"


void PortPCR(PORT_Type * const PortAddr,GPIO_PIN_t Pin) {
    PortAddr->PCR[Pin] = PORT_PCR_MUX(1);
}

void PORT_SpiPins(PERI peripheral) {
    if(peripheral == SPI0) {
        PORTB->PCR[PIN0] = PORT_PCR_MUX(3);        /*  CS  */
        PORTB->PCR[PIN1] = PORT_PCR_MUX(3);        /* MOSI */
        PORTB->PCR[PIN2] = PORT_PCR_MUX(3);        /* SCK  */
        PORTB->PCR[PIN3] = PORT_PCR_MUX(3);        /* MISO */
    } else if (peripheral == SPI1) {
        PORTD->PCR[PIN0] = PORT_PCR_MUX(3);        /* SCK */
        PORTD->PCR[PIN1] = PORT_PCR_MUX(3);        /* MISO */
        PORTD->PCR[PIN3] = PORT_PCR_MUX(3);        /* CSB  */
        PORTE->PCR[PIN0] = PORT_PCR_MUX(5);        /* MOSI */
    }
}