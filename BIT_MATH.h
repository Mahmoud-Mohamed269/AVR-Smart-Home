/*
 * MACROS.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Mahmoud
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(reg, bit_number) 	reg |= (1 << bit_number)

#define CLR_BIT(reg, bit_number) 	reg &= ~(1 << bit_number)

#define TOGGLE_BIT(reg, bit_number)	reg ^= (1 << bit_number)

#define GET_BIT(reg, bit_number)  	((reg >> bit_number) & 1)


#endif /* BIT_MATH_H_ */
