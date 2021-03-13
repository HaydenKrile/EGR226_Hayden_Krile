#include "msp.h"
#include "LCD_lib.h"
#include <string.h>
#define SIZE 15

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    P4->SEL0 &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    P4->SEL1 &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    P4->DIR |= (BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    P4->OUT &= ~(BIT0|BIT2|BIT4|BIT5|BIT6|BIT7);
    SysTick_Init();
    LCD_Init();

    char labOver[SIZE] = "LABORATORY OVER";
    int i = 0;
    int j = 0;
    int k = 0;

    commandWrite(0x80);
    while(1){
        commandWrite(0x80);
        for(i = 0; i < strlen(labOver); i++){
            delay_ms(500);
            commandWrite(1);
            delay_ms(50);
            commandWrite(0x80);
                for(j = i; j < strlen(labOver); j++){
                dataWrite(labOver[j]);
            }
        }
        commandWrite(1);
        delay_ms(50);

        for(i = 143; i > 128; i--){
            delay_ms(500);
            commandWrite(1);
            delay_ms(50);
            commandWrite(i);
            for(j = 0; j <= k; j++){
                dataWrite(labOver[j]);
            }
            k++;
        }
        k=0;
    }
}
