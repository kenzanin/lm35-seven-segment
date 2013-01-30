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
 * Library ini digunakan untuk memudahkan akses dan initialiasasi ADC 10bit
 */

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "adc.h"

inline uint8_t pembagi_sampling(void)
{
    switch(JUMLAH_SAMPLING)
    {
    case  1:
        return 0;
        break;
    case  2:
        return 1;
        break;
    case  4:
        return 2;
        break;
    case  8:
        return 3;
        break;
    case 16:
        return 4;
        break;
    case 32:
        return 5;
        break;
    default:
        return 3;
        break;
    }
}

inline uint8_t div_factor(void)
{
    double  var01=F_CPU/200000.0;
    if (var01 <= 2.0)
    {
        return (uint8_t) 0;
    }
    else if(var01 > 2.0 && var01 <= 4.0)
    {
        return (uint8_t) (1<<ADPS1);
    }
    else if(var01 > 4.0 && var01 <= 8.0)
    {
        return (uint8_t) (1<<ADPS1)|(1<<ADPS0);
    }
    else if(var01 > 8.0 && var01 <= 16.0)
    {
        return (uint8_t) (1<<ADPS2);
    }
    else if(var01 > 16.0 && var01 <= 32.0)
    {
        return (uint8_t) (1<<ADPS2)|(1<<ADPS0);
    }
    else if(var01 > 32.0 && var01 <= 64.0)
    {
        return (uint8_t) (1<<ADPS2)|(1<<ADPS1);
    }
    else
    {
        return (uint8_t) (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    }
}

uint16_t adc10_read(uint8_t _channel)
{
    uint8_t  var01;
    uint16_t data_adc=0;
    for(var01=0; var01<JUMLAH_SAMPLING; ++var01)
    {
        ADMUX=_channel | ADC_VREF_MODE; // choose which ADC channel to read
        sleep_enable();                 // entering ADC noice canceler
        _delay_us(15);                  // delay 15 uS supaya sampling adc tidak terpengaruh oleh aktifitas uC
        ADCSRA|=(1<<ADSC);              // ADC mode singe read
        loop_until_bit_is_clear(ADCSRA,ADSC);         // tunggu hingga ADC selesai
        data_adc+=ADCW;                 // exit form ADC noice canceler
        sleep_disable();
    }
    data_adc>>=pembagi_sampling();
    return (uint16_t) data_adc;
}

void adc10_init(void)
{
#ifdef __AVR_ATmega16__
    PORTA=0x00;
    DDRA=0x00;
#endif // __AVR_ATmega16__
#ifdef __AVR_ATmega8__
    PORTC=0x00;
    DDRC=0x00;
#endif // __AVR_ATmega8__
    set_sleep_mode(SLEEP_MODE_ADC);
    ADMUX=ADC_VREF_MODE;    // ADC menggunakan VREF sesuai yang di tunjuk ACD_VREF_MODE
    ADCSRA |= div_factor(); // scale adc clock to 200Khz to meet max frekuency for 10bit adc
#ifdef __AVR_ATmega16__
    ADCSRA|=(1<<ADATE);     // setup single read
#endif // __AVR_ATmega16__
#ifdef __AVR_ATmega8__
    ADCSRA|=_BV(ADEN);      // setup single read
#endif // __AVR_ATmega8__
    SFIOR&=0x1F;
}
