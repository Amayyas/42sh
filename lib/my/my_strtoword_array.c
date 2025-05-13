/*
** EPITECH PROJECT, 2025
** my_strtoword_array
** File description:
** my_strtoword_array
*/

#include "my.h"

char **my_strtoword_array(char *str)
{
    int token_count = count_tokens(str);
    char **array = malloc(sizeof(char *) * (token_count + 1));

    if (array == NULL)
        return NULL;
    if (fill_array(array, str, token_count) != 0) {
        free(array);
        return NULL;
    }
    return array;
}
