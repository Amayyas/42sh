/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** Parse env to get the PATH variable
*/

#include "my.h"

char *env_parser(mysh_t *mysh, char *search)
{
    char *path;
    int len_search = my_strlen(search);
    char **new_env = my_arraydup(mysh->env);

    for (int i = 0; new_env[i] != NULL; i++) {
        if (my_strncmp(new_env[i], search, len_search) == 0) {
            strtok(new_env[i], "=");
            path = my_strdup(strtok(NULL, ""));
            free_array(new_env);
            return path;
        }
    }
    free_array(new_env);
    return NULL;
}
