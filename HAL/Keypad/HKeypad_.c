/*
 * HKeypad_.c
 *
 *  Created on: Aug 3, 2023
 *      Author: Mahmoud
 *      Layer: HAL
 *      Module: Keypad Program
 *      Version: 1.00
 */

#include "../../STD_TYPES.h"
#include "../../BIT_MATH.h"
#include "../../MCAL/DIO/MDIO_interface.h"
#include "Hkeypad_interface.h"
#include "Hkeypad_private.h"
#include "Hkeypad_config.h"
#include "../LCD/HLCD_interface.h"

u8 Hkeypad_u8GetKey(void)
{
	u8 Local_u8PressedKey = NO_KEY;																				//variable for pressed button
	u8 flag = 0;
	u8 Local_u8ColIterator = 0;
	u8 Local_u8RowIterator = 0;
	u8 Local_u8KeyIsPressed = NOT_PRESSED;																		//check the button is pressed or not
	u8 Col_array[COL_SIZE] = {KEYPAD_C1, KEYPAD_C2, KEYPAD_C3, KEYPAD_C4};
	u8 Row_array[ROW_SIZE] = {KEYPAD_R1, KEYPAD_R2, KEYPAD_R3, KEYPAD_R4};
	u8 Keypad_arr[ROW_SIZE][COL_SIZE] = KeyPad_Type;

	for(Local_u8ColIterator = 0; Local_u8ColIterator< COL_SIZE; Local_u8ColIterator++)							//loop for columns of keypad
	{
		MDIO_SetPinValue(KEYPAD_C_PORT, Col_array[Local_u8ColIterator], DIO_LOW);									//set the keypad columns to be low
		for(Local_u8RowIterator = 0; Local_u8RowIterator < ROW_SIZE; Local_u8RowIterator++)
		{
			MDIO_GetPinValue(KEYPAD_R_PORT, Row_array[Local_u8RowIterator], &Local_u8KeyIsPressed);				//get the keypad columns to be high
			if(Local_u8KeyIsPressed == PRESSED)
			{
				while(Local_u8KeyIsPressed == PRESSED)
				{
					MDIO_GetPinValue(KEYPAD_R_PORT, Row_array[Local_u8RowIterator], &Local_u8KeyIsPressed);				//get the keypad columns to be high
				}
				Local_u8PressedKey = Keypad_arr[Local_u8RowIterator][Local_u8ColIterator];						//store the pressed button value
				flag = 1;
				break;
			}
			else
			{}
		}
		MDIO_SetPinValue(KEYPAD_C_PORT, Col_array[Local_u8ColIterator], DIO_HIGH);									//set the keypad columns to be low
		if(flag)
		{
			break;
		}
		else{}

	}
	return Local_u8PressedKey;
}

char* Hkeypad_charGet_String(void)
{
	static char str[20] = "";
	int i=0;
	char chr;
	while(chr!='=')
	{
		chr = Hkeypad_u8GetKey();
		if(chr != NO_KEY)
		{
			HLCD_voidsendData(chr);
			str[i]=chr;
			i++;
		}
	}
	str[i-1]='\0';
	return str;
}
