/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** is unsetenv function call
*/

#include "my.h"

bool is_unsetenv(mysh_t *mysh, bin_tree_t *node)
{
    if (my_strcmp(node->command[0], "unsetenv") == 0) {
        if (node->command[1] == NULL) {
            mini_printf("unsetenv: Too few arguments.\n");
            mysh->ret_value = 1;
            return true;
        }
        for (int i = 0; node->command[i] != NULL; i++)
            my_unsetenv(mysh, node->command[i]);
        mysh->ret_value = 0;
        return true;
    }
    return false;
}
