#include "msp.h"
#include <stdio.h>

void ADCSetup(void);
void SysTick_Init(void);
void SysTick_Handler(void);
volatile float result, temp;

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    //initialize SysTick
    SysTick_Init();
    ADCSetup();

    while(1);
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
    SysTick->LOAD = 1500000;
    //any write to current clears it
    SysTick->VAL = 0;
    //enable systic, 3MHz, interupts
    SysTick->CTRL = 0x00000007;
}

/*-----------------------------------------------------------
* Function: SysTick_Handler
* Description: This function displayed the current number
*               to the 7-segment LED and increments the value
*               after one second passes from the SysTick Timer
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void SysTick_Handler(){

    //start conversion
    ADC14->CTL0 |= 1;
    //wait until conversion is complete
    while(!ADC14->IFGR0);
    //store value in variable result
    result = ADC14->MEM[5];
    temp = ((result * 0.02) -50);
    //print result to console window
    printf("Value is: %.0f or %.1f °C\n", result, temp);
}
