/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** termios functions
*/

#include "my.h"
#include "termios.h"

void enable_raw_mode(void)
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

void disable_raw_mode(void)
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}
