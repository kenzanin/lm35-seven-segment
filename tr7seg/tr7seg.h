#ifndef TR7SEG_H_INCLUDED
#define TR7SEG_H_INCLUDED

#define sevenSegPORT PORTD

/**< demultiplexer menggunakan 74HC138 */
#define demulPORT   PORTB
#define A0          0
#define A1          1
#define A2          2

#define SEVEN_SEGMEN_DIGIT 4

extern uint8_t sevenSegBuffer[SEVEN_SEGMEN_DIGIT];
void tr7seg_init(void);
void decTo7seg(uint32_t decimal,uint8_t digit,uint8_t *hasil);

#endif // TR7SEG_H_INCLUDED
