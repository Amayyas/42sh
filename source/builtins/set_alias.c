/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** set_alias function
*/

#include "my.h"

int alias_recusion(mysh_t *mysh, char *cmd)
{
    alias_t *tmp = mysh->alias;

    for (; tmp; tmp = tmp->next) {
        if (my_strcmp(tmp->key, cmd) == 0) {
            return 1;
        }
    }
    return 0;
}

void free_tmp(char **save, char **value_array)
{
    free_array(save);
    free_array(value_array);
    return;
}

int set_new_array(mysh_t *mysh, char *value, int *limit)
{
    char **value_array = my_strtoword_array(value);
    char **save = my_arraydup(mysh->command_array);
    int i = 0;

    mysh->command_array = realloc(mysh->command_array,
        sizeof(char *) * (len_tab(save) + len_tab(value_array) + 1));
    for (; value_array[i]; i++) {
        if (mysh->command_array[i])
            free(mysh->command_array[i]);
        mysh->command_array[i] = my_strdup(value_array[i]);
    }
    for (int j = 1; save[j]; j++) {
        mysh->command_array[i] = my_strdup(save[j]);
        i++;
    }
    mysh->command_array[i] = NULL;
    free_tmp(save, value_array);
    if (alias_recusion(mysh, mysh->command_array[0]))
        return set_alias(mysh, limit);
    return 0;
}

int set_alias(mysh_t *mysh, int *limit)
{
    alias_t *tmp = mysh->alias;

    *limit += 1;
    for (; tmp; tmp = tmp->next) {
        if (my_strcmp(tmp->key, mysh->command_array[0]) == 0 && *limit == 10) {
            mini_printstderr("Alias loop.\n");
            return 1;
        }
        if (my_strcmp(tmp->key, mysh->command_array[0]) == 0)
            return set_new_array(mysh, tmp->value, limit);
    }
    return 0;
}
