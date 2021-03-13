#include "msp.h"
#include "LCD_lib.h"
#include <string.h>
#define SIZE 15

/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/12/2021
* Project:     Lab7Part3
* File:        main.c
* Description: This program connects to the MSP432 and configures the
*                   LED screen to print "LABORATORY OVER" to the first row.
*                   The the program slide the text from right-to-left until
*                   the text is no longer visible, then the text slides in
*                   from the right side of the screen until it has wrapped
*                   all the way around and continues forever.
***************************************************************************************/
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    //configure pins 4.0, .2, .4-.7 to be GPIO
    P4->SEL0 &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    P4->SEL1 &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    P4->DIR |= (BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    //turn off all pins before beginning the program just in case
    P4->OUT &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    //initialize Systick and the LCD
    SysTick_Init();
    LCD_Init();

    char labOver[SIZE] = "LABORATORY OVER";
    int i = 0;
    int j = 0;
    int k = 0;

    while(1){
        //start at the first space
        commandWrite(0x80);
        //for loop that dictates how much of the text to print
        for(i = 0; i < strlen(labOver); i++){
            //delay one second
            delay_ms(1000);
            //clear the screen
            commandWrite(1);
            delay_ms(50);
            //start at the first place
            commandWrite(0x80);
                //write the remaining pieces of the string
                for(j = i; j < strlen(labOver); j++){
                dataWrite(labOver[j]);
            }
        }
        //clear the screen when finished
        commandWrite(1);
        delay_ms(50);

        //this for loop dictates where the cursor should start to give the effect of scrolling from the right
        for(i = 143; i > 128; i--){
            //one second delay
            delay_ms(1000);
            //clear the screen
            commandWrite(1);
            delay_ms(50);
            //write to the new starting point
            commandWrite(i);
            //print out the proper number of characters
            for(j = 0; j <= k; j++){
                dataWrite(labOver[j]);
            }
            //add to the amount of characters than can be printed
            k++;
        }
        //reset for the next loop through
        k=0;
    }
}
