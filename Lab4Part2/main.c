/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        02/16/2021
* Project:     Lab4Part2
* File:        main.c
* Description: This program connects to the MSP432 and cycles through red,
*                   green, and blue on the RGB LED. If the user pushes and
*                   holds the on-board button, the LED will hold on the
*                   the button and prevents the debounce from altering the input from the user
***************************************************************************************/

#include "msp.h"

int pause();

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

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

    //turns off all the LEDs before starting the program
    P2->OUT &= ~BIT0;
    P2->OUT &= ~BIT1;
    P2->OUT &= ~BIT2;

    //creates the switch statement varibale and set the initial state to red
    char lightColor = 'R';
    //variable used to detect when the button is being held down
    int holdButton;

    while (1){
        switch(lightColor){

        case 'R':
            if((P1IN & BIT1) == 0){
                P2->OUT |= BIT0;
                holdButton = pause();
                if(holdButton == 1) {
                    P2->OUT |= BIT0;
                }
                else{
                    P2->OUT &= ~BIT0;
                    lightColor = 'G';
                }
            }
            break;

        case 'G':
            if((P1IN & BIT1) == 0){
                P2->OUT |= BIT1;
                holdButton = pause();
                if(holdButton == 1) {
                    P2->OUT |= BIT1;
                }
                else{
                    P2->OUT &= ~BIT1;
                    lightColor = 'B';
                }
            }
            break;

        case 'B':
            if((P1IN & BIT1) == 0){
                P2->OUT |= BIT2;
                holdButton = pause();
                if(holdButton == 1) {
                    P2->OUT |= BIT2;
                }
                else{
                    P2->OUT &= ~BIT2;
                    lightColor = 'R';
                }
            }
            break;
        }
    }
}

int pause(){

    int i;

    for(i = 0; i <= 500; i++){

        if(P1IN & BIT1){
            return 1;
        }
        __delay_cycles(3000);
    }

    return 0;

}
