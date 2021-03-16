#include "msp.h"

void SysTick_Init();
void delay_micro(uint16_t microsecond);

/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/15/2021
* Project:     Lab8Part1
* File:        main.c
* Description: This program connects to the MSP432 and uses the
*                   SysTick Timer to generate a PWM for the DC motor
*                   The duty cycle of the motor can be controlled in the
*                   debug menu with variable "dutyCycle"
***************************************************************************************/
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	SysTick_Init();
	double delayTimeOn, delayTimeOff, dutyCycle;
	static double periodTime = 33.333;

	//setup P2.4 as GPIO
	P2->SEL0 &= ~BIT4;
	P2->SEL1 &= ~BIT4;
	P2->DIR |= BIT4;

	while(1){

	    delayTimeOn = dutyCycle * periodTime;
	    delayTimeOff = periodTime - delayTimeOn;

	    P2->OUT &= ~BIT4;
	    delay_micro(delayTimeOff);
	    P2->OUT |= BIT4;
	    delay_micro(delayTimeOn);

	}
}

/*-----------------------------------------------------------
* Function: SysTick_Init
* Description: This function enables the SysTick timer for
*                   use in accurate delays.
*
* Citation:
*              Code was gathered from lecture powerpoints
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void SysTick_Init(){
    //disable SysTick During this step
    SysTick->CTRL = 0;
    //max reload value
    SysTick->LOAD = 0x00FFFFFF;
    //any write to current clears it
    SysTick->VAL = 0;
    //enable systic, 3MHz, no interupts
    SysTick->CTRL = 0x00000005;
}

/*-----------------------------------------------------------
* Function: delay_micro
* Description: This functions create a microsecond delay
*                   from an inputed integer using SysTick
*
* Citation:
*              Code was gathered from lecture powerpoints
*
* Inputs:
*              unsigned 16 bit integer
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void delay_micro(uint16_t microsecond){
    //convert inputed value to microseconds with 3MHz clock
    SysTick->LOAD = (microsecond * 3 - 1);
    //clear counter
    SysTick->VAL = 0;
    while((SysTick->CTRL & 0x00010000) == 0);
}
