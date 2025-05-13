/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle ctrl+ ...
*/

#include "my.h"
#include "termios_interface.h"

void handle_ctrl_d(mysh_t *mysh)
{
    int ret = mysh->ret_value;

    printf("\n");
    free(mysh->color);
    free(mysh->home_line);
    free(mysh->path_line);
    free_array(mysh->env);
    free(mysh->termios_data);
    free_all_ll(mysh);
    free(mysh);
    exit(ret);
}

// Clear screen
void handle_ctrl_l(mysh_t *mysh)
{
    mini_printf("\033[H\033[J");
    terminal_line(mysh);
    mini_printf("%s", mysh->termios_data->line);
}

void handle_ctrl_a(mysh_t *mysh)
{
    while (mysh->termios_data->cursor_pos > 0) {
        mini_printf("\033[D");
        mysh->termios_data->cursor_pos--;
    }
}

void handle_ctrl_w(mysh_t *mysh)
{
    int cursor_pos = mysh->termios_data->cursor_pos;
    char new_line[BUFSIZ];

    memset(mysh->termios_data->copy, 0, BUFSIZ);
    memset(new_line, 0, BUFSIZ);
    for (int i = 0; i < cursor_pos; i++)
        mysh->termios_data->copy[i] = mysh->termios_data->line[i];
    mysh->termios_data->copy[cursor_pos] = '\0';
    for (int i = cursor_pos; i < mysh->termios_data->len_line; i++)
        new_line[i - cursor_pos] = mysh->termios_data->line[i];
    new_line[mysh->termios_data->len_line - cursor_pos] = '\0';
    mysh->termios_data->len_line -= cursor_pos;
    mysh->termios_data->cursor_pos = 0;
    memset(mysh->termios_data->line, 0, BUFSIZ);
    for (int i = 0; i < mysh->termios_data->len_line; i++)
        mysh->termios_data->line[i] = new_line[i];
    mysh->termios_data->line[mysh->termios_data->len_line] = '\0';
    mini_printf("\r\033[2K");
    terminal_line(mysh);
    mini_printf("%s \033[%dG", mysh->termios_data->line, mysh->prompt_len + 1);
}

void handle_ctrl_y(mysh_t *mysh)
{
    int cursor_pos = mysh->termios_data->cursor_pos;
    int copy_length = strlen(mysh->termios_data->copy);

    if (cursor_pos < mysh->termios_data->len_line) {
        memmove(&mysh->termios_data->line[cursor_pos + copy_length],
                &mysh->termios_data->line[cursor_pos],
                mysh->termios_data->len_line - cursor_pos);
    }
    memcpy(&mysh->termios_data->line[cursor_pos], mysh->termios_data->copy,
    copy_length);
    mysh->termios_data->cursor_pos += copy_length;
    mysh->termios_data->len_line += copy_length;
    mini_printf("\r\033[2K");
    terminal_line(mysh);
    mini_printf("%s", mysh->termios_data->line);
}
