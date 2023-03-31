#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "interpret.h"
#include "lexer.h"
#include "context.h"
#define ARGUMENT_START 1

extern char* line;
extern int CurTok;

void HandleVar(){
    printf("handling var\n");
    ParseVar();
}

void HandleStartSection(){

}

void MainLoop(){
    while (1){
        printf("curTok : %i\n", CurTok);
        switch (CurTok){
            case tok_eof:
                return;
            case ';': // ignore top-level semicolons.
                getNextToken();
                break;
            case tok_var:
                HandleVar();
                break;
            case tok_start_section:
                HandleStartSection();
                break;
            default:
                printf("UNKNOWN EXPRESSION\n");
                //exit(1);
                return;
                break;
        }
    }
}

int main(int argc,char* argv[]){
    int i;
    char inputFilename[15];
    int isDebug = 0;
    int fileNameFound = 0;
    for (i=ARGUMENT_START;i<argc;i++) {
        if(strcmp(argv[i], "-d") == 0){
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
    //interpret(inputFilename, isDebug);
    context_t* context = create_context();
    openConfigFile(inputFilename);
    getNextToken();
    MainLoop();
    destroyContext(context);
    return 0;
}
