/*
** EPITECH PROJECT, 2024
** int to string
** File description:
** convert int into string
*/

#include "my.h"

char *my_inttostring(int num)
{
    char *str = malloc(sizeof(char) * 12);
    int index = 0;
    int buff = num;

    if (num == 0) {
        str[index] = '0';
        index++;
        str[index] = '\0';
        return str;
    }
    while (buff != 0) {
        index++;
        buff /= 10;
    }
    for (int i = index - 1; i >= 0; i--) {
        str[i] = (num % 10) + 48;
        num /= 10;
    }
    str[index] = '\0';
    return str;
}
