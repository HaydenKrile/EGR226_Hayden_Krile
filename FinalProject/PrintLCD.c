#include "msp.h"
#include "PrintLCD.h"
#include "LCD_lib.h"
#include <string.h>
#define SIZE 20

/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        04/06/2021
* Project:     FinalProject
* File:        PrintLCD.c
* Description: This library contains the commands used to print the
*                   menu options to the LCD screen
***************************************************************************************/

/*-----------------------------------------------------------
* Function: HomeMenu
* Description: This function prints out the home menu to the LCD screen
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
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

/*-----------------------------------------------------------
* Function: PrintDoorMenu
* Description: This function prints out the door menu to the LCD screen
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PrintDoorMenu(){
    char firstLine[SIZE] = "[1] Open";
    char secondLine[SIZE] = "[2] Close";
    char thirdLine[SIZE] = "[3] Doorbell";
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

/*-----------------------------------------------------------
* Function: PrintDoorbellMenu
* Description: This function prints out the doorbell menu to the LCD screen
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PrintDoorbellMenu(){
    char firstLine[SIZE] = "[1] Ding Dong";
    char secondLine[SIZE] = "[2] Buzzer";
    char thirdLine[SIZE] = "[3] My Doorbell";
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

/*-----------------------------------------------------------
* Function: PrintMotorMenu
* Description: This function prints out the motor menu to the LCD screen
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
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

/*-----------------------------------------------------------
* Function: PrintLightsMenu
* Description: This function prints out the lights menu to the LCD screen
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
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

/*-----------------------------------------------------------
* Function: PrintBrightnessMenu
* Description: This function prints out the LED brightness menu to the LCD screen
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
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

/*-----------------------------------------------------------
* Function: PrintDoorbell
* Description: This function prints out "Doorbell rang!" when the touch sensor is pressed
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PrintDoorbell(void){
    char firstLine[SIZE] = "Doorbell rang!";
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
}

/*-----------------------------------------------------------
* Function: PrintDoorIsOpen
* Description: This function prints out "Door's open! Come on in!"
                when the door is either open when the doorbell is rung
                or when the door is opened after the doorbell is rung
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PrintDoorIsOpen(){
        char firstLine[SIZE] = "Door is open!";
        char secondLine[SIZE] = "Come on in!";
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
}

/*-----------------------------------------------------------
* Function: PrintDoorbell
* Description: This function prints out "No one's here! Go Away!"
                when access is denied after the doorbell is rung
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void PrintDoorIsClosed(){
    char firstLine[SIZE] = "No one's here!";
    char secondLine[SIZE] = "Go away!";
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
}
