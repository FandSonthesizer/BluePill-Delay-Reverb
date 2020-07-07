EESchema Schematic File Version 4
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
L Device:R R?
U 1 1 5EFB3522
P 1450 1650
F 0 "R?" V 1243 1650 50  0000 C CNN
F 1 "10k" V 1334 1650 50  0000 C CNN
F 2 "" V 1380 1650 50  0001 C CNN
F 3 "~" H 1450 1650 50  0001 C CNN
	1    1450 1650
	0    1    1    0   
$EndComp
Wire Wire Line
	1600 1650 1700 1650
$Comp
L Device:C C?
U 1 1 5EFB3698
P 1850 1650
F 0 "C?" V 1598 1650 50  0000 C CNN
F 1 "150n" V 1689 1650 50  0000 C CNN
F 2 "" H 1888 1500 50  0001 C CNN
F 3 "~" H 1850 1650 50  0001 C CNN
	1    1850 1650
	0    1    1    0   
$EndComp
Wire Wire Line
	2000 1650 2100 1650
$Comp
L Device:R R?
U 1 1 5EFB36FF
P 2100 2000
F 0 "R?" H 2030 1954 50  0000 R CNN
F 1 "10k" H 2030 2045 50  0000 R CNN
F 2 "" V 2030 2000 50  0001 C CNN
F 3 "~" H 2100 2000 50  0001 C CNN
	1    2100 2000
	-1   0    0    1   
$EndComp
Wire Wire Line
	2100 1850 2100 1650
Wire Wire Line
	2100 2150 2100 2275
$Comp
L power:GND #PWR?
U 1 1 5EFB3793
P 2100 2275
F 0 "#PWR?" H 2100 2025 50  0001 C CNN
F 1 "GND" H 2105 2102 50  0000 C CNN
F 2 "" H 2100 2275 50  0001 C CNN
F 3 "" H 2100 2275 50  0001 C CNN
	1    2100 2275
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NJFET_DSG Q?
U 1 1 5EFB37F6
P 2425 1650
F 0 "Q?" H 2616 1696 50  0000 L CNN
F 1 "Q_NJFET_DSG" H 2650 1875 50  0000 L CNN
F 2 "" H 2625 1750 50  0001 C CNN
F 3 "~" H 2425 1650 50  0001 C CNN
	1    2425 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2225 1650 2100 1650
Connection ~ 2100 1650
Wire Wire Line
	2525 1850 2525 1875
$Comp
L Device:R R?
U 1 1 5EFB3867
P 2525 2075
F 0 "R?" H 2455 2029 50  0000 R CNN
F 1 "10k" H 2455 2120 50  0000 R CNN
F 2 "" V 2455 2075 50  0001 C CNN
F 3 "~" H 2525 2075 50  0001 C CNN
	1    2525 2075
	-1   0    0    1   
$EndComp
Wire Wire Line
	2525 2225 2525 2275
$Comp
L power:GND #PWR?
U 1 1 5EFB38D1
P 2525 2275
F 0 "#PWR?" H 2525 2025 50  0001 C CNN
F 1 "GND" H 2530 2102 50  0000 C CNN
F 2 "" H 2525 2275 50  0001 C CNN
F 3 "" H 2525 2275 50  0001 C CNN
	1    2525 2275
	1    0    0    -1  
$EndComp
Wire Wire Line
	2525 1450 2525 1250
Text GLabel 2525 1250 1    50   Input ~ 0
V+
Wire Wire Line
	2525 1875 2950 1875
Connection ~ 2525 1875
Wire Wire Line
	2525 1875 2525 1925
$Comp
L Device:C C?
U 1 1 5EFB39D0
P 3100 1875
F 0 "C?" V 2848 1875 50  0000 C CNN
F 1 "470n" V 2939 1875 50  0000 C CNN
F 2 "" H 3138 1725 50  0001 C CNN
F 3 "~" H 3100 1875 50  0001 C CNN
	1    3100 1875
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5EFB3A46
P 3450 1875
F 0 "R?" V 3243 1875 50  0000 C CNN
F 1 "10k" V 3334 1875 50  0000 C CNN
F 2 "" V 3380 1875 50  0001 C CNN
F 3 "~" H 3450 1875 50  0001 C CNN
	1    3450 1875
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 1875 3250 1875
$Comp
L Amplifier_Operational:TL072 U?
U 1 1 5EFB3B1F
P 4125 1775
F 0 "U?" H 4125 2142 50  0000 C CNN
F 1 "TL072" H 4125 2051 50  0000 C CNN
F 2 "" H 4125 1775 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 4125 1775 50  0001 C CNN
	1    4125 1775
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL072 U?
U 3 1 5EFB3C0B
P 4125 1775
F 0 "U?" H 4083 1821 50  0000 L CNN
F 1 "TL072" H 4083 1730 50  0000 L CNN
F 2 "" H 4125 1775 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 4125 1775 50  0001 C CNN
	3    4125 1775
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EFB3C5F
P 4025 2125
F 0 "#PWR?" H 4025 1875 50  0001 C CNN
F 1 "GND" H 4030 1952 50  0000 C CNN
F 2 "" H 4025 2125 50  0001 C CNN
F 3 "" H 4025 2125 50  0001 C CNN
	1    4025 2125
	1    0    0    -1  
$EndComp
Wire Wire Line
	4025 2125 4025 2075
Wire Wire Line
	4025 1475 4025 1325
Text GLabel 4025 1325 1    50   Input ~ 0
V+
$Comp
L Device:R R?
U 1 1 5EFB3DB5
P 1300 2725
F 0 "R?" H 1230 2679 50  0000 R CNN
F 1 "10k" H 1230 2770 50  0000 R CNN
F 2 "" V 1230 2725 50  0001 C CNN
F 3 "~" H 1300 2725 50  0001 C CNN
	1    1300 2725
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5EFB3E3F
P 1300 3125
F 0 "R?" H 1230 3079 50  0000 R CNN
F 1 "10k" H 1230 3170 50  0000 R CNN
F 2 "" V 1230 3125 50  0001 C CNN
F 3 "~" H 1300 3125 50  0001 C CNN
	1    1300 3125
	-1   0    0    1   
$EndComp
Wire Wire Line
	1300 2975 1300 2900
Wire Wire Line
	1300 3275 1300 3375
$Comp
L power:GND #PWR?
U 1 1 5EFB4065
P 1300 3375
F 0 "#PWR?" H 1300 3125 50  0001 C CNN
F 1 "GND" H 1305 3202 50  0000 C CNN
F 2 "" H 1300 3375 50  0001 C CNN
F 3 "" H 1300 3375 50  0001 C CNN
	1    1300 3375
	1    0    0    -1  
$EndComp
Text GLabel 1300 2425 1    50   Input ~ 0
V+
Wire Wire Line
	1300 2575 1300 2425
Wire Wire Line
	1300 2900 1575 2900
Connection ~ 1300 2900
Wire Wire Line
	1300 2900 1300 2875
Text GLabel 1575 2900 2    50   Input ~ 0
VRef
Text GLabel 3825 1675 0    50   Input ~ 0
VRef
$Comp
L Device:R R?
U 1 1 5EFB43F4
P 4200 2550
F 0 "R?" V 3993 2550 50  0000 C CNN
F 1 "33k" V 4084 2550 50  0000 C CNN
F 2 "" V 4130 2550 50  0001 C CNN
F 3 "~" H 4200 2550 50  0001 C CNN
	1    4200 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 2550 4550 2550
Wire Wire Line
	4550 2550 4550 1775
Wire Wire Line
	4550 1775 4425 1775
Wire Wire Line
	4050 2550 3700 2550
Wire Wire Line
	3700 2550 3700 1875
Wire Wire Line
	3600 1875 3700 1875
Connection ~ 3700 1875
Wire Wire Line
	3700 1875 3825 1875
$Comp
L Device:C C?
U 1 1 5EFB48C3
P 4200 2875
F 0 "C?" V 3948 2875 50  0000 C CNN
F 1 "47p" V 4039 2875 50  0000 C CNN
F 2 "" H 4238 2725 50  0001 C CNN
F 3 "~" H 4200 2875 50  0001 C CNN
	1    4200 2875
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 2875 4550 2875
Wire Wire Line
	4550 2875 4550 2550
Connection ~ 4550 2550
Wire Wire Line
	4050 2875 3700 2875
Wire Wire Line
	3700 2875 3700 2550
Connection ~ 3700 2550
$Comp
L Device:C C?
U 1 1 5EFB4EF1
P 4950 1775
F 0 "C?" V 4698 1775 50  0000 C CNN
F 1 "470n" V 4789 1775 50  0000 C CNN
F 2 "" H 4988 1625 50  0001 C CNN
F 3 "~" H 4950 1775 50  0001 C CNN
	1    4950 1775
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 1775 4550 1775
Connection ~ 4550 1775
Wire Wire Line
	5100 1775 5250 1775
$Comp
L Device:R R?
U 1 1 5EFB55F5
P 5250 2100
F 0 "R?" H 5180 2054 50  0000 R CNN
F 1 "100k" H 5180 2145 50  0000 R CNN
F 2 "" V 5180 2100 50  0001 C CNN
F 3 "~" H 5250 2100 50  0001 C CNN
	1    5250 2100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5EFB5671
P 5250 1425
F 0 "R?" H 5180 1379 50  0000 R CNN
F 1 "100k" H 5180 1470 50  0000 R CNN
F 2 "" V 5180 1425 50  0001 C CNN
F 3 "~" H 5250 1425 50  0001 C CNN
	1    5250 1425
	-1   0    0    1   
$EndComp
Wire Wire Line
	5250 1950 5250 1775
Wire Wire Line
	5250 1775 5250 1575
Connection ~ 5250 1775
Wire Wire Line
	5250 2250 5250 2400
$Comp
L power:GND #PWR?
U 1 1 5EFB6261
P 5250 2550
F 0 "#PWR?" H 5250 2300 50  0001 C CNN
F 1 "GND" H 5255 2377 50  0000 C CNN
F 2 "" H 5250 2550 50  0001 C CNN
F 3 "" H 5250 2550 50  0001 C CNN
	1    5250 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 1275 5250 1225
Text GLabel 5250 1125 0    50   Input ~ 0
3V3
Wire Wire Line
	5250 1775 5525 1775
Text GLabel 5675 1775 2    50   Input ~ 0
ToADC
$Comp
L Diode:BAT41 D?
U 1 1 5EFB6C24
P 5525 1625
F 0 "D?" V 5479 1704 50  0000 L CNN
F 1 "BAT85" V 5570 1704 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5525 1450 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85659/bat41.pdf" H 5525 1625 50  0001 C CNN
	1    5525 1625
	0    1    1    0   
$EndComp
Connection ~ 5525 1775
Wire Wire Line
	5525 1775 5675 1775
Wire Wire Line
	5525 1475 5525 1225
Wire Wire Line
	5525 1225 5250 1225
Connection ~ 5250 1225
Wire Wire Line
	5250 1225 5250 1125
$Comp
L Diode:BAT41 D?
U 1 1 5EFB71A5
P 5525 2100
F 0 "D?" V 5479 2179 50  0000 L CNN
F 1 "BAT85" V 5570 2179 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5525 1925 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85659/bat41.pdf" H 5525 2100 50  0001 C CNN
	1    5525 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	5525 1950 5525 1775
Wire Wire Line
	5525 2250 5525 2400
Wire Wire Line
	5525 2400 5250 2400
Connection ~ 5250 2400
Wire Wire Line
	5250 2400 5250 2550
Text Notes 5575 2325 0    50   ~ 0
Chip protection
$EndSCHEMATC
