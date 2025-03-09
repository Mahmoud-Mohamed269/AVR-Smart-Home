/*
 * HLCD_interface.h
 *
 *  Created on: Aug 3, 2023
 *      Author: Mahmoud
 *      Layer: HAL
 *      Module: LCD Interface
 *      Version: 1.00
 */

#ifndef HAL_LCD_HLCD_INTERFACE_H_
#define HAL_LCD_HLCD_INTERFACE_H_

#include <stdlib.h>

void HLCD_voidSendCommand(u8 Copy_u8Command);
void HLCD_voidsendData(u8 Copy_u8Data);
void HLCD_voidclear(void);
void HLCD_IncrementCursor(u8 times);
void HLCD_DecrementCursor(u8 times);
void Move_Name_LR(u8 *copy_u8String);
void HLCD_voidsendNumber(u8 Number);
void HLCD_voidsendFloat(float32 Number);
void HLCD_voidsendString(char *string);
void HLCD_voidgotoXY(u8 x_pos, u8 y_pos);
void HLCD_voidinit();

#endif /* HAL_LCD_HLCD_INTERFACE_H_ */
