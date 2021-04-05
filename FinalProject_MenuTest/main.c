#include "msp.h"
#include "LCD_lib.h"
#include "Keypad_lib.h"
#include <string.h>
#define SIZE 25
#define TRUE 1
#define FALSE 0

void HomeMenu(void);
void MainMenuSelect(int);
void DoorMenuSelect(int);
void MotorMenuSelect(int);
void PrintDoorMenu(void);
void PrintMotorMenu(void);
void PrintLightsMenu(void);

enum menuOptions{
    mainMenu,
    doorMenu,
    motorMenu,
    lightsMenu
};
enum menuOptions currentMenu = mainMenu;
int firstEnter = TRUE;

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	int keypadCollect;

    //initialize Systick and the LCD
    SysTick_Init();
    LCD_Init();
    Keypad_Init();

    //start at the home menu
	HomeMenu();

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
	        break;
	    default:
	        ;
	    }
	}
}

void HomeMenu(){
        char firstLine[SIZE] = "Select a Menu:";
        char secondLine[SIZE] = "[1] Door Menu";
        char thirdLine[SIZE] = "[2] Motor Menu";
        char fourthLine[SIZE] = "[3] Lights Menu";
        int i;

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

void MainMenuSelect(int i){
    switch(i){
    case 1:
        currentMenu = doorMenu;
        break;
    case 2:
        currentMenu = motorMenu;
        break;
    case 3:
        currentMenu = lightsMenu;
        break;
    default:
        ;
    }
}

void DoorMenuSelect(int i){
    switch(i){
    case 1:
        //TODO
        break;
    case 2:
        //TODO
        break;
    case 10:
        commandWrite(1);
        delay_ms(10);
        HomeMenu();
        firstEnter = TRUE;
        currentMenu = mainMenu;
    }
}

void MotorMenuSelect(int i){
    if(i < 10)
        ;//TODO
    if(i == 10){
        commandWrite(1);
        delay_ms(10);
        HomeMenu();
        firstEnter = TRUE;
        currentMenu = mainMenu;
    }
    if(i == 11)
        ;//TODO
}

void PrintDoorMenu(){
    char firstLine[SIZE] = "  Door Menu";
    char secondLine[SIZE] = "[1] Open Door";
    char thirdLine[SIZE] = "[2] Close Door";
    char fourthLine[SIZE] = "[*] Home";
    int i;

    //clear the screen
    commandWrite(1);
    delay_micro(150);

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

void PrintMotorMenu(){
    char firstLine[SIZE] = "  Use Keypad to";
    char secondLine[SIZE] = "Select Motor";
    char thirdLine[SIZE] = "Speed";
    char fourthLine[SIZE] = "[*] Home";
    int i;

    //clear the screen
    commandWrite(1);
    delay_micro(150);

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

void PrintLightsMenu(){
    char firstLine[SIZE] = "Select Light";
    char secondLine[SIZE] = "[1] Red";
    char thirdLine[SIZE] = "[2] Green";
    char fourthLine[SIZE] = "[3] Blue";
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
