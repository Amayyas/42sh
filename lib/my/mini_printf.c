/*
** EPITECH PROJECT, 2024
** mini_printf
** File description:
** mini_printf
*/

#include "my.h"

static int my_putchar(char c)
{
    write(1, &c, 1);
    return (0);
}

static int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return (0);
}

static int my_put_nbr(int nb)
{
    char c;

    if (nb < 0) {
        write(1, "-", 1);
        if (nb == -2147483648) {
            write(1, "2147483648", 10);
            return 0;
        }
        nb = -nb;
    }
    if (nb >= 10) {
        my_put_nbr(nb / 10);
    }
    c = (nb % 10) + '0';
    write(1, &c, 1);
    return 0;
}

void find_pourcent(const char format, va_list list)
{
    switch (format) {
        case 'd':
            my_put_nbr(va_arg(list, int));
            break;
        case 'i':
            my_put_nbr(va_arg(list, int));
            break;
        case 's':
            my_putstr(va_arg(list, char *));
            break;
        case 'c':
            my_putchar((char)va_arg(list, int));
            break;
        case '%':
            my_putchar('%');
            break;
        default:
            break;
    }
}

int mini_printf(const char *format, ...)
{
    va_list list;

    va_start(list, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            find_pourcent(format[i + 1], list);
            i += 1;
        } else {
            my_putchar(format[i]);
        }
    }
    va_end(list);
    return 0;
}
