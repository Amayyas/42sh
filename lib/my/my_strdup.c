/*
** EPITECH PROJECT, 2024
** strndup
** File description:
** duplicate 'n' number of char of a char *
*/

#include "my.h"
/// @brief duplicate a string into another one
/// @param src string you want to duplicate
/// @return the clone of the src string
char *my_strdup(const char *src)
{
    int len = 0;
    char *dup = NULL;

    if (src == NULL)
        return NULL;
    len = my_strlen(src);
    dup = malloc(sizeof(char) * len + 1);
    if (!dup)
        return NULL;
    for (int i = 0; i < len; i++) {
        dup[i] = src[i];
    }
    dup[len] = '\0';
    return dup;
}
