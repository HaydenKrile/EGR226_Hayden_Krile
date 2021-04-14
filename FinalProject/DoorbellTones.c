#include "msp.h"
#include "DoorbellTones.h"
#include "LCD_lib.h"

/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        04/08/2021
* Project:     FinalProject
* File:        DoorbellTones.c
* Description: This library contains the commands used to
*                   control the tones created by the speaker from
*                   the MSP432 by using a PWM signal on pin 9.2
***************************************************************************************/

/*-----------------------------------------------------------
* Function: DoorbellNote
* Description: This function contains all the note of
*               the C-Major scale. Note tuning was found by
*               altering the pitch multiplication and using
*               an outside tuner to create the correct pitch
*               for each note.
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
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
    case 'b':
        TIMER_A3->CCR[0] = (pitch * 2.12);
        break;
    case 'Z':
        TIMER_A3->CCR[0] = (pitch * 6);
        TIMER_A3->CCR[3] = 3000;
        break;
    case 'P':
        TIMER_A3->CCR[3] = 0;
        break;
    }
}

/*-----------------------------------------------------------
* Function: DoorbellNote
* Description: This function contains all the notes and timings used to re-create
*               the doorbell tone used at my home in Ann Arbor
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
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

/*-----------------------------------------------------------
* Function: Dingdong
* Description: This function when called plays a simple two note tone
*               to simulate a basic "ding-dong" chime with the speaker
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void DingDong(void){
    DoorbellNote('C');
    delay_ms(600);
    DoorbellNote('G');
    delay_ms(700);
    DoorbellNote('P');
}

/*-----------------------------------------------------------
* Function: Buzzer
* Description: This function when called plays a single low tone to
*                   simulate an apartment buzzer with the speaker
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void Buzzer(void){
    DoorbellNote('Z');
    delay_ms(1500);
    DoorbellNote('P');
}
