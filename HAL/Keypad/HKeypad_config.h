/*
 * HKeypad_config.h
 *
 *  Created on: Aug 3, 2023
 *      Author: Mahmoud
 *      Layer: HAL
 *      Module: Keypad Configuration
 *      Version: 1.00
 */

#ifndef HAL_KEYPAD_HKEYPAD_CONFIG_H_
#define HAL_KEYPAD_HKEYPAD_CONFIG_H_

#define KEYPAD_R_PORT		DIO_PORTD
#define KEYPAD_C_PORT		DIO_PORTC

#define KEYPAD_R1			PIN2
#define KEYPAD_R2			PIN3
#define KEYPAD_R3			PIN4
#define KEYPAD_R4			PIN5

#define KEYPAD_C1			PIN4
#define KEYPAD_C2			PIN5
#define KEYPAD_C3			PIN6
#define KEYPAD_C4			PIN7

#define	COL_SIZE		4
#define ROW_SIZE		4

#define	NO_KEY			0
#define KeyPad_Type {{'7' , '8' , '9' , '/'},\
					 {'4' , '5' , '6' , 'X'},\
					 {'1' , '2' , '3' , '-'},\
					 {'C' , '0' , '=' , '+'}}

#endif /* HAL_KEYPAD_HKEYPAD_CONFIG_H_ */
