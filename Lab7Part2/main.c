#include "msp.h"
#include "LCD_lib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 50

/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/11/2021
* Project:     Lab7Part2
* File:        main.c
* Description: This program connects to the MSP432 and configures the
*                   LED screen to print my first name, last name, EGR,
*                   and class number in the middle of the LCD
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

    //character strings to be printed to the LCD
    char firstName[SIZE] = "HAYDEN";
    char lastName[SIZE] = "KRILE";
    char className[SIZE] = "EGR";
    char classNum[SIZE] = "226-10";
    int i;

    //start the cursor near the middle of the first row
    commandWrite(0x85);
    //write the first string
    for(i = 0; i<strlen(firstName); i++){
        dataWrite(firstName[i]);
    }
    //move cursor to second row
    commandWrite(0xC5);
    //write the second string
    for(i = 0; i<strlen(lastName); i++){
        dataWrite(lastName[i]);
    }
    //move cursor to third row
    commandWrite(0x95);
    //write the third string
    for(i = 0; i<strlen(className); i++){
        dataWrite(className[i]);
    }
    //move cursor to fourth row
    commandWrite(0xD5);
    //write the fourth string
    for(i = 0; i<strlen(classNum); i++){
        dataWrite(classNum[i]);
    }

    while(1);
}
