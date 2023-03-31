#include "context.h"
#include <stdlib.h>

#define INITIAL_SIZE 1

context_t *create_context(){
    context_t* context = malloc(sizeof(context_t));
    context->array = malloc(sizeof(struct variable_array));
    context->array->var_arr = malloc(INITIAL_SIZE * sizeof(struct variable));
    context->array->used = 0;
    context->array->size = INITIAL_SIZE;
    return context;
}

void addVariable(struct variable var, context_t* context){
    struct variable_array* arr = context->array;
    if (arr->used == arr->size){
        arr->size *= 2;
        arr->var_arr = realloc(arr->var_arr, arr->size * sizeof(struct variable));
    }
    arr->var_arr[arr->used++] = var;
}


void destroyContext(context_t* context){
    struct variable_array* arr = context->array;
    free(arr->var_arr);
    free(arr);
    free(context);
}