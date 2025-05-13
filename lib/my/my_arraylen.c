/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** get the size of an array
*/

#include "my.h"

int my_arraylen(char **array)
{
    int array_len = 0;

    for (int i = 0; array[i] != NULL; i++) {
        array_len++;
    }
    return array_len;
}
