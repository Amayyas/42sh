/*
** EPITECH PROJECT, 2025
** print binary tree
** File description:
** print a binary tree with endentation
*/

#include "my.h"

void print_tree(bin_tree_t *node, int depth, const char *side)
{
    if (node == NULL)
        return;
    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("%s: ", side);
    if (node->command != NULL) {
        printf("COMMAND: ");
        for (int i = 0; node->command[i] != NULL; i++)
            printf("%s ", node->command[i]);
        printf("\n");
    } else if (node->redirection != NULL)
        printf("REDIRECTION: %s\n", node->redirection);
    if (node->left)
        print_tree(node->left, depth + 1, "LEFT");
    if (node->right)
        print_tree(node->right, depth + 1, "RIGHT");
}
