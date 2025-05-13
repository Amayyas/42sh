/*
** EPITECH PROJECT, 2024
** mini_printstderr
** File description:
** mini_printstderr
*/

#include "my.h"

static int my_putchar_error(char c)
{
    write(2, &c, 1);
    return (0);
}

static int my_putstr_error(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar_error(str[i]);
        i++;
    }
    return (0);
}

static int my_put_nbr_error(int nb)
{
    char c;

    if (nb < 0) {
        write(2, "-", 1);
        if (nb == -2147483648) {
            write(2, "2147483648", 10);
            return 0;
        }
        nb = -nb;
    }
    if (nb >= 10)
        my_put_nbr_error(nb / 10);
    c = (nb % 10) + '0';
    write(2, &c, 1);
    return 0;
}

void find_pourcent_error(const char format, va_list list)
{
    switch (format) {
        case 'd':
            my_put_nbr_error(va_arg(list, int));
            break;
        case 'i':
            my_put_nbr_error(va_arg(list, int));
            break;
        case 's':
            my_putstr_error(va_arg(list, char *));
            break;
        case 'c':
            my_putchar_error((char)va_arg(list, int));
            break;
        case '%':
            my_putchar_error('%');
            break;
        default:
            break;
    }
}

int mini_printstderr(const char *format, ...)
{
    va_list list;

    va_start(list, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            find_pourcent_error(format[i + 1], list);
            i += 1;
        } else {
            my_putchar_error(format[i]);
        }
    }
    va_end(list);
    return 0;
}
