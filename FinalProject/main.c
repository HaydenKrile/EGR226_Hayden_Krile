#include "msp.h"
#include "LCD_lib.h"
#include "Keypad_lib.h"
#include "PrintLCD.h"
#include "PinSet.h"
#include "DoorbellTones.h"
#include <string.h>
#define SIZE 25
#define TRUE 1
#define FALSE 0

void DoorbellSelect (int);
void LEDSelect(int);
void ChangeLEDBrightness(int);
void AdjustLCDLED(void);
void MainMenuSelect(int);
void DoorMenuSelect(int);
void LightsMenuSelect(int);
void MotorMenuSelect(double);
int holding(void);

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

int firstEnter = TRUE, firstEnterLED = TRUE, firstEnterDoorbell = TRUE, doorbellRing = FALSE, doorOpen = FALSE;
volatile double motorDutyCycle = 0;
volatile double redDutyCycle = 0, greenDutyCycle = 0, blueDutyCycle = 0;
volatile double redPeriodTime, greenPeriodTime, bluePeriodTime;

/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        04/09/2021
* Project:     FinalProject
* File:        main.c
* Description: This program connects to the MSP432 and uses
***************************************************************************************/
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
	    //adjust the LCD based on the 10k Pot
	    AdjustLCDLED();
        //read the keypad
        keypadCollect = Keypad_Read();

        //check which menu should be active
	    switch(currentMenu){
	    //if on the main menu
	    case mainMenu:
            //determine which state to be in based on the keypad input
            MainMenuSelect(keypadCollect);
            break;
        //if on the door menu
	    case doorMenu:
	        //if this is the programs first time entering
            if(firstEnter){
                //print the door menu options
                PrintDoorMenu();
                //set the first enter to false
                firstEnter = FALSE;
            }
            //check the current door state
            switch(currentDoorState){
            //if on the door main menu
            case doorMainMenu:
                //wait for the users input
                DoorMenuSelect(keypadCollect);
                break;
            //if on the doorbell menu
            case doorbellMenu:
                //if this is the first time entering the doorbell menu
                if(firstEnterDoorbell){
                    //print the doorbell menu
                    PrintDoorbellMenu();
                    //set the first enter to false
                    firstEnterDoorbell = FALSE;
                }
                //select the doorbell tone to play when pressing the touch sensor
                DoorbellSelect(keypadCollect);
                break;
            }
	        break;

	    //if on the motor menu
	    case motorMenu:
            //if this is the programs first time entering
            if(firstEnter){
                //print the door menu options
                PrintDoorMenu();
                //set the first enter to false
                firstEnter = FALSE;
            }
            //determine the speed of the motor based on the user input
            MotorMenuSelect(keypadCollect);
	        break;

	    //if on the lights menu
	    case lightsMenu:
            //if this is the programs first time entering
            if(firstEnter){
                //print the door menu options
                PrintDoorMenu();
                //set the first enter to false
                firstEnter = FALSE;
            }
            //determine the lights menu to be on
            switch(currentLightState){
            //if on the lights main menu
            case lightsMainMenu:
                //wait for the user to select an LED to control
                LEDSelect(keypadCollect);
                break;
                //if the red light was selected
            case redLight:
                //if this is the first time entering the LED Menu
                if(firstEnterLED){
                    //print the brightness menu
                    PrintBrightnessMenu();
                    //set the firstEnterLED to false
                    firstEnterLED = FALSE;
                }
                //change the brightness of the red LED
                ChangeLEDBrightness(2);
                break;
            case greenLight:
                //if this is the first time entering the LED Menu
                if(firstEnterLED){
                    //print the brightness menu
                    PrintBrightnessMenu();
                    //set the firstEnterLED to false
                    firstEnterLED = FALSE;
                }
                //change the brightness of the green LED
                ChangeLEDBrightness(3);
                break;
            case blueLight:
                //if this is the first time entering the LED Menu
                if(firstEnterLED){
                    //print the brightness menu
                    PrintBrightnessMenu();
                    //set the firstEnterLED to false
                    firstEnterLED = FALSE;
                }
                //change the brightness of the blue LED
                ChangeLEDBrightness(4);
                break;
            }
	        break;
	    default:
	        ;
	    }
	}
}

/*-----------------------------------------------------------
* Function: DoorbellSelect
* Description: This function accepts as an input, and integer that
*               was sent from the keypad to determine which doorbell
*               tone to play when the touch sensor is activated
*
* Inputs:
*              int i
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void DoorbellSelect(int i){
    int holdingCheck;
    switch (i){
    //if the selected tone was "ding dong"
    case 1:
        //check to see if the key is still pressed
        holdingCheck = holding();
        //pause the function while the key is held
        while(holdingCheck){
            //check again to see if the key is held
            holdingCheck = holding();
        }
        //set the doorbell state to dingDong
        currentDoorbell = dingDong;
        //play a sample of the tone
        DingDong();
        break;
    //if the selected time was "buzzer"
    case 2:
        //check to see if the key is still pressed
        holdingCheck = holding();
        //pause the function while the key is held
        while(holdingCheck){
            //check again to see if the key is held
            holdingCheck = holding();
        }
        //set the doorbell state to "buzzer"
        currentDoorbell = buzzer;
        //play a sample of the tone
        Buzzer();
        break;
    //if the selected tone was "My Doorbell"
    case 3:
        //check to see if the key is still pressed
        holdingCheck = holding();
        //pause the function while the key is held
        while(holdingCheck){
            //check again to see if the key is held
            holdingCheck = holding();
        }
        //set the doorbell state to homeDoorbell
        currentDoorbell = homeDoorbell;
        //play a sample of the tone
        HomeDoorbell();
        break;
    //if (*) was pressed
    case 10:
        //clear the screen
        commandWrite(1);
        delay_ms(10);
        //reset all first enter variables
        firstEnterDoorbell = TRUE;
        firstEnter = TRUE;
        //set the currentDoorState back to doorMainMenu
        currentDoorState = doorMainMenu;
        break;
    }
}

/*-----------------------------------------------------------
* Function: ChangeLEDBrightness
* Description: This function accepts as an input, and integer that
*               was sent to determine the PWM duty cycle to send
*               to the selected LED to change its brightness
*
* Inputs:
*              int i
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void ChangeLEDBrightness(int i){
    double keypadRead = Keypad_Read();
    int holdingCheck;

    //if a button is pressed:
    if(keypadRead){
        //if the button is 1-9
        if(keypadRead < 10){
            //determine which LED to modify
            switch(i){
            //if red LED
            case 2:
                //determine duty cycle
                redDutyCycle = (keypadRead/10);
                //determine period time
                redPeriodTime = redDutyCycle*10000;

                TIMER_A0->CCR[3] = redPeriodTime;
                break;
            //if green LED
            case 3:
                //determine duty cycle
                greenDutyCycle = (keypadRead/10);
                //determine period time
                greenPeriodTime = greenDutyCycle*10000;
                //set brightness of LED
                TIMER_A0->CCR[4] = greenPeriodTime;
                break;
            //if blue LED
            case 4:
                //determine duty cycle
                blueDutyCycle = (keypadRead/10);
                //determine period time
                bluePeriodTime = blueDutyCycle*10000;
                //set brightness of LED
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
            //clear screen
            commandWrite(1);
            delay_ms(10);
            //print lights menu
            PrintLightsMenu();
            //set current state to lights main menu
            currentLightState = lightsMainMenu;
            //reset firent enter variable
            firstEnterLED = TRUE;
        }

        //if the button in 0
        else if(keypadRead == 11){
            //determine which LED to modify
            switch(i){
            //if red LED
            case 2:
                //turn off red LED
                redPeriodTime = 0;
                TIMER_A0->CCR[3] = redPeriodTime;
                break;
            //if green LED
            case 3:
                //turn off green LED
                greenPeriodTime = 0;
                TIMER_A0->CCR[4] = greenPeriodTime;
                break;
            //if blue LED
            case 4:
                //turn off blue LED
                bluePeriodTime = 0;
                TIMER_A0->CCR[2] = bluePeriodTime;
                break;
            }
        }

        //if the button is #
        else if(keypadRead == 12){
            //determine which LED to modify
            switch(i){
            //if red LED
            case 2:
                //turn red LED on at 100%
                redPeriodTime = 10000;
                TIMER_A0->CCR[3] = 10000;
                break;
            //if green LED
            case 3:
                //turn green LED on at 100%
                greenPeriodTime = 10000;
                TIMER_A0->CCR[4] = 10000;
                break;
            //if blue LED
            case 4:
                //turn blue LED on at 100%
                bluePeriodTime = 10000;
                TIMER_A0->CCR[2] = 10000;
                break;
            }
        }

    }
}
/*-----------------------------------------------------------
* Function: MainMenuSelect
* Description: This function takes in, as an integer, a value
*               generated by the keypad in order to determine which
*               menu to enter while on the main menu
*
* Inputs:
*              int i
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
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

/*-----------------------------------------------------------
* Function: DoorMenuSelect
* Description: This function accepts as an input, and integer that
*               was collected from the keypad to determine how to interact with the door.
*               if 1 is pressed, the door will open and the green LED will turn on.
*               if 2 is pressed, the door will close and the red LED will turn on.
*               if three is pressed, the doorbell menu is opened up.
*               if 10 is pressed, the menu is closed and the program
*               returns to the main menu.
*
* Inputs:
*              int i
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void DoorMenuSelect(int i){
    int holdingCheck;
    switch(i){
    //open the door
    case 1:
        //set the servo to the open position
        TIMER_A2->CCR[1] = 2250;
        //turn off the red LED
        P2->OUT &= ~BIT0;
        //turn on the green LED
        P2->OUT |= BIT1;
        //set the doorOpen variable to true
        doorOpen = TRUE;
        //if the doorbell was rung
        if(doorbellRing){
            //print that the door is open
            PrintDoorIsOpen();
            //delay to allow the user to read what is on the screen
            delay_ms(2000);
            //re-print the door menu
            PrintDoorMenu();
            //the person is no longer at the door
            doorbellRing = FALSE;
        }
        break;
    //close the door
    case 2:
        //set the servo to the open position
        TIMER_A2->CCR[1] = 250;
        //turn off the green LED
        P2->OUT |= BIT0;
        //turn on the red LED
        P2->OUT &= ~BIT1;
        //the door is in the closed position
        doorOpen = FALSE;
        //if the doorbell was rung
        if(doorbellRing){
            //tell the person at the door to go away
            PrintDoorIsClosed();
            //wait two seconds to let the user read the screen
            delay_ms(2000);
            //re-print the door menu
            PrintDoorMenu();
            //no one is at the door anymore
            doorbellRing = FALSE;
        }
        break;
    //doorbell menu was selected
    case 3:
        currentDoorState = doorbellMenu;
        //check to see if the key is still pressed
        holdingCheck = holding();
        //pause the function while the key is held
        while(holdingCheck){
            //check again to see if the key is held
            holdingCheck = holding();
        }
        break;
    //(*) was pressed
    case 10:
        //clear the screen
        commandWrite(1);
        delay_ms(10);
        //print the main menu
        HomeMenu();
        //reset the first enter variable
        firstEnter = TRUE;
        //the current menu is set back to mainMenu
        currentMenu = mainMenu;
        break;
    }

    //if the doorbell was rung while the door was already open
    if(doorbellRing & doorOpen){
        //tell the person at the door to come in
        PrintDoorIsOpen();
        //wait two seconds to let the user read the screen
        delay_ms(2000);
        //re-print the door menu
        PrintDoorMenu();
        //no one is at the door anymore
        doorbellRing = FALSE;
    }
}

/*-----------------------------------------------------------
* Function: LEDSelect
* Description: This function accepts as an input, and integer that
*               was collected from the keypad to determine which LED
*               state to set the currentLightState to
*
* Inputs:
*              int i
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void MotorMenuSelect(double i){
    double periodTime;
    //if the keypad was pressed
    if(i){
        //if the value was 1-9
        if(i < 10){
            motorDutyCycle = (i/10);
        }
        //if the key was (*)
        else if(i == 10){
            //clear screen
            commandWrite(1);
            delay_ms(10);
            //print home menu
            HomeMenu();
            //reset firEnter variable
            firstEnter = TRUE;
            //current menu is now main menu
            currentMenu = mainMenu;
        }
        //if the key was (0)
        else if(i == 11){
            //set the duty cycle to zero
            motorDutyCycle = 0;
        }
        //set the period time of the motor equal to duty cycle times 40000
        periodTime = (motorDutyCycle * 40000);
        //set the PWM signal
        TIMER_A2->CCR[2] = periodTime;
    }
}

/*-----------------------------------------------------------
* Function: LEDSelect
* Description: This function accepts as an input, and integer that
*               was collected from the keypad to determine which LED
*               state to set the currentLightState to
*
* Inputs:
*              int i
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
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

/*-----------------------------------------------------------
* Function: AdjustLCDLED
* Description: This function checks the voltage recorded from the 10K
*               pot and converts this reading into a PWM signal that controls the
*               brightness of the LCD screen
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void AdjustLCDLED(void){
    float result, voltage;
    //start conversion
    ADC14->CTL0 |= 1;
    //wait until conversion is complete
    while(!ADC14->IFGR0);
    //store value in variable result
    result = ADC14->MEM[5];
    //converts the value so its between 0 - 10,000
    voltage = result * 0.6101;
    //sets this value as a PWM signal for the LCD LED
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
    doorbellRing = TRUE;
    //reset flag
    P5->IFG = 0;
}
