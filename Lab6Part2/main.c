#include "msp.h"
#include <stdio.h>

void Keypad_Init(void);
void SysTick_Init(void);
void SysTick_delay(uint16_t delay);
int Keypad_Read(void);
int holding(void);

#define FALSE 0
#define TRUE 1

/**
 * main.c
 */
void main(void){
    int key, holdingCheck, firstNum, secondNum, thirdNum, fourthNum;
    int isFourNumbersLong = FALSE;

     enum entry{number1, number2, number3, number4};
     enum entry currentState;
     currentState = number1;

     //initalize the keypad
     Keypad_Init();
     //initialize the systick timer
     SysTick_Init();

     //prompt the user to push a button on the keypad
     printf("Enter a 4-digit combination\n");

     while(1){
         //read the keypad entry
         key = Keypad_Read();
         //if a key was pressed
         if(key) {
             switch(currentState){
                 case number1:
                     switch(key){
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

                         case 11:
                             firstNum = 0;
                             printf("Input stored in value 1!\n");
                             //check to see if the key is still pressed
                             holdingCheck = holding();
                             //pause the function while the key is held
                             while(holdingCheck){
                                 //check again to see if the key is held
                                 holdingCheck = holding();
                             }
                             currentState = number2;
                             break;

                         case 12:
                             if(isFourNumbersLong == TRUE)
                                 printf("Your code is: %d%d%d%d\n", firstNum, secondNum, thirdNum, fourthNum);
                             else{
                                 printf("Invalid input! Try again\n");
                                 }
                             //check to see if the key is still pressed
                             holdingCheck = holding();
                             //pause the function while the key is held
                             while(holdingCheck){
                                 //check again to see if the key is held
                                 holdingCheck = holding();
                             }
                             break;

                         default:
                             firstNum = key;
                             printf("Input stored in value 1!\n");
                             //check to see if the key is still pressed
                             holdingCheck = holding();
                             //pause the function while the key is held
                             while(holdingCheck){
                                 //check again to see if the key is held
                                 holdingCheck = holding();
                             }
                             currentState = number2;
                             break;
                     }
                     break;

                 case number2:
                     switch(key){
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

                         case 11:
                             secondNum = 0;
                             printf("Input stored in value 2!\n");
                             //check to see if the key is still pressed
                             holdingCheck = holding();
                             //pause the function while the key is held
                             while(holdingCheck){
                                 //check again to see if the key is held
                                 holdingCheck = holding();
                             }
                             currentState = number3;
                             break;

                         case 12:
                             if(isFourNumbersLong == TRUE)
                                 printf("Your code is: %d%d%d%d\n", firstNum, secondNum, thirdNum, fourthNum);

                             else{
                                 printf("Invalid input! Try again\n");
                             }
                             //check to see if the key is still pressed
                             holdingCheck = holding();
                             //pause the function while the key is held
                             while(holdingCheck){
                                 //check again to see if the key is held
                                 holdingCheck = holding();
                             }
                             break;

                         default:
                             secondNum = key;
                             printf("Input stored in value 2!\n");
                             //check to see if the key is still pressed
                             holdingCheck = holding();
                             //pause the function while the key is held
                             while(holdingCheck){
                                 //check again to see if the key is held
                                 holdingCheck = holding();
                             }
                             currentState = number3;
                             break;
                     }
                     break;

                 case number3:
                     switch(key){
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

                         case 11:
                             thirdNum = 0;
                             printf("Input stored in value 3!\n");
                             //check to see if the key is still pressed
                             holdingCheck = holding();
                             //pause the function while the key is held
                             while(holdingCheck){
                                 //check again to see if the key is held
                                 holdingCheck = holding();
                             }
                             currentState = number4;
                             break;

                         case 12:
                             if(isFourNumbersLong == TRUE)
                                 printf("Your code is: %d%d%d%d\n", firstNum, secondNum, thirdNum, fourthNum);

                             else{
                                 printf("Invalid input! Try again\n");
                                 }
                             //check to see if the key is still pressed
                            holdingCheck = holding();
                            //pause the function while the key is held
                            while(holdingCheck){
                                //check again to see if the key is held
                                holdingCheck = holding();
                             }
                             break;

                         default:
                             thirdNum = key;
                             printf("Input stored in value 3!\n");
                             //check to see if the key is still pressed
                             holdingCheck = holding();
                             //pause the function while the key is held
                             while(holdingCheck){
                                 //check again to see if the key is held
                                 holdingCheck = holding();
                             }
                             currentState = number4;
                             break;
                     }
                     break;

                 case number4:
                     switch(key){
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

                         case 11:
                             fourthNum = 0;
                             printf("Input stored in value 4!\n");
                             //check to see if the key is still pressed
                             holdingCheck = holding();
                             //pause the function while the key is held
                             while(holdingCheck){
                                 //check again to see if the key is held
                                 holdingCheck = holding();
                             }
                             isFourNumbersLong = TRUE;
                             currentState = number1;
                             break;

                         case 12:
                             if(isFourNumbersLong == TRUE)
                                 printf("Your code is: %d%d%d%d\n", firstNum, secondNum, thirdNum, fourthNum);

                             else{
                                 printf("Invalid input! Try again\n");
                                 }
                             //check to see if the key is still pressed
                             holdingCheck = holding();
                             //pause the function while the key is held
                             while(holdingCheck){
                                 //check again to see if the key is held
                                 holdingCheck = holding();
                             }
                             break;

                         default:
                             fourthNum = key;
                             printf("Input stored in value 4!\n");
                             //check to see if the key is still pressed
                             holdingCheck = holding();
                             //pause the function while the key is held
                             while(holdingCheck){
                                 //check again to see if the key is held
                                 holdingCheck = holding();
                             }
                             isFourNumbersLong = TRUE;
                             currentState = number1;
                             break;
                     }
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


int Keypad_Read(){
    int row, col;
    const char row_select[] = {0x01, 0x02, 0x04, 0x08};

    P4->DIR |= 0x0F;
    P4->OUT &= ~0x0F;
    SysTick_delay(10);
    col = P4->IN & 0x70;
    P4->OUT |= 0x0F;
    P4->DIR &= ~0x0F;
    if(col == 0x70)
        return 0;

    for (row = 0; row < 4; row++){
        P4->DIR &= 0x0F;
        P4->DIR |= row_select[row];
        P4->OUT &= ~row_select[row];
        SysTick_delay(10);
        col = P4->IN & 0x70;
        P4->OUT |= row_select[row];
        if(col != 0x70)break;
    }
    P4->OUT |= 0x0F;
    P4->DIR &= 0x0F;
    if(row == 4)
        return 0;

    if (col == 0x60 & (row == 0)) return row * 4 + 1;
    else if (col == 0x50 & (row == 0)) return row * 4 + 2;
    else if (col == 0x30 & (row == 0)) return row * 4 + 3;
    else if (col == 0x60 & (row == 1)) return row * 4;
    else if (col == 0x50 & (row == 1)) return row * 4 + 1;
    else if (col == 0x30 & (row == 1)) return row * 4 + 2;
    else if (col == 0x60 & (row == 2)) return row * 4 - 1;
    else if (col == 0x50 & (row == 2)) return row * 4;
    else if (col == 0x30 & (row == 2)) return row * 4 + 1;
    else if (col == 0x60 & (row == 3)) return row * 4 - 2;
    else if (col == 0x50 & (row == 3)) return row * 4 - 1;
    else if (col == 0x30 & (row == 3)) return row * 4;
    return 0;
}

int holding(){
    int col;

    P4->DIR |= 0x0F;
    P4->OUT &= ~0x0F;
    SysTick_delay(10);
    col = P4->IN & 0x70;
    P4->OUT |= 0x0F;
    P4->DIR &= ~0x0F;
    if(col == 0x70)
        return 0;
    else
        return 1;
}
