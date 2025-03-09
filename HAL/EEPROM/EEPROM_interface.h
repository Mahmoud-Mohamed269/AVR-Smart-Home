/*
 * EEPROM_interface.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Mahmoud
 *      Layer: HAL
 *      Module: EEPROM Interface
 *      Version: 1.00
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


void EEPROM_voidWrite(u8 Copy_u8Data , u8 Copy_u8Address);

void EEPROM_voidRead(u8 Copy_u8Address , u8 *Copy_pu8Data);

#endif /* EEPROM_INTERFACE_H_ */
