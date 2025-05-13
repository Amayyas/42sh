/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_str_to_word_array_delim
*/

#include "my.h"

int nb_word_delim(char *str, char *delim)
{
    char *tmp_str = my_strdup(str);
    int i = 0;
    char *save_token = strtok(tmp_str, delim);

    while (save_token != NULL) {
        save_token = strtok(NULL, delim);
        i++;
    }
    free(tmp_str);
    return i;
}

char **my_str_to_word_array_delim(char *str, char *delim)
{
    char **array = malloc(sizeof(char *) * (nb_word_delim(str, delim) + 1));
    char *token = strtok(str, delim);
    int index = 0;

    while (token != NULL) {
        array[index] = my_strdup(token);
        token = strtok(NULL, delim);
        index++;
    }
    array[index] = NULL;
    return array;
}
