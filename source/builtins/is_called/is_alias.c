/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is_alias function
*/

#include "my.h"

int count_space(char *str)
{
    int count = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == ' ')
            count++;
    }
    return count;
}

void print_alias(alias_t *alias)
{
    alias_t *tmp = alias;

    while (tmp) {
        printf("%s\t", tmp->key);
        if (count_space(tmp->value) > 0)
            printf("(%s)\n", tmp->value);
        else
            printf("%s\n", tmp->value);
        tmp = tmp->next;
    }
}

char *whole_value(char **cmd)
{
    char *value = NULL;
    int len = 0;

    for (int i = 2; cmd[i]; i++)
        len += strlen(cmd[i]) + 1;
    value = malloc(sizeof(char) * (len + 1));
    value[0] = '\0';
    for (int i = 2; cmd[i]; i++) {
        strcat(value, cmd[i]);
        if (cmd[i + 1])
            strcat(value, " ");
    }
    return value;
}

int is_alias(mysh_t *mysh, bin_tree_t *node)
{
    char *value = NULL;

    if (strcmp(node->command[0], "alias") == 0) {
        if (!node->command[1]) {
            mysh->alias = tri_fusion(mysh->alias, compare_str);
            print_alias(mysh->alias);
            return 1;
        }
        if (node->command[1] && node->command[2]) {
            value = whole_value(node->command);
            add_alias(mysh, node->command[1], value);
            free(value);
        }
        return 1;
    }
    return 0;
}
