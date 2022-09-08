/*
 * usart.h
 *
 * Created: 22/7/2020 23:17:50
 *  Author: Jims
 *
 	Description:
	Interrupt Driven USART with software flow control
	XOFF is transmited when EOC1,EOC2 sequence is received
	User must call USART_cmdProccessed() when is done handling incoming data

 */ 

#ifndef USART_H_
#define USART_H_

#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "bitOperations.h"
#include "util/delay.h"

#ifndef EOC1
#error "EOC1 NOT DEFINED"
#endif

#ifndef EOC2
#error "EOC2 NOT DEFINED"
#endif

//constants
#define receiveBufferSize 80
#define MAX_TRANSMIT_REPETITIONS 10//the number of times to resend with 200ms interval when XOFF is received

#define XOFF	0x13
#define XON		0x11		

//UAF bits

#define PAUSE_TRANSMIT_REQUESTED		0//UAF
#define SOFTWARE_FLOW_CONTROL_ENABLED	1//UAF

//variables
char receiveBuffer[receiveBufferSize];
uint8_t receiveBufferPos;


//functions
void USART_init(unsigned int ubrr);
void USART_comdProccessed(void);// call this to resume receiving
void USART_flushBuffer(void);

uint8_t USART_transmitc(char c);
uint8_t USART_transmits(char *msg);
uint8_t USART_ntransmits(char *str, uint8_t length);

extern void parseReceivedCommand(void);









#endif /* USART_H_ */