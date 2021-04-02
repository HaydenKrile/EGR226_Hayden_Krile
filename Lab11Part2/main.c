#include "msp.h"

void InfraredLEDPinSet(void);
void InfraredSensorPinSet(void);
void RedLEDPinSet(void);
void TA2_N_IRQHandler(void);

volatile uint16_t period;

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    //__disable_irq();

    InfraredLEDPinSet();
    InfraredSensorPinSet();
    RedLEDPinSet();

    TIMER_A2->CTL = 0x224;
    TIMER_A2->CCTL[2] = 0x4910;
    NVIC_EnableIRQ(TA2_N_IRQn);
    __enable_interrupt();


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
    TIMER_A0->CCR[1] = 9375;
    TIMER_A0->CTL = 0x0254;
}

void InfraredSensorPinSet(void){
    P5->SEL1 &= ~BIT7;
    P5->SEL0 |= BIT7;
    P5->DIR &= ~BIT7;
    P5->REN |= BIT7;
    P5->OUT |= BIT7;
}

void RedLEDPinSet(void){
    P1->SEL1 &= ~BIT0;
    P1->SEL0 &= ~BIT0;
    P1->DIR |= BIT0;
    P1->OUT &= BIT0;
}

void TA2_N_IRQHandler(void){
    static uint16_t first = 0, second = 0;

    if(TIMER_A2->CCTL[2] & BIT0){
        first = second;
        second = TIMER_A2->CCR[2];
        period = second - first;

        if(period == 9375)
            P1->OUT |= BIT0;
        else
            P1->OUT &= BIT0;

    }

    TIMER_A2->CCTL[2] &= ~(BIT0|BIT1);
}
