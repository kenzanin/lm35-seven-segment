#ifndef TR7SEG_H_INCLUDED
#define TR7SEG_H_INCLUDED

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

#define segSelecShift 0
#define segSelecDemul 0
#define segSelecDirec 1

/**
 * definisi PORT yang digunakan untuk seven Segment
 */
#define sevenSegPORT PORTD

/**
 * definisi jumlah seven segment yang digunakan
 */
#define SEVEN_SEGMEN_DIGIT 3

#define segSelector   PORTB

#define sevenSegmenSwitchingPeriode 215

/**
*   definisi pin uC yang terhubung dengan pin A0 pada 74HC138
*/
#define A0          0
/**
* definisi pin uC yang terhubung dengan pin A1 pada 74HC138
*/
#define A1          1
/**
* definisi pin uC yang terhubung dengan pin A2 pada 74HC138
*/
#define A2          2

/** \brief initialisasi fungsi untuk seven segment dengan switching transistor
 *
 * \param void
 * \return void
 *
 */
void tr7seg_init(void);

/** \brief berfungsi untuk merubah nilai integer kedalam bentuk BCD yang disimpan dalam
 * variable array global sevenSegBuffer contoh jika ingin menampilkan angka 1234 desimal
 * \code
 * decTo7seg(1234,4);
 * \endcode
 * maka pada variable
 * sevenSegBuffer[0]=4
 * sevenSegBuffer[1]=3
 * sevenSegBuffer[2]=2
 * sevenSegBuffer[3]=1
 * \param decimal uint32_t
 * \param digit uint8_t
 * \return void
 *
 */
void decTo7seg(uint32_t decimal,uint8_t digit);

#endif // TR7SEG_H_INCLUDED
