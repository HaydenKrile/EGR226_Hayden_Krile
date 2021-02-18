#include "msp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    P5->SEL1 &= ~3;
    P5->SEL0 &= ~3;
    P5->DIR &= ~3;
    P5->REN |= 3;
    P5->OUT |= 3;

    //sets P2.4, P2.5, and P2.6 as outputs
    P2->DIR |= 0x70;

    //turns off all LEDs
    P2->OUT &= ~0x70;

    while (1){
        P2->OUT ^= BIT4;
        __delay_cycles(500000);
        P2->OUT ^= BIT5;
        __delay_cycles(500000);
        P2->OUT ^= BIT6;
        __delay_cycles(500000);
    }

}
