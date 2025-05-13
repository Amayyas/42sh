/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** is setenv function call
*/

#include "my.h"

bool handling_setenv_error(mysh_t *mysh, bin_tree_t *node)
{
    if (!node->command[1]) {
        my_print_env(mysh);
        mysh->ret_value = 0;
        return true;
    }
    if (!node->command[2]) {
        my_setenv(mysh, node->command[1], "");
        return true;
    }
    if (node->command[3]) {
        mini_printf("setenv: Too many arguments.\n");
        mysh->ret_value = 1;
        return true;
    }
    return false;
}

bool is_setenv(mysh_t *mysh, bin_tree_t *node)
{
    if (my_strcmp(node->command[0], "setenv") == 0) {
        if (handling_setenv_error(mysh, node) == true)
            return true;
        my_setenv(mysh, node->command[1], node->command[2]);
        return true;
    }
    return false;
}
