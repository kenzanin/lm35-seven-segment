#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

/*
AVR ADC 10bit library
Copy-left kenzanin[AT]gmail[dot]com
License LGPLv3
*/

/**< sampling ADC sebagai filter data sederhana */
#define JUMLAH_SAMPLING 2
/**< setting ADC vref Mode (lihat datasheet) */
#define ADC_VREF_MODE   0

/** \brief setting ADC PORT untuk menjadi input dan mengaktifkan ADC dengan mode 10bit
 *
 * cara pakai
 * \code
 * adc10_init();
 * \endcode
 * \param void
 * \return void
 */
void adc10_init(void);

/** \brief membaca tegangan analog pada pin ADC nomer _channel dengan tingkat resolusi 10bit (lihat datahseet)
 *
 * cara pakai
 * \code
 * var16b=adc10_read(0) // untuk membaca ADC0
 * \endcode
 * \param _channel uint8_t
 * \return uint16_t
 *
 */
uint16_t adc10_read(uint8_t _channel);

#endif // ADC_H_INCLUDED
