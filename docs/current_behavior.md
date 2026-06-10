# TalkyPump v1 current behavior map

Status: incomplete, built from source inspection.

This document records observed behavior from the current firmware source. It should distinguish confirmed source facts from inferred behavior, risks, likely bugs, and open questions.

## Source set

The Atmel Studio project and WSL `Makefile` currently build:

```text
main.c
gsm.c
usart.c
```

Headers used by the active firmware include:

```text
config.h
bitOperations.h
gsm.h
usart.h
```

The following files exist but are not currently compiled into the firmware:

```text
adc.c
adc.h
lcd.c
```

## Clock and fuse assumptions

`config.h` defines:

```c
#define F_CPU 8000000UL
#define BAUD 38400
#define MYUBRR F_CPU/16/BAUD-1
```

`fuseSettings.txt` records:

```text
SUT_CKSEL = INTRCOSC_8MHZ_6CK_14CK_65MS
CKDIV8 = [ ]
BODLEVEL = 4V3

EXTENDED = 0xF9
HIGH = 0xDC
LOW = 0xE2
```

Current interpretation:

* firmware assumes 8 MHz CPU clock
* saved fuse settings are consistent with internal 8 MHz oscillator and CKDIV8 disabled
* brown-out level is recorded as 4.3 V
* fuse settings appear to be exported or copied from an IDE/programming UI
* no other project-owned fuse setting record has been found in the repository so far

Open question:

* actual programmed fuses still need readback from at least one known-good device

## Pin map from `config.h`

Outputs:

```text
PD3  relay start pulse output
PD2  relay stop pulse output
PD5  GSM power control
PC4  indication LED
```

Inputs:

```text
PC0  relay sensor
PC1  alarm 1
PC2  alarm 2
PD4  zero-cross / power monitor input
```

## Global flag bytes

### `mainF1`

Initial value:

```c
#define MAINF1_INITIAL 0b00000000
```

Bits:

```text
0  EXPECTING_RESPONSE
1  EXPECTED_RESPONSE_RECEIVED
2  RESPONSE_TIMEOUT
3  GSM_BOOT_DETECTED
4  GSM_COMMUNICATING
5  GSM_CALL_READY_DETECTED
6  RESET_PENDING
7  EEPROM_UPDATE_PENDING
```

Known use so far:

* tracks pending GSM command responses
* tracks GSM communication activity
* tracks response timeout
* requests EEPROM update
* detects possible GSM reboot through `Call Ready`

Some bits are not fully mapped yet.

### `mainF2`

Initial value:

```c
#define MAINF2_INITIAL 0b00010011
```

Bits:

```text
0  ALARM2_FLAG
1  ALARM1_FLAG
2  ALARM2_STATE
3  ALARM1_STATE
4  POWER_STATE
5  POWER_TRANSITION
6  STATE_REPORT_PENDING
```

Known use so far:

* alarm enable/status flags
* power state and power-loss transition tracking
* state report request flag

Open question:

* where alarm enable flags are intentionally changed is not yet fully mapped

### `mainF3`

Initial value:

```c
#define MAINF3_INITIAL 0b00000001
```

Bits:

```text
0  SMS_READY
1  NEW_SMS
2  MASTER_SMS
3  NO_ADMIN_SMS
4  TXT_READY
```

Known use so far:

* serializes SMS handling
* tracks new SMS notification
* distinguishes admin SMS from non-admin SMS
* marks parsed SMS text ready for main-loop handling

### `mainFP1`

Initial value:

```c
#define MAINFP1_INITIAL 0b00000000
```

Bits:

```text
0  RELAY_STATE
1  ADMIN_FLAG
2  CONTROLNO slot 0 flag
3  CONTROLNO slot 1 flag
4  CONTROLNO slot 2 flag
5  CONTROLNO slot 3 flag
6  CONTROLNO slot 4 flag
7  GSM_REBOOT_FLAG
```

Known use so far:

* persisted in EEPROM
* stores relay state
* stores whether admin is registered
* stores which control-number slots are used
* stores GSM reboot flag for later state report handling

## EEPROM persistent state

EEPROM-backed variables declared in `main.c`:

```text
EEValidationByte
EEadminNo[10]
EEControlNums[50]
EEmainFP1
EEpsw[4]
EElastOpNumber[10]
```

RAM mirrors:

```text
adminNo[10]
controlNums[50]
mainFP1
psw[4]
lastOpNumber[10]
```

Current interpretation:

* admin number is 10 digits
* up to 5 control numbers are stored, each 10 digits
* password is 4 digits
* last operation number is 10 digits
* `mainFP1` is persistent

EEPROM validation uses:

```c
#define EEPROM_VALIDATION_BYTE 0x55
```

Default EEPROM reset behavior:

* admin number cleared
* control numbers cleared
* last operation number cleared
* password set to `"0000"`
* `mainFP1` reset to default
* EEPROM validation byte written

Finding:

* `EEValidationByte` appears twice in the declarations.
* This compiled, but it is suspicious and should be reviewed later.
* Do not change yet without checking EEPROM layout and generated symbols.

## USART behavior

Source files inspected:

```text
usart.h
usart.c
```

USART is interrupt-driven.

`USART_init()` configures:

```c
UBRR0H = (unsigned char)(ubrr >> 8);
UBRR0L = (unsigned char)ubrr;

UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
UCSR0C = (1 << USBS0) | (3 << UCSZ00);
```

Current interpretation:

* receiver enabled
* transmitter enabled
* RX complete interrupt enabled
* serial format appears to be 8 data bits, no parity, 2 stop bits
* baud comes from `MYUBRR`, based on `F_CPU=8000000UL` and `BAUD=38400`

Receive buffer:

```c
#define receiveBufferSize 80

char receiveBuffer[receiveBufferSize];
uint8_t receiveBufferPos;
```

Received bytes are collected in `receiveBuffer`.

Line termination:

* command end is detected on `EOC1`, `EOC2`
* `config.h` defines:

  * `EOC1 = '\r'`
  * `EOC2 = '\n'`
* when `\r\n` is received, the previous `\r` is replaced with `'\0'`
* `parseReceivedCommand()` is called

Important behavior:

* `parseReceivedCommand()` is called from inside `ISR(USART_RX_vect)`
* receive buffer is flushed after command processing or overflow
* if software flow control is enabled, XOFF/XON are used:

  * `XOFF = 0x13`
  * `XON = 0x11`

## GSM command wrapper

`gsm.c` provides thin wrappers around USART transmit:

* `GSM_command(cmd)` sends a null-terminated AT command string
* `GSM_command_delimeter()` sends `\r\n`
* `GSM_powerToggle()` pulls the GSM power pin low for about 1.5 seconds, then high

Configured AT commands include:

```text
AT
ATE0
AT+CMGF=1
AT+CLIP=1
AT+IPR=38400
AT+IFC=1,1
AT&W
AT+CCALR?
AT+CMGD=1,4
AT+CMGR=1
ATH
AT+CPOWD=1
```

Current interpretation:

* modem echo is disabled
* SMS text mode is enabled
* caller ID reporting is enabled
* modem baud is fixed to 38400
* software flow control is enabled with `AT+IFC=1,1`
* settings are saved to modem NVM with `AT&W`
* all SMS messages are deleted during GSM configuration
* SMS handling appears to assume SMS slot/index 1

## Startup behavior

Startup sequence:

1. watchdog is disabled early in `.init3`
2. state is set to `INITIALISING`
3. IO is initialized
4. USART is initialized
5. Timer0 is started
6. Timer1 is started
7. pin-change interrupt is enabled for zero-cross input
8. global interrupts are enabled
9. GSM is initialized/configured
10. EEPROM is initialized, or reset to defaults if invalid
11. watchdog is enabled with about 8 second timeout

After initialization, firmware waits until an admin number exists.

If no admin is registered:

* firmware waits in a loop
* watchdog is reset in the loop
* if power state is lost, `forceReset(ERR_POWER_DOWN)` is called

After admin exists:

* relay sensor and alarm inputs are sampled using `INPUTSENSITIVITY`
* relay/alarm state flags are initialized from sampled inputs
* EEPROM update is requested
* SMS system is marked ready
* an initial state report is sent
* state changes to `WORKING`

## GSM initialization behavior

`GSM_init()` waits about 5 seconds at entry.

Current apparent flow:

* clear `GSM_COMMUNICATING`
* send repeated `AT`
* if modem communication is detected, run `GSM_Config()`
* if communication is not detected after a period, power-toggle GSM and then run `GSM_Config()`
* clear `GSM_CALL_READY_DETECTED`
* return success

`GSM_Config()` sends and expects responses for:

```text
AT                       -> OK
ATE0                     -> OK
AT+CMGF=1                -> OK
AT+CLIP=1                -> OK
AT+IPR=38400             -> OK
AT+IFC=1,1               -> OK
AT&W                     -> OK
AT+CCALR?                -> +CCALR: 1
AT+CMGD=1,4              -> OK
```

Risk / possible bug:

* `GSM_init()` may have a path where it returns success even if communication/configuration did not clearly complete.
* This needs careful review before changing.

## GSM command/response behavior

`GSM_command_response(cmd, resp, timeout, repetitions)`:

* requires interrupts
* sends command plus delimiter
* sets expected response string
* waits until either:

  * expected response is received, or
  * response timeout flag is set by Timer0
* retries until repetitions are exhausted

Important note in source:

```c
//NEEDS INTERRUPTS, SO DONT CALL FROM ISR, no?
```

Risk:

* some paths may call response/wait logic close to ISR context or after manual interrupt changes.
* needs careful call-site review.

## Call / ring behavior

If admin is already registered:

* incoming `+CLIP` extracts a 10-digit caller number from a fixed offset in `receiveBuffer`
* if caller is registered:

  * ring count increments
  * after configured ring count:

    * if relay is ON, call triggers stop
    * if relay is OFF, call triggers start
  * call is hung up using repeated `ATH`
  * caller is stored as `lastOpNumber`
  * EEPROM update is requested
* if caller is not registered:

  * ring count resets
  * call is hung up
  * caller buffer is cleared

If no admin is registered:

* incoming calls increment ring count
* after `ADMIN_REGISTER_RINGS`, caller becomes admin
* caller is copied to `adminNo` and `lastOpNumber`
* admin flag is set
* EEPROM update is requested

When `NO CARRIER` is received:

* if ring count is nonzero:

  * `lastOpNumber` is updated from `callingNumber`
  * EEPROM update is requested
  * state report is requested
  * ring count resets

Configured ring counts:

```text
ADMIN_REGISTER_RINGS = 6
RELAY_STOP_RINGS     = 3
RELAY_START_RINGS    = 3
```

## SMS behavior

Incoming SMS indication:

* `+CMTI` sets `NEW_SMS` if SMS system is ready
* main loop reacts by sending `AT+CMGR=1`
* if SMS system is not ready, all SMS messages are deleted

SMS read response:

* `+CMGR` extracts caller number from a fixed offset in `receiveBuffer`
* if caller is admin:

  * next received text line is treated as master/admin SMS body
* otherwise:

  * next received text line is treated as non-admin SMS body

Admin SMS body:

* must start with the 4-byte password
* remaining text is copied into `txt[32]`
* main loop later calls `parseTxt()`

Admin SMS commands currently visible:

```text
+<10-digit number>  add control number
-<10-digit number>  remove control number
?                   list users
chpNNNN             change 4-digit password
rst                 reset device
def                 invalidate EEPROM and reset defaults
other               reply unknown command
```

Non-admin SMS:

* special default/reset path exists
* otherwise SMS messages are deleted and SMS state is reset

SMS timeout/recovery:

* Timer0 increments `tim0OvfSMSTick`
* if SMS handling takes too long while `SMS_READY` is clear:

  * sends delimiters
  * clears SMS state
  * sets `SMS_READY`
  * deletes all SMS

## Relay behavior

Relay output pins:

```text
RELAYSTART = PD3
RELAYSTOP  = PD2
```

`startRelay()`:

* pulses start output for about 200 ms

`stopRelay()`:

* pulses stop output for about 500 ms

Relay sensor:

```text
RELAYSENSOR = PC0
```

Main loop watches relay sensor against stored relay state.

If sensor disagrees with stored state for enough samples:

* waits about 300 ms
* sends SMS to `lastOpNumber` if valid, else admin
* sends either `REL OFF` or `REL ON`
* updates stored relay state
* requests EEPROM update

## Alarm behavior

Alarm inputs:

```text
ALARM1 = PC1
ALARM2 = PC2
```

Alarm flags in `mainF2` control whether alarm reporting is active.

If enabled and breached for enough samples:

* sends SMS to `lastOpNumber` if valid, else admin
* sends `AL1 PARAVIASI` or `AL2 PARAVIASI`
* sets alarm state flag

Open question:

* where alarm flags are enabled/disabled is not yet fully mapped.

## Power-loss / zero-cross behavior

Zero-cross input:

```text
ZEROCROSS = PD4 / PCINT20
```

Pin-change ISR increments:

```text
crossings
```

Timer0 periodically checks crossing count.

Current interpretation:

* if crossings drop below threshold while working, firmware treats this as power-loss transition
* after confirmation, if admin exists, it sends `DEH OFF`
* clears power state
* calls `forceReset(ERR_POWER_DOWN)`

Open question:

* exact electrical meaning of zero-cross input needs hardware confirmation.

## Timer behavior

### Timer0

Configured with 1/1024 prescaler.

Comments indicate about 33 ms overflow at 8 MHz.

Timer0 overflow ISR handles:

* approximate 1 second counter using `tim0Ovf1`
* approximate 0.1 second response timer using `tim0Ovf_1`
* GSM command response timeout
* power-loss detection through zero-cross count
* SMS handling timeout/recovery
* indication LED blink timing

Risk:

* Timer0 ISR can transmit SMS/AT data and call `forceReset()`.
* This is high-risk ISR behavior but appears to be existing behavior.

### Timer1

Configured with 1/1024 prescaler.

Comments indicate about 8.4 second overflow at 8 MHz.

Timer1 overflow ISR handles GSM communication watchdog behavior:

* decrements `tim1OvfTick`
* sends `AT\r\n` at selected ticks if no GSM communication was seen
* if no communication is seen by timeout, calls `forceReset(ERR_GSM_NO_COMM)`

Risk:

* Timer1 ISR transmits UART data and can enter reset path.
* Preserve until GSM recovery behavior is fully understood.

## Reset behavior

`forceReset(errCode)`:

* resets watchdog
* disables interrupts
* sets LED blink timing based on error code
* may update persistent `GSM_REBOOT_FLAG`
* re-enables interrupts
* enters infinite loop
* watchdog is expected to reset MCU

Known error codes:

```text
ERR_GSM_INIT
ERR_POWER_DOWN
ERR_MASTER_DEFAULT_SMS
ERR_ADMIN_RESET_REQUEST
ERR_ADMIN_DEFAULT_REQUEST
ERR_GSM_NO_COMM
ERR_GSM_REBOOT
```

Risk / possible bug:

* `ERR_GSM_REBOOT` case falls through into `ERR_ADMIN_DEFAULT_REQUEST` and then default behavior.
* This may be accidental or intentional.
* Do not change until reviewed.

## High-risk areas found so far

### Parser and command handling run inside RX ISR

`parseReceivedCommand()` is called directly from `USART_RX_vect`.

But `parseReceivedCommand()` may:

* parse GSM responses
* modify global state
* transmit USART data
* call delay functions
* update EEPROM in some paths
* call reset paths
* in one path, temporarily re-enable interrupts and call `GSM_command_response()`

This is high risk, but it is current behavior and should not be refactored casually.

### Blocking transmit may happen from ISR

`USART_transmitc()` waits for `UDRE0`.

This function is called from:

* RX ISR path
* Timer ISR paths
* reset paths
* normal main-loop paths

This can increase interrupt latency or cause hard-to-debug stalls.

### Header-defined globals

`usart.h` defines storage for:

```c
char receiveBuffer[receiveBufferSize];
uint8_t receiveBufferPos;
```

Because `usart.h` is included by multiple `.c` files, newer GCC reports multiple definitions.

Current WSL build uses `-fcommon` to preserve older GCC behavior.

Possible later cleanup:

* move definitions to `usart.c`
* leave `extern` declarations in `usart.h`

Do this only as a separate source cleanup commit.

### Fixed-offset phone number parsing

Caller/SMS phone numbers are copied from fixed offsets in `receiveBuffer`.

This is fragile if SIM800L response formatting varies.

Do not change yet; document and confirm against known modem responses.

### EEPROM writes with interrupts disabled

EEPROM functions call `cli()` and do not always restore interrupt state themselves.

Some callers manually call `sei()` afterward.

This needs careful mapping before cleanup.

### Receive buffer size and termination

Receive buffer is 80 bytes.

The code avoids writing past the array by flushing when full. It does not reserve separate space for a terminator; instead, it null-terminates by replacing the received `\r` when a valid `\r\n` sequence is seen.

Risk needs confirmation against SIM800L response lengths and SMS parsing behavior.

## Likely cleanup candidates

Do not implement these yet unless reviewed separately.

Small candidates:

* move USART globals out of `usart.h`
* document ISR-context parser behavior in source comments
* document EEPROM layout explicitly
* document persistent flag byte meanings
* review duplicate `EEValidationByte`
* review `GSM_init()` success path
* review `forceReset()` switch fallthrough
* review fixed-offset parsing assumptions

Avoid for now:

* rewriting GSM parser
* changing ISR/main-loop architecture
* changing SMS command behavior
* changing modem setup sequence
* changing EEPROM layout
* changing relay behavior