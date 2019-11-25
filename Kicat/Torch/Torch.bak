EESchema Schematic File Version 4
LIBS:Torch-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+5V #PWR?
U 1 1 5DD68005
P 6700 4850
F 0 "#PWR?" H 6700 4700 50  0001 C CNN
F 1 "+5V" H 6715 5023 50  0000 C CNN
F 2 "" H 6700 4850 50  0001 C CNN
F 3 "" H 6700 4850 50  0001 C CNN
	1    6700 4850
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DD68066
P 6400 4750
F 0 "#PWR?" H 6400 4500 50  0001 C CNN
F 1 "GND" H 6405 4577 50  0000 C CNN
F 2 "" H 6400 4750 50  0001 C CNN
F 3 "" H 6400 4750 50  0001 C CNN
	1    6400 4750
	1    0    0    -1  
$EndComp
$Comp
L RF_Module:ESP-12F U?
U 1 1 5DD680CE
P 2450 1800
F 0 "U?" H 2450 2778 50  0000 C CNN
F 1 "ESP-12F" H 2450 2687 50  0000 C CNN
F 2 "RF_Module:ESP-12E" H 2450 1800 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 2100 1900 50  0001 C CNN
	1    2450 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DD68309
P 3350 1600
F 0 "R?" V 3143 1600 50  0000 C CNN
F 1 "470Ohm" V 3234 1600 50  0000 C CNN
F 2 "" V 3280 1600 50  0001 C CNN
F 3 "~" H 3350 1600 50  0001 C CNN
	1    3350 1600
	0    1    1    0   
$EndComp
Text GLabel 9000 2300 2    50   Input ~ 0
Data_inNeopixel
Text GLabel 9000 2550 2    50   Input ~ 0
GND_Bottom_Neopixel
Text GLabel 9000 3100 2    50   Input ~ 0
GND_Top_Neopixel
Text GLabel 9000 3400 2    50   Input ~ 0
5V_Top_Neopixel
Text GLabel 9000 2850 2    50   Input ~ 0
5V_Bottom_Neopixel
$Comp
L Switch:SW_Push SW?
U 1 1 5DD68910
P 8000 1600
F 0 "SW?" H 8000 1885 50  0000 C CNN
F 1 "SW_Push" H 8000 1794 50  0000 C CNN
F 2 "" H 8000 1800 50  0001 C CNN
F 3 "" H 8000 1800 50  0001 C CNN
	1    8000 1600
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_DPST_x2 SW?
U 1 1 5DD68A5C
P 6700 4350
F 0 "SW?" H 6700 4585 50  0000 C CNN
F 1 "SW_DPST_x2" H 6700 4494 50  0000 C CNN
F 2 "" H 6700 4350 50  0001 C CNN
F 3 "" H 6700 4350 50  0001 C CNN
	1    6700 4350
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DD68367
P 3350 3000
F 0 "R?" V 3143 3000 50  0000 C CNN
F 1 "10k" V 3234 3000 50  0000 C CNN
F 2 "" V 3280 3000 50  0001 C CNN
F 3 "~" H 3350 3000 50  0001 C CNN
	1    3350 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1800 3350 1800
Connection ~ 3350 1800
$Comp
L Device:D D?
U 1 1 5DD81266
P 4250 3350
F 0 "D?" V 4204 3429 50  0000 L CNN
F 1 "D" V 4295 3429 50  0000 L CNN
F 2 "" H 4250 3350 50  0001 C CNN
F 3 "~" H 4250 3350 50  0001 C CNN
	1    4250 3350
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 5DD8509F
P 7100 2550
F 0 "J?" H 7206 2828 50  0000 C CNN
F 1 "MR30-Connector" H 7206 2737 50  0000 C CNN
F 2 "" H 7100 2550 50  0001 C CNN
F 3 "~" H 7100 2550 50  0001 C CNN
	1    7100 2550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female J?
U 1 1 5DD851D5
P 6900 2550
F 0 "J?" H 6928 2576 50  0000 L CNN
F 1 "MR30_Connector" H 6928 2485 50  0000 L CNN
F 2 "" H 6900 2550 50  0001 C CNN
F 3 "~" H 6900 2550 50  0001 C CNN
	1    6900 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 3100 8300 2550
Connection ~ 8300 2550
Wire Wire Line
	8200 3400 8200 2850
Connection ~ 8200 2850
Wire Wire Line
	7300 2850 7300 2650
Wire Wire Line
	8700 2300 9000 2300
Wire Wire Line
	7300 2450 8700 2450
Wire Wire Line
	8700 2450 8700 2300
Wire Wire Line
	6400 2550 6700 2550
Wire Wire Line
	3050 1600 3200 1600
Wire Wire Line
	6700 4550 6700 4850
Wire Wire Line
	3350 1800 8000 1800
Wire Wire Line
	8000 1400 4250 1400
Wire Wire Line
	4250 1400 4250 3200
Wire Wire Line
	3500 1600 3800 1600
Wire Wire Line
	3800 1600 3800 2450
Wire Wire Line
	3800 2450 6700 2450
Wire Wire Line
	4250 1000 4250 1400
Wire Wire Line
	2450 1000 4250 1000
Connection ~ 4250 1400
Wire Wire Line
	7950 2850 7300 2850
Wire Wire Line
	8200 2850 7950 2850
Connection ~ 7950 2850
Wire Wire Line
	7950 2550 7300 2550
Wire Wire Line
	8300 2550 7950 2550
Connection ~ 7950 2550
$Comp
L Device:CP C?
U 1 1 5DD6AF48
P 7950 2700
F 0 "C?" V 7698 2700 50  0000 C CNN
F 1 "1000u" V 7789 2700 50  0000 C CNN
F 2 "" H 7988 2550 50  0001 C CNN
F 3 "~" H 7950 2700 50  0001 C CNN
	1    7950 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 2850 8200 2850
Wire Wire Line
	9000 2850 8800 2850
Connection ~ 8800 2850
Wire Wire Line
	8800 2550 8300 2550
Wire Wire Line
	9000 2550 8800 2550
Connection ~ 8800 2550
$Comp
L Device:CP C?
U 1 1 5DD68C9F
P 8800 2700
F 0 "C?" V 8548 2700 50  0000 C CNN
F 1 "470u" V 8639 2700 50  0000 C CNN
F 2 "" H 8838 2550 50  0001 C CNN
F 3 "~" H 8800 2700 50  0001 C CNN
	1    8800 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 3400 8800 3400
Wire Wire Line
	9000 3400 8800 3400
Connection ~ 8800 3400
Wire Wire Line
	8300 3100 8800 3100
Wire Wire Line
	8800 3100 9000 3100
Connection ~ 8800 3100
$Comp
L Device:CP C?
U 1 1 5DD68D2B
P 8800 3250
F 0 "C?" V 8548 3250 50  0000 C CNN
F 1 "470u" V 8639 3250 50  0000 C CNN
F 2 "" H 8838 3100 50  0001 C CNN
F 3 "~" H 8800 3250 50  0001 C CNN
	1    8800 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 2500 2450 3400
Wire Wire Line
	3350 1800 3350 2850
Wire Wire Line
	3350 3150 3350 3400
Wire Wire Line
	3350 3400 2450 3400
Wire Notes Line
	1700 700  5200 700 
Wire Notes Line
	5200 700  5200 3600
Wire Notes Line
	1700 3600 1700 700 
Text Notes 1750 800  0    50   ~ 0
On hole grid pcb
Wire Notes Line
	5200 1000 8500 1000
Text Notes 5850 1150 0    50   ~ 0
Flexible wired
Wire Wire Line
	6400 2550 6400 4200
Wire Wire Line
	6700 2650 6700 4000
Wire Wire Line
	4250 3500 4250 4000
Wire Wire Line
	4250 4000 6700 4000
Connection ~ 6700 4000
Wire Wire Line
	6700 4000 6700 4150
Wire Wire Line
	3350 3400 3350 4200
Wire Wire Line
	3350 4200 6400 4200
Connection ~ 3350 3400
Connection ~ 6400 4200
Wire Wire Line
	6400 4200 6400 4750
Wire Notes Line
	10000 2100 10000 3600
Text Notes 7350 3550 0    50   ~ 0
Installed in cardboard roll
Wire Notes Line
	10000 2100 7000 2100
Wire Notes Line
	8500 1000 8500 2100
Wire Notes Line
	1700 3600 10000 3600
Wire Notes Line
	3100 3600 3100 5000
Wire Notes Line
	3100 5000 7000 5000
Wire Notes Line
	7000 2100 7000 5000
Text Notes 3300 4900 0    50   ~ 0
installed in lower box
$EndSCHEMATC
