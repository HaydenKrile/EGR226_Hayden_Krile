#include "msp.h"
#include "Keypad_lib.h"

void SysTick_Init();
void SysTick_delay(uint16_t delay);
void EStopPinSet(void);
void MotorPinSet(void);
void PORT3_IRQHandler(void);

/**
 * main.c
 */

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	//disable interrupts for this step
	__disable_irq();

    //initialize SysTick and the keypad
    SysTick_Init();
    Keypad_Init();

    //set duty cycle to zero to start
    double dutyCycle = 0;
    double buttonPress, periodTime;

    //enable interrupts
    __enable_irq();

    while(1){
        //call the Keypad_Read() function to see if a button is pressed
        buttonPress = Keypad_Read();
        //if a button is pressed:
        if(buttonPress){
            //if the button is 1-9
            if(buttonPress < 10)
                //set the dutyCycle equal to the buttonPress
                dutyCycle = (buttonPress/10);

            //if the button in 0
            if(buttonPress == 11)
                //set the dutyCycle equal to 0
                dutyCycle = 0;
        }
        //sets the period time equal to the dutyCycle times 40,000
        periodTime = (dutyCycle * 40000);
        //Timer A then gets set to the period time
        TIMER_A0->CCR[1] = periodTime;
    }
}


/*-----------------------------------------------------------
* Function: SysTick_Init
* Description: This function enables the SysTick timer for
*                   use in accurate delays.
*
* Citation:
*              Code was lifted from lecture notes
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void SysTick_Init(){
    //disable SysTick During this step
    SysTick->CTRL = 0;
    //max reload value
    SysTick->LOAD = 0x00FFFFFF;
    //any write to current clears it
    SysTick->VAL = 0;
    //enable systic, 3MHz, no interupts
    SysTick->CTRL = 0x00000005;
}

/*-----------------------------------------------------------
* Function: SysTick_Delay
* Description: This function takes in a milisecond value and uses
*                   the SysTick timer to delay until the specified amount
*                   of time has passed.
*
* Citation:
*              Code was lifted from lecture notes
*
* Inputs:
*              uint16_t delay
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void SysTick_delay(uint16_t delay){
    //delay for 1 ms per delay value
    SysTick->LOAD = ((delay * 3000) - 1);
    //any write to CRV clears it
    SysTick->VAL = 0;
    //wait for flag to be SET
    while((SysTick->CTRL & 0x00010000) == 0);
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
*                   from port 3 by the e-stop button
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PORT3_IRQHandler(void){
    TIMER_A0->CCR[1] = 0;
}
