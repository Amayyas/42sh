/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** is cd function call
*/

#include "my.h"

bool is_cd(mysh_t *mysh, bin_tree_t *node)
{
    if (my_strcmp(node->command[0], "cd") == 0
    || my_strcmp(node->command[0], "chdir") == 0) {
        if (node->command[1] != NULL && node->command[2] != NULL) {
            mini_printstderr("cd: Too many arguments.\n");
            mysh->ret_value = 1;
            return true;
        }
        my_cd(mysh, node->command[1]);
        return true;
    }
    return false;
}
