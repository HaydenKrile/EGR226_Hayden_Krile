#include "msp.h"
#include "Menu.h"
#include "LCD_lib.h"
#include "PrintLCD.h"
#define TRUE 1
#define FALSE 0

/*
 * Menu.c
 *
 *  Created on: Apr 8, 2021
 *      Author: Hayden
 */
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
    int holdingCheck;
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
