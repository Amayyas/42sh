/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** execute my commands
*/

#include "my.h"

bool other_builtins(mysh_t *mysh, bin_tree_t *node)
{
    if (is_set(mysh, node))
        return true;
    if (is_history(mysh, node))
        return true;
    if (is_alias(mysh, node))
        return true;
    return false;
}

bool is_builtins(mysh_t *mysh, bin_tree_t *node)
{
    if (node->command[0] == NULL)
        return true;
    if (is_exit(mysh, node))
        return true;
    if (is_cd(mysh, node))
        return true;
    if (is_setenv(mysh, node))
        return true;
    if (is_unsetenv(mysh, node))
        return true;
    if (is_env(mysh, node))
        return true;
    if (is_setcolor(mysh, node))
        return true;
    return other_builtins(mysh, node);
}
