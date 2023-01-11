#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int pos = 0;
char* line = NULL;
FILE* f;
char* strLexing = NULL;
int strLexing_length = 0;
char* section_name = NULL;
int section_name_length = 0;

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

char getCharLine(){
    if (line == NULL){
        line = malloc(1000 * sizeof(char));
        if (fgets(line, 1000, f) == NULL){
            printf("End of the file\n");
        }
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
    if (LastChar == '-'){
        do {
        LastChar = getCharLine();
        append(LastChar, section_name, section_name_length);
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
        printf("section name found : %s\n", section_name);
        return tok_start_section;
    }
    if (LastChar != '\n'){
        do {
        LastChar = getCharLine();
        append(LastChar, strLexing, strLexing_length);
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
    }
    if (LastChar == EOF)
        return tok_eof;
    int ThisChar = LastChar;
    LastChar = getCharLine();
    return ThisChar;
}

void parseFile(const char* filename){
    f = fopen(filename, "r");
}