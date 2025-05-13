/*
** EPITECH PROJECT, 2025
** my_isalnum
** File description:
** my_isalnum
*/

#include "my.h"

bool my_isalnum(char c)
{
    if ((c >= 'a' && c <= 'z')
    || (c >= 'A' && c <= 'Z')
    || (c >= '0' && c <= '9'))
        return true;
    return false;
}
