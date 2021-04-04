#include "msp.h"

void InfraredLEDInit(void);

/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/27/2021
* Project:     Lab11Part1
* File:        main.c
* Description: This program connects to the MSP432 and uses the Infrared
*                   LED to test the LED to see if its emitting light.
***************************************************************************************/
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	InfraredLEDInit();

	while(1);
}

/*-----------------------------------------------------------
* Function: InfraredLEDPinSetup
* Description: This function sets up the pins for the infrared LED
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void InfraredLEDInit(void){
    //setup P2.4 as GPIO
    P2->SEL0 |= BIT4;
    P2->SEL1 &= ~BIT4;
    P2->DIR |= BIT4;


    TIMER_A0->CCR[0] = 37500;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[1] = 18750;
    TIMER_A0->CTL = 0x0254;
}
