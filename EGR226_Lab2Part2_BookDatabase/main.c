/**************************************************************************************
* Author:      Hayden Krile
* Course:      EGR 226 - 905
* Date:        02/04/2021
* Project:     BookDatabase
* File:        main.c
* Description: This program scans in a .csv file filled with book data seperated by commas.
*                   The program pases each piece of data seperated by a comma into its respective
*                   data slot, those being title, author, ISBN, pages, and year published.
*                   The program then asks the user if it would like to search the library by
*                   book title, author, or ISBN.
*                   The program then scans in the uer input and searches for and prints out the
*                   full details of the book found with matching tilte/author/ISBN.
***************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//structure used for storing book data
typedef struct{
    char title[255];
    char author_name[50];
    char ISBN[10];
    int pages;
    int year_published;
}book;

//function headers
int parse_file(char filename[], book book_array[]);
void print_book(book printBook[], int num);
void search_title(book titleSearch[], int num, char userTitle[]);
void search_author(book authorSearch[], int num, char userAuthor[]);
void search_ISBN(book ISBNSearch[], int num, char userISBN[]);

int main(){
    char nameOfFile[25] = "BookList.csv";
    char titleFinder[100], authorFinder[100], ISBNFinder[100];
    int decision, count, i;
    book main_book_array[360];

    //file is parsed and data is sent to respective area in the book struct
    parse_file(nameOfFile, main_book_array);

    while(1){
    //asks the user if they would like to search by tilte, author, or ISBN
     do {
        printf("[0] Search by Title\n[1] Search by Author Name\n[2] Search by ISBN\n[3] Exit\n");
        count = scanf("%d", &decision);

        if (count == 0 || decision < 0 || decision > 3){
            printf("\nINPUT ERROR!\n\n");
            while(getchar()!= '\n');
            }

        } while (count == 0 || decision < 0 || decision > 3);

        //once decision is made, this switch statement presents the function the user requested
        switch(decision){
            case 0:
                fflush(stdin);
                //asks the user for book title
                printf("Enter the book title: ");
                //scans in the users input until new line is detected, allowing multiple word quirries
                scanf("%[^\n]%*c", titleFinder);
                //shows the user the what the program is looking for
                printf("Searching book titles containing [%s]\n\n", titleFinder);
                //searches throughout the entire library to find a matching title
                search_title(main_book_array, 360, titleFinder);
                break;
            case 1:
                fflush(stdin);
                //asks the user for book author
                printf("Enter the author's name: ");
                //scans in the users input until new line is detected, allowing multiple word quirries
                scanf("%[^\n]%*c", authorFinder);
                //shows the user the what the program is looking for
                printf("Searching authors containing [%s]\n\n", authorFinder);
                //searches throughout the entire library to find a matching author
                search_author(main_book_array, 360, authorFinder);
                break;
            case 2:
                fflush(stdin);
                //asks the user for book ISBN
                printf("Enter the ISBN: ");
                //scans in the users input until new line is detected, allowing multiple word quirries
                scanf("%[^\n]%*c", ISBNFinder);
                //shows the user the what the program is looking for
                printf("Searching ISBN containing [%s]\n\n", ISBNFinder);
                //searches throughout the entire library to find a matching ISBN
                search_ISBN(main_book_array, 360, ISBNFinder);
                break;
            case 3:
                //if the user selected exit, the program ends
                return 0;
                break;
        }
    }
}

/*-----------------------------------------------------------
* Function: parse_file
* Description: Sift through a file of books to populate
*               an empty book array
* Inputs:
*              (char*) filename: file to open and parse
*              (book*) book_array: array of book structures to
*                populate
* Outputs:
*              (int) parse status, 1 if successful, 0 otherwise.
*---------------------------------------------------------*/
int parse_file(char filename[], book book_array[]) {
    FILE* infile = fopen(filename, "r"); // Attempt to open file
    if (infile == NULL) {// Return 0 (failure) if file could not open
        printf("File not Found\n");
        return 0;
    }

    char buffer[512]; // Create temporary string buffer variable
    int i = 0; // Indexer for book array

    while (fgets(buffer, 512, infile)) {    // Loop collecting each line from the file
        char * ptr = strtok(buffer,",");    // Parse string by commas and newline
        if(strcmp(ptr,"N/A")) {             // Validate string
            strcpy(book_array[i].title,ptr);// First parse is title
        }

        ptr = strtok(NULL,",\n");
        if(strcmp(ptr,"N/A")) {                     // Validate string
            strcpy(book_array[i].author_name,ptr);  // second parse is author name
        }

        ptr = strtok(NULL,",\n");
        if(strcmp(ptr,"N/A")) {             // Validate string
            strcpy(book_array[i].ISBN,ptr); // Third parse is ISBN
        }
        else{
            strcpy(book_array[i].ISBN,"N/A");
        }

        ptr = strtok(NULL,",\n");
        if(strcmp(ptr,"N/A")) {             // Validate string
            book_array[i].pages = atoi(ptr);
        }

        ptr = strtok(NULL,",\n");
        if(strcmp(ptr,"N/A")) {             // Validate string
            book_array[i].year_published = atoi(ptr);
        }
        i++;
    }

    fclose(infile);
    return 1;
}

/*-----------------------------------------------------------
* Function: print_book
* Description: Prints out all elements of a book
* Inputs:
*              book printBook: array of book structures to sift and print from
*              int i: location of the book that needs printing
* Outputs:
*              N/A
*---------------------------------------------------------*/
void print_book(book printBook[], int i){

    printf(" |Title: %s\n |Author: %s\n |ISBN: %s", printBook[i].title, printBook[i].author_name, printBook[i].ISBN);

    if(printBook[i].pages){
        printf("\n |Pages: %d", printBook[i].pages);
    }
    else{
        printf("\n |Pages: N/A");
    }

    if(printBook[i].year_published){
        printf("\n |Year Published: %d\n\n", printBook[i].year_published);
    }
    else{
        printf("\n |Year Published: N/A\n\n");
    }

}

/*-----------------------------------------------------------
* Function: search_title
* Description: sift through the array of books to find a matching string
                given by the user
* Inputs:
*              book titleSearch[]: all the titles for the program to sift through
*              int num: number of elements in the book array
*              char userTitle[]: Array containing the users input
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void search_title(book titleSearch[], int num, char userTitle[]){

    int i;

    for(i=0; i<num; i++){
        if(strstr(titleSearch[i].title, userTitle)){
            print_book(titleSearch, i);
        }
    }
}

/*-----------------------------------------------------------
* Function: search_author
* Description: sift through the array of books to find a matching string
                given by the user
* Inputs:
*              book authorSearch[]: all the authors for the program to sift through
*              int num: number of elements in the book array
*              char userAuthor[]: Array containing the users input
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void search_author(book authorSearch[], int num, char userAuthor[]){

    int i;

    for(i=0; i<num; i++){
        if(strstr(authorSearch[i].author_name, userAuthor)){
            print_book(authorSearch, i);
        }
    }
}

/*-----------------------------------------------------------
* Function: search_ISBN
* Description: sift through the array of books to find a matching string
                given by the user
* Inputs:
*              book ISBNSearch[]: all the ISBN's for the program to sift through
*              int num: number of elements in the book array
*              char userISBN[]: Array containing the users input
*
* Outputs:
*              N/A
*---------------------------------------------------------*/
void search_ISBN(book ISBNSearch[], int num, char userISBN[]){

    int i;

    for(i=0; i<num; i++){
        if(strstr(ISBNSearch[i].ISBN, userISBN)){
            print_book(ISBNSearch, i);
        }
    }
}
