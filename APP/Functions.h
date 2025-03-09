/*
 * Functions.h
 *
 *  Created on: Aug 28, 2023
 *      Author: Mahmoud
 *      Layer: Application
 *      Version: 1.00
 */

#ifndef APP_FUNCTIONS_H_
#define APP_FUNCTIONS_H_

typedef enum {
	MENU,
	OPEN_SYSTEM,
	CHANGE_PASSWORD,
	ADD_USER
} EN_SystemStates_t;

typedef enum {
	FIRST_ENTRY_FALSE,
	FIRST_ENTRY_TRUE,
} EN_FirstEntryFlag_t;

void Menu_state(EN_FirstEntryFlag_t *Menu_Flag, EN_SystemStates_t *Current_state);
void Open_System_state(EN_FirstEntryFlag_t *Open_System_Flag, EN_SystemStates_t *Current_state);
void Change_Password_state(EN_FirstEntryFlag_t *Change_Password_Flag, EN_SystemStates_t *Current_state);
void Add_User_state(EN_FirstEntryFlag_t *Add_User_Flag, EN_SystemStates_t *Current_state);

#endif /* APP_FUNCTIONS_H_ */
