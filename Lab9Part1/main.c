#include "msp.h"

void ButtonPinSet(void);
void MotorPinSet(void);
void PORT3_IRQHandler(void);

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    //disable irq for the startup phase
    __disable_irq();
	MotorPinSet();
	ButtonPinSet();
    __enable_irq();

	while(1);
}

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

    NVIC_SetPriority(PORT3_IRQn, 3);
    NVIC_EnableIRQ(PORT3_IRQn);
}

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

void PORT3_IRQHandler(void){

    //initially sets the duty cycle to 50%
    static float dutyCycle = .5;
    float speedSet;

    if (P3->IFG & 0x20){
        dutyCycle = 0;
        TIMER_A0->CCR[1] = 0;
        P3->IFG &= ~0x20;
    }

    if (P3->IFG & 0x40){
        if(dutyCycle <= 0.1){
            dutyCycle = 0;
            TIMER_A0->CCR[1] = 0;
        }

        else{
            dutyCycle = dutyCycle - 0.1;
            speedSet = (40000*dutyCycle);
            TIMER_A0->CCR[1] = speedSet;
        }
        P3->IFG &= ~0x40;
    }

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
