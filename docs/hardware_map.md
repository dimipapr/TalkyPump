# Hardware map

Status: schematic checked, real-device notes included.

## MCU

| Item | Value |
|---|---|
| MCU | ATmega168PA |
| Supply | 5 V |
| Clock | internal 8 MHz |
| UART | USART0 used for SIM800 |
| Programming | ISP header |

## SIM800 modem

The SIM800 modem is connected to the ATmega168 hardware UART.

| Purpose | MCU pin | Board net | Notes |
|---|---:|---|---|
| MCU receives data from modem | PD0 / RXD | `GTx` | SIM800 TX → MCU RX |
| MCU sends data to modem | PD1 / TXD | `GRx` | MCU TX → SIM800 RX |
| Modem power control | PD5 | `GSMPWR` | controls modem power-key circuit |

Firmware settings:

- UART peripheral: USART0
- No second UART is available
- Tested baud rate: 38400, supports autobaud

## Outputs

| Function | MCU pin / net | Active state | Notes |
|---|---|---|---|
| Relay stop pulse | PD2 / `RelStop` | high | drives relay driver, legacy pulse approx. 500 ms |
| Relay start pulse | PD3 / `RelStart` | high | drives relay driver, legacy pulse approx. 200 ms |
| GSM power key | PD5 / `GSMPWR` | high | active-high firmware signal; pulls SIM800 PWRKEY low |
| Status LED | PC4 / `ADC2` terminal | high | external/manual LED connected on real devices |

## Inputs

| Function | MCU pin / net | Open state | Closed state | Notes |
|---|---|---|---|---|
| Relay state feedback | PC0 / `RelSensor` | high | low | external pull-up; contact/input closure pulls low |
| Alarm 1 | PC1 / `Alarm1` | high | low | external pull-up; contact/input closure pulls low |
| Alarm 2 | PC2 / `Alarm2` | high | low | external pull-up; contact/input closure pulls low |
| Mains / zero-cross activity | PD4 / `OptOut` | - | - | pin-change activity indicates mains voltage threshold transition |

## Auxiliary terminals

| Function | MCU pin / net | Open state | Closed state | Notes |
|---|---|---|---|---|
| ADC/input 1 | PC3 / `ADC1` | high | low | available terminal, v2 use TBD |

## Firmware constraints

- Relay outputs must initialize inactive before any application logic runs.
- Relay start/stop pulses must never occur accidentally during boot.
- USART0 is dedicated to the SIM800 modem.
- No second hardware UART is available for logging.
- Status/debug indication shall use the external LED on `ADC2` / PC4.
- Mains presence is detected from zero-cross activity on PD4.
- On confirmed mains loss, firmware shall persist the shutdown event before attempting GSM/SMS work.
- Optional GPRS diagnostics must not be required for pump control.