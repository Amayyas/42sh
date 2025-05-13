/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** is env function call
*/

#include "my.h"

bool is_env(mysh_t *mysh, bin_tree_t *node)
{
    if (my_strcmp(node->command[0], "env") == 0) {
        if (node->command[1] != NULL) {
            mini_printstderr("env: Too many arguments.\n");
            mysh->ret_value = 127;
            return true;
        }
        my_print_env(mysh);
        mysh->ret_value = 0;
        return true;
    }
    return false;
}
