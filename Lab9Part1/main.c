/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/19/2021
* Project:     Lab9Part1
* File:        main.c
* Description: This program connects to the MSP432 and uses three pushbuttons and interrupts
*                   that control the speed of a DC motor. The red button shuts down the motor,
*                   the black button slows the speed of the motor by 10%, and the white button
*                   speeds up the motor by 10%
***************************************************************************************/
#include "msp.h"

void ButtonPinSet(void);
void MotorPinSet(void);
void PORT3_IRQHandler(void);

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    //disable irq for the startup phase
    __disable_irq();
    //enable the pins
	MotorPinSet();
	ButtonPinSet();
	//enable irq
    __enable_irq();

    //since interrupts are being used, no need for anything in the loop
	while(1);
}

/*-----------------------------------------------------------
* Function: ButtonPinSetup
* Description: This function sets up the pins for pushbuttons
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void ButtonPinSet(void){
    //set P3.5-7 as GPIO with internal pull-up resistor
    P3->SEL1 &= ~(BIT5|BIT6|BIT7);
    P3->SEL0 &= ~(BIT5|BIT6|BIT7);
    P3->DIR &= ~(BIT5|BIT6|BIT7);
    P3->REN |= (BIT5|BIT6|BIT7);
    P3->OUT |= (BIT5|BIT6|BIT7);

    //enabling interrupts for pins 3.5-7
    P3->IES |= (BIT5|BIT6|BIT7);
    P3->IFG = 0;
    P3->IE |= (BIT5|BIT6|BIT7);

    //enable interrupts
    NVIC_SetPriority(PORT3_IRQn, 3);
    NVIC_EnableIRQ(PORT3_IRQn);
}

/*-----------------------------------------------------------
* Function: MotorPinSetup
* Description: This function sets up the pins for DC motor
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void MotorPinSet(void){
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
}

/*-----------------------------------------------------------
* Function: PORT3_IRQHandler
* Description: This function handles the interrupts generated
*                   from port three by the buttons
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PORT3_IRQHandler(void){

    //initially sets the duty cycle to 50%
    static float dutyCycle = .5;
    float speedSet;

    //if the red button is pushed
    if (P3->IFG & 0x20){
        //stop the motor
        dutyCycle = 0;
        TIMER_A0->CCR[1] = 0;
        //clear the flag
        P3->IFG &= ~0x20;
    }

    //if the black button is pushed
    if (P3->IFG & 0x40){
        //if the motor is already at 0
        if(dutyCycle <= 0.1){
            dutyCycle = 0;
            TIMER_A0->CCR[1] = 0;
        }

        //decrease the motor speed by 10%
        else{
            dutyCycle = dutyCycle - 0.1;
            speedSet = (40000*dutyCycle);
            TIMER_A0->CCR[1] = speedSet;
        }
        //clear the flag
        P3->IFG &= ~0x40;
    }

    //if the white button is pushed
    if (P3->IFG & 0x80){
        //if the previous input was 0.9 or 1
        if(dutyCycle >= 0.9){
            dutyCycle = 1;
            TIMER_A0->CCR[1] = 40000;
        }

        //if not
        else{
            //increase the duty cycle by 10%
            dutyCycle = dutyCycle + 0.1;
            speedSet = (40000*dutyCycle);
            TIMER_A0->CCR[1] = speedSet;
        }
        //clear the flag
        P3->IFG &= ~0x80;
    }
}
