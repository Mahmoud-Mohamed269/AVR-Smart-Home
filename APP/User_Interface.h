/*
 * User_Interface.h
 *
 *  Created on: Sep 9, 2023
 *      Author: Mahmoud
 *      Layer: Application
 *      Version: 1.00
 */

#ifndef APP_USER_INTERFACE_H_
#define APP_USER_INTERFACE_H_

#define DEFAULT_USER_INDEX		0
#define DEFAULT_USER_ADDRESS	0x00
#define MAX_N_OF_USERS			10
#define INVALID_USER			255
#define USER_NOT_FOUND          255   //user not found
#define PASSWORD_CORRECT        1
#define PASSWORD_INCORRECT      255

typedef enum
{
	available,
	not_available
}Available_t;

typedef struct
{
	u16 address;
	u8 availability;
}User_t;

#define DEFAULT_USER_INDEX 0
#define DEFAULT_USER_Address 0x00

void Init_Default_ID(void);
void Init_Users(void);
u8 Add_User(void);
u8 Change_Password(void);
u8 Open_Smart_System(void);
void Store_ID(u8 user_index, char *user_ID);
void Store_Password(u8 user_index, char *password);
u8 Valid_User(void);
void Enter_User_ID(void);
void Enter_User_Password(void);
s8 Search_For_User(char* user_name);
u8 Check_Password(u8 user_index,char* password);
u8 Check_Available_Space(void);
char* Get_User_ID(void);
char* Get_Password(void);
void mark_user_as_not_available(u8 user_index);
void mark_user_as_available(u8 user_index);
void debug(u8 debug_value);
char* read_user_id(u8 user_index);
char* read_password(u8 user_index);
void User_Added(void);
void No_Space(void);
void Wrong_Password(void);
void User_Not_Found(void);
void Password_Changed(void);

#endif /* APP_USER_INTERFACE_H_ */
