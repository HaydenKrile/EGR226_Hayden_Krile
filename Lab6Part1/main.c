#include "msp.h"
#include <stdio.h>

void Keypad_Init(void);
void SysTick_Init(void);
void SysTick_delay(uint16_t delay);
int Keypad_Read(void);
int holding(void);
/**
 * main.c
 */
void main(void)
{
    int key, holdingCheck;

	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	//initalize the keypad
	Keypad_Init();
	//initialize the systick timer
	SysTick_Init();

	//prompt the user to push a button on the keypad
	printf("Press a number on the keypad\n");

	while(1){
	    //read the keypad entry
	    key = Keypad_Read();
	    //if a key was pressed
	    if(key)
	        switch(key){
                //if the key pressed was the * key
                case 10:
                    //print the key that was pressed
                    printf("You pressed *\n");
                    //check to see if the key is still pressed
                    holdingCheck = holding();
                    //pause the function while the key is held
                    while(holdingCheck){
                        //check again to see if the key is held
                        holdingCheck = holding();
                    }
                    //break when no key is being held
                    break;

                //if the key pressed was the 0 key
                case 11:
                    //print the key that was pressed
                    printf("You pressed 0\n");
                    //check to see if the key is still pressed
                    holdingCheck = holding();
                    //pause the function while the key is held
                    while(holdingCheck){
                        //check again to see if the key is held
                        holdingCheck = holding();
                    }
                    //break when no key is being held
                    break;

                //if the key pressed was the # key
                case 12:
                    //print the key that was pressed
                    printf("You pressed #\n");
                    //check to see if the key is still pressed
                    holdingCheck = holding();
                    //pause the function while the key is held
                    while(holdingCheck){
                        //check again to see if the key is held
                        holdingCheck = holding();
                    }
                    //break when no key is being held
                    break;

                //if the key pressed was a number key
                default:
                    //print the key that was pressed
                    printf("You pressed %d\n", key);
                    //check to see if the key is still pressed
                    holdingCheck = holding();
                    //pause the function while the key is held
                    while(holdingCheck){
                        //check again to see if the key is held
                        holdingCheck = holding();
                    }
                    //break when no key is being held
                    break;
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
