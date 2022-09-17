/*
 * adc.c
 *
 * Created: 18/6/2020 12:15:27
 *  Author: Jims
 */ 

#include "adc.h"
extern float pressure;
void ADC_Init(){
	ADMUX |= (1<<REFS0) | (1<<ADLAR); //AVcc ref, ADC0 channel, left adjusted result
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //adc clock = system clock / 128
	DIDR0 = 0b00111111; //disable adc pin digital input 
	
}

void ADC_StartFreeRunningMode(){
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADIE) | (1<<ADATE);
	
}

ISR(ADC_vect){
	unsigned short a;
	a=ADCH;
	float res = (a) * 4705.88; //pascal
	res = res / 100000;	//bar
	pressure = res;
}

