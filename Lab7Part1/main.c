#include "msp.h"
#include "LCD_lib.h"


/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/10/2021
* Project:     Lab7Part1
* File:        main.c
* Description: This program connects to the MSP432 and configures the
*                   LED screen to initialize to show a blinking cursor in the
*                   first position
***************************************************************************************/
void main(void){
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	//configure pins 4.0, .2, .4-.7 to be GPIO
	P4->SEL0 &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
	P4->SEL1 &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
	P4->DIR |= (BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
	//turn off all pins before beginning the program just in case
	P4->OUT &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
	//initialize Systick and the LCD
	SysTick_Init();
	LCD_Init();

	while(1);

}
