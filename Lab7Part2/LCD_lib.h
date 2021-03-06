/*
 * LCD_lib.h
 *
 *  Created on: Mar 5, 2021
 *      Author: hkril
*/

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
