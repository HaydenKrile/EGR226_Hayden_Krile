#include "msp.h"

void Keypad_Init(void);
void SysTick_Init(void);
void SysTick_delay(uint16_t delay);
int Keypad_Read(void);

/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/16/2021
* Project:     Lab8Part3
* File:        main.c
* Description: This program connects to the MSP432 and uses the
*                   Timer A to generate a PWM for the DC motor
*                   The duty cycle of the motor can be controlled in the
*                   debug menu with variable "dutyCycle"
***************************************************************************************/
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    //initialize SysTick and the keypad
    SysTick_Init();
    Keypad_Init();

    double dutyCycle = .5;
    uint16_t periodTime;
    double buttonPress;

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
* Function: Keypad_Init
* Description: This function enables the internal resistors
*                   and sets the to pull up for the column pins
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/

void Keypad_Init(){
    P4->DIR = 0;
    //enables pull-up resistors for column pins
    P4->REN = 0x70;
    //make column pins pull-up
    P4->OUT = 0x70;
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
* Function: Keypad_Read
* Description: This function is used to detect which key
*                   was pressed and interpret which
*                   number to return.
*
* Citation:    This Code was lifted from the
*              "TI MSP432 ARM Programming for
*              Embedded Systems" Textbook
*
* Inputs:
*              N/A
*
* Outputs:
*              int 1-12
*---------------------------------------------------------*/
int Keypad_Read(){
    int row, col;
    const char row_select[] = {0x01, 0x02, 0x04, 0x08};

    //all row pins set to output
    P4->DIR |= 0x0F;
    //drive all row pins low
    P4->OUT &= ~0x0F;
    //wait for signals to settle
    SysTick_delay(10);
    //read all column pins
    col = P4->IN & 0x70;
    //drive all rows high
    P4->OUT |= 0x0F;
    //disable all row pins
    P4->DIR &= ~0x0F;
    //if all columns are high
    if(col == 0x70)
        //no key pressed
        return 0;

    //if a key was pressed
    for (row = 0; row < 4; row++){
        //disable all rows
        P4->DIR &= 0x0F;
        //enable one row at a time
        P4->DIR |= row_select[row];
        //drive the active row low
        P4->OUT &= ~row_select[row];
        //wait for signal to settle
        SysTick_delay(10);
        //read all columns
        col = P4->IN & 0x70;
        //drive the active row high
        P4->OUT |= row_select[row];
        //if one of the inputs were low, some key is pressed
        if(col != 0x70)break;
    }
    //drive all rows high
    P4->OUT |= 0x0F;
    //disable all rows
    P4->DIR &= 0x0F;
    //if no key was pressed
    if(row == 4)
        return 0;

    //if a key was pressed, return the proper number pressed
    if (col == 0x60 & (row == 0)) return 1;
    else if (col == 0x50 & (row == 0)) return 2;
    else if (col == 0x30 & (row == 0)) return 3;
    else if (col == 0x60 & (row == 1)) return 4;
    else if (col == 0x50 & (row == 1)) return 5;
    else if (col == 0x30 & (row == 1)) return 6;
    else if (col == 0x60 & (row == 2)) return 7;
    else if (col == 0x50 & (row == 2)) return 8;
    else if (col == 0x30 & (row == 2)) return 9;
    else if (col == 0x60 & (row == 3)) return 10;
    else if (col == 0x50 & (row == 3)) return 11;
    else if (col == 0x30 & (row == 3)) return 12;
    return 0;
}

