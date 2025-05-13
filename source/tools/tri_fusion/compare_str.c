/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** compare str
*/

#include "my.h"

bool compare_str(void *str1, void *str2)
{
    return (strcmp((char *)str1, (char *)str2) > 0);
}
