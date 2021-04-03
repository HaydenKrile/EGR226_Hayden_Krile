#include "msp.h"
#include "LCD_lib.h"
#include <string.h>
#include <stdio.h>
#define SIZE 50

void ADCSetup(void);
void ButtonPinSet(void);
void PORT3_IRQHandler(void);

volatile int mode = 0;

/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/27/2021
* Project:     Lab10Part3
* File:        main.c
* Description: This program connects to the MSP432 and uses the temp
*               sensor and ADC to determine the voltage driven to the MSP432
*               and displays this value to the LCD screen along with the converted
*               temperature to degrees C. when the pushbutton is pressed, the value
*               displays is changed to degrees F
***************************************************************************************/
void main(void){
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    //configure pins 4.0, .2, .4-.7 to be GPIO
    P4->SEL0 &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    P4->SEL1 &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    P4->DIR |= (BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    //turn off all pins before beginning the program just in case
    P4->OUT &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);

    char prompt[SIZE] = "Current Temp. is";
    char currentTempString [SIZE];
    float result, temp;
    int i;

	SysTick_Init();
	LCD_Init();
	ADCSetup();
	ButtonPinSet();

	//display the prompt to the screen
    commandWrite(0x80);
    for(i = 0; i<strlen(prompt); i++){
        dataWrite(prompt[i]);
    }

    __enable_irq();
	while(1){
	    //start conversion
	    ADC14->CTL0 |= 1;
	    //wait until conversion is complete
	    while(!ADC14->IFGR0);
	    //store value in variable result
	    result = ADC14->MEM[5];
	    temp = ((result * 0.02) -50);

	    //start at the middle of the second line
	    commandWrite(0xC5);

	    //if in celcius mode
	    if(mode == 0){
	        //copies the temperature to a string so it can be printed to the LCD
	        sprintf(currentTempString, "%.1f", temp);
            for(i = 0; i<strlen(currentTempString); i++){
                dataWrite(currentTempString[i]);
            }
            //displays the degree symbol on the LCD
            dataWrite(0xDF);
            //shows C to tell hte user the mode the program is in
            dataWrite('C');
	    }

	    //if in farenheight mode
	    if(mode == 1){
	        temp = ((1.8*temp)+32);
	        //copies the temperature to a string so it can be printed to the LCD
	        sprintf(currentTempString, "%.1f", temp);
            for(i = 0; i<strlen(currentTempString); i++){
                dataWrite(currentTempString[i]);
            }
            //displays the degree symbol on the LCD
            dataWrite(0xDF);
	        dataWrite('F');
	    }

	    delay_ms(500);
	}
}

/*-----------------------------------------------------------
* Function: ADCSetup
* Description: This function enables ADC converter to be
*               used with the 10k Pot
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
void ADCSetup(){
    //power on and disable during setup stage
    ADC14->CTL0 = 0x10;
    //S/H pulse mode, MCLCK, 32 sample clocks, SW trigger, /4 clock divide
    ADC14->CTL0 |= 0x04D80300;
    //14-bit resolution
    ADC14->CTL1 = 0x30;
    //A0 input, single ended, vref=avcc
    ADC14->MCTL[5] = 0;
    //configure pin 5.5 for AO
    P5->SEL1 |= 0x20;
    P5->SEL0 |= 0x20;
    //start converting at mem reg 5
    ADC14->CTL1 |= 0x00050000;
    //enable ADC after configuration
    ADC14->CTL0 |= 2;
}

/*-----------------------------------------------------------
* Function: ButtonPinSetup
* Description: This function sets up the pins for the push button
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void ButtonPinSet(void){
    //set P3.5-7 as GPIO with internal pull-up resistor
    P3->SEL1 &= ~BIT2;
    P3->SEL0 &= ~BIT2;
    P3->DIR &= ~BIT2;
    P3->REN |= BIT2;
    P3->OUT |= BIT2;

    //enabling interrupts for pins 3.5-7
    P3->IES |= BIT2;
    P3->IFG = 0;
    P3->IE |= BIT2;

    NVIC_SetPriority(PORT3_IRQn, 3);
    NVIC_EnableIRQ(PORT3_IRQn);
}

/*-----------------------------------------------------------
* Function: PORT3_IRQHandler
* Description: This function handles the interrupts generated
*                    by the button
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PORT3_IRQHandler(void){

    //delay to deal with debounce
    delay_ms(50);
    if(P3->IFG & BIT2){

        if (mode == 0)
            mode = 1;
        else
            mode = 0;
    }

    //debounce delay
    delay_ms(50);
    //reset flag
    P3->IFG = 0;;
}
