/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** len_tab
*/

#include "my.h"

int len_tab(char **array)
{
    int i = 0;

    for (; array[i]; i++);
    return i;
}
