#include "msp.h"
#include "LCD_lib.h"

/**
 * main.c
 */
void main(void){
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	SysTick_Init();
}
