/*
 * kenzanin AVR Pin Input Output Driver
 * license LGPLv3
 * Copy-left kenzanin[at]gmail[dot]com
 */
#include <avr/io.h>
#include <stdarg.h>
#include "digital_io.h"

const uint8_t argsToNumber(const uint8_t n,...)
{
    uint8_t i=0;
    uint8_t ii=0;

    va_list lst;
    va_start(lst,n);
    for(; i<n ; ++i)
    {
        ii|=_BV(va_arg ( lst, int));
    }
    va_end(lst);
    return ii;
}

/*
flag01
1  = DDR  output
2  = DDR  input
4  = PORT 1
8  = PORT 0
*/
void ___port_setup(volatile uint8_t* PORT,const uint8_t flag01,const uint8_t __PORT)
{
    uint8_t _port=*PORT;
    uint8_t _ddr =*(PORT-1);

    if(flag01&0x01)
    {
        _ddr|=__PORT;
    }
    else if(flag01&0x02)
    {
        _ddr&=~(__PORT);
    }

    if(flag01&0x04)
    {
        _port|=__PORT;
    }
    else if(flag01&0x08)
    {
        _port&=~(__PORT);
    }
    *PORT    =_port;
    *(PORT-1)=_ddr;
}
