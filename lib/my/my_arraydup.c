/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** duplicate an array
*/

#include "my.h"

char **my_arraydup(char **array)
{
    int array_size;
    char **new_env_array;

    for (array_size = 0; array[array_size] != NULL; array_size++);
    new_env_array = malloc(sizeof(char *) * (array_size + 1));
    if (new_env_array == NULL)
        return NULL;
    for (int i = 0; i < array_size; i++)
        new_env_array[i] = my_strdup(array[i]);
    new_env_array[array_size] = NULL;
    return new_env_array;
}
