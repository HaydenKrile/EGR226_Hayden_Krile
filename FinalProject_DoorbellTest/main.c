#include "msp.h"

void DoorbellPinSet(void);
void DoorbellNote(char);
void BuzzerPinSet(void);
void SysTick_Init();
void delay_ms(uint16_t ms);
void HomeDoorbell(void);

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	SysTick_Init();
	DoorbellPinSet();
	BuzzerPinSet();
	__enable_irq();

	while(1)
	{

	}
}

void DoorbellPinSet(void){
    //set P3.7 as GPIO with internal pull-up resistor
    P5->SEL1 &= ~BIT0;
    P5->SEL0 &= ~BIT0;
    P5->DIR &= ~BIT0;
    P5->REN |= BIT0;
    P5->OUT |= BIT0;

    //enabling interrupts for pins 3.7
    P5->IES |= BIT0;
    P5->IFG = 0;
    P5->IE |= BIT0;

    //enable interrupts
    NVIC_SetPriority(PORT5_IRQn, 3);
    NVIC_EnableIRQ(PORT5_IRQn);
}

void BuzzerPinSet(void){
    //setup P2.4 as GPIO
    P9->SEL0 |= BIT2;
    P9->SEL1 &= ~BIT2;
    P9->DIR |= BIT2;

    //1000 cycles
    TIMER_A3->CCR[0] = 1000;
    TIMER_A3->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;
    //500
    TIMER_A3->CCR[3] = 0;
    TIMER_A3->CTL = 0x0254;
}

void DoorbellNote(char note){
    //C is 2882
    //B is 3054
    float pitch = 2882;
    TIMER_A3->CCR[3] = 500;

    switch(note){
    case 'C':
        TIMER_A3->CCR[0] = pitch;
        break;
    case 'D':
        TIMER_A3->CCR[0] = (pitch * 1.782);
        break;
    case 'E':
        TIMER_A3->CCR[0] = (pitch * 1.587);
        break;
    case 'F':
        TIMER_A3->CCR[0] = (pitch * 1.5);
        break;
    case 'G':
        TIMER_A3->CCR[0] = (pitch * 1.335);
        break;
    case 'A':
        TIMER_A3->CCR[0] = (pitch * 1.19);
        break;
    case 'B':
        TIMER_A3->CCR[0] = (pitch * 1.06);
        break;
    case 'c':
        TIMER_A3->CCR[0] = (pitch * 2);
        break;
    case 'd':
        break;
    case 'e':
        break;
    case 'f':
        break;
    case 'g':
        break;
    case 'a':
        break;
    case 'b':
        TIMER_A3->CCR[0] = (pitch * 2.12);
        break;
    case 'P':
        TIMER_A3->CCR[3] = 0;
        break;
    }
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
    SysTick->LOAD = 0x00FFFFFF;
    //any write to current clears it
    SysTick->VAL = 0;
    //enable systic, 3MHz, no interupts
    SysTick->CTRL = 0x00000005;
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

void HomeDoorbell(void){

    int small = 216, large = 300;

    DoorbellNote('D');
    delay_ms(small);
    DoorbellNote('P');
    delay_ms(3);
    DoorbellNote('D');
    delay_ms(large);
    DoorbellNote('P');
    delay_ms(3);
    DoorbellNote('D');
    delay_ms(small);
    DoorbellNote('P');
    delay_ms(3);
    DoorbellNote('D');
    delay_ms(large);
    DoorbellNote('P');
    delay_ms(3);
    DoorbellNote('c');
    delay_ms(small);
    DoorbellNote('b');
    delay_ms(large);
    DoorbellNote('D');
    delay_ms(small);
    DoorbellNote('G');
    delay_ms(large);
    DoorbellNote('A');
    delay_ms(small);
    DoorbellNote('B');
    delay_ms(large);
    DoorbellNote('P');
    delay_ms(3);
    DoorbellNote('B');
    delay_ms(small);
    DoorbellNote('P');
    delay_ms(3);
    DoorbellNote('B');
    delay_ms(large);
    DoorbellNote('A');
    delay_ms(small);
    DoorbellNote('G');
    delay_ms(600);
    DoorbellNote('P');
}

void PORT5_IRQHandler(void){
    HomeDoorbell();
    P5->IFG = 0;
}

