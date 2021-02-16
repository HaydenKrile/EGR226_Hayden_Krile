/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        02/15/2021
* Project:     Lab4Part1
* File:        main.c
* Description: This program connects to the MSP432 and allows the user to cycle
*                   through red, green and blue by pressing the on-board button.
*                   The program uses a function to account for debounce in
*                   the button and prevents the debounce from altering the input from the user
***************************************************************************************/

#include "msp.h"

uint8_t DebounceSwitch1();

void main(void)
{
    //sets P1.1 to a GPIO
    P1->SEL1 &= ~BIT1;
    P1->SEL0 &= ~BIT1;
    //sets P1.1 to input
    P1->DIR &= ~BIT1;
    //the internal resistor is enabled
    P1->REN |= BIT1;
    // sets the resistor as a pull up resistor
    P1->OUT |= BIT1;
    //sets the LED's as outputs
    P2->DIR |= BIT0;
    P2->DIR |= BIT1;
    P2->DIR |= BIT2;

    //sets the first color to be red
    char lightColor = 'R';
    //this variable is used to deal with switch debounce
    int debouncing = 0;

    //turns off all the LEDs before starting the program
    P2->OUT &= ~BIT0;
    P2->OUT &= ~BIT1;
    P2->OUT &= ~BIT2;

    while(1){
        //the debounce function is called to check the status of the button
        debouncing = DebounceSwitch1();
        switch(lightColor){
        //if lightColor is set to red:
        case 'R':
            //turns the red LED on
            P2->OUT |= BIT0;
            //if the button is pushed:
            if(debouncing){
                //the red LED is turned off
                P2->OUT &= ~BIT0;
                //the light color is then set to green
                lightColor = 'G';
            }
            break;

        // if lightColor is set to green:
        case 'G':
            //the green LED is turned on
            P2->OUT |= BIT1;
            if(debouncing){
                //the green LED is turned off
                P2->OUT &= ~BIT1;
                //the light color is then set to blue
                lightColor = 'B';
            }
            break;

        //if lightColor is set to blue:
        case 'B':
            //the blue LED is turned on
            P2->OUT |= BIT2;
            if(debouncing){
                //the blue LED is turned off
                P2->OUT &= ~BIT2;
                //the light color is then set to red
                lightColor = 'R';
            }
            break;
        }

    }

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

    buttonValue = ((P1IN & BIT1) / BIT1) | (buttonValue<<1) | 0xF800;
    //small delay to account for debounce
    __delay_cycles(100);

    //return true of the button was pressed
    if(buttonValue == 0xFC00){
        return 1;
    }

    //return 0 of the button was not pressed
    else{
        return 0;
    }
}
