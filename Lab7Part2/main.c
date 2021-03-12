#include "msp.h"
#include "LCD_lib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 50


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    P4->SEL0 &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    P4->SEL1 &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    P4->DIR |= (BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    P4->OUT &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    SysTick_Init();
    LCD_Init();

    char firstName[SIZE] = "HAYDEN";
    char lastName[SIZE] = "KRILE";
    char className[SIZE] = "EGR";
    char classNum[SIZE] = "226-10";
    int i;
    commandWrite(0x85);
    for(i = 0; i<strlen(firstName); i++){
        dataWrite(firstName[i]);
    }
    commandWrite(0xC5);
    for(i = 0; i<strlen(lastName); i++){
        dataWrite(lastName[i]);
    }
    commandWrite(0x95);
    for(i = 0; i<strlen(className); i++){
        dataWrite(className[i]);
    }
    commandWrite(0xD5);
    for(i = 0; i<strlen(classNum); i++){
        dataWrite(classNum[i]);
    }

    while(1);
}
