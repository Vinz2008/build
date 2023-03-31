#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int pos = 0;
char* line = NULL;
FILE* f;
char* IdentifierStr = NULL;
int IdentifierStr_length = 0;
char* command = NULL;
char* section_name = NULL;
int section_name_length = 0;
int CurTok = 0;

bool in_section = false;


void append(char c, char* str, int length){
    if (str == NULL){
        str = malloc(sizeof(char) * 2);
        length = 1;
    } else {
        str = realloc(str, (length+1) * sizeof(char));
        length++;
    }
    strncat(str, &c, 1);
}

void initTokenArray(struct token_array* arr, size_t initialSize){
    arr->token_list = malloc(initialSize * sizeof(enum Token));
    arr->used = 0;
    arr->size = initialSize;
}

void addToken(enum Token tok, struct token_array* arr){
    if (arr->used == arr->size){
        arr->size *= 2;
        arr->token_list = realloc(arr->token_list, arr->size * sizeof(enum Token));
    }
    arr->token_list[arr->used++] = tok;
}

char *getLine(FILE * f){
    size_t size = 0;
    size_t len  = 0;
    size_t last = 0;
    char *buf = NULL;

    do {
        size += BUFSIZ; /* BUFSIZ is defined as "the optimal read size for this platform" */
        buf = realloc(buf, size); /* realloc(NULL,n) is the same as malloc(n) */            
        /* Actually do the read. Note that fgets puts a terminal '\0' on the
           end of the string, so we make sure we overwrite this */
        if (buf == NULL) return NULL;
        fgets(buf + last, BUFSIZ, f);
        len = strlen(buf);
        last = len - 1;
    } while (!feof(f) && buf[last] != '\n');
    return buf;
}

char getCharLine(){
    if (line == NULL){
        //line = malloc(1000 * sizeof(char));
        /*if (fgets(line, 1000, f) == NULL){
            printf("End of the file\n");
        }*/
        line = getLine(f);
    }
    char c = line[pos];
    pos++;
    return c;
}

int gettok(){
    static int LastChar = ' ';
    while (isspace(LastChar)){
        LastChar = getCharLine();
    }
    if (LastChar == '\t'){
        command = strdup("");
        while ((LastChar = getCharLine()) != '\n'){
            append(LastChar, command, strlen(command));
        }
        printf("command : %s\n", command);
    }
    if (isalpha(LastChar)){
        IdentifierStr = strdup("");
        append(LastChar, IdentifierStr, strlen(IdentifierStr));
        while (isalnum((LastChar = getCharLine())) || LastChar == '_' || LastChar == ':'){
            append(LastChar, IdentifierStr, strlen(IdentifierStr));
        }
        if (IdentifierStr[strlen(IdentifierStr)-1] == ':'){
            printf("section : %s\n", section_name);
            return tok_start_section;
        }
        if (strcmp(IdentifierStr, "var") == 0){
            return tok_var;
        }
        printf("identifier : %s\n", IdentifierStr);
        return tok_identifier;

        /*command = IdentifierStr;
        while ((LastChar = getCharLine()) != '\n'){
            append(LastChar, command, strlen(command));
        }
        printf("command : %s\n", command);*/
    }
    /*if (LastChar != '\n'){
        do {
        LastChar = getCharLine();
        append(LastChar, IdentifierStr, strlen(IdentifierStr));
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
    }*/
    if (LastChar == EOF)
        return tok_eof;
    int ThisChar = LastChar;
    LastChar = getCharLine();
    printf("other char : %c\n", ThisChar);
    return ThisChar;
}

int getNextToken() {
  CurTok = gettok();
  return CurTok;
}

void openConfigFile(const char* filename){
    f = fopen(filename, "r");
}