/*
** EPITECH PROJECT, 2024
** string to int
** File description:
** convert a string into a int
*/

#include "my.h"
/// @brief cast a string into an int
/// @param str only number composed string tou want to turn into int
/// @return your string into int
int my_atoi(const char *str)
{
    int result = 0;
    int i = 0;
    int sign = 1;

    if (str == NULL || str[0] == '\0') {
        return 84;
    }
    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return 84;
        }
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}
