EESchema Schematic File Version 4
LIBS:Torch_PCB-cache
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
L Device:R R1
U 1 1 5DD815E3
P 2900 1900
F 0 "R1" V 2693 1900 50  0000 C CNN
F 1 "R" V 2784 1900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2830 1900 50  0001 C CNN
F 3 "~" H 2900 1900 50  0001 C CNN
	1    2900 1900
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5DD819DC
P 3550 1300
F 0 "R2" V 3343 1300 50  0000 C CNN
F 1 "R" V 3434 1300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3480 1300 50  0001 C CNN
F 3 "~" H 3550 1300 50  0001 C CNN
	1    3550 1300
	0    1    1    0   
$EndComp
$Comp
L Device:D D1
U 1 1 5DD81A31
P 4300 1700
F 0 "D1" H 4300 1916 50  0000 C CNN
F 1 "D" H 4300 1825 50  0000 C CNN
F 2 "Diode_THT:D_5W_P10.16mm_Horizontal" H 4300 1700 50  0001 C CNN
F 3 "~" H 4300 1700 50  0001 C CNN
	1    4300 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Female J1
U 1 1 5DD81B05
P 2250 1300
F 0 "J1" H 2277 1276 50  0000 L CNN
F 1 "ESP left side" H 2277 1185 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 2250 1300 50  0001 C CNN
F 3 "~" H 2250 1300 50  0001 C CNN
	1    2250 1300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Female J2
U 1 1 5DD81BCF
P 2950 1400
F 0 "J2" H 2844 775 50  0000 C CNN
F 1 "ESP right side" H 2844 866 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 2950 1400 50  0001 C CNN
F 3 "~" H 2950 1400 50  0001 C CNN
	1    2950 1400
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J7
U 1 1 5DD82050
P 4750 2100
F 0 "J7" H 4778 2126 50  0000 L CNN
F 1 "Switch side2" H 4778 2035 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 4750 2100 50  0001 C CNN
F 3 "~" H 4750 2100 50  0001 C CNN
	1    4750 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J6
U 1 1 5DD820D6
P 4750 1900
F 0 "J6" H 4777 1926 50  0000 L CNN
F 1 "Switch Side1" H 4777 1835 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 4750 1900 50  0001 C CNN
F 3 "~" H 4750 1900 50  0001 C CNN
	1    4750 1900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J3
U 1 1 5DD820FC
P 4750 1300
F 0 "J3" H 4778 1326 50  0000 L CNN
F 1 "ToDataIn" H 4778 1235 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 4750 1300 50  0001 C CNN
F 3 "~" H 4750 1300 50  0001 C CNN
	1    4750 1300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J5
U 1 1 5DD8212C
P 4750 1700
F 0 "J5" H 4777 1726 50  0000 L CNN
F 1 "5V" H 4777 1635 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 4750 1700 50  0001 C CNN
F 3 "~" H 4750 1700 50  0001 C CNN
	1    4750 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J4
U 1 1 5DD8215E
P 4750 1500
F 0 "J4" H 4777 1526 50  0000 L CNN
F 1 "GND" H 4777 1435 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 4750 1500 50  0001 C CNN
F 3 "~" H 4750 1500 50  0001 C CNN
	1    4750 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 1700 4450 1700
Wire Wire Line
	3150 1300 3400 1300
Wire Wire Line
	4150 1700 3950 1700
Wire Wire Line
	4550 1500 3650 1500
Wire Wire Line
	3650 1500 3650 1600
Wire Wire Line
	3650 1600 3150 1600
Wire Wire Line
	3700 1300 4550 1300
Wire Wire Line
	3950 1700 3950 1900
Wire Wire Line
	3950 1900 4550 1900
Connection ~ 3950 1700
Wire Wire Line
	3950 1700 3150 1700
Wire Wire Line
	2050 1400 1900 1400
Wire Wire Line
	1900 1400 1900 1900
Wire Wire Line
	1900 2100 4550 2100
Wire Wire Line
	3050 1900 3650 1900
Wire Wire Line
	3650 1900 3650 1600
Connection ~ 3650 1600
Wire Wire Line
	1900 1900 2750 1900
Connection ~ 1900 1900
Wire Wire Line
	1900 1900 1900 2100
$EndSCHEMATC
