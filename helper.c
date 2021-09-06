#include <time.h>
#include <stdlib.h>
#include <string.h>
char *getCurrentTime(){
    static char buffer[27];
    time_t timer = time(NULL);
    struct tm* tm_info =localtime(&timer);
    strftime(buffer, 26, "%d-%m-%Y %I:%M %p", tm_info);
    buffer[27] = '\0';
    return buffer;
}
void clearConsole(){
    system("cls");
}
char *subString(char text[], char delim[], int position){
    char *firstWord, *secondWord, *remainder, *context;
    int inputLength = strlen(text);
    char *inputCopy = (char*) calloc(inputLength + 1, sizeof(char));
    strncpy(inputCopy, text, inputLength);
    firstWord = strtok_r (inputCopy, delim, &context);
    secondWord = strtok_r (NULL, delim, &context);
    remainder = context;
    if(position == 1){
        return firstWord;
    } else if(position == 2){
        return secondWord;
    } else {
        return remainder;
    }
}

char *randomString(){
    static char random[20];
    itoa(time(NULL), random, 10);
    return random;
}