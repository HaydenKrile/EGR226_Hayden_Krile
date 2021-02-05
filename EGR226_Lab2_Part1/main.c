/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        02/04/2021
* Project:     ResistorLabPart2
* File:        main.c
* Description: This program determines the color-code of a 4-band resistor given a user
*                   inputted resistor value between 1-99M or color code to resistance value. The program is designed to
*                   detect invalid inputs and clear them out and ask for a proper one.
*                   This program can be repeated at the users request or ended at their desire.
***************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50

void prompt(void);
void getResistorColors(int);
void calcResistorColors(int);
void getColorBands(char *, char *, char *, char *);
void calcResistance(char, char, char, char);

int main(){

    int resistor, count, decision, repeat;
    char bandColorOne, bandColorTwo, bandColorThree, bandColorFour;

    //this while loop keeps the program continuing until the user tells it to stop
    while(1){

        //ask the user for the resistance
        prompt();

        printf("Would you like to convert a resistance to color code, or color code to resistance?\n");

        //error check the user's input
          do {
            printf("Enter 1 for resistance to color code\nEnter 2 for color code to resistance\n");
            count = scanf("%d", &decision);

           if (count == 0 || decision < 1 || decision > 2)
              {
              printf("\nINPUT ERROR!\n\n");
              while(getchar()!= '\n');
              }

           } while (count == 0 || decision < 0 || decision > 2);

        if(decision == 1){

                //error check the user's input
                  do {
                   printf("Enter a value between 1 and 99000000: \n");
                   count = scanf("%d", &resistor);

                   //if the input is less than 1, greater than 99000000, or a letter, the user is asked to enter again
                   if (count == 0 || resistor < 1 || resistor > 99000000)
                      {
                      printf("\nINPUT ERROR!\n\n");
                      while(getchar()!= '\n');
                      }

                   } while (count == 0 || resistor < 0 || resistor > 99000000);

                //takes the user input and converts the numerical value into the color bands and prints the results
                calcResistorColors(resistor);
                }

        else {

            getColorBands(&bandColorOne, &bandColorTwo, &bandColorThree, &bandColorFour);

            calcResistance(bandColorOne, bandColorTwo, bandColorThree, bandColorFour);
        }
        //ask the user if they would like to enter another resistance value
        printf("\nWould you like to input another value? Enter 0 to exit or any value to continue\n");
        //scan in the user input
        scanf("%d", &repeat);

        //if the user inputed 0, the program returns 0
        if (repeat == 0){
            return 0;
        }
    }
}

/*-----------------------------------------------------------
* Function: prompt
* Description: prints the resistor chart for the users convenience
*
* Inputs:
*              N/A
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void prompt(void) {
    //this is the prompt for the colors of the resistors and what they mean
    printf("--------------------Resistor Codes---------------------\n");
    printf("|Character|  Color | Band 1 & 2 |   Band 3  |  Band 4  |\n");
    printf("|    K    | Black  |      0     |*1         |+/- 1%%    |\n");
    printf("|    N    | Brown  |      1     |*10        |+/- 2%%    |\n");
    printf("|    R    |  Red   |      2     |*100       |          |\n");
    printf("|    O    | Orange |      3     |*1,000     |          |\n");
    printf("|    Y    | Yellow |      4     |*10,000    |          |\n");
    printf("|    G    | Green  |      5     |*100,000   |+/- 0.5%%  |\n");
    printf("|    B    |  Blue  |      6     |*1,000,000 |+/- 0.25%% |\n");
    printf("|    V    | Violet |      7     |*10,000,000|+/- 0.1%%  |\n");
    printf("|    E    |  Grey  |      8     |           |+/- 0.05%% |\n");
    printf("|    W    |  White |      9     |           |          | \n");
    printf("|    D    |  Gold  |            |           |+/- 5%%    |\n");
    printf("|    S    | Silver |            |           |+/- 10%%   |\n");
    printf("-------------------------------------------------------\n\n");
}

/*-----------------------------------------------------------
* Function: calcResistorColors
* Description: Takes in the users inputted resistance value and converts that value to
*               a color-code and prints it to the console
* Inputs:
*              int resistor: resistance value inputted by the user
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void calcResistorColors(int resistor){
    //these ints hold the numerical value of the colored bands
    int bandNumOne;
    int bandNumTwo;
    int bandNumThree = 0;

    //determines the third band by the number of times the input can be divided by 10
    while(resistor > 100){
        resistor = resistor / 10;
        bandNumThree++;
    }

    //determines the 2nd band by finding the modulus of 10
    bandNumTwo = resistor % 10;

    //determines the 1st band by the number of times 10 can be subtracted
    while(resistor > 9){
        resistor = resistor - 10;
        bandNumOne++;
    }

    printf("\nThe color bands of the resistor you inputed are: ");

    //these switch statements print out the color of the bands depending on what numerical values the bandNum ints hold
    switch(bandNumOne){
        case 1:
            printf("Brown-");
            break;
        case 2:
            printf("Red-");
            break;
        case 3:
            printf("Orange-");
            break;
        case 4:
            printf("Yellow-");
            break;
        case 5:
            printf("Green-");
            break;
        case 6:
            printf("Blue-");
            break;
        case 7:
            printf("Violet-");
            break;
        case 8:
            printf("Grey-");
            break;
        case 9:
            printf("White-");
            break;
    }

    switch(bandNumTwo){
        case 0:
            printf("Black-");
            break;
        case 1:
            printf("Brown-");
            break;
        case 2:
            printf("Red-");
            break;
        case 3:
            printf("Orange-");
            break;
        case 4:
            printf("Yellow-");
            break;
        case 5:
            printf("Green-");
            break;
        case 6:
            printf("Blue-");
            break;
        case 7:
            printf("Violet-");
            break;
        case 8:
            printf("Grey-");
            break;
        case 9:
            printf("White-");
            break;
    }

    switch(bandNumThree){
        case 0:
            printf("Black\n");
            break;
        case 1:
            printf("Brown\n");
            break;
        case 2:
            printf("Red\n");
            break;
        case 3:
            printf("Orange\n");
            break;
        case 4:
            printf("Yellow\n");
            break;
        case 5:
            printf("Green\n");
            break;
        case 6:
            printf("Blue\n");
            break;
        case 7:
            printf("Violet\n");
            break;
        case 8:
            printf("Grey\n");
            break;
        case 9:
            printf("White\n");
            break;
        }
    }

    /*-----------------------------------------------------------
* Function: getColorBands
* Description: asks the user for the resistor band colors and sends the valid inputs
                back to the variables in main through pointers
* Inputs:
*              char *one: pointer to first band variable
*              char *two: pointer to second band variable
*              char *three: pointer to third band variable
*              char *four: pointer to fourth band variable
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void getColorBands(char *one, char *two, char *three, char *four){

    char firstTwoBand[SIZE] = "KNROYGBVEW";
    char thirdBand[SIZE] = "KNROYGBVDS";
    char fourthBand[SIZE] = "KNGBVEDS";

    //error check the user's input
    do {
        printf("Enter the first band color\n");
        fflush(stdin);
        scanf("%c", one);

        if (!strchr(firstTwoBand, *one))
          {
              printf("\nINPUT ERROR!\n\n");
              while(getchar()!= '\n');
          }
    } while (!strchr(firstTwoBand, *one));

    //error check the user's input
    do {
        printf("Enter the second band color\n");
        fflush(stdin);
        scanf("%c", two);

        if (!strchr(firstTwoBand, *two))
          {
              printf("\nINPUT ERROR!\n\n");
              while(getchar()!= '\n');
          }
    } while (!strchr(firstTwoBand, *two));

    //error check the user's input
    do {
        printf("Enter the third band color\n");
        fflush(stdin);
        scanf("%c", three);

        if (!strchr(thirdBand, *three))
          {
              printf("\nINPUT ERROR!\n\n");
              while(getchar()!= '\n');
          }
    } while (!strchr(thirdBand, *three));\

    //error check the user's input
    do {
        printf("Enter the fourth band color\n");
        fflush(stdin);
        scanf("%c", four);

        if (!strchr(fourthBand, *four))
          {
              printf("\nINPUT ERROR!\n\n");
              while(getchar()!= '\n');
          }
    } while (!strchr(fourthBand, *four));
}

/*-----------------------------------------------------------
* Function: calcResistance
* Description: takes in the users four bands as chars and converts those into resistor values
                and print the total resistance value and tolerance to the console
* Inputs:
*              char colorOne: color of the first band
*              char colorTwo: color of the second band
*              char colorThree: color of the third band
*              char colorFour: color of the fourth band
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void calcResistance(char colorOne, char colorTwo, char colorThree, char ColorFour){

    int totalResistance;

    switch(colorOne){
        case 'K':
            totalResistance = 0;
            break;
        case 'N':
            totalResistance = 10;
            break;
        case 'R':
            totalResistance = 20;
            break;
        case 'O':
            totalResistance = 30;
            break;
        case 'Y':
            totalResistance = 40;
            break;
        case 'G':
            totalResistance = 50;
            break;
        case 'B':
            totalResistance = 60;
            break;
        case 'V':
            totalResistance = 70;
            break;
        case 'E':
            totalResistance = 80;
            break;
        case 'W':
            totalResistance = 90;
            break;
    }

    switch(colorTwo){
        case 'K':
            break;
        case 'N':
            totalResistance = totalResistance + 1;
            break;
        case 'R':
            totalResistance = totalResistance + 2;
            break;
        case 'O':
            totalResistance = totalResistance + 3;
            break;
        case 'Y':
            totalResistance = totalResistance + 4;
            break;
        case 'G':
            totalResistance = totalResistance + 5;
            break;
        case 'B':
            totalResistance = totalResistance + 6;
            break;
        case 'V':
            totalResistance = totalResistance + 7;
            break;
        case 'E':
            totalResistance = totalResistance + 8;
            break;
        case 'W':
            totalResistance = totalResistance + 9;
            break;
    }

    switch(colorThree){
        case 'K':
            break;
        case 'N':
            totalResistance = totalResistance * 10;
            break;
        case 'R':
            totalResistance = totalResistance * 100;
            break;
        case 'O':
            totalResistance = totalResistance * 1000;
            break;
        case 'Y':
            totalResistance = totalResistance * 10000;
            break;
        case 'G':
            totalResistance = totalResistance * 100000;
            break;
        case 'B':
            totalResistance = totalResistance * 1000000;
            break;
        case 'V':
            totalResistance = totalResistance * 10000000;
            break;
    }

    printf("Your resistor is %d ", totalResistance);

    switch(ColorFour){
        case 'K':
            printf("+/- 1%% Ohms\n");
            break;
        case 'N':
            printf("+/- 2%% Ohms\n");
            break;
        case 'G':
            printf("+/- 0.5%% Ohms\n");
            break;
        case 'B':
            printf("+/- 0.25%% Ohms\n");
            break;
        case 'V':
            printf("+/- 0.1%% Ohms\n");
            break;
        case 'E':
            printf("+/- 0.05%% Ohms\n");
            break;
        case 'D':
            printf("+/- 5%% Ohms\n");
            break;
        case 'S':
            printf("+/- 10%% Ohms\n");
            break;
    }
}
