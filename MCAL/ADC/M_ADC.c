/*
 * M_ADC.c
 *
 *  Created on: Aug 9, 2023
 *      Author: Mahmoud
 *      Layer: MCAL
 *      Module: ADC Program
 *      Version: 1.00
 */

#include "../../STD_TYPES.h"
#include "../../BIT_MATH.h"
#include "M_ADC_private.h"
#include "M_ADC_interface.h"
#include "M_ADC_config.h"
#include "M_ADC_register.h"

void MADC_voidInit(void)
{
	/*Select VREF using AVCC mode*/
#if ADC_REFERENCE == AREF
	CLR_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);


#elif ADC_REFERENCE == AVCC
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

#elif ADC_REFERENCE == INTERNAL
	SET_BIT(ADMUX, ADMUX_REFS0);
	SET_BIT(ADMUX, ADMUX_REFS1);

#else
#warning "Invalid ADC Reference Selection "

#endif

	/*Select Right Adjust, the data size is 10 bits*/
	CLR_BIT(ADMUX, ADMUX_ADLAR);

	/*Set Prescaler MCU freq / 32*/
#if PRESCALER == DIV_2
	CLR_BIT(ADCSRA, ADCSRA_ADPS0);
	CLR_BIT(ADCSRA, ADCSRA_ADPS1);
	CLR_BIT(ADCSRA, ADCSRA_ADPS2);


#elif PRESCALER == DIV_4
	SET_BIT(ADCSRA, ADCSRA_ADPS0);
	CLR_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS2);

#elif PRESCALER == DIV_8
	SET_BIT(ADCSRA, ADCSRA_ADPS0);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	CLR_BIT(ADCSRA, ADCSRA_ADPS2);

#elif PRESCALER == DIV_16
	CLR_BIT(ADCSRA, ADCSRA_ADPS0);
	CLR_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS2);

#elif PRESCALER == DIV_32
	SET_BIT(ADCSRA, ADCSRA_ADPS0);
	CLR_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS2);

#elif PRESCALER == DIV_64
	CLR_BIT(ADCSRA, ADCSRA_ADPS0);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS2);

#elif PRESCALER == DIV_128
	SET_BIT(ADCSRA, ADCSRA_ADPS0);
	SET_BIT(ADCSRA, ADCSRA_ADPS1);
	SET_BIT(ADCSRA, ADCSRA_ADPS2);

#else
#warning "Invalid ADC Prescaler Selection "

#endif

	/*Enable ADC*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);
}

u16 MADC_u16GetValue(u8 copy_u8Channel)
{
	/*clear the first 5 bits to choose the ADC channel*/
	ADMUX &= 0b11100000;

	/*select the ADC channel*/
	ADMUX |= copy_u8Channel;

	/*ADC start conversion*/
	SET_BIT(ADCSRA, ADCSRA_ADSC);

	/*Busy wait until ADC complete conversion flag is set and counter reaching timeout*/
	while(GET_BIT(ADCSRA, ADCSRA_ADIF) == 0);
	/*clear the flag*/
	SET_BIT(ADCSRA, ADCSRA_ADIF);
	return ADC_DATA_REG;
}
