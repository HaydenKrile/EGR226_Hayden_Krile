#include "msp.h"
#include "LCD_lib.h"
#include "Keypad_lib.h"
#include "PrintLCD.h"
#include "PinSet.h"
#include "DoorbellTones.h"
#include "Menu.h"
#include <string.h>
#define SIZE 25
#define TRUE 1
#define FALSE 0

void DoorbellSelect (int);
void LEDSelect(int);
void ChangeLEDBrightness(int);
void AdjustLCDLED(void);

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

enum doorOptions{
    doorMainMenu,
    doorbellMenu
};
enum doorOptions currentDoorState = doorMainMenu;

enum doorbellOptions{
    dingDong,
    buzzer,
    homeDoorbell
};
enum doorbellOptions currentDoorbell = dingDong;

int firstEnter = TRUE, firstEnterLED = TRUE, firstEnterDoorbell = TRUE;
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
    //initialize all pins, LCD, and systick
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
	    AdjustLCDLED();
	    //if on the main menu, wait for an input from the user
	    if(currentMenu == mainMenu){
            //read the keypad
            keypadCollect = Keypad_Read();
            //determine which state to be in based on the keypad input
            MainMenuSelect(keypadCollect);
	    }

	    switch(currentMenu){
	    case doorMenu:
	        //read the keypad
	        keypadCollect = Keypad_Read();
            if(firstEnter){
                PrintDoorMenu();
                firstEnter = FALSE;
            }

            switch(currentDoorState){
            case doorMainMenu:
                DoorMenuSelect(keypadCollect);
                break;
            case doorbellMenu:
                if(firstEnterDoorbell){
                    PrintDoorbellMenu();
                    firstEnterDoorbell = FALSE;
                }
                DoorbellSelect(keypadCollect);
                break;
            }

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



void DoorbellSelect(int i){

    int holdingCheck;
    switch (i){
    case 1:
        //check to see if the key is still pressed
        holdingCheck = holding();
        //pause the function while the key is held
        while(holdingCheck){
            //check again to see if the key is held
            holdingCheck = holding();
        }
        currentDoorbell = dingDong;
        DingDong();
        break;
    case 2:
        //check to see if the key is still pressed
        holdingCheck = holding();
        //pause the function while the key is held
        while(holdingCheck){
            //check again to see if the key is held
            holdingCheck = holding();
        }
        currentDoorbell = buzzer;
        Buzzer();
        break;
    case 3:
        //check to see if the key is still pressed
        holdingCheck = holding();
        //pause the function while the key is held
        while(holdingCheck){
            //check again to see if the key is held
            holdingCheck = holding();
        }
        currentDoorbell = homeDoorbell;
        HomeDoorbell();
        break;
    case 10:
        commandWrite(1);
        delay_ms(10);
        HomeMenu();
        firstEnterDoorbell = TRUE;
        firstEnter = TRUE;
        //currentMenu = mainMenu;
        currentDoorState = doorMainMenu;
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

        //if the button in #
        else if(keypadRead == 12){
            switch(i){
            case 2:
                redPeriodTime = 10000;
                TIMER_A0->CCR[3] = 10000;
                break;
            case 3:
                greenPeriodTime = 10000;
                TIMER_A0->CCR[4] = 10000;
                break;
            case 4:
                bluePeriodTime = 10000;
                TIMER_A0->CCR[2] = 10000;
                break;
            }
        }

    }
}



void AdjustLCDLED(void){
    float result, voltage;
    //start conversion
    ADC14->CTL0 |= 1;
    //wait until conversion is complete
    while(!ADC14->IFGR0);
    //store value in variable result
    result = ADC14->MEM[5];
    voltage = result * 0.6101;
    TIMER_A0->CCR[1] = voltage;
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
        //turn them all back on with their original brightness
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
    switch(currentDoorbell){
    case dingDong:
        DingDong();
        break;
    case buzzer:
        Buzzer();
        break;
    case homeDoorbell:
        HomeDoorbell();
        break;
    }
    //print door menu
    PrintDoorMenu();
    //reset lights menu just in case
    currentLightState = lightsMainMenu;
    //set the mode to the door menu
    currentMenu = doorMenu;
    currentDoorState = doorMainMenu;
    firstEnterLED = TRUE;
    firstEnterDoorbell = TRUE;
    //reset flag
    P5->IFG = 0;
}
