/*
 * LCD.c
 *
 *  Created on: Aug 3, 2023
 *      Author: Mahmoud
 *      Layer: HAL
 *      Module: LCD Program
 *      Version: 1.00
 */
#include <util/delay.h>
#include "../../BIT_MATH.h"
#include "../../STD_TYPES.h"
#include "HLCD_interface.h"
#include "HLCD_config.h"
#include "../../MCAL/DIO/MDIO_interface.h"

u8 Pin_array[4] = {D4, D5, D6, D7};

#if LCD_MODE == 4
void HLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*clear RS pin to send command*/
	MDIO_SetPinValue(LCD_PORT_Control,LCD_RS,DIO_LOW);
	/*clear the RW pin to write*/
	//MDIO_SetPinValue(LCD_PORT_Control,LCD_RW,DIO_LOW);
	/*send data*/
	if(GET_BIT(Copy_u8Command, 4))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[0], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[0], DIO_LOW);}
	if(GET_BIT(Copy_u8Command, 5))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[1], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[1], DIO_LOW);}
	if(GET_BIT(Copy_u8Command, 6))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[2], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[2], DIO_LOW);}
	if(GET_BIT(Copy_u8Command, 7))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[3], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[3], DIO_LOW);}
	/*set EN to make LCD Micro. read command*/
	MDIO_SetPinValue(LCD_PORT_Control,LCD_EN,DIO_HIGH);
	_delay_ms(1);
	MDIO_SetPinValue(LCD_PORT_Control,LCD_EN,DIO_LOW);
	_delay_ms(2);
	if(GET_BIT(Copy_u8Command, 0))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[0], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[0], DIO_LOW);}
	if(GET_BIT(Copy_u8Command, 1))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[1], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[1], DIO_LOW);}
	if(GET_BIT(Copy_u8Command, 2))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[2], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[2], DIO_LOW);}
	if(GET_BIT(Copy_u8Command, 3))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[3], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[3], DIO_LOW);}
	/*set EN to make LCD Micro. read command*/
	MDIO_SetPinValue(LCD_PORT_Control,LCD_EN,DIO_HIGH);
	_delay_ms(1);
	MDIO_SetPinValue(LCD_PORT_Control,LCD_EN,DIO_LOW);
	_delay_ms(2);
}

void HLCD_voidsendData(u8 Copy_u8Data)
{
	/*set RS pin to send command*/
	MDIO_SetPinValue(LCD_PORT_Control,LCD_RS,DIO_HIGH);
	/*clear the RW pin to write*/
	//MDIO_SetPinValue(LCD_PORT_Control,LCD_RW,DIO_LOW);
	/*send data*/
	if(GET_BIT(Copy_u8Data, 4))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[0], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[0], DIO_LOW);}
	if(GET_BIT(Copy_u8Data, 5))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[1], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[1], DIO_LOW);}
	if(GET_BIT(Copy_u8Data, 6))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[2], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[2], DIO_LOW);}
	if(GET_BIT(Copy_u8Data, 7))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[3], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[3], DIO_LOW);}
	/*set EN to make LCD Micro. read command*/
	MDIO_SetPinValue(LCD_PORT_Control,LCD_EN,DIO_HIGH);
	_delay_ms(1);
	MDIO_SetPinValue(LCD_PORT_Control,LCD_EN,DIO_LOW);
	_delay_ms(2);
	if(GET_BIT(Copy_u8Data, 0))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[0], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[0], DIO_LOW);}
	if(GET_BIT(Copy_u8Data, 1))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[1], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[1], DIO_LOW);}
	if(GET_BIT(Copy_u8Data, 2))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[2], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[2], DIO_LOW);}
	if(GET_BIT(Copy_u8Data, 3))
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[3], DIO_HIGH);}
	else
	{MDIO_SetPinValue(LCD_PORT_DATA, Pin_array[3], DIO_LOW);}
	/*set EN to make LCD Micro. read command*/
	MDIO_SetPinValue(LCD_PORT_Control,LCD_EN,DIO_HIGH);
	_delay_ms(1);
	MDIO_SetPinValue(LCD_PORT_Control,LCD_EN,DIO_LOW);
	_delay_ms(2);
}

void HLCD_voidinit()
{
	_delay_ms(40);
	HLCD_voidSendCommand(0x33);
	HLCD_voidSendCommand(0x32);			//send for 4 bit initialization of LCD
	HLCD_voidSendCommand(0x28);			//select 4 bit mode, 5*7 dots
	HLCD_voidSendCommand(0x0F);			//display on, cursor blinking
	HLCD_voidSendCommand(0x06);			//entry mode increment cursor to right
	HLCD_voidSendCommand(0x01);			//clear display
}

#elif LCD_MODE == 8
void HLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*clear RS pin to send command*/
	MDIO_SetPinValue(LCD_PORT_Control,LCD_RS,DIO_LOW);
	/*clear the RW pin to write*/
	MDIO_SetPinValue(LCD_PORT_Control,LCD_RW,DIO_LOW);
	/*send data*/
	MDIO_SetPortValue(LCD_PORT_DATA, Copy_u8Command);
	/*set EN to make LCD Micro. read command*/
	MDIO_SetPinValue(LCD_PORT_Control,LCD_EN,DIO_HIGH);
	_delay_ms(2);
	MDIO_SetPinValue(LCD_PORT_Control,LCD_EN,DIO_LOW);
}

void HLCD_voidsendData(u8 Copy_u8Data)
{
	/*set RS pin to send command*/
	MDIO_SetPinValue(LCD_PORT_Control,LCD_RS,DIO_HIGH);
	/*clear the RW pin to write*/
	MDIO_SetPinValue(LCD_PORT_Control,LCD_RW,DIO_LOW);
	/*send data*/
	MDIO_SetPortValue(LCD_PORT_DATA, Copy_u8Data);
	/*set EN to make LCD Micro. read command*/
	MDIO_SetPinValue(LCD_PORT_Control,LCD_EN,DIO_HIGH);
	_delay_ms(2);
	MDIO_SetPinValue(LCD_PORT_Control,LCD_EN,DIO_LOW);
}

void HLCD_voidinit()
{
	_delay_ms(40);
	HLCD_voidSendCommand(0b00111100);	//function set
	HLCD_voidSendCommand(0b000001100);	//display ON/OFF control
	HLCD_voidSendCommand(1);			//clear the screen
}


#endif

void HLCD_voidclear(void)
{
	HLCD_voidSendCommand(0x01);			//clear command
	HLCD_voidSendCommand(0x80);			//8 is for first line & 0 is for 0th position
}

void HLCD_voidsendNumber(u8 Number)
{
	char n[20];
	itoa(Number, n, 10);
	HLCD_voidsendString(n);
}

void HLCD_voidsendFloat(float32 Number)
{
	char n[20];
	dtostre(Number,n, 2, 2);				//convert 2 characters width & 2 decimal places
	HLCD_voidsendString(n);
}

void HLCD_voidsendString(char *string)
{
	u8 i;
	for(i=0; string[i] != 0; i++)
	{
		HLCD_voidsendData(string[i]);
	}
}

void HLCD_voidgotoXY(u8 x_pos, u8 y_pos)
{
	u8 add = 0;
	if(x_pos == 0)
	{
		add = 0x80;
	}
	else if(x_pos == 1)
	{
		add = 0xc0;
	}
	else{}
	if(y_pos <16)
	{
		add += y_pos;
	}
	HLCD_voidSendCommand(add);
}

void HLCD_IncrementCursor(u8 times){
	for (u8 i=0; i<times;i++)
	{
		HLCD_voidSendCommand(0x14);
	}
}

void HLCD_DecrementCursor(u8 times){
	for (u8 i=0; i<times;i++)
	{
		HLCD_voidSendCommand(0x10);
	}
}

void Move_Name_LR(u8 *copy_u8String)
{
	HLCD_voidsendString(copy_u8String);
	HLCD_DecrementCursor(1);
	for (u8 i=0; i<5;i++)
	{

		_delay_ms(100);
		HLCD_IncrementCursor(1);
		_delay_ms(100);

	}
}
