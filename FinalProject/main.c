#include "msp.h"
#include "LCD_lib.h"
#include "Keypad_lib.h"
#include "PrintLCD.h"
#include "PinSet.h"
#include <string.h>
#define SIZE 25
#define TRUE 1
#define FALSE 0

void MainMenuSelect(int);
void DoorMenuSelect(int);
void LightsMenuSelect(int);
void MotorMenuSelect(double);
int holding(void);
void LEDSelect(int);
void ChangeLEDBrightness(int);
void HomeDoorbell(void);
void DoorbellNote(char);

enum menuOptions{
    mainMenu,
    doorMenu,
    motorMenu,
    lightsMenu
};
enum menuOptions currentMenu = mainMenu;

enum lightsOptions{
    lightsMainMenu,
    redLight,
    greenLight,
    blueLight
};
enum lightsOptions currentLightState = lightsMainMenu;
int firstEnter = TRUE, firstEnterLED = TRUE;
volatile double motorDutyCycle = 0;
volatile double redDutyCycle = 0, greenDutyCycle = 0, blueDutyCycle = 0;
volatile double redPeriodTime, greenPeriodTime, bluePeriodTime;

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	//disable irq for the setup phase
	__disable_irq();
    //initialize Systick and the LCD
    SysTick_Init();
    LCD_Init();
    Keypad_Init();
    MasterPinSet();

    //start at the home menu
	HomeMenu();

    double keypadCollect;

    //enable interrupts
	__enable_irq();
	while(1){
	    //if on the main menu, wait for an input from the user
	    if(currentMenu == mainMenu){
            //read the keypad
            keypadCollect = Keypad_Read();
            //determine which state to be in based on the keypad input
            MainMenuSelect(keypadCollect);
	    }

	    switch(currentMenu){
	    case doorMenu:
            if(firstEnter){
                PrintDoorMenu();
                firstEnter = FALSE;
            }
            //read the keypad
            keypadCollect = Keypad_Read();
            //determine which state to be in based on the keypad input
            DoorMenuSelect(keypadCollect);
	        break;
	    case motorMenu:
	        if(firstEnter){
                PrintMotorMenu();
                firstEnter = FALSE;
	        }
            //read the keypad
            keypadCollect = Keypad_Read();
            //determine which state to be in based on the keypad input
            MotorMenuSelect(keypadCollect);
	        break;
	    case lightsMenu:
            if(firstEnter){
                PrintLightsMenu();
                firstEnter = FALSE;
            }
            switch(currentLightState){
            case lightsMainMenu:
                keypadCollect = Keypad_Read();
                LEDSelect(keypadCollect);
                break;
            case redLight:
                if(firstEnterLED){
                    PrintBrightnessMenu();
                    firstEnterLED = FALSE;
                }
                ChangeLEDBrightness(2);
                break;
            case greenLight:
                if(firstEnterLED){
                    PrintBrightnessMenu();
                    firstEnterLED = FALSE;
                }
                ChangeLEDBrightness(3);
                break;
            case blueLight:
                if(firstEnterLED){
                    PrintBrightnessMenu();
                    firstEnterLED = FALSE;
                }
                ChangeLEDBrightness(4);
                break;
            }
	        break;
	    default:
	        ;
	    }
	}
}

void MainMenuSelect(int i){
    int holdingCheck;
    switch(i){
    case 1:
        //check to see if the key is still pressed
        holdingCheck = holding();
        //pause the function while the key is held
        while(holdingCheck){
            //check again to see if the key is held
            holdingCheck = holding();
        }
        currentMenu = doorMenu;
        break;
    case 2:
        //check to see if the key is still pressed
        holdingCheck = holding();
        //pause the function while the key is held
        while(holdingCheck){
            //check again to see if the key is held
            holdingCheck = holding();
        }
        currentMenu = motorMenu;
        break;
    case 3:
        //check to see if the key is still pressed
        holdingCheck = holding();
        //pause the function while the key is held
        while(holdingCheck){
            //check again to see if the key is held
            holdingCheck = holding();
        }
        currentMenu = lightsMenu;
        break;
    default:
        ;
    }
}

void DoorMenuSelect(int i){
    switch(i){
    case 1:
        TIMER_A2->CCR[1] = 2250;
        P2->OUT &= ~BIT0;
        P2->OUT |= BIT1;
        break;
    case 2:
        TIMER_A2->CCR[1] = 250;
        P2->OUT |= BIT0;
        P2->OUT &= ~BIT1;
        break;
    case 10:
        commandWrite(1);
        delay_ms(10);
        HomeMenu();
        firstEnter = TRUE;
        currentMenu = mainMenu;
        break;
    }
}

void MotorMenuSelect(double i){
    double periodTime;
    if(i){
        if(i < 10){
            motorDutyCycle = (i/10);
        }
        else if(i == 10){
            commandWrite(1);
            delay_ms(10);
            HomeMenu();
            firstEnter = TRUE;
            currentMenu = mainMenu;
        }
        else if(i == 11){
            motorDutyCycle = 0;
        }
        periodTime = (motorDutyCycle * 40000);
        TIMER_A2->CCR[2] = periodTime;
    }
}

void LightsMenuSelect(int i){

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

void LEDSelect(int i){
    int holdingCheck;
    switch(i){
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
    case 10:
        commandWrite(1);
        delay_ms(10);
        HomeMenu();
        firstEnterLED = TRUE;
        firstEnter = TRUE;
        currentMenu = mainMenu;
        break;
    }
}

void ChangeLEDBrightness(int i){
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
            currentLightState = lightsMainMenu;
            firstEnterLED = TRUE;
        }

        //if the button in 0
        else if(keypadRead == 11){
            switch(i){
            case 2:
                redPeriodTime = 0;
                TIMER_A0->CCR[3] = redPeriodTime;
                break;
            case 3:
                greenPeriodTime = 0;
                TIMER_A0->CCR[4] = greenPeriodTime;
                break;
            case 4:
                bluePeriodTime = 0;
                TIMER_A0->CCR[2] = bluePeriodTime;
                break;
            }
        }

    }
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
* Function: PORT3_IRQHandler
* Description: This function handles the interrupts generated
*                   from port 2 by the LEDne-stop button
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PORT2_IRQHandler(void){
    static int isOn = TRUE;
    delay_ms(75);
    //if there are LED's on
    if(isOn){
        //turn all LEDs off
        TIMER_A0->CCR[2] = 0;
        TIMER_A0->CCR[3] = 0;
        TIMER_A0->CCR[4] = 0;
        isOn = FALSE;
    }

    //if the LEDs are off
    else{
        //turn them all back on wth their original brightness
        TIMER_A0->CCR[3] = redPeriodTime;
        TIMER_A0->CCR[4] = greenPeriodTime;
        TIMER_A0->CCR[2] = bluePeriodTime;
        isOn = TRUE;
    }
    delay_ms(75);
    //reset flag
    P2->IFG = 0;
}

/*-----------------------------------------------------------
* Function: PORT3_IRQHandler
* Description: This function handles the interrupts generated
*                   from port 3 by the motor e-stop button
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PORT3_IRQHandler(void){
    //turn off motor
    TIMER_A2->CCR[2] = 0;
    //clear flag
    P3->IFG = 0;
}

/*-----------------------------------------------------------
* Function: PORT5_IRQHandler
* Description: This function handles the interrupts generated
*                   from port 5 by the doorbell
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PORT5_IRQHandler(void){

    //show that someone is at the door
    PrintDoorbell();
    //play doorbell tune
    HomeDoorbell();
    //print door menu
    PrintDoorMenu();
    //reset lights menu just in case
    currentLightState = lightsMainMenu;
    //set the mode to the door menu
    currentMenu = doorMenu;
    //reset flag
    P5->IFG = 0;
}
