#include <stdio.h>
#include "lexer.h"


extern char* IdentifierStr;

void ParseVar(){
    getNextToken(); // eat var token
    char* VariableName = IdentifierStr;
    printf("VariableName : %s\n", VariableName);
}