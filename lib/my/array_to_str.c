/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** array_to_str
*/

#include "my.h"

int len_array(char **array)
{
    int len = 0;

    for (int i = 0; array[i]; i++) {
        for (int j = 0; array[i][j]; j++)
            len++;
        len++;
    }
    return len;
}

char *array_to_str(char **array)
{
    int len = len_array(array);
    char *str = malloc(sizeof(char) * len + 1);
    int i = 0;

    for (int j = 0; array[j]; j++) {
        for (int k = 0; array[j][k]; k++) {
            str[i] = array[j][k];
            i++;
        }
        str[i] = ' ';
        i++;
    }
    return str;
}
