#include <stdio.h>
#include <dirent.h>

void createDirectory(char dirName[]){
    DIR *dir = opendir(dirName);
    if(dir){
        closedir(dir);
    } else {
        mkdir("notes");
    }
}
int fileExists(char filename[]){
    return access( filename, F_OK ) == 0 ? 1 : 0;
}

void writeRecord(char path[], char text[], char mode[]){
    FILE *file;
    file = fopen(path, mode);
    for(int i = 0; i < strlen(text); i++){
        fputc(text[i], file);
    }
    fclose(file);
}

char *readRecord(char path[]){
    FILE *file;
    file = fopen(path, "r");
    static char text[10000];
    int i = 0;
    while(!feof(file)){
        text[i] = fgetc(file);
        i++;
    }
    fclose(file);
    text[i] = '\0';
    return text;
}