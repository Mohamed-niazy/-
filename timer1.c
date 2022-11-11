/*
 * timer1.c
 *
 *  Created on: Oct 26, 2022
 *      Author: haidy
 */

#include <avr/io.h>
#include "timer1.h"
#include "common_macros.h"
#include "std_types.h"

static volatile void (*timer1_interrupt_callBackPtr)(void) = NULL_PTR;

/*
 * this function initialize the timer1 where it:
 * 1-Open general interrupt
 * 2-Set timer1 initial value
 * 3-choose the prescalar
 * 4-choose the mode(compare,overflow)
 * 5- enables the overflow interrupt of TIMER1 (in case of overflow mode)
 * 6-enables the overflow interrupt of TIMER1 ( in case of compare mode)
 * 7- put the compare value  ( in case of compare mode)
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{

	/* Open general interrupt */
	SREG |= (1<<7);
	/* Set timer1 initial value */
	TCNT1 =Config_Ptr->initial_value ;
	/*
	 * choose the prescalar
	 */
	TCCR1B =(TCCR1B &0xF8)|(Config_Ptr->prescaler);

	if (Config_Ptr->mode == NORMAL )
	{
		/*
		 * TO CHOOSE the normal mode
		 */
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);

		/*
		 * SET the Overflow Interrupt Enable bit that enables the overflow interrupt of TIMER1
		 */
		SET_BIT (TIMSK,TOIE1);
	}
	else if (Config_Ptr->mode == CTC )
	{
		/*
		 * to choose CTC mode
		 */
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		/*Force Output Compare for Compare unit A*/
		TCCR1A = (1<<FOC1A);
		/*
		 * SET the Output Compare A Match Interrupt Enable
		 *  that enables the compare mode interrupt of TIMER1
		 */
		SET_BIT(TIMSK,OCIE1A);
		/*
		 * put the compare value
		 */
		OCR1A =Config_Ptr->compare_value;
	}

}
/*
 * ISR in compare mode which is implemented when timer1 finish and reachs the compare value
 */
IS(TIM1_COMPA_vect)
{

	if(timer1_interrupt_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application */
			(*timer1_interrupt_callBackPtr)();
		}
}
/*
 * ISR in overflow mode which is implemented when timer1 finish counting
 */

ISR(TIM1_OVF_vect)
{

	if(timer1_interrupt_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application */
			(*timer1_interrupt_callBackPtr)();
		}
}
/*
 * call back function:
 * this function stores the address of a function in the application
 * which we want to call each time an interrupt happens in timer1
 * (in compare mode or in overflow mode)
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Store the address of the Call back function in a global variable */
	timer1_interrupt_callBackPtr = a_ptr;
}
/*
 * this function stops timer1
 */
void Timer1_deinit(void)
{
	/*diable the overflow interrupt */
	CLEAR_BIT (TIMSK,TOIE1);
	/*diable the compare mode interrupt */
	SET_BIT(TIMSK,OCIE1A);
	/*
	 * STOPS THE TIMER
	 */
	CLEAR_BIT(TCCR1B,CS10);
	CLEAR_BIT(TCCR1B,CS11);
	CLEAR_BIT(TCCR1B,CS12);
}
