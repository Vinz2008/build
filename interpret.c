#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interpret.h"
#include "libs/startswith.h"
#include "libs/color.h"

struct Variable {
char name[10];
char value[20];
};

int interpret(char fileName[], int debugMode) {
    FILE *commandReadPtr;
    int i;
    int i2;
    int i3;
    int i4;
    int posVar;
    char varAskedName[15];
    FILE *fptr;
    char line[1000];
    char lineList[500][400];
    struct Variable varArray[10];
    int nbVariable = 0;
    fptr = fopen(fileName, "r");
    if (fptr == NULL)
    {
        printf(BRED "Error! The Buildfile doesn't exist or is empty\n" reset);   
        exit(1);
    }
     while (fgets(line,150, fptr)) {
         char line2[1000];
        strcpy(line2, line);
        int c = 0;
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
	for (i = 0; i < sizeLineList; i++) {
        if (startswith("$(",lineList[i])) {
        if (debugMode == 1) {
        printf("word startswith $(\n");
        }
	i3 = 0;
        memset(varAskedName, 0, sizeof(varAskedName));
	for (i2 = 2; i2 < strlen(lineList[i]) - 1; i2++) {
        if (debugMode == 1) {
        printf("lineList[%i][%i] : %c\n",i,i2,lineList[i][i2]);
        }
	    varAskedName[i3] = lineList[i][i2];
	    i3++;
	    }
	    for (i2 = 0; i2 < nbVariable; i2++){
	    if (startswith(varAskedName, varArray[i2].name)) {
	    posVar = i2;
	    }
	    }
            strcpy(lineList[i], varArray[posVar].value);
            memset(line2, 0, sizeof(line2));
            i4 = 0;
	    if (debugMode == 1) {
            printf("replacing var :\n");
            printf("sizeLineList : %i\n",sizeLineList);
        }
            for (i2 = 0; i2 < sizeLineList; i2++) {
                for (i3 = 0; i3 < strlen(lineList[i2]); i3++) {
		    if (debugMode == 1) {
		    printf("lineList[%i][%i] : %c\n",i2,i3,lineList[i2][i3]);
		    }
                    line2[i4] = lineList[i2][i3];
                    i4++;
                }
		//i4++;
                line2[strlen(lineList[i2]) + 1] = ' ';
                //i4++;
            }
	    if (debugMode == 1) {
	    printf("line2 after changing variable : %s\n", line2);
	    }
        }
        if (debugMode == 1) {
            printf("lineList[%i]: %s\n",i, lineList[i]);
        }
        }

	if (startswith("var",lineList[0])) {
        if (debugMode == 1) {
        printf("var detected\n");
	    printf("var name: %s\n", lineList[3]);
	    printf("var value : %s\n", lineList[1]);
        }
	    strcpy(varArray[nbVariable].name, lineList[1]);
	    strcpy(varArray[nbVariable].value, lineList[3]);
	    nbVariable++;
    }
    else if (startswith("-", lineList[0])) {
        if (debugMode == 1) {
            printf("section detected\n");
        }
    }
    else  {
        if (debugMode == 1) {
            printf("line2 before running command : %s\n", line2);
        }
        commandReadPtr = popen(line2, "r");
	if (debugMode == 1) {
	printf("process ptr created\n");
	}
        memset(output, 0, sizeof(output));
	if (debugMode == 1) {
        printf("empty ouput\n");
        }
        fscanf(commandReadPtr,"%s",output);
	if (debugMode == 1) {
        printf("launch process\n");
        }
        if (debugMode == 1) {
            printf("---REAL OUTPUT---\n");
        }
        printf("%s\n", output);
        if (debugMode == 1) {
        printf("-----------------\n");
        }         
        }
        if (debugMode == 1) {
            printf("end of line\n");
        }
     }
     memset(lineList, 0, sizeof(lineList));
    return 0;
}
