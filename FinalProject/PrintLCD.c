#include "msp.h"
#include "PrintLCD.h"
#include "LCD_lib.h"
#include <string.h>
#define SIZE 20
/*
 * PrintLCD.c
 *
 *  Created on: Apr 6, 2021
 *      Author: Hayden
 */

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

void PrintDoorMenu(){
    char firstLine[SIZE] = "  Open Door?";
    char secondLine[SIZE] = "[1] Open";
    char thirdLine[SIZE] = "[2] Close";
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
