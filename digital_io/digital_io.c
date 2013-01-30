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
 * Library ini digunakan untuk memudahkan akses dan initialiasasi IO PORT
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

void ___port_setup(volatile uint8_t* PORT,const uint8_t flag01,const uint8_t __PORT)
{
    /*
    flag01
    1  = DDR  output
    2  = DDR  input
    4  = PORT 1
    8  = PORT 0
    */
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
    *(PORT)     =_port;
    *(PORT-1)   =_ddr;
}
