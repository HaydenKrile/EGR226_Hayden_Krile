/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/10/2021
* File:        LCD_lib.h
* Description: This library contains all the functions headers needed for starting and
*                   interacting to the LCD when connected to the MSP432
***************************************************************************************/

#ifndef LCD_LIB_H_
#define LCD_LIB_H_

void SysTick_Init();
void LCD_Init();
void delay_micro(uint16_t microsecond);
void delay_ms(uint16_t ms);
void PulseEnablePin();
void pushNibble(uint8_t nibble);
void pushByte(uint8_t byte);
void commandWrite(uint8_t command);
void dataWrite(uint8_t data);

#endif /* LCD_LIB_H_ */
