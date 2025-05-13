/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** termios interface
*/

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#ifndef TERMIOS_INTERFACE_H
    #define TERMIOS_INTERFACE_H
    #define CTRL_D 4
    #define CTRL_L 12
    #define ESCAPE 27
    #define ARROW_RIGHT 'C'
    #define ARROW_LEFT 'D'
    #define ARROW_UP 'A'
    #define ARROW_DOWN 'B'
    #define SUPPR 3
    #define ENTER 10
    #define BACKSPACE 127
    #define CTRL_C 3
    #define CTRL_H 8
    #define CTRL_A 1
    #define CTRL_W 23
    #define CTRL_Y 25

typedef struct termios_data {
    char ch;
    int cursor_pos;
    int len_line;
    char line[BUFSIZ];
    char copy[BUFSIZ];
} termios_data_t;

void enable_raw_mode(void);
void disable_raw_mode(void);

#endif /* !TERMIOS_INTERFACE_H */
