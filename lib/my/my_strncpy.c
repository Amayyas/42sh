/*
** EPITECH PROJECT, 2024
** mathys
** File description:
** my
*/

#include "my.h"

char *my_strncpy(char *dest, char *src, int n)
{
    int i = 0;

    if (n < 1 || !dest || !src)
        return NULL;
    for (; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
