/*
 * main.c
 *
 *  Created on: Aug 14, 2023
 *      Author: Mahmoud
 */

#define __OPTIMIZE__
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "HAL/LED/HLED_interface.h"
#include "HAL/LED/HLED_config.h"
#include "HAL/Stepper_Motor/HStepper_Motor_interface.h"
#include "HAL/Stepper_Motor/HStepper_Motor_config.h"
#include "HAL/DC_Motor/HDC_interface.h"
#include "HAL/Seven_Segment/HSeven_Segment_config.h"
#include "HAL/Seven_Segment/HSeven_Segment_interface.h"

#include "MCAL/Golbal_Interrupt/M_GLOBAL_INTERRUPT_interface.h"
#include "MCAL/DIO/MDIO_interface.h"
#include "MCAL/SPI/MSPI_register.h"
#include "MCAL/SPI/MSPI_interface.h"
#include "MCAL/Timer/MTIMER_config.h"
#include "MCAL/Timer/MTIMER_interface.h"

u8 Temperature = 0;
u8 LDR = 0;
u8 Command = 0;
u8 ACK = 0;

u8 left, right;
u16 i;

u8 led_flag = 0, dc_flag = 0;

EN_StepperModes_t StepperMode = STOP;
u16 max_iterator = (90/FULL_STEP)+1;
u16 iterator ;

int main()
{
	Port_VoidInit();
	//MSPI_voidInit();
	SPI_voidInitSlave();
	MGIE_voidEnable();
	MTIMER1_voidInit(FAST_PWM_NON_INVERTING, TOP_FPWM_ICR1, DIV_8);				/*Initialize Timer1*/
	MTIMER1_voidSetTopValue(20000, TOP_FPWM_ICR1);

	while(1)																	/*Infinite loop*/
	{
		if(Temperature < 100)
		{
			left = Temperature / 10;
			HSSD_voidDisable(SSD_PORTB,SSD_PIN0);
			HSSD_voidEnable(SSD_PORTB,SSD_PIN1);
			HSSD_voidSendNumber(left);
			_delay_ms(2);

			right = Temperature % 10;
			HSSD_voidDisable(SSD_PORTB,SSD_PIN1);
			HSSD_voidEnable(SSD_PORTB,SSD_PIN0);
			HSSD_voidSendNumber(right);
			_delay_ms(2);
		}

		switch(Command)
		{
		case '1':
			MTIMER1_voidSetDutyCycle(2500);
			Command = 0;
			break;

		case '2':
			MTIMER1_voidSetDutyCycle(750);
			Command = 0;
			break;

		case '3':
			HDC_ON(PIN6);
			Command = 0;
			break;

		case '4':
			HDC_OFF(PIN6);
			dc_flag = 1;
			Command = 0;
			break;

		case '5':
			/* Stepper C.W */
			StepperMode = StepperClockWise;
			iterator = 0;
			Command = 0;
			break;

		case '6':
			/* Stepper C.C.W */
			StepperMode = StepperCounterClockWise;
			iterator = 0;
			Command = 0;
			break;

		case '7':
			HLED_Leds(DIO_PORTC, 255);
			Command = 0;
			break;

		case '8':
			HLED_Leds(DIO_PORTC, 0);
			led_flag = 1;
			Command = 0;
			break;

		default:
			Command = 0;
			break;
		}

		if((Temperature >= 35) && (dc_flag == 0))
		{
			HDC_ON(PIN6);
		}
		else if(Temperature < 35)
		{
			dc_flag = 0;
		}

		if((LDR > 120) && (led_flag == 0))
		{
			HLED_Leds(DIO_PORTC, 0);
		}
		else if(LDR < 120)
		{
			HLED_Leds(DIO_PORTC, 255);
			led_flag = 0;
		}

		switch(StepperMode)
		{
		case StepperClockWise:
			HStepper_Motor_Rotoate_OneStep();
			iterator++;
			break;

		case StepperCounterClockWise:
			HStepper_Motor_C_Rotoate_OneStep();
			iterator++;
			break;

		default:
			break;
		}
		if(iterator == max_iterator)
		{
			iterator = 0;
			StepperMode = STOP;
		}
	}
}

void __vector_12(void)	__attribute__((signal));	//Neglect the linker optimization
void __vector_12(void)
{
	u8 data = SPDR;

	if(data == 1 || data == 2 || data == 3)
	{
		ACK = SPDR;
	}
	else
	{
		switch(ACK)
		{
		case 1:
			Temperature = data;
			break;

		case 2:
			LDR = data;
			break;

		case 3:
			Command = data;
			break;
		}
	}
}
