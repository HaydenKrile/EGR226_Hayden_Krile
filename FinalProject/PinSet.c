#include "msp.h"
#include "PinSet.h"
/*
 * PinSet.c
 *
 *  Created on: Apr 6, 2021
 *      Author: Hayden
 */

/*-----------------------------------------------------------
* Function: MasterPinSet
* Description: This function sets up the pins for all modules
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void MasterPinSet(){
    ServoPinSet();
    OnBoardLEDPinSet();
    EStopPinSet();
    MotorPinSet();
    OffBoardLEDPinSet();
    LEDEStopPinSet();
    DoorbellPinSet();
    BuzzerPinSet();
}
/*-----------------------------------------------------------
* Function: ServoPinSet
* Description: This function sets up the pins for the servo motor
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void ServoPinSet(void){
    //setup P5.6 as GPIO
    P5->SEL0 |= BIT6;
    P5->SEL1 &= ~BIT6;
    P5->DIR |= BIT6;

    //40000 cycles
    TIMER_A2->CCR[0] = 40000;
    TIMER_A2->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    //by default, sets the duty cycle to 0%
    TIMER_A2->CCR[1] = 250;
    TIMER_A2->CTL = 0x0254;
}

/*-----------------------------------------------------------
* Function: OnBoardLEDPinSet
* Description: This function sets up the pins for the on-board 3LED
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void OnBoardLEDPinSet(void){
    //sets 2.0 & 2.1 as LED outputs
    P2->DIR |= BIT0;
    P2->DIR |= BIT1;

    P2->OUT |= BIT0;
    P2->OUT &= ~BIT1;
}

/*-----------------------------------------------------------
 * Function: EStopPinSet
 * Description: This function sets up the pins for the motor e-stop
 *
 * Inputs:
 *              N/A
 *
 * Outputs:
 *              N/A
 *---------------------------------------------------------*/
 void EStopPinSet(void){
     //set P3.7 as GPIO with internal pull-up resistor
     P3->SEL1 &= ~BIT7;
     P3->SEL0 &= ~BIT7;
     P3->DIR &= ~BIT7;
     P3->REN |= BIT7;
     P3->OUT |= BIT7;

     //enabling interrupts for pins 3.7
     P3->IES |= BIT7;
     P3->IFG = 0;
     P3->IE |= BIT7;

     //enable interrupts
     NVIC_SetPriority(PORT3_IRQn, 3);
     NVIC_EnableIRQ(PORT3_IRQn);
 }

 /*-----------------------------------------------------------
 * Function: MotorPinSetup
 * Description: This function sets up the pins for DC motor
 *
 * Inputs:
 *              N/A.
 *
 * Outputs:
 *              N/A
 *---------------------------------------------------------*/
 void MotorPinSet(void){
     //setup P2.4 as GPIO
     P5->SEL0 |= BIT7;
     P5->SEL1 &= ~BIT7;
     P5->DIR |= BIT7;

     TIMER_A2->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;
     TIMER_A2->CCR[2] = 0;
 }

 /*-----------------------------------------------------------
  * Function: LEDEStopPinSet
  * Description: This function sets up the pins for the LED e-stop
  *
  * Inputs:
  *              N/A
  *
  * Outputs:
  *              N/A
  *---------------------------------------------------------*/
 void LEDEStopPinSet(void){
     //set P2.3 as GPIO with internal pull-up resistor
     P2->SEL1 &= ~BIT3;
     P2->SEL0 &= ~BIT3;
     P2->DIR &= ~BIT3;
     P2->REN |= BIT3;
     P2->OUT |= BIT3;

     //enabling interrupts for pins 2.3
     P2->IES |= BIT3;
     P2->IFG = 0;
     P2->IE |= BIT3;

     //enable interrupts
     NVIC_SetPriority(PORT2_IRQn, 3);
     NVIC_EnableIRQ(PORT2_IRQn);
 }

 /*-----------------------------------------------------------
 * Function: OffBoardLEDPinSet
 * Description: This function sets up the pins for the off board 3 LED
 *
 * Inputs:
 *              N/A
 *
 * Outputs:
 *              N/A
 *---------------------------------------------------------*/
 void OffBoardLEDPinSet(void){
     //setup P2.5-7 as GPIO
     P2->SEL0 |= (BIT5|BIT6|BIT7);
     P2->SEL1 &= ~(BIT5|BIT6|BIT7);
     P2->DIR |= (BIT5|BIT6|BIT7);
     //P2->REN |= BIT5;


     //10000 cycles
     TIMER_A0->CCR[0] = 10000;
     TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;
     TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;
     TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;
     //by default, sets the duty cycle to 0%
     TIMER_A0->CCR[2] = 0;
     TIMER_A0->CCR[3] = 0;
     TIMER_A0->CCR[4] = 0;
     TIMER_A0->CTL = 0x0254;
 }

 void DoorbellPinSet(void){
     //set P3.7 as GPIO with internal pull-up resistor
     P5->SEL1 &= ~BIT0;
     P5->SEL0 &= ~BIT0;
     P5->DIR &= ~BIT0;
     P5->REN |= BIT0;
     P5->OUT |= BIT0;

     //enabling interrupts for pins 3.7
     P5->IES |= BIT0;
     P5->IFG = 0;
     P5->IE |= BIT0;

     //enable interrupts
     NVIC_SetPriority(PORT5_IRQn, 3);
     NVIC_EnableIRQ(PORT5_IRQn);
 }

 void BuzzerPinSet(void){
     //setup P2.4 as GPIO
     P9->SEL0 |= BIT2;
     P9->SEL1 &= ~BIT2;
     P9->DIR |= BIT2;

     //1000 cycles
     TIMER_A3->CCR[0] = 1000;
     TIMER_A3->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;
     //500
     TIMER_A3->CCR[3] = 0;
     TIMER_A3->CTL = 0x0254;
 }
