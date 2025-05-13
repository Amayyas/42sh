/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** create a binary tree from an array
*/

#include "my.h"

static char **get_command(int type, char **command)
{
    if (type == COMMAND)
        return my_arraydup(command);
    return NULL;
}

static char *get_separator(int type, char *str)
{
    if (type == REDIRECTION || type == PIPE || type == SEMICOLON)
        return my_strdup(str);
    return NULL;
}

bin_tree_t *create_node_bintree(char **command)
{
    bin_tree_t *node = malloc(sizeof(bin_tree_t));

    if (node == NULL)
        return NULL;
    node->type = get_type(command[0]);
    node->command = get_command(node->type, command);
    node->redirection = get_separator(node->type, command[0]);
    node->left = NULL;
    node->right = NULL;
    return node;
}

bin_tree_t *create_command_node(char **command_array, int start, int end)
{
    char **sub_array = NULL;
    bin_tree_t *node = NULL;

    sub_array = malloc((end - start + 2) * sizeof(char *));
    for (int i = start; i <= end; i++)
        sub_array[i - start] = command_array[i];
    sub_array[end - start + 1] = NULL;
    node = create_node_bintree(sub_array);
    free(sub_array);
    return node;
}

bin_tree_t *create_sep_node(char **array, int sep_pos, int start, int end)
{
    char *temp_array[2] = {NULL, NULL};
    bin_tree_t *node = NULL;

    temp_array[0] = array[sep_pos];
    node = create_node_bintree(temp_array);
    node->left = create_bin_tree(array, start, sep_pos - 1);
    node->right = create_bin_tree(array, sep_pos + 1, end);
    return node;
}

int get_priority(int type, int i, int *separator_pos, int *priority_pos)
{
    if (type != COMMAND) {
        if (type == SEMICOLON) {
            *priority_pos = i;
            return 0;
        }
        if (*separator_pos == -1)
            *separator_pos = i;
    }
    return 0;
}

bin_tree_t *create_bin_tree(char **command_array, int start, int end)
{
    int separator_pos = -1;
    int priority_pos = -1;
    int type = 0;

    if (start > end)
        return NULL;
    for (int i = end; i >= start; i--) {
        type = get_type(command_array[i]);
        get_priority(type, i, &separator_pos, &priority_pos);
    }
    if (priority_pos != -1)
        return create_sep_node(command_array, priority_pos, start, end);
    if (separator_pos == -1)
        return create_command_node(command_array, start, end);
    else
        return create_sep_node(command_array, separator_pos, start, end);
}
