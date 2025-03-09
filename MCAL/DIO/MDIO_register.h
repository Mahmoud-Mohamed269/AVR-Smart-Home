/*
 * MDIO_register.h
 *
 *  Created on: Aug 2, 2023
 *      Author: Mahmoud
 *      Layer: MCAL
 *      Module: DIO Registers
 *      Version: 1.00
 */

#ifndef MCAL_DIO_MDIO_REGISTER_H_
#define MCAL_DIO_MDIO_REGISTER_H_

/*define port A address*/
#define PORTA			*((volatile u8 *)0x3B)
#define DDRA			*((volatile u8 *)0x3A)
#define PINA			*((volatile u8 *)0x39)

/*define port B address*/
#define PORTB			*((volatile u8 *)0x38)
#define DDRB			*((volatile u8 *)0x37)
#define PINB			*((volatile u8 *)0x36)

/*define port C address*/
#define PORTC			*((volatile u8 *)0x35)
#define DDRC			*((volatile u8 *)0x34)
#define PINC			*((volatile u8 *)0x33)

/*define port D address*/
#define PORTD			*((volatile u8 *)0x32)
#define DDRD			*((volatile u8 *)0x31)
#define PIND			*((volatile u8 *)0x30)

#endif /* MCAL_DIO_MDIO_REGISTER_H_ */
