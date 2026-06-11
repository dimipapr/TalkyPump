/*
 * main.c
 *
 * Created: 22/7/2020 23:04:42
 *  Author: Jims
 */ 
#include "config.h"
#include "bitOperations.h"
#include "usart.h"
#include "gsm.h"

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include <avr/pgmspace.h>






void init(void);
void IO_init(void);
void forceReset(uint8_t errCode);
void parseReceivedCommand(void);
void parseTxt(void);
uint8_t GSM_command_response(char *cmd, char *resp, uint8_t timeout/*(1-255* 0.1 seconds)*/,uint8_t repetitions); 
uint8_t setExpectedResponse(char *resp);
uint8_t GSM_init(void);
uint8_t GSM_Config(void);
uint8_t EEPROM_isValid(void);
uint8_t EEPROM_init(void);
void EEPROM_reset(void);
void EEPROM_update(void);
void EEPROM_validate(void);
uint8_t isValidNumber(char* number);
uint8_t isAdmin(char* number);
uint8_t isRegistered(char* number);
void startRelay(void);
void stopRelay(void);
void SMS_start(char* number);
void SMS_end(void);
uint8_t addControllingNumber(char* number);
uint8_t removeControllingNumber(char* number);
void stateReport();

volatile uint8_t mainF1 = MAINF1_INITIAL;
volatile uint8_t mainF2 = MAINF2_INITIAL;
volatile uint8_t mainF3 = MAINF3_INITIAL;
volatile uint8_t mainFP1 = MAINFP1_INITIAL;

char expectedResponse[EXPECTED_RESPONSE_SIZE];

uint8_t responseTimer,responseTimeout;

//indication LED
volatile uint8_t indLEDOnTime = 255; //0 - 255 = 0-8,4sec
volatile uint8_t indLEDCycleTime = 254;//0-255 = 0-8,4sec

volatile uint8_t tim0OvfIndTick;
volatile uint8_t tim0Ovf1;
volatile uint8_t tim0Ovf_1;
volatile uint8_t secCounter;
volatile uint8_t crossings;
volatile uint8_t tim0OvfSMSTick;

volatile uint8_t tim1OvfTick; 

uint8_t EEMEM EEValidationByte;
uint8_t EEMEM EEadminNo[10];
uint8_t EEMEM EEControlNums[50];
uint8_t EEMEM EEmainFP1;
uint8_t EEMEM EEValidationByte;
uint8_t EEMEM EEpsw[4];
uint8_t EEMEM EElastOpNumber[10];

uint8_t adminNo[10];
uint8_t controlNums[50];
uint8_t psw[4];
uint8_t callingNumber[10];
uint8_t lastOpNumber[10];
uint8_t rings;
uint8_t txt[32];


uint8_t state;






void disableWD(void) \
__attribute__((naked)) \
__attribute__((section(".init3")));
void disableWD(void)
{
	MCUSR = 0;
	wdt_disable();
}
int main(){
	state = INITIALISING;
	uint8_t tmp1=0,tmp2=0,tmp3=0,tmp4=0; //dont touch in isr
	uint8_t relChangeHits = 0,al1BreachHits = INPUTSENSITIVITY ,al2BreachHits = INPUTSENSITIVITY;
	
	init();
	indLEDCycleTime = 30;
	indLEDOnTime = 15;
	
	tim1OvfTick = 20; //~2.5mins
	
//wait for admin
	while(GET_BIT(mainFP1,ADMIN_FLAG)==0){
		wdt_reset();
		if(!GET_BIT(mainF2,POWER_STATE)){
			forceReset(ERR_POWER_DOWN);
		}
	}
	wdt_reset();
	tmp1 = INPUTSENSITIVITY;
	tmp2=0;
	tmp3=0;
	tmp4=0;
	do{
		if(!GET_BIT(PIN(P_RELAYSENSOR),B_RELAYSENSOR))tmp2++;
		if(GET_BIT(PIN(P_ALARM),B_ALARM1))tmp3++;
		if(GET_BIT(PIN(P_ALARM),B_ALARM2))tmp4++;
	}while(--tmp1>0);
	
	if((INPUTSENSITIVITY - tmp2)<(INPUTSENSITIVITY>>1) ){
		SET_BIT(mainFP1,RELAY_STATE);
		}else{
		CLEAR_BIT(mainFP1,RELAY_STATE);
	}
	if((INPUTSENSITIVITY - tmp3)<(INPUTSENSITIVITY>>1) ){
		SET_BIT(mainF2,ALARM1_STATE);
		}else{
		CLEAR_BIT(mainF2,ALARM1_STATE);
	}
	if((INPUTSENSITIVITY - tmp4)<(INPUTSENSITIVITY>>1) ){
		SET_BIT(mainF2,ALARM2_STATE);
		}else{
		CLEAR_BIT(mainF2,ALARM2_STATE);
	}
	SET_BIT(mainF1, EEPROM_UPDATE_PENDING);
	SET_BIT(mainF3,SMS_READY);
//main loop
	_delay_ms(1500);
	
	stateReport();
	indLEDOnTime = 1;
	indLEDCycleTime = 126;
	
	state = WORKING;
	while(1){
		wdt_reset();
		if(GET_BIT(mainF1,GSM_CALL_READY_DETECTED))
		{
			forceReset(ERR_GSM_REBOOT);
		}
	//eeprom Update
		if(GET_BIT(mainF1,EEPROM_UPDATE_PENDING)){
			EEPROM_update();
			sei();
		}
	//state report
		if(GET_BIT(mainF2,STATE_REPORT_PENDING)){
			stateReport();
		}
		if(!GET_BIT(mainF2,POWER_STATE)){ //anafora apo ISR_TIMER0
			cli();
			forceReset(ERR_POWER_DOWN);
		}
		if(GET_BIT(mainF3,NEW_SMS)){
			CLEAR_BIT(mainF3,NEW_SMS);
			_delay_ms(500);
			GSM_command(READ_SMS1);
			GSM_command_delimeter();
		}
		if(GET_BIT(mainF3,TXT_READY)){
			parseTxt();
			CLEAR_BIT(mainF3,NEW_SMS);
			CLEAR_BIT(mainF3,TXT_READY);
			CLEAR_BIT(mainF3,MASTER_SMS);
			SET_BIT(mainF3,SMS_READY);
			
		}
	//relay state read
		if(GET_BIT(PIN(P_RELAYSENSOR),B_RELAYSENSOR) == GET_BIT(mainFP1,RELAY_STATE)){
			relChangeHits ++;
			if(relChangeHits >= INPUTSENSITIVITY){
				_delay_ms(300);
				if(isValidNumber((char*)lastOpNumber)){
					SMS_start((char*)lastOpNumber);
					}else{
					SMS_start((char*)adminNo);
				}
				if(GET_BIT(PIN(P_RELAYSENSOR),B_RELAYSENSOR)){
					CLEAR_BIT(mainFP1,RELAY_STATE);
					USART_transmits("REL OFF");
				}else{
					SET_BIT(mainFP1,RELAY_STATE);
					USART_transmits("REL ON");
				}
				SMS_end();
				SET_BIT(mainF1,EEPROM_UPDATE_PENDING);
				relChangeHits = 0;
			}
		}else{
			relChangeHits = 0;
		}
	
	//alarms
		//alarm1
		if(GET_BIT(mainF2,ALARM1_FLAG))
		{
			if((PIN(P_ALARM)&(1<<B_ALARM1)) && !GET_BIT(mainF2,ALARM1_STATE) )
			{
				al1BreachHits--;
				if(al1BreachHits == 0)
				{
					if(isValidNumber((char*)lastOpNumber)){
						SMS_start((char*)lastOpNumber);
						}else{
						SMS_start((char*)adminNo);
					}
					USART_transmits("AL1 PARAVIASI");//anafora
					SMS_end();
					SET_BIT(mainF2,ALARM1_STATE);
				}
			}
			else
			{
				al1BreachHits = INPUTSENSITIVITY;
			}
		}
		if(GET_BIT(mainF2,ALARM2_FLAG) && !GET_BIT(mainF2,ALARM2_STATE) )
		{
			if(PIN(P_ALARM)&(1<<B_ALARM2))
			{
				al2BreachHits--;
				if(al2BreachHits == 0)
				{
					if(isValidNumber((char*)lastOpNumber)){
						SMS_start((char*)lastOpNumber);
						}else{
						SMS_start((char*)adminNo);
					}
					USART_transmits("AL2 PARAVIASI");//anafora
					SMS_end();
					SET_BIT(mainF2,ALARM2_STATE);
				}
			}else{
				al2BreachHits = INPUTSENSITIVITY;
			}
		}
	}
	return 0;
}
void init(){
	IO_init();
	USART_init(MYUBRR);
	//timer0 setup
	TCCR0B |= 0b00000101; // 1/1024 prescaler, ~33ms ovf @8MHz
	TIMSK0 |= (1<<TOIE0); //timer0 ovf interrupt enabled
	//timer1 setup
	TCCR1B |= 0b00000101; // 1/1024 prescaler, ~8,4sec ovf @8MHz
	TIMSK1 |= (1<<TOIE1);
	//zero cross monitor setup
	PCICR |= (1<<PCIE2);
	PCMSK2 |= (1<<PCINT20);
	sei(); //!!!!!!!!!!!!!!!!!!!!!!!!!!
	if(GSM_init()==0){
		//watchdog setup to reset early
		wdt_reset();
		WDTCSR |= (1<<WDCE)|(1<<WDE);
		WDTCSR =(1<<WDE)|(1<<WDP3)|(1<<WDP0);  //8s watchdog loop
		GSM_command(POWER_DOWN);
		GSM_command_delimeter();
		forceReset(ERR_GSM_INIT);
	}
	CLEAR_BIT(mainF1,GSM_CALL_READY_DETECTED);
	if(!EEPROM_init()){
		EEPROM_reset();
	}
	cli();
	//watchdog setup
	wdt_reset();
	WDTCSR |= (1<<WDCE)|(1<<WDE);
	WDTCSR = (1<<WDE)|(1<<WDP3)|(1<<WDP0);  //8s watchdog loop
	sei();
}
void IO_init(){
	DDR(P_RELAYCONTROL) |= (1<<B_RELAYSTART)|(1<<B_RELAYSTOP);
	DDR(P_GSMPOWER) |= (1<<B_GSMPOWER);
	PORT(P_GSMPOWER) |= (1<<B_GSMPOWER);
	DDR(P_INDICATION_LED) |= (1<<B_INDICATION_LED);
	PORT(P_INDICATION_LED) |= (1<<B_INDICATION_LED);
}
uint8_t EEPROM_init(){
	uint8_t tmp;
cli();																//interrupts disabled
	_delay_us(5);
	eeprom_busy_wait();
	tmp = eeprom_read_byte(&EEValidationByte);
	if(!EEPROM_isValid()){
		return 0;	
	}else
	{
		eeprom_busy_wait();
		eeprom_read_block((void*)psw,(const void*)EEpsw,4);
		mainFP1 = eeprom_read_byte(&EEmainFP1);
		if(GET_BIT(mainFP1,ADMIN_FLAG)==1)
		{
			eeprom_busy_wait();
			eeprom_read_block((void *)adminNo,(void *)EEadminNo,10);
			eeprom_busy_wait();
			eeprom_read_block((void *)lastOpNumber, (void *) EElastOpNumber,10);
			tmp = 5;
			do 
			{
				tmp--;
				if(GET_BIT(mainFP1,(CONTROLNO+tmp))){
					eeprom_busy_wait();
					eeprom_read_block((void*)(controlNums+tmp*10),(void *)(EEControlNums+tmp*10),10);
				}
			} while (tmp>0);	
		}
		return 1;
	}
}
void EEPROM_reset(){
cli();																//interrupts disabled
	_delay_us(5);
	memset((void*)adminNo,0x00,10);
	memset((void*)controlNums,0x00,50);
	memset((void*)lastOpNumber,0x00,10);
	memset((void*)psw,0x30,4); //password default "0000"
	mainFP1 = MAINFP1_INITIAL;
	EEPROM_update();
	EEPROM_validate();
	
}
void EEPROM_update(){
cli();																//interrupts disabled
	_delay_us(5);
	CLEAR_BIT(mainF1,EEPROM_UPDATE_PENDING);
	eeprom_busy_wait();
	eeprom_update_byte( &EEmainFP1, mainFP1);
	eeprom_busy_wait();
	//wdt_reset();
	eeprom_update_block((const void *)adminNo,(void *)EEadminNo,10);
	eeprom_busy_wait();
	eeprom_update_block((const void *)controlNums, (void *)EEControlNums, 50);
	eeprom_busy_wait();
	eeprom_update_block((const void *)lastOpNumber, (void *)EElastOpNumber,10);
	eeprom_busy_wait();
	eeprom_update_block((const void *)psw, (void *)EEpsw,4);
}
void EEPROM_validate(){
cli();																//interrupts disabled
	_delay_us(5);
	eeprom_busy_wait();
	eeprom_update_byte(&EEValidationByte, EEPROM_VALIDATION_BYTE);
}
uint8_t EEPROM_isValid(){
	uint8_t tmp;
cli();																//interrupts disabled
	_delay_us(5);
	eeprom_busy_wait();
	tmp = eeprom_read_byte(&EEValidationByte);
	return (tmp==EEPROM_VALIDATION_BYTE);
}
uint8_t GSM_init(){
	_delay_ms(5000);//bypass NORMAL POWER DOWN sent from GSM
		secCounter = 0;
		CLEAR_BIT(mainF1,GSM_COMMUNICATING);
		while(secCounter < 12){
			GSM_command("AT");
			GSM_command_delimeter();
			_delay_ms(200);
			if(GET_BIT(mainF1,GSM_COMMUNICATING)){
				secCounter = 0;
				while(!(!(secCounter<30)||GET_BIT(mainF1,GSM_CALL_READY_DETECTED)));//**
				if(GSM_Config()==0)return 0;
				break;
			}else if(secCounter == 10){
				GSM_powerToggle();
				secCounter = 0;
				while(!(!(secCounter<15)||GET_BIT(mainF1,GSM_CALL_READY_DETECTED)));
				if(GSM_Config()==0)return 0;
				break;
			}
		}
		CLEAR_BIT(mainF1,GSM_CALL_READY_DETECTED);
		return 1;
}
uint8_t GSM_Config(void){
	if(GSM_command_response("AT","OK",20,255) != RETVAL_SUCCESS)														return 0;
	if(GSM_command_response(DISABLE_ECHO,DISABLE_ECHO_RESPONSE,10,20)!= RETVAL_SUCCESS)									return 0;
	if(GSM_command_response(SMS_TXT_MODE,SMS_TXT_MODE_RESPONSE,10,20)!= RETVAL_SUCCESS)									return 0;
	if(GSM_command_response(ENABLE_CALL_RECOGNITION,ENABLE_CALL_RECOGNITION_RESPONSE,10,20)!= RETVAL_SUCCESS)			return 0;
	if(GSM_command_response(SET_FIXED_BAUD_38400,SET_FIXED_BAUD_38400_RESPONSE,10,20)!= RETVAL_SUCCESS)					return 0;
	if(GSM_command_response(ENABLE_SOFTWARE_FLOW_CONTROLL,ENABLE_SOFTWARE_FLOW_CONTROLL_RESPONSE,10,20)!= RETVAL_SUCCESS)return 0;
	if(GSM_command_response(SAVE_SETTINGS,SAVE_SETTINGS_RESPONSE,10,20)!= RETVAL_SUCCESS)								return 0;
	if(GSM_command_response(CALL_READY_CHECK,CALL_READY_RESPONSE,10,20)!= RETVAL_SUCCESS)								return 0;
	_delay_ms(2000);
	if(GSM_command_response(DELETE_ALL_SMS,DELETE_ALL_SMS_RESPONSE,10,40)!= RETVAL_SUCCESS)								return 0;
	return 1;
}
uint8_t GSM_command_response(char *cmd, char *resp, uint8_t timeout/*0.1sec, 25.5s max timeout @ timeout=0xFF*/,uint8_t repetitions)
{
	//NEEDS INTERRUPTS, SO DONT CALL FROM ISR, no?
	wdt_reset();
	if(repetitions>0){
		if(GET_BIT(mainF1,EXPECTING_RESPONSE))
		{
			return RETVAL_ALREADY_WAITING_FOR_RESPONSE;
		}
		while(repetitions > 0)
		{
			SET_BIT(mainF1, EXPECTING_RESPONSE);
			repetitions--;
			setExpectedResponse(resp);
			CLEAR_BIT(mainF1,EXPECTED_RESPONSE_RECEIVED);
			responseTimeout = timeout;
			responseTimer = 0;
			GSM_command(cmd);
			GSM_command_delimeter();
		
			while(!GET_BIT(mainF1,RESPONSE_TIMEOUT))
			{
				if(GET_BIT(mainF1,EXPECTED_RESPONSE_RECEIVED))
				{
					CLEAR_BIT(mainF1, EXPECTED_RESPONSE_RECEIVED);
					CLEAR_BIT(mainF1, EXPECTING_RESPONSE);
					return RETVAL_SUCCESS; //response received
				}
			}
			CLEAR_BIT(mainF1, EXPECTING_RESPONSE);
			CLEAR_BIT(mainF1,RESPONSE_TIMEOUT);
		}
		return RETVAL_TIMEOUT;// response timed out
	}else{
		return RETVAL_ZERO_REPETITIONS; // repetitions set to 0
	}
}
uint8_t setExpectedResponse(char *resp){
	if(strlen(resp)<EXPECTED_RESPONSE_SIZE){
		uint8_t i=0;
		while(resp[i]!='\0'){
			expectedResponse[i] = resp[i];
			i++;
		}
		expectedResponse[i] = resp[i];
		return 1;
	}
	return 0;
}
uint8_t addControllingNumber(char* number){
	uint8_t i;
	
	i=5;
	do 
	{
		i--;
		if(!GET_BIT(mainFP1,(CONTROLNO+i)))
		{//space found
			memcpy(controlNums+i*10,number,10);
			SET_BIT(mainFP1,(CONTROLNO+i));
			SET_BIT(mainF1,EEPROM_UPDATE_PENDING);
			return 1;
		}
	} while (i>0);
	return 0;
}
// called from usart.h
void parseReceivedCommand(){		//INTERRUPTS SHOULD BE DISABLED IN HERE!!!
	uint8_t i;
	SET_BIT(mainF1,GSM_COMMUNICATING);
	if( GET_BIT(mainF1,EXPECTING_RESPONSE) )
	{	
		if((strncmp(expectedResponse,receiveBuffer, strlen(expectedResponse))==0)){ 
			SET_BIT(mainF1,EXPECTED_RESPONSE_RECEIVED);
		}
	}
	if(strncmp(receiveBuffer,"OK",2)==0){
		
	}else if(strncmp(receiveBuffer,"ERR",3)==0)
	{
		
	}	
	else if(strncmp(receiveBuffer, "+CLIP", 5) == 0)
	{
		//save calling number
		i=10;
		do 
		{
			i--;
			callingNumber[i] = receiveBuffer[i+8];
		} while (i>0);
		if(GET_BIT(mainFP1,ADMIN_FLAG)){//admin registered
			if(isRegistered((char*)callingNumber)){
				rings++;
				if((rings >= RELAY_STOP_RINGS) && (GET_BIT(mainFP1,RELAY_STATE) ) ){
					rings = 0;
					memcpy((void*)lastOpNumber,(const void*) callingNumber, 10*sizeof(char));
					SET_BIT(mainF1, EEPROM_UPDATE_PENDING);
					USART_transmits("ATH\r\nATH\r\n");
					stopRelay();
				}
				else if((rings >= RELAY_START_RINGS) && !(GET_BIT(mainFP1,RELAY_STATE) ) ){
					rings = 0;
					memcpy((void*)lastOpNumber,(const void*) callingNumber, 10*sizeof(char));
					SET_BIT(mainF1, EEPROM_UPDATE_PENDING);
					USART_transmits("ATH\r\nATH\r\n");
					startRelay();
				}
			}else{
				rings = 0;
				GSM_command(HANG_UP);
				GSM_command_delimeter();
				memset((void*)callingNumber,0x00,10);
			}
		}else{//no admin registered
			rings ++;
			if(rings >= ADMIN_REGISTER_RINGS){
				//register new admin
				USART_transmits("ATH\r\nATH\r\n");
				memcpy((void*)adminNo,(const void*) callingNumber, 10*sizeof(char));
				memcpy((void*)lastOpNumber,(const void*) callingNumber, 10*sizeof(char));
				SET_BIT(mainFP1,ADMIN_FLAG);
				SET_BIT(mainF1, EEPROM_UPDATE_PENDING);
				rings = 0;
			}
		}
}else if (  GET_BIT(mainF3,MASTER_SMS) )
{
	wdt_reset();
	GSM_command(DELETE_ALL_SMS);
	GSM_command_delimeter();
	_delay_ms(1000);
	if((strncmp(receiveBuffer,(char*)psw,4 )==0)){
		CLEAR_BIT(mainF3,MASTER_SMS);
		memccpy(txt,receiveBuffer+4,'\0',31);
		txt[31]='\0';
		SET_BIT(mainF3,TXT_READY);
		
		}else if((strncmp(receiveBuffer,MASTER_DEFAULT,16 )==0)){
			sei();
			GSM_command_response(DELETE_ALL_SMS,DELETE_ALL_SMS_RESPONSE,10,20);
			cli();
			SET_BIT(mainF3,SMS_READY);
			CLEAR_BIT(mainF3,NEW_SMS);
			CLEAR_BIT(mainF3,NO_ADMIN_SMS);
			cli();
			eeprom_busy_wait();
			eeprom_update_byte(&EEValidationByte, 0xFF);
			USART_transmits("\r\nAT+CMGS=\"");
			USART_ntransmits((char* )adminNo,10);
			USART_transmits("\"\rEPANAFORA");
			_delay_ms(1500);
			USART_transmitc(0x1A);//Ctrl+Z
			//_delay_ms(1000);
			forceReset(ERR_ADMIN_DEFAULT_REQUEST);	
		}else{
			SET_BIT(mainF3,SMS_READY);
			wdt_reset();
		}
	
	CLEAR_BIT(mainF3,MASTER_SMS);
	CLEAR_BIT(mainF3,NEW_SMS);
	
}
else if(GET_BIT(mainF3,NO_ADMIN_SMS)){
	if((strncmp(receiveBuffer,MASTER_DEFAULT,16 )==0)){		
		SET_BIT(mainF3,SMS_READY);
		CLEAR_BIT(mainF3,NEW_SMS);
		CLEAR_BIT(mainF3,NO_ADMIN_SMS);
		cli();
		eeprom_busy_wait();
		eeprom_update_byte(&EEValidationByte, 0xFF);
		USART_transmits("\r\nAT+CMGS=\"");
		USART_ntransmits((char* )adminNo,10);
		USART_transmits("\"\rEPANAFORA");
		
		_delay_ms(1500);
		USART_transmitc(0x1A);//Ctrl+Z
		
		
		
		//_delay_ms(1000);
		forceReset(ERR_ADMIN_DEFAULT_REQUEST);
		
	}
	GSM_command(DELETE_ALL_SMS);
	GSM_command_delimeter();
	CLEAR_BIT(mainF3,NEW_SMS);
	CLEAR_BIT(mainF3,NO_ADMIN_SMS);
	SET_BIT(mainF3,SMS_READY);
	
}
	else if(strncmp(receiveBuffer,"NO CAR",6)==0){ //NO CARRIER
		if(rings>0){
			memcpy((void*)lastOpNumber,(const void*) callingNumber, 10*sizeof(char));
			SET_BIT(mainF1, EEPROM_UPDATE_PENDING);
			SET_BIT(mainF2,STATE_REPORT_PENDING);
			rings = 0;
		}
	}else if(strncmp(receiveBuffer,"Call R",6)==0){ //CALL READY
		SET_BIT(mainF1,GSM_CALL_READY_DETECTED);
	}else if(strncmp(receiveBuffer, "+CMTI",5) == 0 )
	{	
		if(GET_BIT(mainF3,SMS_READY))
		{
			SET_BIT(mainF3,NEW_SMS);
			CLEAR_BIT(mainF3,SMS_READY);
			tim0OvfSMSTick = 0x00;
		}else{
			GSM_command(DELETE_ALL_SMS);
			GSM_command_delimeter();
		}	
	}else if(strncmp(receiveBuffer,"+CMGR",5) == 0){
		i=10;
		do 
		{
			i--;
			callingNumber[i] = receiveBuffer[i+24];
		} while (i>0);
		if(isAdmin((char*)callingNumber))
		{
			//master sms
			SET_BIT(mainF3,MASTER_SMS);
		}else
		{ //non admin sms
			SET_BIT(mainF3,NO_ADMIN_SMS);
		}
	}
	USART_comdProccessed();
}
void parseTxt()
{
	uint8_t i;
	char tmpc[10];
	memset((void *)tmpc,0x00,10);
	if(strncmp((char*)txt,"+",1)==0)	//prosthiki arithmou
	{
		i=10;
		do 
		{
			i--;
			tmpc[i] = txt[i+1];
		} while (i>0);
		
		_delay_ms(500);
		USART_transmits("\r\nAT+CMGS=\"");
		USART_ntransmits((char* )adminNo,10);
		USART_transmits("\"\r");
		if(isValidNumber(tmpc))
		{
			if(isRegistered(tmpc))
			{
				USART_ntransmits(tmpc,10);
				USART_transmits(":HDH APOTHIKEUMENOS");
			}else
			{
				if(!addControllingNumber(tmpc)){
					USART_transmits("MNHMH PLHRHS");
					}else{
					USART_transmits("PROSTHIKI:\n");
					USART_ntransmits(tmpc,10);
					USART_transmits("\nOK");
				}
			}
		}else
		{
			USART_transmits("ARITHMOS MH APODEKTOS");
		}
		SMS_end();
		
	}
	else if(strncmp((char*)txt, "-",1) == 0)
	{
		i=10;
		do 
		{
			i--;
			tmpc[i] = txt[i+1];
		} while (i>0);
		_delay_ms(500);
		USART_transmits("\r\nAT+CMGS=\"");
		USART_ntransmits((char* )adminNo,10);
		USART_transmits("\"\rAFAIRESI:\n");
		USART_ntransmits(tmpc,10);
		if(!removeControllingNumber(tmpc)){
			USART_transmits(":\nDE VRETHIKE");
			}else{
			USART_transmits("\nOK");
		}
		SMS_end();
	}
	else if(strncmp((char*)txt, "?",1) == 0)
	{
		_delay_ms(500);
		USART_transmits("\r\nAT+CMGS=\"");
		USART_ntransmits((char* )adminNo,10);
		USART_transmits("\"\rHRISTES:\n");
		
		i=0;
		do 
		{
			if(GET_BIT(mainFP1,(CONTROLNO+i))){
				USART_transmitc(0x31+i);
				USART_transmits(":");
				USART_ntransmits((char*)controlNums+i*10,10);
				USART_transmits("\n");
			}
		} while (i++<5);
		SMS_end();
		
	}
	else if(strncmp((char*)txt, "chp",3) == 0)
	{
		i=4;
		do 
		{
			i--;
			tmpc[i] = txt[i+3];
			if(tmpc[i]>'9'||tmpc[i]<'0'){
				i=5;
				break;
			}
		} while (i>0);
		_delay_ms(500);
		USART_transmits("\r\nAT+CMGS=\"");
		USART_ntransmits((char* )adminNo,10);
		USART_transmits("\"\r");
		if(i==5){
			USART_ntransmits(tmpc,4);
			USART_transmits(":MH APODEKTOS");
			}else{
			memcpy((void*)psw,(const void *)tmpc,4);
			USART_ntransmits((char*)psw,4);
			SET_BIT(mainF1,EEPROM_UPDATE_PENDING);
		}
		SMS_end();
	}
	else if(strncmp((char*)txt,"rst",3) == 0)
	{
		
		cli();
		forceReset(ERR_ADMIN_RESET_REQUEST);
		
	}
	else if(strncmp((char*)txt, "def",3) == 0)
	{
		_delay_ms(500);
		USART_transmits("\r\nAT+CMGS=\"");
		USART_ntransmits((char* )adminNo,10);
		USART_transmits("\"\r");
		USART_transmits("EPANAFORA");
		_delay_ms(15);
		USART_transmitc(0x1A);
		
		cli();
		eeprom_busy_wait();
		eeprom_update_byte(&EEValidationByte, 0xFF);
		forceReset(ERR_ADMIN_DEFAULT_REQUEST);
	}
	else{
		_delay_ms(500);
		USART_transmits("\r\nAT+CMGS=\"");
		USART_ntransmits((char* )adminNo,10);
		USART_transmits("\"\rAGNWSTH ENTOLH");
		SMS_end();
	}
}
void startRelay(){
	PORT(P_RELAYCONTROL) |= (1<<B_RELAYSTART);
	_delay_ms(200);
	PORT(P_RELAYCONTROL) &= ~(1<<B_RELAYSTART);
}
void stopRelay(){
	PORT(P_RELAYCONTROL) |= (1<<B_RELAYSTOP);
	_delay_ms(500);
	PORT(P_RELAYCONTROL) &= ~(1<<B_RELAYSTOP);
}
void stateReport(){//NEEDS INTERRUPTS ENABLED
	CLEAR_BIT(mainF2,STATE_REPORT_PENDING);
	
	if(isValidNumber((char*)lastOpNumber)){
		SMS_start((char*)lastOpNumber);
	}else{
		SMS_start((char*)adminNo);
	}
	cli();
	if(GET_BIT(mainFP1,GSM_REBOOT_FLAG)){
		//USART_transmits("GSM REBOOT\n");
		CLEAR_BIT(mainFP1,GSM_REBOOT_FLAG);
		SET_BIT(mainF1,EEPROM_UPDATE_PENDING);
	}
	GET_BIT(mainFP1,RELAY_STATE)?USART_transmits("REL ON"):USART_transmits("REL OFF");
	USART_transmits("\n");
	if(GET_BIT(mainF2,ALARM1_FLAG)){
		GET_BIT(mainF2,ALARM1_STATE)?USART_transmits("PARAVIASI 1"):USART_transmits("AL1 OK");
	}
	USART_transmits("\n");
	if(GET_BIT(mainF2,ALARM2_FLAG)){
		GET_BIT(mainF2,ALARM2_STATE)?USART_transmits("PARAVIASI 2"):USART_transmits("AL2 OK");
	}
	SMS_end();
	sei();
}
uint8_t isValidNumber(char* number){
	uint8_t i;
	if((number[0]=='6') && (number[1]== '9')){
		i=10;
		do
		{
			i--;
			if(number[i]<'0' || number[i]>'9')return 0;
		}while(i > 1);
		return 1;
	}else{
		return 0;
	}
}
uint8_t isAdmin(char* number){
	if( (GET_BIT(mainFP1,ADMIN_FLAG)==1 ) && ( strncmp((char*)adminNo,number,10)==0) )
	{
		return 1;
	}
	return 0;
}
uint8_t isRegistered(char* number){
	uint8_t i;
	
	if(isAdmin(number))return 1;
	for (i=0;i<5;i++)
	{
		if(GET_BIT(mainFP1,(CONTROLNO+i))){
			
			if(strncmp(number,(char*)controlNums+i*10,10)==0){
				return 1;
			}
		}
	}
	return 0;
	
}
uint8_t removeControllingNumber(char* number){
	uint8_t i=0;
	while (i<5)
	{
		if(GET_BIT(mainFP1,(CONTROLNO+i)))
		{//saved number
			if(strncmp(number, (char*)controlNums+i*10, 10)==0){
				//number matched
				CLEAR_BIT(mainFP1,(CONTROLNO+i)); //clear flag
				memset(controlNums+i*10, 0x00, 10); //delete number from memory
				SET_BIT(mainF1,EEPROM_UPDATE_PENDING); //update EEPROM
				if(strncmp(number,(char*)lastOpNumber,10)==0){
					memcpy((void*)lastOpNumber,(void*)adminNo,10);
				}
				return 1;
			}
		}
		i++;
	}
	return 0;
}
void forceReset(uint8_t errCode){
wdt_reset();
cli();
	switch (errCode)
	{
		case ERR_GSM_INIT:
			//USART_transmits("gsm init error");
			indLEDCycleTime = 10;
			indLEDOnTime = 5; 
			break;
		case ERR_POWER_DOWN:
			indLEDCycleTime = 20;
			indLEDOnTime = 10;
			//USART_transmits("power down reset");
			break;
		case ERR_ADMIN_RESET_REQUEST:
			indLEDCycleTime = 30;
			indLEDOnTime = 15;
			//USART_transmits("admin reset");
			break;
		case ERR_GSM_REBOOT:
			cli();
			indLEDCycleTime = 40;
			indLEDOnTime = 20;
			SET_BIT(mainFP1,GSM_REBOOT_FLAG);
			EEPROM_update();
		case ERR_ADMIN_DEFAULT_REQUEST:
			USART_transmits("\nok");
		default:
		indLEDCycleTime = 50;
		indLEDOnTime = 250;
		//USART_transmits("default?");
		break;
	}
	crossings = 10;
sei();
	while(1){
	}
}
void SMS_start(char* number){	
	//_delay_ms(2000);
	GSM_command_response("AT","OK",2,10);
	//_delay_ms(100);
	USART_transmits("AT+CMGS=\"");
	USART_ntransmits(number,10);
	//_delay_ms(100);
	USART_transmits("\"\r");
	
	
}
void SMS_end(){
	_delay_ms(15);
	USART_transmitc(0x1A);//Ctrl+Z
}

ISR(TIMER0_OVF_vect){
	tim0Ovf_1++;
	tim0Ovf1++;
	tim0OvfIndTick++; //overflowing at ~8.4 secs
	
	if(tim0Ovf1 == 30){//~ 1 second tick
		tim0Ovf1 = 0;
		secCounter++;
	}
	if(tim0Ovf_1 == 3){//~ 0.1 second tick
		tim0Ovf_1=0;
		if(GET_BIT(mainF1,EXPECTING_RESPONSE)){
			responseTimer++;
			if(responseTimer >= responseTimeout){
				SET_BIT(mainF1,RESPONSE_TIMEOUT);
			}
		}
		if (state == WORKING)
		{
			if(crossings<8 && (GET_BIT(mainF2,POWER_STATE)==1) ){
				if(GET_BIT(mainF2,POWER_TRANSITION)==1){
					//minimise power consumption
					//CLEAR_BIT(PORT(P_INDICATION_LED),B_INDICATION_LED);			//turn off led
					//TCCR0B = 0x00;												//turn off timer 0
					//TCCR1B = 0x00;												//turn off timer 1
					//PCICR = 0x00;												//disable pin change interrupts
					//PCMSK2 = 0x00;
				
					if(GET_BIT(mainFP1,ADMIN_FLAG)){//anafora
						USART_transmits("AT\r\n");
						_delay_ms(15);
						USART_transmits("AT+CMGS=\"");
						USART_ntransmits((char*)lastOpNumber,10);
						USART_transmits("\"\r");
						USART_transmits("DEH OFF");
						_delay_ms(15);
						SMS_end();
						}
					CLEAR_BIT(mainF2,POWER_STATE);
					CLEAR_BIT(mainF2,POWER_TRANSITION);
				
					//UCSR0B = 0x00;												//USART disable
					forceReset(ERR_POWER_DOWN);
				}else{
					SET_BIT(mainF2,POWER_TRANSITION);
				}
			}else if(crossings >= 8 && (GET_BIT(mainF2,POWER_STATE)==1))
			{
				CLEAR_BIT(mainF2,POWER_TRANSITION);
			}
		}
		crossings = 0;
	}
	
	if(++tim0OvfSMSTick == 0xFF && !GET_BIT(mainF3,SMS_READY))
	{
		GSM_command_delimeter();
		GSM_command_delimeter();
		CLEAR_BIT(mainF3,NEW_SMS);
		CLEAR_BIT(mainF3,MASTER_SMS);
		SET_BIT(mainF3,SMS_READY);
		GSM_command(DELETE_ALL_SMS);
		GSM_command_delimeter();
		
		
		
	}
	
	if (tim0OvfIndTick == indLEDOnTime)
	{
		CLEAR_BIT(PORT(P_INDICATION_LED),B_INDICATION_LED);
	}else if (tim0OvfIndTick >= indLEDCycleTime){
		SET_BIT(PORT(P_INDICATION_LED),B_INDICATION_LED);
		tim0OvfIndTick = 0;
	}
}

ISR(TIMER1_OVF_vect){
	tim1OvfTick--;
	if(tim1OvfTick == 6){
		if(GET_BIT(mainF1,GSM_COMMUNICATING)){
			CLEAR_BIT(mainF1,GSM_COMMUNICATING);
			tim1OvfTick = 20;
			}else{
			USART_transmits("AT\r\n");
		}
	}else if(tim1OvfTick == 2){
		if(GET_BIT(mainF1,GSM_COMMUNICATING)){
			CLEAR_BIT(mainF1,GSM_COMMUNICATING);
			tim1OvfTick = 20;
		}else{
			USART_transmits("AT\r\n");
		}
	}else if(tim1OvfTick == 0){
		if(GET_BIT(mainF1,GSM_COMMUNICATING)){
			CLEAR_BIT(mainF1,GSM_COMMUNICATING);
			tim1OvfTick = 20;
		}else{
			forceReset(ERR_GSM_NO_COMM);
		}
	}
}

ISR(PCINT2_vect){
	crossings++;
	
}
