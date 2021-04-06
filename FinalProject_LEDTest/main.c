#include "msp.h"
#include "LCD_lib.h"
#include "Keypad_lib.h"
#include <string.h>
#define SIZE 20
#define TRUE 1
#define FALSE 0

void OffBoardLEDPinSet(void);
void PrintLightsMenu(void);
void PrintBrightnessMenu(void);
void ChangeLEDBrightness(int);
int holding(void);

enum lightsOptions{
    lightsMenu,
    redLight,
    greenLight,
    blueLight
};
enum lightsOptions currentLightState = lightsMenu;

int firstEnter = TRUE;
volatile double redDutyCycle = 0, greenDutyCycle = 0, blueDutyCycle = 0;
/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	SysTick_Init();
	Keypad_Init();
	LCD_Init();
	OffBoardLEDPinSet();
	PrintLightsMenu();

	int keyHold = 0, holdingCheck;

	while(1){
	    switch(currentLightState){
	    case lightsMenu:
            keyHold = Keypad_Read();
            switch(keyHold){
            case 1:
                currentLightState = redLight;
                //check to see if the key is still pressed
                holdingCheck = holding();
                //pause the function while the key is held
                while(holdingCheck){
                    //check again to see if the key is held
                    holdingCheck = holding();
                }
                break;
            case 2:
                currentLightState = greenLight;
                //check to see if the key is still pressed
                holdingCheck = holding();
                //pause the function while the key is held
                while(holdingCheck){
                    //check again to see if the key is held
                    holdingCheck = holding();
                }
                break;
            case 3:
                currentLightState = blueLight;
                //check to see if the key is still pressed
                holdingCheck = holding();
                //pause the function while the key is held
                while(holdingCheck){
                    //check again to see if the key is held
                    holdingCheck = holding();
                }
                break;
            default:
                ;
            }
            break;
        case redLight:
            if(firstEnter){
                PrintBrightnessMenu();
                firstEnter = FALSE;
            }
            ChangeLEDBrightness(2);
            break;
        case greenLight:
            if(firstEnter){
                PrintBrightnessMenu();
                firstEnter = FALSE;
            }
            ChangeLEDBrightness(3);
            break;
        case blueLight:
            if(firstEnter){
                PrintBrightnessMenu();
                firstEnter = FALSE;
            }
            ChangeLEDBrightness(4);
            break;
	    }
	}
}

/*-----------------------------------------------------------
* Function: OffBoardLEDPinSet
* Description: This function sets up the pins for the off board 3 LED
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void OffBoardLEDPinSet(void){
    //setup P2.5-7 as GPIO
    P2->SEL0 |= (BIT5|BIT6|BIT7);
    P2->SEL1 &= ~(BIT5|BIT6|BIT7);
    P2->DIR |= (BIT5|BIT6|BIT7);
    //P2->REN |= BIT5;


    //40000 cycles
    TIMER_A0->CCR[0] = 10000;
    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;
    //by default, sets the duty cycle to 0%
    TIMER_A0->CCR[2] = 0;
    TIMER_A0->CCR[3] = 0;
    TIMER_A0->CCR[4] = 0;
    TIMER_A0->CTL = 0x0254;

}

void PrintLightsMenu(){
    char firstLine[SIZE] = "[1] Red";
    char secondLine[SIZE] = "[2] Green";
    char thirdLine[SIZE] = "[3] Blue";
    char fourthLine[SIZE] = "[*] Home";
    int i;

    //clear the screen
    commandWrite(1);
    delay_ms(10);

    //start the cursor on the first row
    commandWrite(0x80);
    //write the first string
    for(i = 0; i<strlen(firstLine); i++){
        dataWrite(firstLine[i]);
    }
    //move cursor to second row
    commandWrite(0xC0);
    //write the second string
    for(i = 0; i<strlen(secondLine); i++){
        dataWrite(secondLine[i]);
    }
    //move cursor to third row
    commandWrite(0x90);
    //write the third string
    for(i = 0; i<strlen(thirdLine); i++){
        dataWrite(thirdLine[i]);
    }
    //move cursor to fourth row
    commandWrite(0xD0);
    //write the fourth string
    for(i = 0; i<strlen(fourthLine); i++){
        dataWrite(fourthLine[i]);
    }
}

void PrintBrightnessMenu(void){
    char firstLine[SIZE] = "Use Keypad to";
    char secondLine[SIZE] = "Select LED";
    char thirdLine[SIZE] = "Brightness";
    char fourthLine[SIZE] = "[*] Back";
    int i;

    //clear the screen
    commandWrite(1);
    delay_ms(10);

    //start the cursor on the first row
    commandWrite(0x80);
    //write the first string
    for(i = 0; i<strlen(firstLine); i++){
        dataWrite(firstLine[i]);
    }
    //move cursor to second row
    commandWrite(0xC0);
    //write the second string
    for(i = 0; i<strlen(secondLine); i++){
        dataWrite(secondLine[i]);
    }
    //move cursor to third row
    commandWrite(0x90);
    //write the third string
    for(i = 0; i<strlen(thirdLine); i++){
        dataWrite(thirdLine[i]);
    }
    //move cursor to fourth row
    commandWrite(0xD0);
    //write the fourth string
    for(i = 0; i<strlen(fourthLine); i++){
        dataWrite(fourthLine[i]);
    }
}

void ChangeLEDBrightness(int i){
    double redPeriodTime, greenPeriodTime, bluePeriodTime;
    double keypadRead = Keypad_Read();
    int holdingCheck;

    //if a button is pressed:
    if(keypadRead){
        //if the button is 1-9
        if(keypadRead < 10){
            switch(i){
            case 2:
                redDutyCycle = (keypadRead/10);
                redPeriodTime = redDutyCycle*10000;
                TIMER_A0->CCR[3] = redPeriodTime;
                break;
            case 3:
                greenDutyCycle = (keypadRead/10);
                greenDutyCycle = (keypadRead/10);
                greenPeriodTime = greenDutyCycle*10000;
                TIMER_A0->CCR[4] = greenPeriodTime;
                break;
            case 4:
                blueDutyCycle = (keypadRead/10);
                blueDutyCycle = (keypadRead/10);
                bluePeriodTime = blueDutyCycle*10000;
                TIMER_A0->CCR[2] = bluePeriodTime;
                break;
            }
        }

        else if(keypadRead == 10){
            //check to see if the key is still pressed
            holdingCheck = holding();
            //pause the function while the key is held
            while(holdingCheck){
                //check again to see if the key is held
                holdingCheck = holding();
            }
            commandWrite(1);
            delay_ms(10);
            PrintLightsMenu();
            currentLightState = lightsMenu;
            firstEnter = TRUE;
        }

        //if the button in 0
        else if(keypadRead == 11){
            switch(i){
            case 2:
                redDutyCycle = 0;
                TIMER_A0->CCR[3] =redDutyCycle;
                break;
            case 3:
                greenDutyCycle = 0;
                TIMER_A0->CCR[4] =greenDutyCycle;
                break;
            case 4:
                blueDutyCycle = 0;
                TIMER_A0->CCR[2] = blueDutyCycle;
                break;
            }
        }

    }
}

/*-----------------------------------------------------------
* Function: holding
* Description: This function is used to detect when a key is
*                   being pressed and returns 0 if no key was pressed
*                   and 1 if a key was detected to be pressed.
* Inputs:
*              N/A
*
* Outputs:
*              0 or 1
*---------------------------------------------------------*/
int holding(){
    int col;

    //all row pins set to output
    P7->DIR |= 0x0F;
    //drive all row pins low
    P7->OUT &= ~0x0F;
    //wait for signals to settle
    delay_ms(10);
    //read all column pins
    col = P7->IN & 0x70;
    //drive all rows high
    P7->OUT |= 0x0F;
    //disable all row pins
    P7->DIR &= ~0x0F;
    //if all columns are high
    if(col == 0x70)
        //no key pressed
        return 0;
    //if a column is low
    else
        //key is pressed
        return 1;
}
