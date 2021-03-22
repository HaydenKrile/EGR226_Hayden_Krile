#include "msp.h"

void SysTick_Init(void);
void SysTick_Handler(void);
void DisplayNum(int);
void LEDPinSetup(void);
volatile int num;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	//set the initial number to 0
    num = 0;

	SysTick_Init();
	LEDPinSetup();
	__enable_irq();

	//since interrupts are being used, no need for code in the while loop
	while(1);
}

void SysTick_Handler(){

    //Clear out the last value in the pins
    P4->OUT &= ~0xFF;
    //display the number to the LED
    DisplayNum(num);

    //if the number is 0-8
    if(num < 9)
        num++;
    //else, loop back to 0
    else
        num = 0;
}

/*-----------------------------------------------------------
* Function: DisplayNum
* Description: This function turns on the LEDs to
*                   display the proper number on the
*                   7-segment LED
*
* Inputs:
*              int display
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void DisplayNum(int display){
    switch(display){
    case 0:
        P4->OUT |= (BIT1|BIT2|BIT3|BIT4|BIT5|BIT6);
        break;
    case 1:
        P4->OUT |= (BIT1|BIT4);
        break;
    case 2:
        P4->OUT |= (BIT2|BIT3|BIT4|BIT5|BIT7);
        break;
    case 3:
        P4->OUT |= (BIT1|BIT2|BIT4|BIT5|BIT7);
        break;
    case 4:
        P4->OUT |= (BIT1|BIT4|BIT6|BIT7);
        break;
    case 5:
        P4->OUT |= (BIT1|BIT2|BIT5|BIT6|BIT7);
        break;
    case 6:
        P4->OUT |= (BIT1|BIT2|BIT3|BIT5|BIT6|BIT7);
        break;
    case 7:
        P4->OUT |= (BIT1|BIT4|BIT5);
        break;
    case 8:
        P4->OUT |= 0xFE;
        break;
    case 9:
        P4->OUT |= (BIT1|BIT4|BIT5|BIT6|BIT7);
        break;
    }
}

/*-----------------------------------------------------------
* Function: SysTick_Init
* Description: This function enables the SysTick timer for
*                   use in accurate delays.
*
* Citation:
*              Code was gathered from lecture powerpoints
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
    SysTick->LOAD = 3000000;
    //any write to current clears it
    SysTick->VAL = 0;
    //enable systic, 3MHz, interupts
    SysTick->CTRL = 0x00000007;
}

/*-----------------------------------------------------------
* Function: LEDPinSetup
* Description: This function sets up the pins for the 7-segment LED
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void LEDPinSetup(){
    //enabled all pins for port 4
    P4->SEL0 &= ~0xFF;
    P4->SEL1 &= ~0xFF;
    P4->DIR |= 0xFF;
    //turn off all ports at the beginning
    P4->OUT &= ~0xFF;
}
