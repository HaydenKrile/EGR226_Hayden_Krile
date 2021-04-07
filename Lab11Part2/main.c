#include "msp.h"

void RedLEDInit(void);
void InfraredLEDInit(void);
void InfraredSensorInit(void);

/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        04/05/2021
* Project:     Lab11Part
* File:        main.c
* Description: This program connects to the MSP432 and uses the infrared
*                   LED and sensor to detected when the LED is emitting light.
*                   If the sensor detects the LED, the on-board red LED will light
*                   up, and if no infrared light is detected, the red LED will turn off.
***************************************************************************************/
void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    RedLEDInit();
    InfraredLEDInit();
    InfraredSensorInit();
    __enable_interrupt();

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

void TA2_N_IRQHandler()
{
    static uint16_t previousTime = 0, currentTime = 0, period;

    //if capture is detected
    if(TIMER_A2->CCTL[2] & BIT0){
        //set the previous time to the time detected during the last interrupt
        previousTime = currentTime;
        //set the current time
        currentTime = TIMER_A2->CCR[2];
        //determine the period of the signal detected
        period = currentTime - previousTime;

        //if the infrared sensor detected light
        if((period > 37495) & (period < 37505)){
            //tunr on red light
            P1->OUT |= BIT0;
        }

        //if no light is detected
        else{
            //turn off light
            P1->OUT &= ~BIT0;
        }
    }

    //reset flag
    TIMER_A2->CCTL[2] &= ~3;
}

