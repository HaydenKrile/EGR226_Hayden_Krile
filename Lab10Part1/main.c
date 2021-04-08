#include "msp.h"
#include "LCD_lib.h"
#include <stdio.h>

void ADCSetup(void);

/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        03/26/2021
* Project:     Lab10Part1
* File:        main.c
* Description: This program connects to the MSP432 and uses the 10K
*               pot and ADC to determine the voltage driven to the MSP432
*               and displays this value to the console window
***************************************************************************************/
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	float result, voltage;

	//initialize SysTick
	SysTick_Init();
    ADCSetup();

	while(1){
        //start conversion
        ADC14->CTL0 |= 1;
        //wait until conversion is complete
        while(!ADC14->IFGR0);
	    //store value in variable result
        result = ADC14->MEM[5];
        voltage = result * 0.6101;
        //print result to console window
        printf("Value is: %.0f or %.2f V\n", result, voltage);
        //wait for next value
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
