#include "msp.h"
#include "LCD_lib.h"
/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/10/2021
* File:        LCD_lib.c
* Description: This library contains all the functions needed for starting and
*                   interacting to the LCD when connected to the MSP432
***************************************************************************************/

/*-----------------------------------------------------------
* Function: SysTick_Init
* Description: This function enables the SysTick timer for
*                   use in accurate delays.
*
* Citation:
*              Code was gathered from lecture powerpoints
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
* Function: LCD_Init
* Description: This function enables and configures the LCD
*                   so that the user can interact with it
*
* Citation:
*              Code was gathered from lab pdf
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void LCD_Init(){
    //configure pins 4.0, .2, .4-.7 to be GPIO
    P4->SEL0 &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    P4->SEL1 &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    P4->DIR |= (BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    //turn off all pins before beginning the program just in case
    P4->OUT &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);

    P4->OUT &= ~BIT0;

    commandWrite(0x03);
    delay_ms(100);
    commandWrite(0x03);
    delay_micro(200);
    commandWrite(0x03);
    delay_ms(100);
    commandWrite(0x02);

    delay_micro(100);
    commandWrite(0x28);
    delay_micro(100);

    delay_micro(100);
    commandWrite(0x0F);
    delay_micro(100);
    commandWrite(0x01);
    delay_micro(100);
    commandWrite(0x06);
    delay_ms(10);

}

/*-----------------------------------------------------------
* Function: delay_micro
* Description: This functions create a microsecond delay
*                   from an inputed integer using SysTick
*
* Citation:
*              Code was gathered from lecture powerpoints
*
* Inputs:
*              unsigned 16 bit integer
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void delay_micro(uint16_t microsecond){
    //convert inputed value to microseconds with 3MHz clock
    SysTick->LOAD = (microsecond * 3 - 1);
    //clear counter
    SysTick->VAL = 0;
    while((SysTick->CTRL & 0x00010000) == 0);
}

/*-----------------------------------------------------------
* Function: delay_ms
* Description: This function takes in a milisecond value and uses
*                   the SysTick timer to delay until the specified amount
*                   of time has passed.
* Citation:
*              Code was gathered from lecture powerpoints
*
* Inputs:
*              uint16_t delay
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void delay_ms(uint16_t ms){
    //delay for 1 ms per delay value
    SysTick->LOAD = ((ms * 3000) - 1);
    //any write to CRV clears it
    SysTick->VAL = 0;
    //wait for flag to be SET
    while((SysTick->CTRL & 0x00010000) == 0);
}

/*-----------------------------------------------------------
* Function: PulseEnablePin
* Description: This function turns on the enable pin in the LCD,
*                   waits 50 microseconds
* Citation:
*              Code was gathered from lecture powerpoints
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PulseEnablePin(void){
    P4->OUT |= BIT2;
    delay_micro(50);
    P4->OUT &= ~BIT2;
    delay_micro(50);
}

/*-----------------------------------------------------------
* Function: pushNibble
* Description: This function collects the nibble given by the pushByte function
*               and pulses the enable pin
* Citation:
*              Code was gathered from lecture powerpoints
*
* Inputs:
*              uint8_t nibble
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void pushNibble(uint8_t nibble){
    //clear P4.4-P4.7
    P4->OUT &= ~(0xF0);
    //Port pins P4.4 - P4.7 wired to D4 - D7
    P4->OUT |= ((nibble << 4));
    PulseEnablePin();
}

/*-----------------------------------------------------------
* Function: pushByte
* Description: This function breaks the Byte into two nibbles and sends
*                   them to the pushNibble function
* Citation:
*              Code was gathered from lecture powerpoints
*
* Inputs:
*              uint8_t byte
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void pushByte(uint8_t byte){
    pushNibble(byte>>4);
    pushNibble(byte & 0x0F);
}

/*-----------------------------------------------------------
* Function: commandWrite
* Description: This function sets the RW pin to low, to indicate
*                   the command sent is a command, and sends the command
*                   to the pushByte function
* Citation:
*              Code was gathered from lecture powerpoints
*
* Inputs:
*              uint8_t command
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void commandWrite(uint8_t command){
    //drive P4.0 Low
    P4->OUT &= ~BIT0;
    delay_micro(50);
    //send the command
    pushByte(command);
}

/*-----------------------------------------------------------
* Function: dataWrite
* Description: This function sets the RW pin to high, to indicate
*                   the command sent is data, and sends the data to
*                   the pushByte function
* Citation:
*              Code was gathered from lecture powerpoints
*
* Inputs:
*              uint8_t command
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void dataWrite(uint8_t data){
    //drive P4.0 High
    P4->OUT |= BIT0;
    delay_micro(50);
    //send the data
    pushByte(data);
}


