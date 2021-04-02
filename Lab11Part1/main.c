#include "msp.h"

void InfraredLEDPinSet(void);

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	InfraredLEDPinSet();

	while(1);
}

/*-----------------------------------------------------------
* Function: InfraredLEDPinSetup
* Description: This function sets up the pins for the infrared sensor
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void InfraredLEDPinSet(void){
    //setup P2.4 as GPIO
    P2->SEL0 |= BIT4;
    P2->SEL1 &= ~BIT4;
    P2->DIR |= BIT4;

    //40000 cycles
    TIMER_A0->CCR[0] = 37500;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    //by default, sets duty cycle to 10Hz
    TIMER_A0->CCR[1] = 18750;
    TIMER_A0->CTL = 0x0254;
}
