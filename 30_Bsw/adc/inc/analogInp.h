#ifndef ANALOGINP_H
#define ANALOGINP_H

#include "common.h"
#include "gpio.h"
#include "clock.h"

typedef enum {
  CH00,
  CH01,
  CH02,
  CH03,
  CH04,
  CH05,
  CH06,
  CH07,
  CH08,
  CH09,
  CH10,
  CH11,
  CH12,
  CH13,
  CH14,
  CH15,
} ADC_CH;

typedef enum {
  AN_PIN0,
  AN_PIN1,
  AN_PIN2
} AN_PINS;

STD_RETYPE ADC_Init();
uint16_t readADC(ADC_CH ch);
uint16_t GetAnalogVal(AN_PINS);

#endif