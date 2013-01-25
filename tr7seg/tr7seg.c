#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "tr7seg.h"
#include "digital_io.h"

uint8_t sevenSegBuffer[SEVEN_SEGMEN_DIGIT]= {0xff};
uint8_t sevenSegmenKe=0;

void setupTimer10ms(void)
{
    //! OVF saat 20ms dengan crystal 4e6hz
    TCNT0=215;
    //! enable 1024 prescaler
    TCCR0=_BV(CS02)|_BV(CS00);
    //! enable interrupt
    TIMSK=_BV(TOIE0);
}

void tr7seg_init(void)
{
    port_output_lo(sevenSegPORT,8,0,1,2,3,4,5,6,7);
    port_output_hi(demulPORT,3,A0,A1,A2);
    setupTimer10ms();
    sei();
}

const __flash uint8_t seg7[]= {0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000010,0b11111000,0b10000000,0b10010000};

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

void decTo7seg(uint32_t var01,uint8_t digit,uint8_t *hasil)
{
    uint8_t i=1;

    for(i=1; i<digit; i++)
    {
        hasil[i]=seg7[bcd(var01,i)];
    }
    hasil[0]=seg7[var01%10];
}


SIGNAL(TIMER0_OVF_vect)
{
    TCNT0=215;
    demulPORT=7;
    sevenSegPORT=sevenSegBuffer[sevenSegmenKe];
    demulPORT=sevenSegmenKe;
    sevenSegmenKe++;
    if(sevenSegmenKe>SEVEN_SEGMEN_DIGIT)sevenSegmenKe=0;
}
