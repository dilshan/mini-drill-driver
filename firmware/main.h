/*******************************************************************************
 Copyright (c) 2019 Dilshan R Jayakody. [jayakody2000lk@gmail.com]

 Permission is hereby granted, free of charge, to any person obtaining a copy of 
 this software and associated documentation files (the "Software"), to deal in 
 the Software without restriction, including without limitation the rights to 
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do 
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 SOFTWARE.
 ******************************************************************************/

#ifndef MAIN_H
#define	MAIN_H

// PIC12F629 configuration bits.
#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config BOREN = ON
#pragma config CP = OFF
#pragma config CPD = OFF

// Use internal oscillator which is calibrated for 4MHz.
#define _XTAL_FREQ 4000000

#include <xc.h>

// Lower and upper limits of the Triac firing timer [range is 10 to 165]
// For INGCO MG1502.2 this is between 10 to 130.
#define MAX_TIME 130
#define MIN_TIME 10

// Default E2PROM configuration.
__EEPROM_DATA(MAX_TIME, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);

unsigned char triggerTime;

void initSystem(void);

#endif	/* MAIN_H */

