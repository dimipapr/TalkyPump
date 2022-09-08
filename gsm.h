/*
 * gsm.h
 *
 * Created: 23/7/2020 0:09:06
 *  Author: Jims
 */ 


#ifndef GSM_H_
#define GSM_H_

#include "config.h"
#include "usart.h"
#include <inttypes.h>
#include <util/delay.h>

#ifndef P_GSMPOWER 
#error "P_GSMPOWER NOT DEFINED! (GSM POWER PIN PORT)"
#endif

#ifndef B_GSMPOWER
#error "B_GSMPOWER NOT DEFINED! (GSM POWER PIN BIT)"
#endif 

#ifndef EOC1
#error "EOC1 NOT DEFINED"
#endif

#ifndef EOC2
#error "EOC2 NOT DEFINED"
#endif

//COMMANDS
#define ENABLE_SOFTWARE_FLOW_CONTROLL			"AT+IFC=1,1"
#define	ENABLE_SOFTWARE_FLOW_CONTROLL_RESPONSE	"OK"
#define SAVE_SETTINGS							"AT&W"
#define SAVE_SETTINGS_RESPONSE					"OK"
#define POWER_DOWN								"AT+CPOWD=1"
#define POWER_DOWN_RESPONSE						"NORMAL POWER DOWN"
#define SMS_TXT_MODE							"AT+CMGF=1"
#define SMS_TXT_MODE_RESPONSE					"OK"
#define DISABLE_ECHO							"ATE0"
#define DISABLE_ECHO_RESPONSE					"OK"
#define ENABLE_CALL_RECOGNITION					"AT+CLIP=1"
#define ENABLE_CALL_RECOGNITION_RESPONSE		"OK"
#define DELETE_ALL_SMS							"AT+CMGD=1,4"
#define DELETE_ALL_SMS_RESPONSE					"OK"
#define SET_FIXED_BAUD_38400					"AT+IPR=38400"
#define SET_FIXED_BAUD_38400_RESPONSE			"OK"
#define CALL_READY_CHECK						"AT+CCALR?"
#define CALL_READY_RESPONSE						"+CCALR: 1"
#define HANG_UP									"ATH"
#define HANG_UP_RESPONSE						"OK"
#define READ_SMS1								"AT+CMGR=1"
#define READ_SMS1_RESPONSE						"+CMGR"




//GSM_command_response return values
#define RETVAL_ALREADY_WAITING_FOR_RESPONSE		0
#define RETVAL_SUCCESS							1
#define RETVAL_TIMEOUT							2
#define RETVAL_ZERO_REPETITIONS					3

//GSM flags
//GSMF bits




void GSM_command(char *cmd);//null terminated command
void GSM_command_delimeter(void);
void GSM_powerToggle(void);
void GSM_command_ok(char* cmd);



#endif /* GSM_H_ */