/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        01/28/2021
* Project:     ResistorLab
* File:        main.c
* Description: This program determines the color-code of a 4-band resistor given a user
*                   inputted resistor value between 1-99M. The program is designed to
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

           //if the input is less than 1, greater than 99000000, or a letter, the user is asked to enter again
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

}






