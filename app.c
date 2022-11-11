/*
 * app.c
 *
 *  Created on: Oct 26, 2022
 *      Author: haidy
 */

#include "timer1.h"
#include "gpio.h"
uint8 counter;
void CALLBACK(void)
{
	counter++;
}
int main()

{
	GPIO_setupPinDirection(PORTA_ID,PIN0_ID,PIN_OUTPUT);
	Timer1_ConfigType configstruct = {0,0,FCPU_1024,NORMAL};
	Timer1_init(&configstruct);
	Timer1_setCallBack(CALLBACK);

	while (!(counter ==459))
	{

	}
	GPIO_writePin (PORTA_ID,PIN0_ID,LOGIC_HIGH);
}
