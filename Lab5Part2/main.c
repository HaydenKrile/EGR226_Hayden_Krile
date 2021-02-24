/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        02/21/2021
* Project:     Lab5Part2
* File:        main.c
* Description: This program connects to the MSP432 and cycles through green,
*                   yellow, and red LEDs if the user pushes and
*                   holds the off-board white button. When the button is released,
*                   the LED will hold on the color that is is currently showing until the user
*                   holds the button down again.
***************************************************************************************/

#include "msp.h"

void pinSet(void);
void SysTick_Init(void);
void SysTick_delay(uint16_t delay);
int pause();

void main(void){
    //sets all the pins on the MSP tp be used by the program
    pinSet();
    //initialize SysTick timer
    SysTick_Init();

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
                //if the button wasn't released after the second delay:
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
            //if the button isn't being held:
            if((P5IN & BIT1) == 0){
                //green LED is turned on
                P2->OUT |= BIT6;
                //the program waits half a second to see if the user holds the button
                holdButton = pause();
                //if the button wasn't released after the second delay:
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
            //if the button isn't being held:
            if((P5IN & BIT1) == 0){
                //yellow LED is turned on
                P2->OUT |= BIT5;
                //the program waits half a second to see if the user holds the button
                holdButton = pause();
                //if the button wasn't released after the second delay:
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
    //enable systic, 3MHz, no interrupts
    SysTick->CTRL = 0x00000005;
}

/*-----------------------------------------------------------
* Function: SysTick_Delay
* Description: This function takes in a millisecond value and uses
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
* Function: pause
* Description: This function checks to see if the user is pressing and holding the white button.
*                   If the user is pressing and holding the button, the program returns true,
*                   but if the user releases the button and a second passes, the program will then return false.
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
int pause(){

    int i;

    //this for loop checks 500 times to see if the button is held every 2ms, resulting in a second delay with a 3 mHz clock
    for(i = 0; i <= 500; i++){

        //if the button is detected to be not pressed, the function returns true
        if(P5IN & BIT1){
            return 1;
        }
        //2ms delay
        SysTick_delay(2);
    }
    // if a button input was detected in the second delay, the program returns false
    return 0;
}
