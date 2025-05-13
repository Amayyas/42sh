/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** get_file
*/

#include "my.h"

int get_size(char *str, char c)
{
    int i = 0;

    while (str[i] != '\0' && str[i] != c) {
        i++;
    }
    return i + 1;
}

char *my_strdup_char(char *str, char c)
{
    char *new_str = malloc(sizeof(char) * get_size(str, c));
    int i = 0;

    while (str[i] != '\0' && str[i] != c) {
        new_str[i] = str[i];
        i++;
    }
    new_str[i] = '\0';
    return new_str;
}
