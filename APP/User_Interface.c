/*
 * User_Interface.c
 *
 *  Created on: Sep 9, 2023
 *      Author: Mahmoud
 *      Layer: Application
 *      Version: 1.00
 */

#define __OPTIMIZE__
#include <util/delay.h>
#include "string.h"
#include "../STD_TYPES.h"
#include "../BIT_MATH.h"
#include "User_Interface.h"

#include "../MCAL/Golbal_Interrupt/M_GLOBAL_INTERRUPT_interface.h"
#include "../MCAL/Timer0/M_Timer0_interface.h"
#include "../MCAL/ADC/M_ADC_interface.h"
#include "../MCAL/ADC/M_ADC_config.h"

#include "../HAL/EEPROM/EEPROM_interface.h"
#include "../HAL/Keypad/HKeypad_interface.h"
#include "../HAL/LCD/HLCD_interface.h"

User_t users[MAX_N_OF_USERS];													/*Create array of user struct of size 10*/
u8 iterator;																	/*Used for loops*/

/*
 * Each user is stored in EEPROM as follows:
 * location 0 -> location 3 for ID
 * Location 4 has '\0'
 * location 5 -> location 8 for Password
 * Location 9 has '\0'
 * Location 10 has the available bit
 * */

void Init_Default_ID(void)														/*Create a default id used for adding new user*/
{
	users[DEFAULT_USER_INDEX].address = DEFAULT_USER_ADDRESS;					/*Define it's address in the first index of array*/
	users[DEFAULT_USER_INDEX].availability = not_available;						/*Make it not available for adding user in this location*/
	Store_ID(DEFAULT_USER_INDEX, "1234");										/*Store the default id 1234 in EEPROM*/
	Store_Password(DEFAULT_USER_INDEX, "1234");									/*Store the default password 1234 in EEPROM*/
	EEPROM_voidWrite(not_available, DEFAULT_USER_ADDRESS + 10);					/*Adding available bit in the address + 9*/
}

void Init_Users(void)															/*Store each user address in EEPROM*/
{
	for(iterator = 1; iterator<MAX_N_OF_USERS; iterator++)						/*Loop on each user*/
	{
		users[iterator].address = iterator * 10;								/*Give each user a 10 memory locations*/
		EEPROM_voidWrite(available, users[iterator].address + 10);				/*Adding available bit in the address + 10*/
	}
}

void Store_ID(u8 user_index, char *user_ID)										/*Store the ID in EEPROM*/
{
	for(iterator = 0; iterator<strlen(user_ID); iterator++)						/*Loop on the size of ID*/
	{
		EEPROM_voidWrite(user_ID[iterator], users[user_index].address + iterator);	/*Write each number of ID in the desired location in EEPROM*/
	}
	EEPROM_voidWrite('\0', users[user_index].address + iterator);				/*Add NULL after the ID*/
}

void Store_Password(u8 user_index, char *password)								/*Store the Password in EEPROM*/
{
	for(iterator = 0; iterator<strlen(password); iterator++)					/*Loop on the size of password*/
	{
		EEPROM_voidWrite(password[iterator], users[user_index].address + 5 + iterator);	/*Write the password in the desired location in EEPROM*/
	}
	EEPROM_voidWrite('\0', users[user_index].address + 5 + iterator);			/*Add NULL after the ID*/
}

u8 Open_Smart_System(void)														/*Entered Open System Mode*/
{
	u8 user_index = INVALID_USER;												/*Local variable to check the user is valid or not*/
	user_index = Valid_User();													/*Save the user index*/
	if(user_index >=0 && user_index != 255)										/*Check the user is valid or not*/
	{
		MGIE_voidEnable();														/*Initialize Global Interrupt*/
		M_Timer0Init();															/*Initialize Timer0*/
		MADC_voidInit();														/*Initialize ADC*/
	}
	else
	{
		//un authorized user
		//we can count false attempts here and block the system after 3 false attempts
		//return;
	}
	return 1;

}


u8 Add_User(void)																/*Entered Add User Mode*/
{
	char user_id[20];															/*Local variable to save user id*/
	char password[20];															/*Local variable to save user password*/
	u8 check_space = 255;														/*Local variable to check the space in EEPROM*/
	u8 user_index = INVALID_USER;												/*Local variable to check the user is valid or not*/
	user_index = Valid_User();													/*Save the user index*/

	if(user_index != INVALID_USER)												/*Check the user is valid or not*/
	{
		//check if there is space for new user
		check_space = Check_Available_Space();									/*Save the index space*/
		if(check_space)															/*Check the space*/
		{
			Enter_User_ID();													/*Read the id*/
			strcpy(user_id,Get_User_ID());										/*Copy the entered id to user_id*/

			Enter_User_Password();												/*Read the password*/
			strcpy(password,Get_Password());									/*Copy the entered id to password*/

			Store_ID(check_space,user_id);										/*Save the id*/
			Store_Password(check_space,password);								/*Save the password*/
			mark_user_as_not_available(check_space);							/*Make the user is available*/
			User_Added();														/*Print User is Added*/

		}
		else																	/*No space for new user*/
		{
			No_Space();															/*Print No space*/
		}
	}
	return 1;
}

u8 Change_Password(void)														/*Entered Change Password Mode*/
{
	char password[20];															/*Local variable to save user password*/
	u8 user_index = INVALID_USER;												/*Local variable to check the user is valid or not*/
	user_index = Valid_User();													/*Save the user index*/

	if(user_index != INVALID_USER)												/*Check the user is valid or not*/
	{
		Enter_User_Password();													/*Read the password*/
		strcpy(password,Get_Password());										/*Copy the entered id to password*/

		Store_Password(user_index,password);									/*Save the new password*/
		Password_Changed();														/*Print Password is Changed*/
	}																			/**/
	return 1;																	/**/
}																				/**/

u8 Valid_User(void)																/**/
{																				/**/
	u8 user_status = INVALID_USER;												/**/
	u8 user_index;																/**/
	char user_id[20];															/**/
	char password[20];															/**/

	Enter_User_ID();															/**/
	strcpy(user_id,Get_User_ID());												/**/

	user_index = Search_For_User(user_id);										/**/
	if(user_index != USER_NOT_FOUND)											/**/
	{																			/**/
		Enter_User_Password();													/**/
		strcpy(password,Get_Password());										/**/

		if(Check_Password(user_index,password) == PASSWORD_CORRECT)				/**/
		{																		/**/
			user_status = user_index;											/**/
		}																		/**/
		else																	/**/
		{																		/**/
			Wrong_Password();													/**/
			user_status =  PASSWORD_INCORRECT;									/**/
		}																		/**/
	}																			/**/
	else																		/**/
	{																			/**/
		User_Not_Found();														/**/
		user_status = INVALID_USER;												/**/
	}																			/**/
	return user_status;															/**/
}																				/**/

void Enter_User_ID(void)														/**/
{																				/**/
	HLCD_voidclear();															/**/
	HLCD_voidgotoXY(0,0);														/**/
	HLCD_voidsendString("Enter User ID:");										/**/
	_delay_ms(500);																/**/
}																				/**/

void Enter_User_Password(void)													/**/
{																				/**/
	HLCD_voidclear();															/**/
	HLCD_voidgotoXY(0,0);														/**/
	HLCD_voidsendString("Enter Password:");										/**/
	_delay_ms(500);																/**/
}																				/**/

void User_Added(void)															/**/
{																				/**/
	HLCD_voidclear();															/**/
	HLCD_voidgotoXY(0,0);														/**/
	HLCD_voidsendString("User Added");											/**/
	_delay_ms(500);																/**/
}																				/**/

void No_Space(void)																/**/
{																				/**/
	HLCD_voidclear();															/**/
	HLCD_voidgotoXY(0,0);														/**/
	HLCD_voidsendString("No Space");											/**/
	_delay_ms(500);																/**/
}																				/**/

s8 Search_For_User(char* user_id)												/**/
{																				/**/
	for(iterator=0;iterator<MAX_N_OF_USERS;iterator++)							/**/
	{																			/**/
		if(strcmp(read_user_id(iterator),user_id)==0)							/**/
		{																		/**/
			//user found
			//return user index
			return iterator;													/**/
		}																		/**/
		else																	/**/
		{}																		/**/
	}																			/**/
	return USER_NOT_FOUND;														/**/
}																				/**/

u8 Check_Password(u8 user_index,char* password)
{
	if(strcmp(read_password(user_index),password)==0)
	{
		//password is correct
		//return 1
		return PASSWORD_CORRECT;
	}
	//password is incorrect
	//return 0
	return PASSWORD_INCORRECT;
}

u8 Check_Available_Space(void)
{
	for(iterator=0; iterator<MAX_N_OF_USERS; iterator++)
	{
		if(users[iterator].availability == available)
		{
			return iterator;
		}
	}
	return 0;
}

char* Get_User_ID(void)
{
	static char user_id[20];
	HLCD_voidgotoXY(0,0);
	HLCD_voidsendString("Enter User ID");
	HLCD_voidgotoXY(1,0);
	strcpy(user_id,Hkeypad_charGet_String());
	HLCD_voidclear();
	return user_id;
}

char* Get_Password(void)
{
	static char password[20];
	HLCD_voidgotoXY(0,0);
	HLCD_voidsendString("Enter Password");
	HLCD_voidgotoXY(1,0);
	strcpy(password,Hkeypad_charGet_String());
	HLCD_voidclear();
	return password;
}

void mark_user_as_not_available(u8 user_index)
{
	users[user_index].availability = not_available;
	EEPROM_voidWrite(not_available,users[user_index].address+10);
}

void mark_user_as_available(u8 user_index)
{
	users[user_index].availability = available;
	EEPROM_voidWrite(available,users[user_index].address+10);
}

void debug(u8 debug_value)
{
	HLCD_voidsendNumber(debug_value);
	_delay_ms(500);
}

char* read_user_id(u8 user_index)
{
	iterator=0;
	char temp;
	static char user_id[20];
	while (temp != '\0' && iterator<20){
		EEPROM_voidRead(users[user_index].address+iterator,&temp);
		user_id[iterator] = temp;
		iterator++;
	}
	return user_id;
}

char* read_password(u8 user_index)
{
	iterator=0;
	char temp;
	static char password[20];
	while (temp != '\0'&&iterator<20){
		EEPROM_voidRead(users[user_index].address + 5 + iterator, &temp);
		password[iterator] = temp;
		iterator++;
	}
	return password;
}

void Wrong_Password(void)
{
	HLCD_voidclear();
	HLCD_voidgotoXY(0,0);
	HLCD_voidsendString("Wrong Password");
	_delay_ms(500);
}

void User_Not_Found(void)
{
	HLCD_voidclear();
	HLCD_voidgotoXY(0,0);
	HLCD_voidsendString("User Not Found");
	_delay_ms(500);
}

void Password_Changed(void)
{
	HLCD_voidclear();
	HLCD_voidgotoXY(0,0);
	HLCD_voidsendString("password changed");
	_delay_ms(500);
}
