/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** exec command in a binary tree
*/

#include "my.h"

void have_toexit(mysh_t *mysh)
{
    if (isatty(0) == 0 && mysh->ret_value != 0)
        exit(mysh->ret_value);
}

// more check for PAR
int execute_command(bin_tree_t *node, mysh_t *mysh)
{
    if (is_builtins(mysh, node))
        have_toexit(mysh);
    else if (node->command[0][0] == OPEN_PAR)
        exec_parentheses(mysh, node);
    else
        return new_process(node, mysh);
    return 0;
}

int exec_tree(mysh_t *mysh, bin_tree_t *node)
{
    if (node == NULL)
        return 0;
    if (node->type == COMMAND)
        return execute_command(node, mysh);
    if (node->type == SEMICOLON) {
        exec_tree(mysh, node->left);
        exec_tree(mysh, node->right);
    }
    if (node->type == OR)
        or_redirection(mysh, node);
    if (node->type == AND)
        and_redirection(mysh, node);
    if (node->type == PIPE)
        exec_pipe(mysh, node);
    if (node->type == REDIRECTION)
        exec_redirection(mysh, node);
    return 0;
}
