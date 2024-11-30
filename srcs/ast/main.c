#include "../../includes/ast.h"

char *join_argv(char **argv) {
    if (argv == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    for (int i = 1; argv[i] != NULL; i++) {
        total_length += strlen(argv[i]) + 1; // +1 for the space or null terminator
    }

    // Allocate memory for the resulting string
    char *result = (char *)malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    // Initialize the resulting string
    result[0] = '\0';

    // Concatenate each word to the resulting string -> do not count first argument -> that is the name of the binary, eg ./test
    for (int i = 1; argv[i] != NULL; i++) {
        strcat(result, argv[i]);
        if (argv[i + 1] != NULL) {
            strcat(result, " ");
        }
    }

    return result;
}

int main(int argc, char **argv) {

    if (argc < 2) {
      printf("Usage: %s <command>\n", argv[0]);
      return 1;
    }
    // printf("Input command: %s\n", argv[1]);
    // printf("====================================\n");

    t_tokenqueue *tokens;
    t_astnode    *root;
    char              *str;

    str = join_argv(argv);
    // printf("str from argv: %s\n", str);
    // for (int i = 0; tokens_str[i] != NULL; i++) {
    //   printf("Token %d: %s\n", i, tokens_str[i]);
    // }
    tokens = tokenizer(str);
    printf("tokens created:\n");
    // print_tokens(tokens);
    // printf("Tokens created:\n");
    // print_tokens(tokens);
    // printf("Now creating AST\n");
    root = create_ast(tokens);
    // printf("AST created:\n");
    // print_ast_tree(root);
    printf("\n");
    printf("execute ast result:");
    int result = -1;
    result = execute_node_main(root);
    printf("ast executed with result: %i\n", result);
    printf("-------- FREING AST --------\n");
    free_ast(root);
    free(str);

    return 0; 
    // execute_ast(root);
}
