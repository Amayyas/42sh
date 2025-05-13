/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** alias
*/

#include "my.h"

alias_t *create_alias(char *key, char *value)
{
    alias_t *new_alias = malloc(sizeof(alias_t));

    if (!new_alias)
        return NULL;
    new_alias->key = strdup(key);
    new_alias->value = strdup(value);
    new_alias->next = NULL;
    return new_alias;
}

void add_alias_end(mysh_t *mysh, char *key, char *value)
{
    alias_t *new_alias = create_alias(key, value);
    alias_t *tmp = mysh->alias;

    if (!tmp) {
        mysh->alias = new_alias;
        mysh->alias->next = NULL;
        return;
    }
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = new_alias;
}

void add_alias(mysh_t *mysh, char *key, char *value)
{
    alias_t *tmp = mysh->alias;

    for (; tmp; tmp = tmp->next) {
        if (strcmp(tmp->key, key) == 0) {
            free(tmp->value);
            tmp->value = strdup(value);
            return;
        }
    }
    add_alias_end(mysh, key, value);
    return;
}
