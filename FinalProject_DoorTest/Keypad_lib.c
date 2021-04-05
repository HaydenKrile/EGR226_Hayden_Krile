#include "msp.h"
#include "Keypad_lib.h"
/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        04/01/2021
* File:        Keypad_lib.c
* Description: This library contains all the functions needed for
*                   interacting with the keypad when connected to the MSP432
***************************************************************************************/

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
    P7->DIR = 0;
    //enables pull-up resistors for column pins
    P7->REN = 0x70;
    //make column pins pull-up
    P7->OUT = 0x70;
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
    P7->DIR |= 0x0F;
    //drive all row pins low
    P7->OUT &= ~0x0F;
    //wait for signals to settle
    delay_ms(10);
    //read all column pins
    col = P7->IN & 0x70;
    //drive all rows high
    P7->OUT |= 0x0F;
    //disable all row pins
    P7->DIR &= ~0x0F;
    //if all columns are high
    if(col == 0x70)
        //no key pressed
        return 0;

    //if a key was pressed
    for (row = 0; row < 4; row++){
        //disable all rows
        P7->DIR &= 0x0F;
        //enable one row at a time
        P7->DIR |= row_select[row];
        //drive the active row low
        P7->OUT &= ~row_select[row];
        //wait for signal to settle
        delay_ms(10);
        //read all columns
        col = P7->IN & 0x70;
        //drive the active row high
        P7->OUT |= row_select[row];
        //if one of the inputs were low, some key is pressed
        if(col != 0x70)break;
    }
    //drive all rows high
    P7->OUT |= 0x0F;
    //disable all rows
    P7->DIR &= 0x0F;
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

