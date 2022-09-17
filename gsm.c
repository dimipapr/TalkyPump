/*
 * gsm.c
 *
 * Created: 23/7/2020 0:09:16
 *  Author: Jims
 */ 


#include "gsm.h"
#include "usart.h"
#include <avr/pgmspace.h>
#include <util/delay.h>

void GSM_command(char *cmd){ // cmd: null terminated string
	USART_transmits(cmd);
}



void GSM_command_delimeter(){
	USART_transmitc(EOC1);
	USART_transmitc(EOC2);
}

void GSM_powerToggle(){
	CLEAR_BIT(PORT(P_GSMPOWER),B_GSMPOWER);
	_delay_ms(1500);
	SET_BIT(PORT(P_GSMPOWER),B_GSMPOWER);
}

