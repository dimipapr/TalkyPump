/*
 * config.h
 *
 * Created: 22/7/2020 23:52:51
 *  Author: Jims
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#include <inttypes.h>
#include <avr/pgmspace.h>

#define F_CPU		8000000UL
#define BAUD		38400
#define MYUBRR		F_CPU/16/BAUD-1
#define EEPROM_VALIDATION_BYTE 0x55

#define INPUTSENSITIVITY 100

//macros
#define _CONCAT(A,B) A##B
#define PORT(x) _CONCAT(PORT,x)
#define PIN(x) _CONCAT(PIN,x)
#define DDR(x) _CONCAT(DDR,x)

//outputs
#define P_RELAYCONTROL D
#define B_RELAYSTART 3
#define B_RELAYSTOP 2

#define P_GSMPOWER D
#define B_GSMPOWER 5

//inputs
#define P_RELAYSENSOR C
#define B_RELAYSENSOR 0

#define P_ALARM C
#define B_ALARM1 1
#define B_ALARM2 2

#define P_ZEROCROSS D
#define B_ZEROCROSS 4

#define ADC1 3

#define P_INDICATION_LED C
#define B_INDICATION_LED 4


//MAIN DEFINITIONS
#define MASTER_DEFAULT "3101560339240709"		//6
#define EXPECTED_RESPONSE_SIZE 20
#define ADMIN_REGISTER_RINGS	6
#define RELAY_STOP_RINGS		3
#define RELAY_START_RINGS		3

#define MAINF1_INITIAL	0b00000000
// mainF1 bits
#define EXPECTING_RESPONSE			0//mainF1
#define EXPECTED_RESPONSE_RECEIVED	1//mainF1
#define RESPONSE_TIMEOUT			2//mainF1
#define GSM_BOOT_DETECTED			3//mainF1
#define GSM_COMMUNICATING			4//mainF1
#define GSM_CALL_READY_DETECTED		5//mainF1
#define RESET_PENDING				6//mainF1
#define EEPROM_UPDATE_PENDING		7//mainF1

#define MAINF2_INITIAL 0b00010011
//mainF2 bits
#define ALARM2_FLAG				0//mainF2
#define ALARM1_FLAG				1//mainF2
#define ALARM2_STATE			2//mainF2
#define ALARM1_STATE			3//mainF2
#define POWER_STATE				4//mainF2
#define POWER_TRANSITION		5//mainF2
#define STATE_REPORT_PENDING	6//mainF2


#define  MAINF3_INITIAL 0b00000001
//mainF3 bits
#define SMS_READY				0//mainF3
#define NEW_SMS					1//mainF3
#define MASTER_SMS				2//mainF3
#define NO_ADMIN_SMS			3//mainF3
#define TXT_READY				4//mainF3

#define MAINFP1_INITIAL 0b00000000
//mainFP1 bits
#define RELAY_STATE			0  //mainFP1
#define ADMIN_FLAG			1  //mainFP1
#define CONTROLNO			2  //mainFP1
//#define CONTROLNO_2			CONTROL_NO+1 (3) RESERVED
//#define CONTROLNO_3			CONTROL_NO+2 (4)	//
//#define CONTROLNO_4			CONTROL_NO+3 (5)	//
//#define CONTROLNO_5			CONTROL_NO+4 (6)	//
#define GSM_REBOOT_FLAG		7 //mainFP1

//ERROR CODES
#define ERR_GSM_INIT			0//ERR CODE
#define ERR_POWER_DOWN			1//ERR CODE
#define ERR_MASTER_DEFAULT_SMS	2//ERR CODE
#define ERR_ADMIN_RESET_REQUEST	3//ERR CODE
#define ERR_ADMIN_DEFAULT_REQUEST	4//ERR CODE
#define ERR_GSM_NO_COMM				5//ERR CODE
#define ERR_GSM_REBOOT				6//ERR CODE


//USART DEFINITIONS
#define EOC1	'\r'
#define EOC2	'\n'

//WORKING STATES
#define INITIALISING 0
#define WORKING 1



#endif /* CONFIG_H_ */