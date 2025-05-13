/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** set function
*/

#include "my.h"

bool id_in_list(variables_t *current, char *name, char *value)
{
    if (strcmp(current->name, name) == 0) {
        if (current->value != NULL)
            free(current->value);
        current->value = (value != NULL) ? strdup(value) : strdup("");
        return true;
    }
    return false;
}

variables_t *add_node_start(variables_t *variables, char *name, char *value)
{
    variables_t *new_node = NULL;
    variables_t *current = variables;

    while (current != NULL) {
        if (id_in_list(current, name, value))
            return variables;
        current = current->next;
    }
    new_node = malloc(sizeof(variables_t));
    if (new_node == NULL) {
        perror("malloc");
        return NULL;
    }
    new_node->name = strdup(name);
    if (value != NULL)
        new_node->value = strdup(value);
    else
        new_node->value = NULL;
    new_node->next = variables;
    return new_node;
}

int my_set(mysh_t *mysh, char *command)
{
    char *name = NULL;
    char *value = NULL;

    name = strtok(command, "=\n\0");
    if (name == NULL) {
        mini_printstderr("set: Invalid null name.\n");
        mysh->ret_value = 1;
        return 1;
    }
    value = strtok(NULL, "\n\0");
    if (value == NULL) {
        mysh->variables = add_node_start(mysh->variables, name, "");
        mysh->ret_value = 0;
        return 0;
    }
    mysh->variables = add_node_start(mysh->variables, name, value);
    mysh->ret_value = 0;
    return 0;
}
