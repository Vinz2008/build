#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interpret.h"
#include "libs/startswith.h"

int interpret(char fileName[], int debugMode) {
    FILE *commandReadPtr;
    int i;
    FILE *fptr;
    char line[40];
    fptr = fopen(fileName, "r");
    if (fptr == NULL)
    {
        printf("Error! The file is empty\n");   
        exit(1);
    }
     while (fgets(line,150, fptr)) {
         char line2[40];
        strcpy(line2, line);
        int c = 0;
         char lineList[15][15];
         char output[50];
         int sizeLineList = 0;
         char *pch = strtok(line," ");
        while (pch != NULL)
	    {
            sizeLineList++;
             strcpy(lineList[c], pch);
            for (i = 0; i < strlen(lineList[c]); i++) {
           if (debugMode == 1) {
            printf("char : %c\n",lineList[c][i]);
           }
        }
        pch = strtok(NULL, " ");

	    c++;
        }
        if (debugMode == 1) {
            printf("lineList[i]: %s\n", lineList[i]);
            }
            if (startswith("-", lineList[0])) {
                if (debugMode == 1) {
                printf("section detected\n");
                }
            }
            else  {
                commandReadPtr = popen(line2, "r");
                fscanf(commandReadPtr,"%s",output);
                 if (debugMode == 1) {
                     printf("---REAL OUTPUT---\n");
                 }
                printf("%s\n", output);
                if (debugMode == 1) {
                printf("-----------------\n");
                }
                 
            }
        for (i = 0; i < sizeLineList; i++) {
            //for now nothing
        }
        if (debugMode == 1) {
            printf("end of line\n");
        }
     }
    return 0;
}