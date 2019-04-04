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

#include "main.h"

unsigned char timerPos = 0;

int main() 
{
    unsigned char portStatus = 0x03;
    unsigned char lastStatus = 0x03;
    unsigned char tempVal; 
    
    // Initialize system and load last Traic timing value from E2PROM.
    initSystem();
    __delay_ms(10);
    triggerTime = eeprom_read(0x00);
    
    // Clamp Traic timing value into valid range.
    if((triggerTime < MIN_TIME) || (triggerTime > MAX_TIME))
    {
        triggerTime = 100;
    }
    
    while(1)
    {
        portStatus = GPIO;
        
        // Handle INC button event.
        if(((portStatus & 0x10) == 0x10) && ((lastStatus & 0x10) == 0x00))
        {
            triggerTime = (triggerTime > 5 + MIN_TIME) ? (triggerTime - 5) : MIN_TIME;
            eeprom_write(0x00, triggerTime);
        }
        
        // Handle DEC button event.
        if(((portStatus & 0x20) == 0x20) && ((lastStatus & 0x20) == 0x00))
        {
            tempVal = triggerTime;
            tempVal += 5;
            
            if(tempVal >= MAX_TIME)
            {
                tempVal = MAX_TIME;
            }
            
            triggerTime = tempVal;
            eeprom_write(0x00, triggerTime);
        }
        
        lastStatus = portStatus;
        __delay_ms(10);
    }
    
    return 0;
}

void __interrupt () interruptHandler()
{
    // Check POWER button status.
    if((GPIO & 0x8) == 0x0)
    {
        // Edge interrupt handler to manage first 180 degrees of the wave.
        if((INTCON & 0x02) == 0x02)
        {
            // Timer 0 is set to handle 50Hz AC line.
				TMR0 = 90; 
            INTCON = 0xE0;

            for(timerPos = 0; timerPos < triggerTime; timerPos++)
            {
                __delay_us(50);
            }

            GPIO = 0x00;
            __delay_us(50);
            GPIO = 0x03;
        }

        // Timer0 interrupt handler to manage remaining 180 degrees of the wave. 
        if((INTCON & 0x04) == 0x04) 
        {
            NOP();
            NOP();

            for(timerPos = 0; timerPos < triggerTime; timerPos++)
            {
                __delay_us(50);
            }

            GPIO = 0x00;
            __delay_us(50);
            GPIO = 0x03;

            INTCON = 0xD0;
        }
    }
    else 
    {
        // POWER button is in OFF state and therefor ignore all interrupts.
        GPIO = 0x03;
        INTCON = 0xD0;
    }
}

void initSystem()
{
    triggerTime = 100;
    
    // Setup GPIO port of the PIC16F629 MCU.
    GPIO = 0x03;
    TRISIO = 0x3C;
    
    // Configure pull-up for GPIO port.
    OPTION_REG = 0x45;
    WPU = 0x38;

    // Disable comparator and enable interrupts.
    CMCON = 0x07;
    INTCON = 0xD0;
}
