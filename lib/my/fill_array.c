/*
** EPITECH PROJECT, 2025
** B-PSU-200-MPL-2-1-42sh-nielsen.combe-bracciale
** File description:
** fill_array
*/

#include "my.h"

static void free_array_tokens(char **array, int count)
{
    for (int j = 0; j < count; j++)
        free(array[j]);
}

static int process_token(char **array, int *array_index, char *str, int *i)
{
    char *token = get_next_token(str, i);

    if (token == NULL) {
        free_array_tokens(array, *array_index);
        return 1;
    }
    array[*array_index] = token;
    (*array_index)++;
    return 0;
}

int fill_array(char **array, char *str, int max_tokens)
{
    int array_index = 0;
    int i = 0;
    int len = my_strlen(str);

    skip_whitespace(str, &i);
    while (i < len && str[i]) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
            skip_whitespace(str, &i);
            continue;
        }
        if (array_index >= max_tokens) {
            break;
        }
        if (process_token(array, &array_index, str, &i) != 0)
            return 1;
    }
    array[array_index] = NULL;
    return 0;
}
