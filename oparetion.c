#include <stdio.h>
#include <string.h>
#include <dirent.h>

struct ListStructure {
    int position;
    char *filename;
    char *title;
    char *date;
    char *data;
};

void showDetailsNote(struct ListStructure details);
void modifyNote(struct ListStructure details);

void writeNewNote(){
    fflush(stdin);
    char title[50];
    char description[10000];
    char data[10000];
    char path[20];
    printf("Title (max 50 charecters) : ");
    scanf("%[^\n]", title);
    fflush(stdin);
    if(strlen(title) > 1){
        printf("\nWrite Note : (press * and hit enter to save note)\n");
        scanf("%[^*]", description);
        strcat(data, title);
        strcat(data, "\n\r");
        strcat(data, getCurrentTime());
        strcat(data, "\n\r");
        strcat(data, description);
        strcat(path, "notes/");
        strcat(path, randomString());
        writeRecord(path, data, "w");
        printf("\nNew note created!\nPress any key to continue...");
    } else{
        return;
    }
}

void readNotes(char path[]){
    DIR *dp = opendir (path);
    struct dirent *ep;
    char *fileName;
    struct ListStructure listStructure, list[1000];
    if (dp != NULL){
        int position = 0;
        while (ep = readdir(dp)){
            fileName = ep->d_name;
            if(strlen(fileName) > 2){
                char filePath[20];
                strcat(filePath, path);
                strcat(filePath, fileName);
                char *data = readRecord(filePath);
                char *noteTitle = subString(data, "\n\r", 1);
                char *noteDate = subString(data, "\n\r", 2);
                char *noteData = subString(data, "\n\r", 3);
                listStructure.position = position+1;
                listStructure.filename = fileName;
                listStructure.title = noteTitle;
                listStructure.date = noteDate;
                listStructure.data = noteData;
                list[position] = listStructure;
                position++;
                memset(filePath, 0, sizeof(filePath));

            }
        }
        printf("\n\t================= Notes =================\n\n");
        for(int i = 0; i < position; i++){
            printf("\t%d. [%s]  %s\n", list[i].position, list[i].date, list[i].title);
        }
        if(position > 0){
            int noteIndex;
            printf("\n\nSelect note : ");
            scanf("%d", &noteIndex);
            showDetailsNote(list[noteIndex - 1]);
        } else {
            printf("\n\t\t    Note not found!\n\n\n\nPress any key to continue...");
            return;
        }
        closedir (dp);
    }
}

void showDetailsNote(struct ListStructure details){
    clearConsole();
    printf("\nTitle : %s\n", details.title);
    printf("Date modified : %s\n\n", details.date);
    printf("%s\n\n", details.data);
    printf("-------------------------------------------------");
    printf("\n\nOptions : \n\n");
    printf("\t1. Modify\n");
    printf("\t2. Delete\n");
    printf("\t3. Back\n\n");
    printf("Select option : ");
    int option;
    scanf("%d", &option);
    if(option == 1){
        clearConsole();
        modifyNote(details);
        fflush(stdin);
    } else if (option == 2){
        clearConsole();
        char filePath[70] = "notes/";
        strcat(filePath, details.filename);
        remove(filePath);
        memset(filePath, 0, sizeof(filePath));
        printf("\n\n\tNote deleted!\n\nPress any key to continue...");
    } else if( option == 3){
        return;
    } else {
        printf("Enter valid command\n");
        return;
    }
}

void modifyNote(struct ListStructure details){
    fflush(stdin);
    char title[50];
    char description[10000];
    char data[10000];
    char path[20];
    printf("Title (max 50 charecters) : ");
    scanf("%[^\n]", title);
    fflush(stdin);
    if(strlen(title) > 1){
        printf("\nWrite Note : (press * and hit enter to save note)\n");
        scanf("%[^*]", description);
        strcat(data, title);
        strcat(data, "\n\r");
        strcat(data, getCurrentTime());
        strcat(data, "\n\r");
        strcat(data, description);
        strcat(path, "notes/");
        strcat(path, details.filename);
        clearConsole();
        writeRecord(path, data, "w");
        printf("\n\"%s\" has modified!\nPress any key to continue...", details.title);
    }
}