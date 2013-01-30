/**
 * @file
 * @author  kenzanin@gmail.com
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/lgpl.html
 *
 * @section DESCRIPTION
 *
 * Library ini digunakan untuk memudahkan driver seven segment
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "tr7seg.h"
#include "digital_io.h"

uint8_t sevenSegBuffer[SEVEN_SEGMEN_DIGIT]= {0};
uint8_t sevenSegmenKe=0;

void setupTimer10ms(void)
{
    // OVF saat 20ms dengan crystal 4e6hz
    TCNT0=sevenSegmenSwitchingPeriode;
    // enable 1024 prescaler
    TCCR0=_BV(CS02)|_BV(CS00);
    // enable interrupt
    TIMSK=_BV(TOIE0);
}

void tr7seg_init(void)
{
    port_output_lo(sevenSegPORT,8,0,1,2,3,4,5,6,7);
#if segSelecDirec == 1
    port_output_lo(segSelector,4,0,1,2,3);
#endif // segSelecDirec

    setupTimer10ms();
    sei();
}

//const __flash uint8_t seg7[]= {0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000010,0b11111000,0b10000000,0b10010000};
const __flash uint8_t seg7[]= {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};

uint8_t bcd(uint32_t number,uint8_t number_ke)
{
    uint8_t i=0;
    for(; i<number_ke; i++)
    {
        number/=10;
    }
    number%=10;
    return number;
}

void decTo7seg(uint32_t var01,uint8_t digit)
{
    uint8_t i=1;

    for(i=1; i<digit; i++)
    {
        sevenSegBuffer[i]=seg7[bcd(var01,i)];
    }
    sevenSegBuffer[0]=seg7[var01%10];
}


SIGNAL(TIMER0_OVF_vect)
{
    uint8_t var01=0;
    uint8_t var02=sevenSegPORT;
    TCNT0=sevenSegmenSwitchingPeriode;

    var01=segSelector;
    segSelector=0;
    var02=sevenSegBuffer[sevenSegmenKe];
    ++sevenSegmenKe;
    if(sevenSegmenKe>SEVEN_SEGMEN_DIGIT)sevenSegmenKe=0;

    if(var01==0)
    {
        var01=1;
    }else if(var01!=_BV(SEVEN_SEGMEN_DIGIT-1))
    {
        var01<<=1;
    }else
    {
        var01=0;
    }

    sevenSegPORT=var02;
    segSelector=var01;
}

