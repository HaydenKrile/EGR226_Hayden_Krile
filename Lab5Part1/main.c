#include "msp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

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
            default:
                if(debouncing){
                    //the light color is then set to green
                    lightColor = 'G';
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

        buttonValue = ((P5IN & BIT1) / BIT1) | (buttonValue<<1) | 0xF800;
        //small delay to account for debounce
        __delay_cycles(1000);

        //return true of the button was pressed
        if(buttonValue == 0xFC00){
            return 1;
        }

        //return 0 of the button was not pressed
        else{
            return 0;
        }
    }


