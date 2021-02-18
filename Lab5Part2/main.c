/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        02/23/2021
* Project:     Lab5Part2
* File:        main.c
* Description: This program connects to the MSP432 and cycles through green,
*                   yellow, and red LEDs if the user pushes and
*                   holds the off-board button. When the button is released,
*                   the LED will hold on the color that is is currently showing until the user
*                  holds the button down again.
***************************************************************************************/

#include "msp.h"

int pause();

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

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

    //creates the switch statement variable and set the initial state to green
    char lightColor = 'G';
    //variable used to detect when the button is being held down
    int holdButton;

    //infinite while loop
    while (1){
        //the color of the LED is checked with this switch statement
        switch(lightColor){

        //if the color state is red:
        case 'R':
            if((P5IN & BIT1) == 0){
                //red LED is turned on
                P2->OUT |= BIT4;
                //the program waits half a second to see if the user holds the button
                holdButton = pause();
                //if the button wasn't released after the half-second delay:
                if(holdButton == 0) {
                    //turns off the red LED
                    P2->OUT &= ~BIT4;
                    //sets the state variable to green
                    lightColor = 'G';
                }
            }
            break;

        //if the color state is green:
        case 'G':
            //if the button isnt being held:
            if((P5IN & BIT1) == 0){
                //green LED is turned on
                P2->OUT |= BIT6;
                //the program waits half a second to see if the user holds the button
                holdButton = pause();
                //if the button wasn't released after the half-second delay:
                if(holdButton == 0) {
                    //turns off the green LED
                    P2->OUT &= ~BIT6;
                    //sets the state variable to yellow
                    lightColor = 'Y';
                }
            }
            break;

        //if the color state is yellow:
        case 'Y':
            //if the button isnt being held:
            if((P5IN & BIT1) == 0){
                //yellow LED is turned on
                P2->OUT |= BIT5;
                //the program waits half a second to see if the user holds the button
                holdButton = pause();
                //if the button wasn't released after the half-second delay:
                if(holdButton == 0) {
                    //turns off the yellow LED
                    P2->OUT &= ~BIT5;
                    //sets the state variable to red
                    lightColor = 'R';
                }
            }
            break;
        }
    }
}

/*-----------------------------------------------------------
* Function: pause
* Description: This function checks to see if the user is pressing and holding the button.
*                   If the user is pressing and holding the button, the program returns true,
*                   but if the user releases the button and 0.5 seconds pass, the program will then return false.
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
int pause(){

    int i;

    //this for loop checks 500 times to see if the button is held every 3000 cycles, resulting in a 0.5 second delay with a 3 mHz clock
    for(i = 0; i <= 500; i++){

        //if the button is detected to be pressed, the function returns true
        if(P5IN & BIT1){
            return 1;
        }
        //the function is delayed 3000 cycles
        __delay_cycles(3000);
    }

    // if no button input was detected in the 0.5 second delay, the program returns false
    return 0;

}
