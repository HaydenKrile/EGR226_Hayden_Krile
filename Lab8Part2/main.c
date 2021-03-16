#include "msp.h"


/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/16/2021
* Project:     Lab8Part2
* File:        main.c
* Description: This program connects to the MSP432 and uses the
*                   Timer A to generate a PWM for the DC motor
*                   The duty cycle of the motor can be controlled in the
*                   debug menu with variable "dutyCycle"
***************************************************************************************/
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    double dutyCycle = .5;
    uint16_t periodTime;

    //setup P2.4 as GPIO
    P2->SEL0 |= BIT4;
    P2->SEL1 &= ~BIT4;
    P2->DIR |= BIT4;

    //40000 cycles
    TIMER_A0->CCR[0] = 40000;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    //by default, sets the duty cycle to 50%
    TIMER_A0->CCR[1] = 20000;
    TIMER_A0->CTL = 0x0254;

    while(1){
        //sets the period time equal to the dutyCycle times 40,000
        periodTime = (dutyCycle * 40000);
        //Timer A then gets set to the period time
        TIMER_A0->CCR[1] = periodTime;

    }
}
