/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** set variable
*/

#include "my.h"

void print_variables(variables_t *variables)
{
    if (!variables)
        return;
    while (variables) {
        if (variables->value != NULL)
            printf("%s\t%s\n", variables->name, variables->value);
        else
            printf("%s\n", variables->name);
        variables = variables->next;
    }
}

bool is_letter_or_underscore(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

bool call_my_set(mysh_t *mysh, bin_tree_t *node)
{
    for (int i = 1; node->command[i]; i++) {
        if (!is_letter_or_underscore(node->command[i][0])) {
            mini_printstderr("set: Variable name must begin with a letter.\n");
            mysh->ret_value = 1;
            return true;
        }
        my_set(mysh, node->command[i]);
    }
    mysh->ret_value = 0;
    return true;
}

bool is_set(mysh_t *mysh, bin_tree_t *node)
{
    if (my_strcmp(node->command[0], "set") == 0) {
        if (node->command[1] == NULL) {
            print_variables(mysh->variables);
            mysh->ret_value = 0;
            return true;
        }
        call_my_set(mysh, node);
        return true;
    }
    return false;
}
