/*
 * M_ADC_interface.h
 *
 *  Created on: Aug 9, 2023
 *      Author: Mahmoud
 *      Layer: MCAL
 *      Module: ADC Interface
 *      Version: 1.00
 */

#ifndef MCAL_ADC_M_ADC_INTERFACE_H_
#define MCAL_ADC_M_ADC_INTERFACE_H_

void MADC_voidInit(void);
u16 MADC_u16GetValue(u8 copy_u8Channel);

#endif /* MCAL_ADC_M_ADC_INTERFACE_H_ */
