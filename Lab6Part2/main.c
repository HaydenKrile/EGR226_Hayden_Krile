/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/02/2021
* Project:     Lab6Part2
* File:        main.c
* Description: This program connects to the MSP432 and uses the keypad to
*                   collect user inputs to create a 4 digit PIN code. If the user
*                   inputs 4 digits and hits the pound key, the PIN they entered will be
*                   displayed on the console window. If the user inputs more than
*                   4 digits, only the last 4 digits they entered will be saved when displayed.
*                   If the user enters less than 4, or hits the star key, they will be told
*                   their entry was invalid and they need to try again.
***************************************************************************************/
#include "msp.h"
#include <stdio.h>

void Keypad_Init(void);
void SysTick_Init(void);
void SysTick_delay(uint16_t delay);
int Keypad_Read(void);
int holding(void);

void main(void){
     int holdingCheck, inputs[1000];
     int i = 0;

     WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;        // stop watchdog timer

     //initalize the keypad
     Keypad_Init();
     //initialize the systick timer
     SysTick_Init();

     //prompt the user to push a button on the keypad
     printf("Enter a 4-digit combination\n");

     while(1){
         //if a key was pressed
         if(Keypad_Read()) {
             //check the key that is being pressed
             switch(Keypad_Read()){
                 //if the star is pressed
                 case 10:
                     printf("Invalid input! Try again\n");
                     //check to see if the key is still pressed
                     holdingCheck = holding();
                     //pause the function while the key is held
                     while(holdingCheck){
                         //check again to see if the key is held
                         holdingCheck = holding();
                     }
                     break;
                 //if zero was pressed
                 case 11:
                     //zero is stored in the array
                     inputs[i] = 0;
                     printf("Input stored [0]\n");
                     //check to see if the key is still pressed
                     holdingCheck = holding();
                     //pause the function while the key is held
                     while(holdingCheck){
                         //check again to see if the key is held
                         holdingCheck = holding();
                     }
                     i++;
                     break;

                 //if the pound was pressed
                 case 12:
                     //if the pound was pressed after four numbers were entered
                     if(i > 3){
                         printf("Your code is: [%d][%d][%d][%d]\nEnter another 4-digit combination\n", inputs[i-4], inputs[i-3], inputs[i-2], inputs[i-1]);
                         i = 0;
                     }
                     //if the pound was pressed before four numbers were entered
                     else{
                         printf("Too few inputs!\n");
                         }
                     //check to see if the key is still pressed
                     holdingCheck = holding();
                     //pause the function while the key is held
                     while(holdingCheck){
                         //check again to see if the key is held
                         holdingCheck = holding();
                     }
                     break;
                 //if 1-9 was pressed
                 default:
                     //the the number that was pressed is stored in the array
                     inputs[i] = Keypad_Read();
                     printf("Input stored [%d]\n", inputs[i]);
                     //check to see if the key is still pressed
                     holdingCheck = holding();
                     //pause the function while the key is held
                     while(holdingCheck){
                         //check again to see if the key is held
                         holdingCheck = holding();
                     }
                     //move to the next array value
                     i++;
                     break;
             }
         }
     }
}

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
    P4->DIR = 0;
    //enables pull-up resistors for column pins
    P4->REN = 0x70;
    //make column pins pull-up
    P4->OUT = 0x70;
}

/*-----------------------------------------------------------
* Function: SysTick_Init
* Description: This function enables the SysTick timer for
*                   use in accurate delays.
*
* Citation:
*              Code was lifted from lecture notes
*
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
*
* Citation:
*              Code was lifted from lecture notes
*
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
    P4->DIR |= 0x0F;
    //drive all row pins low
    P4->OUT &= ~0x0F;
    //wait for signals to settle
    SysTick_delay(10);
    //read all column pins
    col = P4->IN & 0x70;
    //drive all rows high
    P4->OUT |= 0x0F;
    //disable all row pins
    P4->DIR &= ~0x0F;
    //if all columns are high
    if(col == 0x70)
        //no key pressed
        return 0;

    //if a key was pressed
    for (row = 0; row < 4; row++){
        //disable all rows
        P4->DIR &= 0x0F;
        //enable one row at a time
        P4->DIR |= row_select[row];
        //drive the active row low
        P4->OUT &= ~row_select[row];
        //wait for signal to settle
        SysTick_delay(10);
        //read all columns
        col = P4->IN & 0x70;
        //drive the active row high
        P4->OUT |= row_select[row];
        //if one of the inputs were low, some key is pressed
        if(col != 0x70)break;
    }
    //drive all rows high
    P4->OUT |= 0x0F;
    //disable all rows
    P4->DIR &= 0x0F;
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

/*-----------------------------------------------------------
* Function: holding
* Description: This function is used to detect when a key is
*                   being pressed and returns 0 if no key was pressed
*                   and 1 if a key was detected to be pressed.
* Inputs:
*              N/A
*
* Outputs:
*              0 or 1
*---------------------------------------------------------*/
int holding(){
    int col;

    //all row pins set to output
    P4->DIR |= 0x0F;
    //drive all row pins low
    P4->OUT &= ~0x0F;
    //wait for signals to settle
    SysTick_delay(10);
    //read all column pins
    col = P4->IN & 0x70;
    //drive all rows high
    P4->OUT |= 0x0F;
    //disable all row pins
    P4->DIR &= ~0x0F;
    //if all columns are high
    if(col == 0x70)
        //no key pressed
        return 0;
    //if a column is low
    else
        //key is pressed
        return 1;
}
