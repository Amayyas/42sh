/*
** EPITECH PROJECT, 2025
** my_isalpha
** File description:
** my_isalpha
*/

#include "my.h"

bool my_isalpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
        return true;
    return false;
}
