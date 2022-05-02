#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interpret.h"
#ifdef _WIN32
#define ARGUMENT_START 1
#else
#define ARGUMENT_START 1
#endif

int main(int argc,char* argv[]){
    int i;
    char argument[100];
    char inputFilename[15];
    int isDebug = 0;
    int fileNameFound = 0;
        for (i=ARGUMENT_START;i<argc;i++) 
        {
            //printf("argv[%i] : %s\n",i, argv[i]);
        if(strcmp(argv[i], "-d") == 0)
        {
        isDebug = 1;
        }
        else if (strcmp(argv[i], "-f" ) == 0){
            strcpy(inputFilename, argv[i+1]);
            fileNameFound = 1;
        }
        }
    if (fileNameFound == 0) {
        strcpy(inputFilename,"Buildfile");
    }
    interpret(inputFilename, isDebug);



    return 0;
}
