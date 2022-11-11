/*
 * timer1.h
 *
 *  Created on: Oct 26, 2022
 *      Author: haidy
 */

#ifndef TIMER1_H_
#define TIMER1_H_
#include "std_types.h"
#define CPU_FREQ 8000000
/*
 * enum for the prescalars
 */
typedef enum
{
	NO_PRESCALAR =1 ,FCPU_8,FCPU_64 ,FCPU_256 ,FCPU_1024

}Timer1_Prescaler;
/*-------------------------------------------------------------------------------*/
/*
 * enum for modes
 */
typedef enum
{
	NORMAL , CTC

}Timer1_Mode;
/*-----------------------------------------------------------------------------*/
/*
 * configuration structure for timer 1
 */
typedef struct
{
uint16 initial_value;
uint16 compare_value; // it will be used in compare mode only.
Timer1_Prescaler prescaler;
Timer1_Mode mode;
} Timer1_ConfigType;

/*------------------------------------------------------------------------*/
/*****************************************************************************************/
/***********************************FUNC_DECLARATION*************************************/
/*
 * this function initialize the timer1 according to the configuration structure where it:
 * 1-Open general interrupt
 * 2-Set timer1 initial value
 * 3-choose the prescalar
 * 4-choose the mode(compare,overflow)
 * 5- enables the overflow interrupt of TIMER1 (in case of overflow mode)
 * 6-enables the overflow interrupt of TIMER1 ( in case of compare mode)
 * 7- put the compare value  ( in case of compare mode)
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
/*------------------------------------------------------------------------------------*/

/*
 * call back function:
 * this function stores the address of a function in the application
 * which we want to call each time an interrupt happens in timer1
 * (in compare mode or in overflow mode)
 */
void Timer1_setCallBack(void(*a_ptr)(void));

/*------------------------------------------------------------------------------------*/
/*
 * this function stops timer1
 */
void Timer1_deinit(void);
/*------------------------------------------------------------------------------------*/


#endif /* TIMER1_H_ */
