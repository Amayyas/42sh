/*
** EPITECH PROJECT, 2025
** free_bin_tree
** File description:
** free averything of a binary tree
*/

#include "my.h"

void free_bin_tree(bin_tree_t *node)
{
    if (node == NULL)
        return;
    if (node->command != NULL)
        free_array(node->command);
    if (node->redirection != NULL)
        free(node->redirection);
    free_bin_tree(node->left);
    free_bin_tree(node->right);
    free(node);
    node = NULL;
}
