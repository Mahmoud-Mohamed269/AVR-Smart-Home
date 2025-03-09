/*
 * MDIO_interface.h
 *
 *  Created on: Aug 2, 2023
 *      Author: Mahmoud
 *      Layer: MCAL
 *      Module: DIO Interface
 *      Version: 1.00
 */

#ifndef MCAL_DIO_MDIO_INTERFACE_H_
#define MCAL_DIO_MDIO_INTERFACE_H_

typedef enum{
	Return_Ok,
	Return_NOk,
	Return_NULLPointer
}Error_State_t;

#define DIO_INPUT 	0
#define DIO_OUTPUT 	1
#define DIO_LOW 	0
#define DIO_HIGH 	1

#define DIO_PORTA	1
#define DIO_PORTB	2
#define DIO_PORTC	3
#define DIO_PORTD	4

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4		4
#define PIN5		5
#define PIN6		6
#define PIN7		7

void Port_VoidInit(void);
//void MDIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Mode);
Error_State_t MDIO_SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);
Error_State_t MDIO_SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);
Error_State_t MDIO_GetPortValue(u8 Copy_u8Port, u8* P_u8Value);
Error_State_t MDIO_GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* P_u8Value);
Error_State_t MDIO_TogglePin(u8 Copy_u8Port, u8 Copy_u8Pin);

#endif /* MCAL_DIO_MDIO_INTERFACE_H_ */
