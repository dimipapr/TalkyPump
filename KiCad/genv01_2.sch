EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev "v01.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R Rb1
U 1 1 5EDD58C2
P 7700 1650
F 0 "Rb1" V 7493 1650 50  0000 C CNN
F 1 "1k" V 7584 1650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 7630 1650 50  0001 C CNN
F 3 "~" H 7700 1650 50  0001 C CNN
	1    7700 1650
	0    1    1    0   
$EndComp
Wire Wire Line
	7850 1650 7950 1650
$Comp
L Transistor_BJT:BC337 Q1
U 1 1 5EDD28D6
P 8150 1650
F 0 "Q1" H 8341 1696 50  0000 L CNN
F 1 "BC337" H 8341 1605 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92L_Wide" H 8350 1575 50  0001 L CIN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bc337.pdf" H 8150 1650 50  0001 L CNN
	1    8150 1650
	1    0    0    -1  
$EndComp
Wire Notes Line
	7450 550  10250 550 
Wire Notes Line
	10250 550  10250 2150
Wire Notes Line
	9900 450  7100 450 
Wire Notes Line
	7450 2150 7450 550 
Text Notes 7900 2100 2    50   ~ 0
StartRel\n
$Comp
L Isolator:H11L1 U2
U 1 1 5EDEDF0E
P 6150 1350
F 0 "U2" H 6100 1750 50  0000 L CNN
F 1 "H11L1" H 6250 1600 50  0000 L CNN
F 2 "Package_DIP:DIP-6_W7.62mm_Socket" H 6060 1350 50  0001 C CNN
F 3 "https://www.fairchildsemi.com/datasheets/H1/H11L1M.pdf" H 6060 1350 50  0001 C CNN
	1    6150 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5EDF1B67
P 6550 1200
F 0 "R2" H 6650 1250 50  0000 L CNN
F 1 "30k" H 6650 1150 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 6480 1200 50  0001 C CNN
F 3 "~" H 6550 1200 50  0001 C CNN
	1    6550 1200
	1    0    0    -1  
$EndComp
Text Notes 4900 800  2    50   ~ 0
240Vac\nControlled Power
Wire Wire Line
	6450 1350 6550 1350
Connection ~ 6550 1350
Wire Wire Line
	6150 1050 6150 1000
Wire Wire Line
	6150 1000 6550 1000
Wire Wire Line
	6550 1000 6550 1050
Wire Notes Line
	7350 2150 4200 2150
Wire Notes Line
	4200 2150 4200 550 
Wire Notes Line
	7350 550  7350 2150
Text Notes 4250 2100 0    50   ~ 0
240Vac zero cross sensing module
$Comp
L Device:R R3
U 1 1 5EE2DC2A
P 6950 5900
F 0 "R3" H 7020 5946 50  0001 L CNN
F 1 "10k" V 7065 5900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 6880 5900 50  0001 C CNN
F 3 "~" H 6950 5900 50  0001 C CNN
	1    6950 5900
	0    -1   -1   0   
$EndComp
$Comp
L Connector:AVR-ISP-6 J5
U 1 1 5EE9996C
P 10800 5400
F 0 "J5" H 10470 5496 50  0000 R CNN
F 1 "AVR-ISP-6" H 10470 5405 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" V 10550 5450 50  0001 C CNN
F 3 " ~" H 9525 4850 50  0001 C CNN
	1    10800 5400
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5EE9A7DC
P 5300 7400
F 0 "#PWR06" H 5300 7150 50  0001 C CNN
F 1 "GND" H 5305 7227 50  0000 C CNN
F 2 "" H 5300 7400 50  0001 C CNN
F 3 "" H 5300 7400 50  0001 C CNN
	1    5300 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 7100 5300 7400
$Comp
L power:GND #PWR016
U 1 1 5EE9D4E2
P 10900 5850
F 0 "#PWR016" H 10900 5600 50  0001 C CNN
F 1 "GND" V 10905 5722 50  0000 R CNN
F 2 "" H 10900 5850 50  0001 C CNN
F 3 "" H 10900 5850 50  0001 C CNN
	1    10900 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10900 5850 10900 5800
Connection ~ 6550 1000
Text Label 6850 1350 0    50   ~ 0
OptOut
$Comp
L power:GND #PWR07
U 1 1 5EED4FEE
P 6150 1750
F 0 "#PWR07" H 6150 1500 50  0001 C CNN
F 1 "GND" H 6155 1577 50  0000 C CNN
F 2 "" H 6150 1750 50  0001 C CNN
F 3 "" H 6150 1750 50  0001 C CNN
	1    6150 1750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR08
U 1 1 5EED7800
P 6550 900
F 0 "#PWR08" H 6550 750 50  0001 C CNN
F 1 "+5V" H 6565 1073 50  0000 C CNN
F 2 "" H 6550 900 50  0001 C CNN
F 3 "" H 6550 900 50  0001 C CNN
	1    6550 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 900  6550 1000
Wire Wire Line
	6150 1650 6150 1750
Wire Wire Line
	6550 1350 6850 1350
$Comp
L power:GND #PWR012
U 1 1 5EEF6ADC
P 8250 1900
F 0 "#PWR012" H 8250 1650 50  0001 C CNN
F 1 "GND" H 8255 1727 50  0000 C CNN
F 2 "" H 8250 1900 50  0001 C CNN
F 3 "" H 8250 1900 50  0001 C CNN
	1    8250 1900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 5EEF6E8D
P 8250 650
F 0 "#PWR011" H 8250 500 50  0001 C CNN
F 1 "+5V" V 8265 778 50  0000 L CNN
F 2 "" H 8250 650 50  0001 C CNN
F 3 "" H 8250 650 50  0001 C CNN
	1    8250 650 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8250 1900 8250 1850
Text Label 7550 1650 1    50   ~ 0
RelStop
Wire Wire Line
	7450 1650 7550 1650
$Comp
L power:+5V #PWR015
U 1 1 5EF03549
P 10900 4800
F 0 "#PWR015" H 10900 4650 50  0001 C CNN
F 1 "+5V" H 10915 4973 50  0000 C CNN
F 2 "" H 10900 4800 50  0001 C CNN
F 3 "" H 10900 4800 50  0001 C CNN
	1    10900 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10900 4800 10900 4900
Wire Wire Line
	1950 5650 2200 5650
Wire Wire Line
	1950 5950 2200 5950
$Comp
L power:GND #PWR02
U 1 1 5EF0F612
P 2200 6050
F 0 "#PWR02" H 2200 5800 50  0001 C CNN
F 1 "GND" H 2205 5877 50  0000 C CNN
F 2 "" H 2200 6050 50  0001 C CNN
F 3 "" H 2200 6050 50  0001 C CNN
	1    2200 6050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 5EF0FD7C
P 2200 5550
F 0 "#PWR01" H 2200 5400 50  0001 C CNN
F 1 "+5V" H 2215 5723 50  0000 C CNN
F 2 "" H 2200 5550 50  0001 C CNN
F 3 "" H 2200 5550 50  0001 C CNN
	1    2200 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 5550 2200 5650
Wire Wire Line
	2200 5950 2200 6050
Connection ~ 2200 5950
Text Label 10200 5200 0    50   ~ 0
MISO
Wire Wire Line
	10200 5200 10400 5200
Wire Wire Line
	10200 5300 10400 5300
Wire Wire Line
	10200 5400 10400 5400
Wire Wire Line
	10200 5500 10400 5500
Text Label 10200 5300 0    50   ~ 0
MOSI
Text Label 10200 5400 0    50   ~ 0
SCK
Text Label 10200 5500 0    50   ~ 0
RST
Text Label 5950 5900 0    50   ~ 0
RST
Text Label 5950 4800 0    50   ~ 0
MISO
Text Label 5950 4900 0    50   ~ 0
SCK
Text Label 5950 4700 0    50   ~ 0
MOSI
Wire Wire Line
	5900 6100 6150 6100
Text Label 5900 6100 0    51   ~ 0
Rx
Text Label 6050 6100 0    51   ~ 0
GTx
Wire Wire Line
	5900 4900 6350 4900
Wire Wire Line
	5900 4800 6350 4800
Wire Wire Line
	5900 6200 6150 6200
Text Label 5900 6200 0    51   ~ 0
Tx
Text Label 6050 6200 0    51   ~ 0
GRx
Text Label 5950 6500 0    51   ~ 0
ZCrossMonitor
Text Label 6550 6500 0    51   ~ 0
OptOut
Wire Wire Line
	5900 6300 6500 6300
$Comp
L MCU_Microchip_ATmega:ATmega168PA-PU U1
U 1 1 5EE29083
P 5300 5600
F 0 "U1" H 4657 5646 50  0000 R CNN
F 1 "ATmega168PA-PU" H 4657 5555 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 5300 5600 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48PA_88PA_168PA-Data-Sheet-40002011A.pdf" H 5300 5600 50  0001 C CNN
	1    5300 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 5F068C71
P 2450 5650
F 0 "L1" V 2269 5650 50  0000 C CNN
F 1 "10u" V 2360 5650 50  0000 C CNN
F 2 "gen:L_Radial_5mm_2mm" H 2450 5650 50  0001 C CNN
F 3 "~" H 2450 5650 50  0001 C CNN
	1    2450 5650
	0    1    1    0   
$EndComp
Wire Wire Line
	2300 5650 2200 5650
Connection ~ 2200 5650
Wire Wire Line
	2200 5950 2750 5950
$Comp
L power:+5V #PWR05
U 1 1 5F078D6A
P 5150 4100
F 0 "#PWR05" H 5150 3950 50  0001 C CNN
F 1 "+5V" H 5165 4273 50  0000 C CNN
F 2 "" H 5150 4100 50  0001 C CNN
F 3 "" H 5150 4100 50  0001 C CNN
	1    5150 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 4100 5150 4100
Text Label 2750 5650 0    51   ~ 0
AVcc
Wire Wire Line
	5400 4100 5550 4100
Text Label 5550 4100 0    51   ~ 0
AVcc
NoConn ~ 4700 4400
Wire Wire Line
	5750 1450 5850 1450
$Comp
L power:+5V #PWR010
U 1 1 5F0B8272
P 7600 5900
F 0 "#PWR010" H 7600 5750 50  0001 C CNN
F 1 "+5V" V 7615 6028 50  0000 L CNN
F 2 "" H 7600 5900 50  0001 C CNN
F 3 "" H 7600 5900 50  0001 C CNN
	1    7600 5900
	0    1    1    0   
$EndComp
Text Label 8600 4350 0    51   ~ 0
RelSensor
Text Label 6500 5300 2    51   ~ 0
RelSensor
Text Label 6500 5400 2    51   ~ 0
Alarm1
Text Label 6500 5500 2    51   ~ 0
Alarm2
Text Label 6050 6300 0    51   ~ 0
RelStop
$Comp
L Diode:1N4005 D2
U 1 1 5F1DAC9A
P 5500 1250
F 0 "D2" H 5500 1034 50  0000 C CNN
F 1 "1N4005" H 5500 1125 50  0000 C CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 5500 1075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 5500 1250 50  0001 C CNN
	1    5500 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	4650 1000 4650 1650
$Comp
L Device:R R1
U 1 1 5EDF13DE
P 5000 1250
F 0 "R1" V 5200 1200 50  0000 L CNN
F 1 "68k1W" V 5115 1250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 4930 1250 50  0001 C CNN
F 3 "~" H 5000 1250 50  0001 C CNN
	1    5000 1250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4005 D1
U 1 1 5EE46930
P 5350 1500
F 0 "D1" H 5350 1284 50  0000 C CNN
F 1 "1N4005" H 5350 1375 50  0000 C CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 5350 1325 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 5350 1500 50  0001 C CNN
	1    5350 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	5350 1350 5350 1250
Wire Wire Line
	5350 1250 5150 1250
Connection ~ 5350 1250
Wire Wire Line
	4650 900  4850 900 
Wire Wire Line
	4850 900  4850 1250
Wire Wire Line
	4650 1650 5350 1650
Wire Wire Line
	5650 1250 5850 1250
Wire Wire Line
	5750 1650 5350 1650
Wire Wire Line
	5750 1450 5750 1650
Connection ~ 5350 1650
Wire Notes Line
	4200 550  7350 550 
$Comp
L Device:R Rb2
U 1 1 5EE658B5
P 10700 1650
F 0 "Rb2" V 10493 1650 50  0000 C CNN
F 1 "1k" V 10584 1650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 10630 1650 50  0001 C CNN
F 3 "~" H 10700 1650 50  0001 C CNN
	1    10700 1650
	0    1    1    0   
$EndComp
Wire Wire Line
	10850 1650 10950 1650
$Comp
L Transistor_BJT:BC337 Q2
U 1 1 5EE658C2
P 11150 1650
F 0 "Q2" H 11341 1696 50  0000 L CNN
F 1 "BC337" H 11341 1605 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92L_Wide" H 11350 1575 50  0001 L CIN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bc337.pdf" H 11150 1650 50  0001 L CNN
	1    11150 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	11250 650  11250 900 
Wire Notes Line
	10350 550  13150 550 
Wire Notes Line
	13150 2150 10350 2150
Wire Notes Line
	10350 2150 10350 550 
Text Notes 10650 2100 2    50   ~ 0
StopRel
$Comp
L power:GND #PWR018
U 1 1 5EE658E4
P 11250 1900
F 0 "#PWR018" H 11250 1650 50  0001 C CNN
F 1 "GND" H 11255 1727 50  0000 C CNN
F 2 "" H 11250 1900 50  0001 C CNN
F 3 "" H 11250 1900 50  0001 C CNN
	1    11250 1900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR017
U 1 1 5EE658EA
P 11250 650
F 0 "#PWR017" H 11250 500 50  0001 C CNN
F 1 "+5V" V 11265 778 50  0000 L CNN
F 2 "" H 11250 650 50  0001 C CNN
F 3 "" H 11250 650 50  0001 C CNN
	1    11250 650 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	11250 1900 11250 1850
Text Label 10500 1650 1    50   ~ 0
RelStart
Wire Wire Line
	10450 1650 10550 1650
Text Label 5950 6400 0    50   ~ 0
RelStart
Wire Wire Line
	5900 6400 6200 6400
$Comp
L Diode:1N4001 D3
U 1 1 5EE3FE81
P 8250 1250
F 0 "D3" V 8204 1329 50  0000 L CNN
F 1 "1N4001" V 8295 1329 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 8250 1075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 8250 1250 50  0001 C CNN
	1    8250 1250
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4001 D4
U 1 1 5EE41184
P 11250 1050
F 0 "D4" V 11204 1129 50  0000 L CNN
F 1 "1N4001" V 11295 1129 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 11250 875 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 11250 1050 50  0001 C CNN
	1    11250 1050
	0    1    1    0   
$EndComp
$Comp
L genv01_2-rescue:IRM-20-5-SamacSys_Parts PS1
U 1 1 5EE43B9F
P 1450 1050
F 0 "PS1" H 1950 1315 50  0000 C CNN
F 1 "IRM-20-5" H 1950 1224 50  0000 C CNN
F 2 "gen:IRM2024" H 2300 1150 50  0001 L CNN
F 3 "https://www.arrow.com/en/products/irm-20-5/mean-well-enterprises" H 2300 1050 50  0001 L CNN
F 4 "20W Single Output Encapsulated Type, Converter" H 2300 950 50  0001 L CNN "Description"
F 5 "24" H 2300 850 50  0001 L CNN "Height"
F 6 "Mean Well" H 2300 750 50  0001 L CNN "Manufacturer_Name"
F 7 "IRM-20-5" H 2300 650 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "IRM-20-5" H 2300 550 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/irm-20-5/mean-well-enterprises" H 2300 450 50  0001 L CNN "Arrow Price/Stock"
F 10 "709-IRM20-5" H 2300 350 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/MEAN-WELL/IRM-20-5?qs=WkdRfq4wf1PtpRVy5G6J8g%3D%3D" H 2300 250 50  0001 L CNN "Mouser Price/Stock"
	1    1450 1050
	1    0    0    -1  
$EndComp
$Comp
L genv01_2-rescue:ALQ105-SamacSys_Parts K1
U 1 1 5EE24F44
P 8800 650
F 0 "K1" V 9496 322 50  0000 R CNN
F 1 "ALQ105" V 9405 322 50  0000 R CNN
F 2 "gen:ALQ105" H 9950 750 50  0001 L CNN
F 3 "https://na.industrial.panasonic.com/products/relays/mechanical-power-relays/general/series/lq-relays/2635/model/ALQ105" H 9950 650 50  0001 L CNN
F 4 "SPDT PCB Mount Non-Latching Relay 10 A, 5V dc" H 9950 550 50  0001 L CNN "Description"
F 5 "15" H 9950 450 50  0001 L CNN "Height"
F 6 "Panasonic" H 9950 350 50  0001 L CNN "Manufacturer_Name"
F 7 "ALQ105" H 9950 250 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "ALQ105" H 9950 150 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/alq105/panasonic" H 9950 50  50  0001 L CNN "Arrow Price/Stock"
F 10 "769-ALQ105" H 9950 -50 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Panasonic-Industrial-Devices/ALQ105?qs=kkkG%2F8HgOiLTrZ6QoQqhfg%3D%3D" H 9950 -150 50  0001 L CNN "Mouser Price/Stock"
	1    8800 650 
	0    -1   1    0   
$EndComp
Wire Wire Line
	8250 650  8250 1100
Wire Wire Line
	8250 1400 8250 1450
Wire Notes Line
	13150 550  13150 2150
$Comp
L genv01_2-rescue:ALQ105-SamacSys_Parts K2
U 1 1 5EEE7D55
P 11850 2000
F 0 "K2" V 12546 1672 50  0000 R CNN
F 1 "ALQ105" V 12455 1672 50  0000 R CNN
F 2 "gen:ALQ105" H 13000 2100 50  0001 L CNN
F 3 "https://na.industrial.panasonic.com/products/relays/mechanical-power-relays/general/series/lq-relays/2635/model/ALQ105" H 13000 2000 50  0001 L CNN
F 4 "SPDT PCB Mount Non-Latching Relay 10 A, 5V dc" H 13000 1900 50  0001 L CNN "Description"
F 5 "15" H 13000 1800 50  0001 L CNN "Height"
F 6 "Panasonic" H 13000 1700 50  0001 L CNN "Manufacturer_Name"
F 7 "ALQ105" H 13000 1600 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "ALQ105" H 13000 1500 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/alq105/panasonic" H 13000 1400 50  0001 L CNN "Arrow Price/Stock"
F 10 "769-ALQ105" H 13000 1300 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Panasonic-Industrial-Devices/ALQ105?qs=kkkG%2F8HgOiLTrZ6QoQqhfg%3D%3D" H 13000 1200 50  0001 L CNN "Mouser Price/Stock"
	1    11850 2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	11250 1450 11650 1450
Wire Wire Line
	11650 1450 11650 2000
Wire Wire Line
	11650 2000 11850 2000
Wire Wire Line
	11250 1200 11250 1450
Connection ~ 11250 1450
Text Label 1450 1050 2    50   ~ 0
ACL
Text Label 1450 1150 2    50   ~ 0
ACN
$Comp
L power:+5V #PWR03
U 1 1 5EF552AC
P 2550 950
F 0 "#PWR03" H 2550 800 50  0001 C CNN
F 1 "+5V" H 2565 1123 50  0000 C CNN
F 2 "" H 2550 950 50  0001 C CNN
F 3 "" H 2550 950 50  0001 C CNN
	1    2550 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 1050 2550 1050
Wire Wire Line
	2550 1050 2550 950 
$Comp
L power:GND #PWR04
U 1 1 5EF637EF
P 2550 1250
F 0 "#PWR04" H 2550 1000 50  0001 C CNN
F 1 "GND" H 2555 1077 50  0000 C CNN
F 2 "" H 2550 1250 50  0001 C CNN
F 3 "" H 2550 1250 50  0001 C CNN
	1    2550 1250
	1    0    0    -1  
$EndComp
Text Label 14350 1300 0    50   ~ 0
StopNC
Wire Wire Line
	14150 850  14850 850 
Text Label 14200 1000 0    50   ~ 0
StartComm
Text Label 14350 1400 0    50   ~ 0
StopComm
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5EFDEEE1
P 2550 1050
F 0 "#FLG01" H 2550 1125 50  0001 C CNN
F 1 "PWR_FLAG" V 2550 1178 50  0000 L CNN
F 2 "" H 2550 1050 50  0001 C CNN
F 3 "~" H 2550 1050 50  0001 C CNN
	1    2550 1050
	0    1    1    0   
$EndComp
Connection ~ 2550 1050
Text Label 9100 1950 0    50   ~ 0
StopNC
$Comp
L power:PWR_FLAG #FLG03
U 1 1 5EE594E5
P 2750 5650
F 0 "#FLG03" H 2750 5725 50  0001 C CNN
F 1 "PWR_FLAG" H 2750 5823 50  0000 C CNN
F 2 "" H 2750 5650 50  0001 C CNN
F 3 "~" H 2750 5650 50  0001 C CNN
	1    2750 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 5650 2750 5650
Text Label 4650 900  0    50   ~ 0
ACL
Text Label 4650 1000 3    50   ~ 0
ACN
Wire Wire Line
	11250 650  11850 650 
Wire Wire Line
	11850 650  11850 700 
Connection ~ 11250 650 
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 5EF2E8D7
P 9300 5300
F 0 "J1" V 9500 5200 50  0000 R CNN
F 1 "Screw_Terminal_1x3" V 9400 5400 50  0001 R CNN
F 2 "gen:Screw_terminal_1x3_5.08mm" H 9300 5300 50  0001 C CNN
F 3 "~" H 9300 5300 50  0001 C CNN
	1    9300 5300
	1    0    0    -1  
$EndComp
Connection ~ 8250 650 
Wire Wire Line
	8250 650  8800 650 
Connection ~ 8250 1450
Wire Wire Line
	8250 1450 8600 1450
Wire Wire Line
	8600 1950 8800 1950
Wire Wire Line
	8600 1450 8600 1950
Text Label 12450 2000 2    50   ~ 0
StartNO
Text Label 11950 2100 3    50   ~ 0
StartComm
Wire Wire Line
	8900 650  8900 600 
Wire Wire Line
	8900 600  9700 600 
Wire Wire Line
	9700 600  9700 1300
Wire Notes Line
	7450 2150 10250 2150
Text Label 9700 1300 0    50   ~ 0
StopComm
Wire Wire Line
	11950 2000 11950 2100
Wire Wire Line
	11950 2100 12600 2100
NoConn ~ 5900 6700
NoConn ~ 5900 6800
NoConn ~ 5900 5000
NoConn ~ 5900 5100
NoConn ~ 5900 4400
NoConn ~ 5900 4500
NoConn ~ 5900 4600
$Comp
L Connector:Screw_Terminal_01x03 J3
U 1 1 5EE753B3
P 9300 4450
F 0 "J3" V 9500 4350 50  0000 R CNN
F 1 "Screw_Terminal_1x3" V 9400 4550 50  0001 R CNN
F 2 "gen:Screw_terminal_1x3_5.08mm" H 9300 4450 50  0001 C CNN
F 3 "~" H 9300 4450 50  0001 C CNN
	1    9300 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 5200 8850 5200
Wire Wire Line
	9100 5300 8850 5300
Wire Wire Line
	9100 5400 8850 5400
$Comp
L power:+5V #PWR014
U 1 1 5EE82246
P 8850 5400
F 0 "#PWR014" H 8850 5250 50  0001 C CNN
F 1 "+5V" V 8865 5528 50  0000 L CNN
F 2 "" H 8850 5400 50  0001 C CNN
F 3 "" H 8850 5400 50  0001 C CNN
	1    8850 5400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8850 5200 8850 5300
$Comp
L power:GND #PWR013
U 1 1 5EE86214
P 8850 5200
F 0 "#PWR013" H 8850 4950 50  0001 C CNN
F 1 "GND" V 8855 5072 50  0000 R CNN
F 2 "" H 8850 5200 50  0001 C CNN
F 3 "" H 8850 5200 50  0001 C CNN
	1    8850 5200
	0    1    1    0   
$EndComp
Connection ~ 8850 5200
Wire Wire Line
	5900 5300 6500 5300
Wire Wire Line
	5900 5400 6500 5400
Wire Wire Line
	5900 5500 6500 5500
Wire Wire Line
	5900 6600 6150 6600
Text Label 6000 6600 0    28   ~ 0
GSMPWR
$Comp
L Device:R R6
U 1 1 5EEB4341
P 15200 3850
F 0 "R6" H 15270 3896 50  0000 L CNN
F 1 "47k" H 15270 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 15130 3850 50  0001 C CNN
F 3 "~" H 15200 3850 50  0001 C CNN
	1    15200 3850
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5EEB4C5D
P 15450 3700
F 0 "R5" V 15243 3700 50  0000 C CNN
F 1 "4.7k" V 15334 3700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 15380 3700 50  0001 C CNN
F 3 "~" H 15450 3700 50  0001 C CNN
	1    15450 3700
	0    -1   1    0   
$EndComp
$Comp
L Transistor_BJT:BC547 Q3
U 1 1 5EEB5A9D
P 14900 3700
F 0 "Q3" H 15091 3746 50  0000 L CNN
F 1 "BC547" H 15091 3655 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92L_Wide" H 15100 3625 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 14900 3700 50  0001 L CNN
	1    14900 3700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	15300 3700 15200 3700
Wire Wire Line
	15200 3700 15100 3700
Connection ~ 15200 3700
Wire Wire Line
	15200 4000 15200 4050
Wire Wire Line
	15200 4050 15000 4050
Wire Wire Line
	14800 4050 14800 3900
$Comp
L power:GND #PWR019
U 1 1 5EEE2D91
P 15000 4100
F 0 "#PWR019" H 15000 3850 50  0001 C CNN
F 1 "GND" H 15005 3927 50  0000 C CNN
F 2 "" H 15000 4100 50  0001 C CNN
F 3 "" H 15000 4100 50  0001 C CNN
	1    15000 4100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	15000 4100 15000 4050
Connection ~ 15000 4050
Wire Wire Line
	15000 4050 14800 4050
Wire Wire Line
	15600 3700 15750 3700
Text Label 15750 3700 2    28   ~ 0
GSMPWR
$Comp
L Device:C C2
U 1 1 5EEF27DC
P 2750 5800
F 0 "C2" H 2865 5846 50  0000 L CNN
F 1 "100n" H 2865 5755 50  0000 L CNN
F 2 "gen:K104K10X7RF5UL2" H 2788 5650 50  0001 C CNN
F 3 "~" H 2750 5800 50  0001 C CNN
	1    2750 5800
	1    0    0    -1  
$EndComp
Connection ~ 2750 5650
$Comp
L Device:C C1
U 1 1 5EEF37BC
P 1950 5800
F 0 "C1" H 2065 5846 50  0000 L CNN
F 1 "100n" H 2065 5755 50  0000 L CNN
F 2 "gen:K104K10X7RF5UL2" H 1988 5650 50  0001 C CNN
F 3 "~" H 1950 5800 50  0001 C CNN
	1    1950 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 5900 7600 5900
$Comp
L power:+5V #PWR020
U 1 1 5EF7BD30
P 13800 4650
F 0 "#PWR020" H 13800 4500 50  0001 C CNN
F 1 "+5V" V 13815 4778 50  0000 L CNN
F 2 "" H 13800 4650 50  0001 C CNN
F 3 "" H 13800 4650 50  0001 C CNN
	1    13800 4650
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR021
U 1 1 5EF7D1C5
P 13800 4750
F 0 "#PWR021" H 13800 4500 50  0001 C CNN
F 1 "GND" V 13805 4622 50  0000 R CNN
F 2 "" H 13800 4750 50  0001 C CNN
F 3 "" H 13800 4750 50  0001 C CNN
	1    13800 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	13800 4650 13850 4650
Wire Wire Line
	13800 4750 13850 4750
Wire Wire Line
	13850 4850 13750 4850
Text Label 13750 4950 0    50   ~ 0
GRx
Text Label 13750 4850 0    50   ~ 0
GTx
Wire Wire Line
	13850 4950 13750 4950
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5EFDF8FB
P 2550 1150
F 0 "#FLG02" H 2550 1225 50  0001 C CNN
F 1 "PWR_FLAG" V 2550 1278 50  0000 L CNN
F 2 "" H 2550 1150 50  0001 C CNN
F 3 "~" H 2550 1150 50  0001 C CNN
	1    2550 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	2450 1150 2550 1150
Connection ~ 2550 1150
Wire Wire Line
	2550 1150 2550 1250
$Comp
L Device:R R7
U 1 1 5EF54B58
P 8350 4350
F 0 "R7" V 8350 4700 50  0000 L CNN
F 1 "30k" V 8350 4550 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8280 4350 50  0001 C CNN
F 3 "~" H 8350 4350 50  0001 C CNN
	1    8350 4350
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R8
U 1 1 5EF5840F
P 8350 4450
F 0 "R8" V 8350 4000 50  0000 L CNN
F 1 "30k" V 8350 4100 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8280 4450 50  0001 C CNN
F 3 "~" H 8350 4450 50  0001 C CNN
	1    8350 4450
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 5EF5BE75
P 8350 4550
F 0 "R9" V 8350 4100 50  0000 L CNN
F 1 "30k" V 8350 4200 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8280 4550 50  0001 C CNN
F 3 "~" H 8350 4550 50  0001 C CNN
	1    8350 4550
	0    1    1    0   
$EndComp
Wire Wire Line
	8500 4350 9100 4350
Wire Wire Line
	8500 4450 9100 4450
Wire Wire Line
	8500 4550 9100 4550
Wire Wire Line
	8200 4550 8200 4450
Wire Wire Line
	8200 4450 8200 4350
Connection ~ 8200 4450
Wire Wire Line
	8200 4350 8200 4200
Connection ~ 8200 4350
$Comp
L power:+5V #PWR022
U 1 1 5EF7D510
P 8200 4200
F 0 "#PWR022" H 8200 4050 50  0001 C CNN
F 1 "+5V" H 8215 4373 50  0000 C CNN
F 2 "" H 8200 4200 50  0001 C CNN
F 3 "" H 8200 4200 50  0001 C CNN
	1    8200 4200
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J2
U 1 1 5EF7DD27
P 9300 4850
F 0 "J2" V 9500 4750 50  0000 R CNN
F 1 "Screw_Terminal_1x3" V 9400 4950 50  0001 R CNN
F 2 "gen:Screw_terminal_1x3_5.08mm" H 9300 4850 50  0001 C CNN
F 3 "~" H 9300 4850 50  0001 C CNN
	1    9300 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 4750 8850 4750
Wire Wire Line
	9100 4850 8850 4850
Wire Wire Line
	9100 4950 8850 4950
Text Label 8850 4750 0    50   ~ 0
ADC1
Text Label 8600 4450 0    50   ~ 0
Alarm1
Text Label 8600 4550 0    50   ~ 0
Alarm2
$Comp
L genv01_2-rescue:SIM800C-mylib U3
U 1 1 5EF21209
P 12800 4000
F 0 "U3" H 13675 3877 50  0000 C CNN
F 1 "SIM800C" H 13675 3786 50  0000 C CNN
F 2 "Button_Switch_Keyboard:SIM800C" H 12800 4000 50  0001 C CNN
F 3 "" H 12800 4000 50  0001 C CNN
	1    12800 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	13100 3550 12800 3550
Wire Wire Line
	13100 3650 12800 3650
$Comp
L power:+5V #PWR023
U 1 1 5EF2F688
P 13450 3000
F 0 "#PWR023" H 13450 2850 50  0001 C CNN
F 1 "+5V" H 13350 3100 50  0000 C CNN
F 2 "" H 13450 3000 50  0001 C CNN
F 3 "" H 13450 3000 50  0001 C CNN
	1    13450 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 5EF308E3
P 13550 3000
F 0 "#PWR024" H 13550 2750 50  0001 C CNN
F 1 "GND" H 13450 2900 50  0000 C CNN
F 2 "" H 13550 3000 50  0001 C CNN
F 3 "" H 13550 3000 50  0001 C CNN
	1    13550 3000
	-1   0    0    1   
$EndComp
Wire Wire Line
	13550 3000 13550 3150
Wire Wire Line
	13450 3150 13450 3050
Text Label 12800 3550 0    50   ~ 0
GTx
Text Label 12800 3650 0    50   ~ 0
GRx
$Comp
L Connector:Conn_01x04_Female J4
U 1 1 5EF3F92E
P 14050 4750
F 0 "J4" H 14078 4726 50  0000 L CNN
F 1 "Conn_01x04_Female" H 14078 4635 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 14050 4750 50  0001 C CNN
F 3 "~" H 14050 4750 50  0001 C CNN
	1    14050 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	14250 3450 14800 3450
Wire Wire Line
	14800 3450 14800 3500
NoConn ~ 14250 3350
NoConn ~ 14250 3550
NoConn ~ 14250 3650
NoConn ~ 14250 3800
NoConn ~ 14250 3950
NoConn ~ 13100 3950
NoConn ~ 13100 3850
NoConn ~ 13100 3750
Wire Wire Line
	13450 3050 13050 3050
Wire Wire Line
	13050 3050 13050 3450
Wire Wire Line
	13050 3450 13100 3450
Connection ~ 13450 3050
Wire Wire Line
	13450 3050 13450 3000
Text Label 14200 1100 0    50   ~ 0
StartNO
Wire Wire Line
	14150 1300 14650 1300
Wire Wire Line
	14150 1400 14650 1400
Text Label 14550 850  0    50   ~ 0
ACL
Wire Wire Line
	5900 5600 6500 5600
Wire Wire Line
	5900 5700 6500 5700
$Comp
L power:+5V #PWR025
U 1 1 5EF9F1C4
P 8850 4950
F 0 "#PWR025" H 8850 4800 50  0001 C CNN
F 1 "+5V" V 8865 5078 50  0000 L CNN
F 2 "" H 8850 4950 50  0001 C CNN
F 3 "" H 8850 4950 50  0001 C CNN
	1    8850 4950
	0    -1   -1   0   
$EndComp
Text Label 6300 5600 0    50   ~ 0
ADC1
Text Label 8850 4850 0    50   ~ 0
ADC2
Text Label 6300 5700 0    50   ~ 0
ADC2
NoConn ~ 5900 5800
Wire Wire Line
	5900 4700 6350 4700
Wire Wire Line
	5900 6500 6550 6500
$Comp
L Connector:Screw_Terminal_01x02 J8
U 1 1 5F0964D4
P 13950 1300
F 0 "J8" H 14150 1300 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 14300 1200 50  0001 C CNN
F 2 "gen:Screw_terminal_1x2_5.08mm" H 13950 1300 50  0001 C CNN
F 3 "~" H 13950 1300 50  0001 C CNN
	1    13950 1300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	14150 750  14850 750 
Text Label 14300 750  0    50   ~ 0
ACN
$Comp
L Connector:Screw_Terminal_01x02 J7
U 1 1 5F096055
P 13950 1000
F 0 "J7" H 14100 1000 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 14400 900 50  0001 C CNN
F 2 "gen:Screw_terminal_1x2_5.08mm" H 13950 1000 50  0001 C CNN
F 3 "~" H 13950 1000 50  0001 C CNN
	1    13950 1000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	14150 1100 14200 1100
Wire Wire Line
	14150 1000 14200 1000
$Comp
L Connector:Screw_Terminal_01x02 J6
U 1 1 5F09501B
P 13950 750
F 0 "J6" H 14100 750 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 14350 650 50  0001 C CNN
F 2 "gen:Screw_terminal_1x2_5.08mm" H 13950 750 50  0001 C CNN
F 3 "~" H 13950 750 50  0001 C CNN
	1    13950 750 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5900 5900 6800 5900
Wire Wire Line
	12050 2000 12450 2000
Wire Wire Line
	8950 1950 9100 1950
NoConn ~ 12000 700 
NoConn ~ 9000 650 
$EndSCHEMATC
