#include "msp.h"

void RedLEDInit(void);
void InfraredLEDInit(void);
void InfraredSensorInit(void);

volatile int period;

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    RedLEDInit();
    InfraredLEDInit();
    InfraredSensorInit();
    __enable_irq();

    while(1);
}

/*-----------------------------------------------------------
* Function: RedLEDInit
* Description: This function sets up the pins for the on-board red LED
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void RedLEDInit(){
    P1->SEL0 &= ~BIT0;
    P1->SEL1 &= ~BIT0;
    P1->DIR |= BIT0;
    P1->OUT &= ~BIT0;
}

/*-----------------------------------------------------------
* Function: InfraredLEDInit
* Description: This function sets up the pins for the infrared LED
*                   and timer A for PWM
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void InfraredLEDInit(){
    P2->SEL0 |=  BIT4;
    P2->SEL1 &= ~BIT4;
    P2->DIR  |=  BIT4;

    TIMER_A0->CTL = 0x214;
    TIMER_A0->CCR[0] = 37500;

    TIMER_A0->CCR[1] = 18750;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
}

/*-----------------------------------------------------------
* Function: InfraredSenserInit
* Description: This function sets up the pins for the infrared sensor
*                   and timer A for capture
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void InfraredSensorInit(){
    P5->SEL0 |=  BIT7;
    P5->SEL1 &= ~BIT7;
    P5->DIR  &= ~BIT7;

    TIMER_A2->CTL = 0x224;
    TIMER_A2->CCTL[2] = 0x4910;
    NVIC_EnableIRQ(TA2_N_IRQn);
}

/*-----------------------------------------------------------
* Function: TA2_N_IRQHandler
* Description: This function controls the state of the red LED
*                   based on the sensors detection of the
*                   infrared LED
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void TA2_N_IRQHandler(){
    static int previousTime = 0;
    statis int currentTime = 0;

    //sets the previous time to the current time
    previousTime = currentTime;
    //update the current time
    currentTime = TIMER_A2->CCR[2];
    //calculate the period by finding the difference between the current time and the previous time
    period = currentTime - previousTime;

    //if the infrared sensor is detected
    if(period > 37450)
        //turn on the  red LED
        P1->OUT |= BIT0;
    //if no infrared light is detected
    else
        //turn off red LED
        P1->OUT &= ~BIT0;

    TIMER_A2->CCTL[2] &= ~2;
}
