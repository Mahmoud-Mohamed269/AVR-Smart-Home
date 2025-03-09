/*
 * HKeypad_interface.h
 *
 *  Created on: Aug 3, 2023
 *      Author: Mahmoud
 *      Layer: HAL
 *      Module: Keypad Interface
 *      Version: 1.00
 */

#ifndef HAL_KEYPAD_HKEYPAD_INTERFACE_H_
#define HAL_KEYPAD_HKEYPAD_INTERFACE_H_


u8 Hkeypad_u8GetKey(void);
char* Hkeypad_charGet_String(void);

#endif /* HAL_KEYPAD_HKEYPAD_INTERFACE_H_ */
