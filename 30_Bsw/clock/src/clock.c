/*
**  Processor: S32K144
**  Author: Saurabh Kumar
**  GCC Version: 12.3
**  
**  C file for clock peripheral
*/
#include "clock.h"

void initClk() {
    PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock to PORT A */
    PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock to PORT B */
    PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock to PORT C */
    PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock to PORT D */
    PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock to PORT E */

    SCG->SIRCDIV = SCG_SIRCDIV_SIRCDIV2(2);
}

void CLK_Enable(PERI peripheral) {
    switch (peripheral)
    {
        case SPI0:
        PCC-> PCCn[PCC_LPSPI0_INDEX] |= PCC_PCCn_PCS(2); /* Select the Functional Clock as SIRCDIV2 (make sure its on from SCG) */
        PCC-> PCCn[PCC_LPSPI0_INDEX] |= PCC_PCCn_CGC(1); /* Enable clock to SPI0 */
        break;

        case SPI1:
        PCC-> PCCn[PCC_LPSPI1_INDEX] |= PCC_PCCn_PCS(2);    /* Select the Functional Clock as SIRCDIV2 (make sure its on from SCG) */
        PCC-> PCCn[PCC_LPSPI1_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clock to SPI1 */
        break;

        case ADC_1:
        PCC-> PCCn[PCC_ADC1_INDEX] |= PCC_PCCn_PCS(2);    /* Select the Functional Clock as SIRCDIV2 (make sure its on from SCG) */
        PCC-> PCCn[PCC_ADC1_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clock to SPI1 */
        break;
    }


    

}