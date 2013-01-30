#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "digital_io.h"
#include "tr7seg.h"

void avr_init(void)
{
    adc10_init();
    tr7seg_init();
}

int main(void)
{
    uint32_t var01=0;
    avr_init();
    while(1)
    {
        var01=adc10_read(0);
        /*
        * seharusnya var01=var01*0.488 namun untuk menghindari perhitungan bilangan float, perhitungan
        * diganti menjadi var01=var01*488, var01=var01/1000
        */
        var01*=488;
        var01+=500; // round up
        var01/=1000;
        decTo7seg(var01,SEVEN_SEGMEN_DIGIT);
    };
    return 0;
}
