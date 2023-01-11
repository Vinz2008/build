
#include <stddef.h>

enum Token {
    tok_eof = -1,
    tok_var = -2,
    tok_start_section = -3,
    tok_command = -4,
};

struct token_array {
    enum Token* token_list;
    size_t used;
    size_t size;
};