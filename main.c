#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "helper.c"
#include "file.c"
#include "oparetion.c"
void main(){
    // create note directory if not exists
    createDirectory("notes");
    int input;
    while (1){
        clearConsole();
        printf("\t\t----------------\n");
        printf("\t\t Personal Diary\n");
        printf("\t\t----------------\n\n");
        printf("\t1. Create new note\n");
        printf("\t2. View all notes\n\n\n");
        printf("Choose option : ");
        scanf("%d", &input);
        if(input == 1){
            clearConsole();
            writeNewNote();
            getch();
            fflush(stdin);
        } else if (input == 2){
            clearConsole();
            readNotes("notes/");
            getch();
            fflush(stdin);
        } else {
            printf("Enter valid command\n");
            getch();
            fflush(stdin);
        }
    }
}