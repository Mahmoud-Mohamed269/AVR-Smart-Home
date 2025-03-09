/*
 * Functions.c
 *
 *  Created on: Aug 28, 2023
 *      Author: Mahmoud
 *      Layer: Application
 *      Version: 1.00
 */

#define __OPTIMIZE__
#include <util/delay.h>
#include "../STD_TYPES.h"
#include "../BIT_MATH.h"
#include "Functions.h"

#include "../MCAL/SPI/MSPI_interface.h"											/*Include SPI interface file from MCAL*/
#include "../MCAL/USART/MUSART_interface.h"										/*Include USART interface file from MCAL*/
#include "../MCAL/USART/MUSART_register.h"										/*Include USART register file from MCAL*/
#include "../MCAL/ADC/M_ADC_interface.h"										/*Include ADC interface file from MCAL*/
#include "../MCAL/ADC/M_ADC_config.h"											/*Include ADC configuration file from MCAL*/

#include "../HAL/Keypad/HKeypad_interface.h"									/*Include Keypad interface file from HAL*/
#include "../HAL/Keypad/HKeypad_config.h"										/*Include Keypad configuration file from HAL*/
#include "../HAL/LCD/HLCD_interface.h"											/*Include LCD interface file from HAL*/

#include "User_Interface.h"														/*Include User interface file*/

u8 Key_value;																	/*Global variable for keypad value*/

u16 MADC_LM35_u16Reading;														/*Global variable for LM35 Sensor*/
u16 MilliVolt = 0;																/*Global variable for LM35 in milli-volt*/
u8 Temperature = 0;																/*Global variable for Temperature value*/

u16 MADC_LDR_u16Reading;														/*Global variable for LDR Sensor*/
u8 ADC_u8Mapped;																/*Global variable for LDR mapped reading*/

u16 MAP_u16Mapping(u16 x_Max, u16 x_Min, u16 y_Max, u16 y_Min, u16 y);			/*Mapping Function declaration*/

u8 G_u8RecivedData = 0;															/*Global variable for the received data from bluetooth*/

void Menu_state(EN_FirstEntryFlag_t *Menu_Flag, EN_SystemStates_t *Current_state)	/*Entering Menu state function*/
{
	/* First Entry Action */
	if(*Menu_Flag == FIRST_ENTRY_TRUE)											/*Check the entry flag*/
	{																			/*Entering the if statement*/
		HLCD_voidgotoXY(0, 0);													/*Set the cursor to location 0,0*/
		HLCD_voidsendString("1)Open System");									/*Print string on LCD*/
		HLCD_voidgotoXY(1, 0);													/*Set the cursor to location 1,0*/
		HLCD_voidsendString("2)Change Pass.");									/*Print string on LCD*/
		_delay_ms(1000);														/*wait for 1s*/
		HLCD_voidclear();														/*Clear the LCD*/
		HLCD_voidgotoXY(0, 0);													/*Set the cursor to location 0,0*/
		HLCD_voidsendString("2)Change Pass.");									/*Print string on LCD*/
		HLCD_voidgotoXY(1, 0);													/*Set the cursor to location 1,0*/
		HLCD_voidsendString("3)Add User");										/*Print string on LCD*/
		*Menu_Flag = FIRST_ENTRY_FALSE;											/*Update the Menu flag*/
	}																			/*Exit the if statement*/

	/* Within State Action */
	Key_value = Hkeypad_u8GetKey();												/*Read the Key pressed in Keypad*/
	/* Exit Action */
	while(Key_value != NO_KEY)													/*Check if there is any key is pressed*/
	{
		switch(Key_value)														/*Switch on the key value*/
		{
		case '1':																/*Entering case 1*/
			HLCD_voidclear();													/*Clear the LCD*/
			/* Update the first entry flag to be true for the next entry time */
			*Menu_Flag = FIRST_ENTRY_TRUE;
			/* Update state object for the transition */
			*Current_state = OPEN_SYSTEM;
			break;																/*Exit the case*/

		case '2':																/*Entering case 2*/
			HLCD_voidclear();													/*Clear the LCD*/
			/* Update the first entry flag to be true for the next entry time */
			*Menu_Flag = FIRST_ENTRY_TRUE;
			/* Update state object for the transition */
			*Current_state = CHANGE_PASSWORD;
			break;																/*Exit the case*/

		case '3':																/*Entering case 3*/
			HLCD_voidclear();													/*Clear the LCD*/
			/* Update the first entry flag to be true for the next entry time */
			*Menu_Flag = FIRST_ENTRY_TRUE;
			/* Update state object for the transition */
			*Current_state = ADD_USER;
			break;																/*Exit the case*/

		default:																/*Default case*/
			break;																/*Exit the default case*/
		}																		/*Exit the switch*/
		break;																	/*Break the loop*/
	}																			/*Exit the loop*/
}																				/*Exit the function*/

void Open_System_state(EN_FirstEntryFlag_t *Open_System_Flag, EN_SystemStates_t *Current_state) 	/*Entering Open system state function*/
{
	/* First Entry Action */
	if(*Open_System_Flag == FIRST_ENTRY_TRUE)									/*Check the entry flag*/
	{																			/*Entering the if statement*/
		HLCD_voidgotoXY(0, 0);													/*Set the cursor to location 0,0*/
		HLCD_voidsendString("Open System Mode");								/*Print string on LCD*/
		HLCD_voidgotoXY(1, 0);													/*Set the cursor to location 1,0*/
		HLCD_voidsendString("Press C to Back");									/*Print string on LCD*/
		_delay_ms(500);
		*Open_System_Flag = FIRST_ENTRY_FALSE;									/*Update the Open system flag*/
	}																			/*Exit the if statement*/

	/* Within State Action */
	Open_Smart_System();														/*Call the open system function*/

	/* Exit Action */
	Key_value = Hkeypad_u8GetKey();												/*Read the Key pressed in Keypad*/
	while(Key_value != NO_KEY)													/*Check if there is any key is pressed*/
	{																			/*Entering the while loop*/
		if(Key_value == 'C')													/*Check if the pressed key is C*/
		{																		/*Entering the if statement*/
			HLCD_voidclear();													/*Clear the LCD*/
			/* Update the first entry flag to be true for the next entry time */
			*Open_System_Flag = FIRST_ENTRY_TRUE;
			/* Update state object for the transition */
			*Current_state = MENU;
		}																		/*Exit the if statement*/
		break;																	/*Break the loop*/
	}																			/*Exit the loop*/
}																				/*Exit the function*/

void Change_Password_state(EN_FirstEntryFlag_t *Change_Password_Flag, EN_SystemStates_t *Current_state)	/*Entering Change password state function*/
{
	/* First Entry Action */
	if(*Change_Password_Flag == FIRST_ENTRY_TRUE)								/*Check the entry flag*/
	{																			/*Entering the if statement*/
		HLCD_voidgotoXY(0, 0);													/*Set the cursor to location 0,0*/
		HLCD_voidsendString("Change Pass.Mode");								/*Print string on LCD*/
		HLCD_voidgotoXY(1, 0);													/*Set the cursor to location 1,0*/
		HLCD_voidsendString("Press C to Back");									/*Print string on LCD*/
		_delay_ms(500);
		*Change_Password_Flag = FIRST_ENTRY_FALSE;								/*Update the Change password flag*/
	}																			/*Exit the if statement*/

	/* Within State Action */
	Change_Password();															/*Call the change password function*/

	/* Exit Action */
	Key_value = Hkeypad_u8GetKey();												/*Read the Key pressed in Keypad*/
	while(Key_value != NO_KEY)													/*Check if there is any key is pressed*/
	{																			/*Entering the while loop*/
		if(Key_value == 'C')													/*Check if the pressed key is C*/
		{																		/*Entering the if statement*/
			HLCD_voidclear();													/*Clear the LCD*/
			/* Update the first entry flag to be true for the next entry time */
			*Change_Password_Flag = FIRST_ENTRY_TRUE;
			/* Update state object for the transition */
			*Current_state = MENU;
		}																		/*Exit the if statement*/
		break;																	/*Break the loop*/
	}																			/*Exit the loop*/
}																				/*Exit the function*/

void Add_User_state(EN_FirstEntryFlag_t *Add_User_Flag, EN_SystemStates_t *Current_state)	/*Entering Add user state function*/
{
	/* First Entry Action */
	if(*Add_User_Flag == FIRST_ENTRY_TRUE)										/*Check the entry flag*/
	{																			/*Entering the if statement*/
		HLCD_voidgotoXY(0, 0);													/*Set the cursor to location 0,0*/
		HLCD_voidsendString("Add User Mode");									/*Print string on LCD*/
		HLCD_voidgotoXY(1, 0);													/*Set the cursor to location 1,0*/
		HLCD_voidsendString("Press C to Back");									/*Print string on LCD*/
		_delay_ms(500);
		*Add_User_Flag = FIRST_ENTRY_FALSE;										/*Update the Add user flag*/
	}																			/*Exit the if statement*/

	/* Within State Action */
	//Add_User();																	/*Call the add user function*/
	if(Add_User())
	{
		HLCD_voidclear();													/*Clear the LCD*/
		/* Update the first entry flag to be true for the next entry time */
		*Add_User_Flag = FIRST_ENTRY_TRUE;
		/* Update state object for the transition */
		*Current_state = MENU;
	}
	/* Exit Action */
	Key_value = Hkeypad_u8GetKey();												/*Read the Key pressed in Keypad*/
	while(Key_value != NO_KEY)													/*Check if there is any key is pressed*/
	{																			/*Entering the while loop*/
		if(Key_value == 'C')													/*Check if the pressed key is C*/
		{																		/*Entering the if statement*/
			HLCD_voidclear();													/*Clear the LCD*/
			/* Update the first entry flag to be true for the next entry time */
			*Add_User_Flag = FIRST_ENTRY_TRUE;
			/* Update state object for the transition */
			*Current_state = MENU;
		}																		/*Exit the if statement*/
		break;																	/*Break the loop*/
	}																			/*Exit the loop*/
}																				/*Exit the function*/

u16 MAP_u16Mapping(u16 x_Max, u16 x_Min, u16 y_Max, u16 y_Min, u16 y)			/*Entering Mapping function*/
{																				/*Entering the function*/
	u16 x;																		/*local variable*/
	x = (((u32)(x_Max - x_Min) * (y - y_Min)) / (y_Max - y_Min)) + x_Min;		/*Calculate the mapped value*/
	return x;																	/*Return the value*/
}																				/*Exit the function*/

void __vector_10(void)		__attribute__((signal));
void __vector_10(void)
{
	static u16 counter;
	counter++;
	if(counter == 4000)
	{
		SPI_u8Transceiver(1);
		//reading from LM35
		MADC_LM35_u16Reading = MADC_u16GetValue(ADC_CHANNEL0);
		MilliVolt = ((u32)MADC_LM35_u16Reading * 5000UL)/1024;
		Temperature = MilliVolt/10;
		SPI_u8Transceiver(Temperature);
		_delay_ms(50);
	}
	if(counter == 8000)
	{
		SPI_u8Transceiver(2);
		//reading from LDR to control leds
		MADC_LDR_u16Reading = MADC_u16GetValue(ADC_CHANNEL1);
		ADC_u8Mapped = MAP_u16Mapping(255, 0,1023, 0, MADC_LDR_u16Reading);
		SPI_u8Transceiver(ADC_u8Mapped);
		_delay_ms(50);
		counter = 0;
	}
}

void __vector_13(void)	__attribute__((signal));	//Neglect the linker optimization
void __vector_13(void)
{
	G_u8RecivedData = UDR;
	SPI_u8Transceiver(3);
	_delay_ms(10);
	SPI_u8Transceiver(G_u8RecivedData);
	_delay_ms(50);
}
