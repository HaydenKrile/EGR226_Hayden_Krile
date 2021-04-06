#include "msp.h"
#include "Keypad_lib.h"

void ServoPinSet(void);
void LEDPinSet(void);
void SysTick_Init(void);
void delay_ms(uint16_t delay);

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	SysTick_Init();
	Keypad_Init();
	ServoPinSet();
	LEDPinSet();

	int keypadStore;

	while(1){
	    keypadStore = Keypad_Read();

	    if(keypadStore == 1){
	        TIMER_A2->CCR[1] = 2250;
	        P2->OUT &= ~BIT0;
	        P2->OUT |= BIT1;
	    }

	    if(keypadStore == 2){
            TIMER_A2->CCR[1] = 250;
            P2->OUT |= BIT0;
            P2->OUT &= ~BIT1;
	    }
	}
}

/*-----------------------------------------------------------
* Function: ServoPinSetup
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

void LEDPinSet(void){
    //sets the LED's as outputs
    P2->DIR |= BIT0;
    P2->DIR |= BIT1;

    P2->OUT |= BIT0;
    P2->OUT &= ~BIT1;
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
void delay_ms(uint16_t delay){
    //delay for 1 ms per delay value
    SysTick->LOAD = ((delay * 3000) - 1);
    //any write to CRV clears it
    SysTick->VAL = 0;
    //wait for flag to be SET
    while((SysTick->CTRL & 0x00010000) == 0);
}
