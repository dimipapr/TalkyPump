/*
 * usart.c
 *
 * Created: 22/7/2020 23:17:36
 *  Author: Jims
 */ 

#include "usart.h"

volatile uint8_t UAF = 0x00;	//USART FLAGS



ISR(USART_RX_vect){
	uint8_t tmp;
	tmp = UDR0;
	if(GET_BIT(UAF,SOFTWARE_FLOW_CONTROL_ENABLED)){
		if(GET_BIT(UAF,PAUSE_TRANSMIT_REQUESTED))USART_transmitc(XOFF);//resend xoff if he doesnt get it with the 1st
		if(tmp == XOFF){
			SET_BIT(UAF,PAUSE_TRANSMIT_REQUESTED);
			}else if(tmp == XON){
			CLEAR_BIT(UAF,PAUSE_TRANSMIT_REQUESTED);
		}
		else if(tmp == EOC2){
			if( (receiveBufferPos>2) && (receiveBuffer[receiveBufferPos-1] == EOC1) ){
				//valid termination sequence
				USART_transmitc(XOFF);
				receiveBuffer[receiveBufferPos-1] = '\0';
				parseReceivedCommand();
			}
			USART_flushBuffer();
		}else{
			if(receiveBufferPos != receiveBufferSize){
				receiveBuffer[receiveBufferPos++] = tmp;
			}else{
				USART_flushBuffer();
			}
		}
	}else{
		if(tmp == EOC2){
			if( (receiveBufferPos>0) && (receiveBuffer[receiveBufferPos-1] == EOC1) ){
				//valid termination sequence
				receiveBuffer[receiveBufferPos-1] = '\0';
				parseReceivedCommand();
				USART_flushBuffer();
			}
		}else{
			if(receiveBufferPos != receiveBufferSize){
				receiveBuffer[receiveBufferPos++] = tmp;
			}else{
				USART_flushBuffer();
			}
		}
	}
}
void USART_init(unsigned int ubrr){
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);//enable receiver, transmiter, receive complete interrupt
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);//frame format: 8d-0p-2s
	USART_flushBuffer();
	
}
void USART_flushBuffer(void){
	receiveBufferPos = 0;
	receiveBuffer[0] = 0x00; 
}
uint8_t USART_transmitc(char c){
	//if(GET_BIT(UAF,PAUSE_TRANSMIT_REQUESTED))return 0;
	while(!(UCSR0A & (1<<UDRE0))); //wait for transmit buffer to empty
	UDR0 = c; //put data to buffer
	return 1;
}
uint8_t USART_transmits(char *msg){//MSG MUST BE NULL TERMINATED!!!!
	uint8_t i=0;
	//uint8_t j = MAX_TRANSMIT_REPETITIONS;
	while(msg[i]!='\0'){
		USART_transmitc(msg[i++]);
		//if(USART_transmitc(msg[i++]) == 0){
			//i=0;
			//if(j-- == 0)return 0;
			//_delay_ms(200);
		//}
	}
	return 1;
}
uint8_t USART_ntransmits(char *str, uint8_t length){
	uint8_t i=0;
	//uint8_t j = MAX_TRANSMIT_REPETITIONS;
	for (i=0;i<length;i++)
	{
		USART_transmitc(str[i]);
		//if(USART_transmitc(str[i])==0)
		//{
			//i=0;
			//if(j-- == 0)return 0;
			//_delay_ms(200);
		//}
	}return 1;
}
void USART_comdProccessed(){
	USART_flushBuffer();
	if(GET_BIT(UAF,SOFTWARE_FLOW_CONTROL_ENABLED))USART_transmitc(XON);
}
