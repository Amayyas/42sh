/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_unsetenv
*/

#include "my.h"

void fill_newenv(mysh_t *mysh, char **new_env_array, char *name, int env_size)
{
    int index = 0;
    int len_name = my_strlen(name);

    for (int i = 0; i < env_size; i++) {
        if (my_strncmp(mysh->env[i], name, len_name) == 0
        && mysh->env[i][len_name] == '=')
            continue;
        new_env_array[index] = my_strdup(mysh->env[i]);
        index++;
    }
    new_env_array[index] = NULL;
    free_array(mysh->env);
    mysh->env = new_env_array;
}

void my_unsetenv(mysh_t *mysh, char *name)
{
    int len_name = my_strlen(name);
    int env_size;
    int new_env_size = 0;
    char **new_env_array;

    if (!is_inenv(mysh->env, name))
        return;
    for (env_size = 0; mysh->env[env_size] != NULL; env_size++) {
        if (my_strncmp(mysh->env[env_size], name, len_name) != 0
        || mysh->env[env_size][len_name] != '=')
            new_env_size++;
    }
    new_env_array = malloc(sizeof(char *) * (new_env_size + 1));
    fill_newenv(mysh, new_env_array, name, env_size);
}
