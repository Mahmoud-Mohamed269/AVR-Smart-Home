/*
 * HLCD_config.h
 *
 *  Created on: Aug 3, 2023
 *      Author: Mahmoud
 *      Layer: HAL
 *      Module: LCD Configuration
 *      Version: 1.00
 */

#ifndef HAL_LCD_HLCD_CONFIG_H_
#define HAL_LCD_HLCD_CONFIG_H_

#define LCD_PORT_DATA		DIO_PORTA
#define D4					PIN4
#define D5					PIN5
#define D6					PIN6
#define D7					PIN7

#define LCD_PORT_Control	DIO_PORTD

#define	LCD_RS				6		//Register select pin
//#define	LCD_RW				2		//Read/Write pin
#define LCD_EN				7		//Enable select pin

#define LCD_MODE			4		//LCD Mode: 4,8 bit

#endif /* HAL_LCD_HLCD_CONFIG_H_ */
