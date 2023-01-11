#include <stddef.h>

struct variable {
    char* name;
    char* value;
};

struct variable_array {
    struct variable* var_arr;
    size_t used;
    size_t size;
};

typedef struct {
    struct variable_array* array;
} context_t;