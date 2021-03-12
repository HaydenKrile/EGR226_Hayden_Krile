#include "msp.h"
#include "LCD_lib.h"
/*
 * LCD_lib.c
 *
 *  Created on: Mar 5, 2021
 *      Author: hkril
 */

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

void LCD_Init(){
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
*              unsigned 32 bit integer
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

void PulseEnablePin(void){
    P4->OUT |= BIT2;
    delay_micro(10);
    P4->OUT &= ~BIT2;
    delay_micro(10);
}

void pushNibble(uint8_t nibble){
    //clear P4.4-P4.7
    P4->OUT &= ~(0xF0);
    //Port pins P4.4 - P4.7 wired to D4 - D7
    P4->OUT |= ((nibble << 4));
    PulseEnablePin();
}

void pushByte(uint8_t byte){
    pushNibble(byte>>4);
    pushNibble(byte & 0x0F);
}

void commandWrite(uint8_t command){
    //drive P4.1 Low
    P4->OUT &= ~BIT0;
    //send the command
    pushByte(command);
}

void dataWrite(uint8_t data){
    //drive P4.1 High
    P4->OUT |= BIT0;
    //send the data
    pushByte(data);
}
