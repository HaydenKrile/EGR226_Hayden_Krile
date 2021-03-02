/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/02/2021
* Project:     Lab6Part3
* File:        main.c
* Description: This program connects to the MSP432 and uses the keypad to
*                   collect user inputs to create a 4 digit PIN code.
*                   After a successful PIN is accepted, the user will then be asked
*                   to re-enter their PIN, if the user enters the correct PIN again, they
*                   will be told they successfully repeated the PIN. If they fail, they will
*                   be told they incorrectly re-entered the Pin code.
***************************************************************************************/
#include "msp.h"
#include <stdio.h>

void Keypad_Init(void);
void SysTick_Init(void);
void SysTick_delay(uint16_t delay);
int Keypad_Read(void);
int holding(void);

void main(void){
     int holdingCheck, inputs[1000], master[1000];
     int i = 0;
     int j = 0;
     int isInput = 0;

     WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;        // stop watchdog timer

     //initalize the keypad
     Keypad_Init();
     //initialize the systick timer
     SysTick_Init();

     //prompt the user to push a button on the keypad
     printf("Enter a 4-digit combination\n");

     while(1){
         //if a key was detected
         if(Keypad_Read()){
             //if this is to re-enter the PIN
            if(isInput == 1){
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
                            //if the inputed code matches the master code
                            if((master[j-4] == inputs[i-4]) & (master[j-3] == inputs[i-3]) & (master[j-2] == inputs[i-2]) & (master[j-1] == inputs[i-1]))
                                printf("Your codes match!\n[%d][%d][%d][%d]\n[%d][%d][%d][%d]\n", master[j-4], master[j-3], master[j-2], master[j-1], inputs[i-4], inputs[i-3], inputs[i-2], inputs[i-1]);
                            //if the codes do not match
                            else
                                printf("Your codes do not match!\n[%d][%d][%d][%d]\n[%d][%d][%d][%d]\n", master[j-4], master[j-3], master[j-2], master[j-1], inputs[i-4], inputs[i-3], inputs[i-2], inputs[i-1]);
                            i = 0;
                            j = 0;
                            isInput = 0;
                        }
                        //if the pound was pressed before four numbers were entered
                        else{
                            printf("Too few inputs!\n");
                            //check to see if the key is still pressed
                            holdingCheck = holding();
                            //pause the function while the key is held
                            while(holdingCheck){
                            //check again to see if the key is held
                            holdingCheck = holding();
                            }
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

            //if this is to enter the master PIN
            else{
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
                        master[j] = 0;
                        printf("Input stored [0]\n");
                        //check to see if the key is still pressed
                        holdingCheck = holding();
                        //pause the function while the key is held
                        while(holdingCheck){
                            //check again to see if the key is held
                            holdingCheck = holding();
                        }
                        j++;
                        break;

                    //if the pound was pressed
                    case 12:
                        //if the pound was pressed after four numbers were entered
                        if(j > 3){
                            printf("Your master code is: [%d][%d][%d][%d]\nRe-enter your code\n", master[j-4], master[j-3], master[j-2], master[j-1]);
                            isInput = 1;
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
                        master[j] = Keypad_Read();
                        printf("Input stored [%d]\n", master[j]);
                        //check to see if the key is still pressed
                        holdingCheck = holding();
                        //pause the function while the key is held
                        while(holdingCheck){
                            //check again to see if the key is held
                            holdingCheck = holding();
                        }
                        //move to the next array value
                        j++;
                        break;
                }
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
* Function: Keypad_Init
* Description: This function is used to detect which key
*                   was pressed and interpret which
*                   number to return. Code was lifted from
*                   MSP432 textbook.
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
