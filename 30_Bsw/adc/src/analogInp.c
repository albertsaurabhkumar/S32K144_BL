#include "analogInp.h"

STD_RETYPE ADC_Init() {
    CLK_Enable(ADC_1);
    ADC1->CFG1 |= ADC_CFG1_MODE(1);                            /* Calibrate the ADC */
    ADC1->SC3 |= ADC_SC3_CAL(1);                            /* Calibrate the ADC */
    while(ADC1->SC3 & ADC_SC3_CAL(1));                      /* Wait for Calibration to complete */
    return OK;
}

uint16_t readADC(ADC_CH ch) {
    uint16_t adc_result=0;
    ADC1->SC1[0]&= ~ADC_SC1_ADCH_MASK;                              /* Clear prior ADCH bits */
    ADC1->SC1[0] = ADC_SC1_ADCH(ch);                                /* Initiate Conversion*/
    while((ADC1->SC1[0] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT);  /* Wait till complete */
    
    adc_result=ADC1->R[0];                                          /* For SW trigger mode, R[0] is used */
    return ((5000*adc_result)/0xFFF);                               /* Convert result to mv for 0-5V range */
}


uint16_t GetAnalogVal(AN_PINS pin) {
    switch(pin){
        case AN_PIN0:
            return(readADC(CH08));
            break;
        
        case AN_PIN1:
            return(readADC(CH04));
            break;

        case AN_PIN2:
            return(readADC(CH07));
            break;
    }
    return 0;       /* Never expecting to reach here */
}