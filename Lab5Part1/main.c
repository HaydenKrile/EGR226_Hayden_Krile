/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        02/20/2021
* Project:     Lab5Part1
* File:        main.c
* Description: This program connects to the MSP432 and cycles through green,
*                   yellow, and red LEDs if the user pushes the off-board white
*                   button. This program uses the SysTick timer to account for
*                   switch debounce when reading the user pressing the button.
***************************************************************************************/
#include "msp.h"

void pinSet(void);
void SysTick_Init(void);
void SysTick_delay(uint16_t delay);
uint8_t DebounceSwitch1(void);

void main(void)
{
    //sets all the pins on the MSP tp be used by the program
	pinSet();
	//initialize SysTick timer
	SysTick_Init();

    char lightColor;
    //this variable is used to deal with switch debounce
    int debouncing = 0;

    while(1){
        //the debounce function is called to check the status of the button
        debouncing = DebounceSwitch1();
        switch(lightColor){
        //if lightColor is set to red:
        case 'R':
            //turns the red LED on
            P2->OUT |= BIT4;
            //if the button is pushed:
            if(debouncing){
                //the red LED is turned off
                P2->OUT &= ~BIT4;
                //the light color is then set to green
                lightColor = 'G';
            }
            break;

        // if lightColor is set to yellow:
        case 'Y':
            //the yellow LED is turned on
            P2->OUT |= BIT5;
            if(debouncing){
                //the yellow LED is turned off
                P2->OUT &= ~BIT5;
                //the light color is then set to red
                lightColor = 'R';
            }
            break;

        //if lightColor is set to green:
        case 'G':
            //the green LED is turned on
            P2->OUT |= BIT6;
            if(debouncing){
                //the green LED is turned off
                P2->OUT &= ~BIT6;
                //the light color is then set to yellow
                lightColor = 'Y';
            }
            break;
        //at the beginning of the program, all LEDs are off
        default:
            //when the first button press is detected:
            if(debouncing){
                //the light color is then set to green
                lightColor = 'G';
            }
            break;
        }
    }
}

/*-----------------------------------------------------------
* Function: pinSet
* Description: This function sets each of the MSP432 pins used in the program
*                   to their respective I/O, and also enables the internal
*                   pull-down resistor for the button.
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void pinSet(){
    // stop watchdog timer
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    //sets P5.1 to a GPIO
    P5->SEL1 &= ~BIT1;
    P5->SEL0 &= ~BIT1;
    //sets P5.1 to input
    P5->DIR &= ~BIT1;
    //the internal resistor is enabled
    P5->REN |= BIT1;
    // sets the resistor as a pull up resistor
    P5->OUT |= BIT1;

    //sets P2.4, P2.5, and P2.6 as outputs
    P2->DIR |= 0x70;
    //turns off all LEDs
    P2->OUT &= ~0x70;
}

/*-----------------------------------------------------------
* Function: SysTick_Init
* Description: This function enables the SysTick timer for
*                   use in accurate delays.
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
* Function: DebounceSwitch1
* Description: Checks to see if switch 1 was pressed, and delays the read and checks again
                to account for debounce. If the function detects a valid press, the
                program returns as true.
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
uint8_t DebounceSwitch1(){

    static uint16_t buttonValue = 0;

    buttonValue = ((P5IN & BIT1) / BIT1) | (buttonValue<<1) | 0xF800;
    //5ms delay to deal with debounce
    SysTick_delay(5);

    //return true of the button was pressed
    if(buttonValue == 0xFC00){
        return 1;
    }

    //return 0 of the button was not pressed
    else{
        return 0;
    }
}
