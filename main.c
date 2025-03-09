/*
 * main.c
 *
 *  Created on: Aug 1, 2023
 *      Author: Mahmoud
 *      Layer: Application
 *      Version: 1.00
 */

#define __OPTIMIZE__
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MCAL/DIO/MDIO_interface.h"
#include "MCAL/SPI/MSPI_interface.h"

#include "MCAL/USART/MUSART_interface.h"
#include "MCAL/USART/MUSART_register.h"

#include "HAL/Keypad/HKeypad_interface.h"
#include "HAL/Keypad/HKeypad_config.h"
#include "HAL/LCD/HLCD_interface.h"

#include "APP/Functions.h"
#include "APP/User_Interface.h"

EN_SystemStates_t Current_state = MENU;
EN_FirstEntryFlag_t Menu_Flag = FIRST_ENTRY_TRUE;
EN_FirstEntryFlag_t Open_System_Flag = FIRST_ENTRY_TRUE;
EN_FirstEntryFlag_t Change_Password_Flag = FIRST_ENTRY_TRUE;
EN_FirstEntryFlag_t Add_User_Flag = FIRST_ENTRY_TRUE;


int main()
{
	Port_VoidInit();															/*Initialize Ports*/

	HLCD_voidinit();															/*Initialize LCD*/

	Init_Default_ID();															/*Create the default id*/
	Init_Users();																/*Create users*/

	while(1)
	{
		switch(Current_state)
		{
		case MENU:
			Menu_state(&Menu_Flag, &Current_state);
			break;

		case OPEN_SYSTEM:
			Open_System_state(&Open_System_Flag, &Current_state);
			break;

		case CHANGE_PASSWORD:
			Change_Password_state(&Change_Password_Flag, &Current_state);
			break;

		case ADD_USER:
			Add_User_state(&Add_User_Flag, &Current_state);
			break;

		default:
			break;
		}

	}
}
