/*
** EPITECH PROJECT, 2025
** my_isdigit
** File description:
** check if a string is only composed of digit
*/

#include "my.h"

bool my_isdigit(char *str)
{
    int i = 0;

    if (str == NULL || str[0] == '\0')
        return false;
    if (str[0] == '-' || str[0] == '+')
        i++;
    for (; str[i] != '\0'; i++) {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return false;
    }
    return true;
}
