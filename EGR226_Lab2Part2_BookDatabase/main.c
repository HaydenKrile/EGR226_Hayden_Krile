#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char title[255];
    char author_name[50];
    char ISBN[10];
    int pages;
    int year_published;
}book;

int parse_file(char filename[], book book_array[]);
void print_book(book printBook[], int num);
void search_title(book titalSearch[], int num, char userTitle[]);
void search_author(book authorSearch[], int num, char userAuthor[]);
void search_ISBN();

int main(){
    char nameOfFile[25] = "BookList.csv";
    char titleFinder[100], authorFinder[100], ISBNFinder[100];
    int decision, count, i;
    book main_book_array[360];
    parse_file(nameOfFile, main_book_array);

    while(1){
     do {
        printf("[0] Search by Title\n[1] Search by Author Name\n[2] Search by ISBN\n[3] Exit\n");
        count = scanf("%d", &decision);

        if (count == 0 || decision < 0 || decision > 3){
            printf("\nINPUT ERROR!\n\n");
            while(getchar()!= '\n');
            }

        } while (count == 0 || decision < 0 || decision > 3);

        switch(decision){
            case 0:
                fflush(stdin);
                printf("Enter the book title: ");
                scanf("%[^\n]%*c", titleFinder);
                printf("Searching book titles containing [%s]\n", titleFinder);
                search_title(main_book_array, 360, titleFinder);
                break;
            case 1:
                fflush(stdin);
                printf("Enter the author's name: ");
                scanf("%[^\n]%*c", authorFinder);
                printf("Searching authors containing [%s]\n", authorFinder);
                search_author(main_book_array, 360, authorFinder);
                break;
            case 2:
                fflush(stdin);
                printf("Enter the ISBN: ");
                scanf("%[^\n]%*c", titleFinder);
                printf("Searching ISBN containing [%s]\n", titleFinder);
                search_title(main_book_array, 360, titleFinder);
                break;
            case 3:
                return 0;
                break;
        }
    }
}

/*-----------------------------------------------------------
* Function: parse_file
* Description: Sift through a file of books to populate
* an empty book array
* Inputs:
* (char*) filename: file to open and parse
* (book*) book_array: array of book structures to
* populate
* Outputs:
* (int) parse status, 1 if successful, 0 otherwise.
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

void print_book(book printBook[], int i){

    printf(" |Title: %s\n |Author: %s\n |ISBN: %s", printBook[i].title, printBook[i].author_name, printBook[i].ISBN);

    if(printBook[i].pages){
        printf("\n |Pages: %d", printBook[i].pages);
    }
    else{
        printf("\n |Pages: N/A");
    }

    if(printBook[i].pages){
        printf("\n |Year Published: %d\n\n", printBook[i].year_published);
    }
    else{
        printf("\n |Year Published: N/A\n\n");
    }

}

void search_title(book titalSearch[], int num, char userTitle[]){

    int i;

    for(i=0; i<num; i++){
        if(strstr(titalSearch[i].title, userTitle)){
            print_book(titalSearch, i);
        }
    }
}

void search_author(book authorSearch[], int num, char userAuthor[]){

    int i;

    for(i=0; i<num; i++){
        if(strstr(authorSearch[i].author_name, userAuthor)){
            print_book(authorSearch, i);
        }
    }
}

void search_ISBN(book ISBNSearch[], int num, char userISBN[]){

    int i;

    for(i=0; i<num; i++){
        if(strstr(ISBNSearch[i].ISBN, userISBN)){
            print_book(ISBNSearch, i);
        }
    }
}
