#include "msp.h"

void LEDPinSetup(void);
void ButtonPinSet(void);
void PORT3_IRQHandler(void);
void DisplayNum(int);
volatile int num;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    //set the initial number to 0
    num = 0;

    LEDPinSetup();
    ButtonPinSet();
    DisplayNum(num);

    while(1);
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

/*-----------------------------------------------------------
* Function: ButtonPinSetup
* Description: This function sets up the pins for push buttons
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void ButtonPinSet(void){
    //set P3.5-7 as GPIO with internal pull-up resistor
    P3->SEL1 &= ~(BIT5|BIT6);
    P3->SEL0 &= ~(BIT5|BIT6);
    P3->DIR &= ~(BIT5|BIT6);
    P3->REN |= (BIT5|BIT6);
    P3->OUT |= (BIT5|BIT6);

    //enabling interrupts for pins 3.5-7
    P3->IES |= (BIT5|BIT6);
    P3->IFG = 0;
    P3->IE |= (BIT5|BIT6);

    NVIC_SetPriority(PORT3_IRQn, 3);
    NVIC_EnableIRQ(PORT3_IRQn);
}

/*-----------------------------------------------------------
* Function: PORT3_IRQHandler
* Description: This function handles the interrupts generated
*                   from port 3 by the buttons
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PORT3_IRQHandler(void){


    if (P3->IFG & 0x20){
        if (num<9)
            num++;
        else
            num = 0;

        //Clear out the last value in the pins
        P4->OUT &= ~0xFF;
        //display the number to the LED
        DisplayNum(num);
        P3->IFG &= ~0x20;
    }

    //if the black button is pushed
    if (P3->IFG & 0x40){
        if (num>0)
            num--;
        else
            num = 9;

        //Clear out the last value in the pins
        P4->OUT &= ~0xFF;
        //display the number to the LED
        DisplayNum(num);
        P3->IFG &= ~0x40;
    }

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
