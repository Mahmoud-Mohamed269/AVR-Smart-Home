/*
 * MDIO_program.c
 *
 *  Created on: Aug 2, 2023
 *      Author: Mahmoud
 *      Layer: MCAL
 *      Module: DIO Program
 *      Version: 1.00
 */

#include "../../BIT_MATH.h"
#include "../../STD_TYPES.h"
#include "MDIO_register.h"
#include "MDIO_private.h"
#include "MDIO_interface.h"
#include "MDIO_config.h"

/*void MDIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Mode)
{
	if(Copy_u8Mode == DIO_INPUT)
	{
		switch(Copy_u8Port)
		{
		case DIO_PORTA:	CLR_BIT(DDRA, Copy_u8Pin);	break;
		case DIO_PORTB:	CLR_BIT(DDRB, Copy_u8Pin);	break;
		case DIO_PORTC:	CLR_BIT(DDRC, Copy_u8Pin);	break;
		case DIO_PORTD:	CLR_BIT(DDRD, Copy_u8Pin);	break;
		default:	break;
		}
	}
	else if(Copy_u8Mode == DIO_OUTPUT)
	{
		switch(Copy_u8Port)
		{
		case DIO_PORTA:	SET_BIT(DDRA, Copy_u8Pin);	break;
		case DIO_PORTB:	SET_BIT(DDRB, Copy_u8Pin);	break;
		case DIO_PORTC:	SET_BIT(DDRC, Copy_u8Pin);	break;
		case DIO_PORTD:	SET_BIT(DDRD, Copy_u8Pin);	break;
		default:	break;
		}
	}
}*/

Error_State_t MDIO_SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
	Error_State_t Error_state = Return_Ok;
	if(Copy_u8Pin > 7)
	{
		Error_state = Return_NOk;
	}
	else
	{
		if(Copy_u8Value == DIO_LOW)
		{
			switch(Copy_u8Port)
			{
			case DIO_PORTA:	CLR_BIT(PORTA, Copy_u8Pin);	break;
			case DIO_PORTB:	CLR_BIT(PORTB, Copy_u8Pin);	break;
			case DIO_PORTC:	CLR_BIT(PORTC, Copy_u8Pin);	break;
			case DIO_PORTD:	CLR_BIT(PORTD, Copy_u8Pin);	break;
			default:	Error_state = Return_NOk;	break;
			}
		}
		else if(Copy_u8Value == DIO_HIGH)
		{
			switch(Copy_u8Port)
			{
			case DIO_PORTA:	SET_BIT(PORTA, Copy_u8Pin);	break;
			case DIO_PORTB:	SET_BIT(PORTB, Copy_u8Pin);	break;
			case DIO_PORTC:	SET_BIT(PORTC, Copy_u8Pin);	break;
			case DIO_PORTD:	SET_BIT(PORTD, Copy_u8Pin);	break;
			default:	Error_state = Return_NOk;	break;
			}
		}
	}
	return Error_state;
}

Error_State_t MDIO_GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* P_u8Value)
{
	Error_State_t Error_state = Return_Ok;
	if(Copy_u8Pin > 7)
	{
		Error_state = Return_NOk;
	}
	else
	{
		switch(Copy_u8Port)
		{
		case DIO_PORTA:	*P_u8Value = GET_BIT(PINA, Copy_u8Pin);	break;
		case DIO_PORTB:	*P_u8Value = GET_BIT(PINB, Copy_u8Pin);	break;
		case DIO_PORTC:	*P_u8Value = GET_BIT(PINC, Copy_u8Pin);	break;
		case DIO_PORTD:	*P_u8Value = GET_BIT(PIND, Copy_u8Pin);	break;
		default:	Error_state = Return_NOk;					break;
		}
	}
	return Error_state;
}

Error_State_t MDIO_SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
	Error_State_t Error_state = Return_Ok;
	switch(Copy_u8Port)
	{
	case DIO_PORTA:	PORTA = Copy_u8Value;	break;
	case DIO_PORTB:	PORTB = Copy_u8Value;	break;
	case DIO_PORTC:	PORTC = Copy_u8Value;	break;
	case DIO_PORTD:	PORTD = Copy_u8Value;	break;
	default:	Error_state = Return_NOk;	break;
	}
	return Error_state;
}

Error_State_t MDIO_GetPortValue(u8 Copy_u8Port, u8* P_u8Value)
{
	Error_State_t Error_state = Return_Ok;
	switch(Copy_u8Port)
	{
	case DIO_PORTA:	*P_u8Value = GET_BIT(PORTA, Copy_u8Port);	break;
	case DIO_PORTB:	*P_u8Value = GET_BIT(PORTB, Copy_u8Port);	break;
	case DIO_PORTC:	*P_u8Value = GET_BIT(PORTC, Copy_u8Port);	break;
	case DIO_PORTD:	*P_u8Value = GET_BIT(PORTD, Copy_u8Port);	break;
	default:	Error_state = Return_NOk;						break;
	}
	return Error_state;
}

Error_State_t MDIO_TogglePin(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	Error_State_t Error_state = Return_Ok;
	if(Copy_u8Pin > 7)
	{
		Error_state = Return_NOk;
	}
	else
	{
		switch(Copy_u8Port)
		{
		case DIO_PORTA:	TOGGLE_BIT(PORTA, Copy_u8Pin);	break;
		case DIO_PORTB:	TOGGLE_BIT(PORTB, Copy_u8Pin);	break;
		case DIO_PORTC:	TOGGLE_BIT(PORTC, Copy_u8Pin);	break;
		case DIO_PORTD:	TOGGLE_BIT(PORTD, Copy_u8Pin);	break;
		default:	Error_state = Return_NOk;			break;
		}
	}
	return Error_state;
}


void Port_VoidInit(void)
{
	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;

	PORTA = PORTA_INIT_VAL;
	PORTB = PORTB_INIT_VAL;
	PORTC = PORTC_INIT_VAL;
	PORTD = PORTD_INIT_VAL;
}
