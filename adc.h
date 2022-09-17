/*
 * adc.h
 *
 * Created: 18/6/2020 12:14:33
 *  Author: Jims
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_Init();
void ADC_StartFreeRunningMode();


#endif /* ADC_H_ */