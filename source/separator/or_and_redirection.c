/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** and redirection: && or redirection: ||
*/

#include "my.h"

int and_redirection(mysh_t *mysh, bin_tree_t *node)
{
    if (node->left == NULL && node->right == NULL) {
        mysh->ret_value = 1;
        return 1;
    }
    if (node->right == NULL) {
        mini_printstderr("Invalid null command.\n");
        mysh->ret_value = 1;
        return 1;
    }
    if (node->left == NULL) {
        exec_tree(mysh, node->right);
        mysh->ret_value = 0;
        return mysh->ret_value;
    }
    exec_tree(mysh, node->left);
    if (mysh->ret_value == 0) {
        exec_tree(mysh, node->right);
    }
    return mysh->ret_value;
}

int or_redirection(mysh_t *mysh, bin_tree_t *node)
{
    if (node->left == NULL || node->right == NULL) {
        mini_printstderr("Invalid null command.\n");
        mysh->ret_value = 1;
        return 1;
    }
    exec_tree(mysh, node->left);
    if (mysh->ret_value != 0) {
        exec_tree(mysh, node->right);
    }
    return mysh->ret_value;
}
