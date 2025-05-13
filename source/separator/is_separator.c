/*
** EPITECH PROJECT, 2025
** Minishell2
** File description:
** return true is the node of the binary tree is field with a separator
*/

#include "my.h"

bool is_separator(bin_tree_t *node)
{
    if (node->type == SEMICOLON || node->type == PIPE
        || node->type == REDIRECTION)
        return true;
    return false;
}
