/*
 * M_GLOABAL_INTERRUPT.c
 *
 *  Created on: Aug 8, 2023
 *      Author: Mahmoud
 *       Layer: MCAL
 *      Module: Global Interrupt Program
 *      Version: 1.00
 */

#include "../../STD_TYPES.h"
#include "../../BIT_MATH.h"
#include "M_GLOABAL_INTERRUPT_register.h"
#include "M_GLOBAL_INTERRUPT_interface.h"

void MGIE_voidEnable()
{
	SET_BIT(SREG, SREG_I);
}

void MGIE_voidDisable()
{
	CLR_BIT(SREG, SREG_I);
}
