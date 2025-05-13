/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** get the command line
*/

#include "my.h"

void reset_termios(mysh_t *mysh)
{
    mysh->termios_data->ch = '\0';
    mysh->termios_data->cursor_pos = 0;
    mysh->termios_data->len_line = 0;
    memset(mysh->termios_data->line, 0, BUFSIZ);
    mysh->history_cursor = NULL;
    memset(mysh->saved_line, 0, BUFSIZ);
}

void handle_escape_sequence(mysh_t *mysh)
{
    char seq = 0;

    if (getchar() == '[') {
        seq = getchar();
        if (seq == '3' && getchar() == '~')
            suppr(mysh);
        if (seq == ARROW_RIGHT || seq == ARROW_LEFT)
            arrows(mysh, seq);
        if (seq == ARROW_UP || seq == ARROW_DOWN)
            history_arrows(mysh, seq);
    }
}

void handle_enter_key(mysh_t *mysh)
{
    mysh->termios_data->line[mysh->termios_data->len_line] = '\0';
    mysh->command = my_strdup(mysh->termios_data->line);
    memset(mysh->termios_data->line, 0, BUFSIZ);
    mini_printf("\n");
}

void handle_regular_character(mysh_t *mysh)
{
    if (mysh->termios_data->len_line >= BUFSIZ - 1)
        return;
    if (mysh->termios_data->cursor_pos < mysh->termios_data->len_line) {
        memmove(&mysh->termios_data->line[mysh->termios_data->cursor_pos + 1],
                &mysh->termios_data->line[mysh->termios_data->cursor_pos],
                mysh->termios_data->len_line - mysh->termios_data->cursor_pos);
    }
    mysh->termios_data->line[mysh->termios_data->cursor_pos]
        = mysh->termios_data->ch;
    mysh->termios_data->cursor_pos++;
    mysh->termios_data->len_line++;
    printf("\033[s");
    printf("\033[K");
    printf("%s",
        &mysh->termios_data->line[mysh->termios_data->cursor_pos - 1]);
    printf("\033[u");
    printf("\033[C");
}

static void process_input2(mysh_t *mysh)
{
    switch (mysh->termios_data->ch) {
        case ESCAPE:
            handle_escape_sequence(mysh);
            break;
        case ENTER:
            handle_enter_key(mysh);
            break;
        case BACKSPACE:
        case CTRL_H:
            handle_backspace(mysh);
            break;
        default:
            handle_regular_character(mysh);
            break;
    }
}

static void process_input(mysh_t *mysh)
{
    switch (mysh->termios_data->ch) {
        case CTRL_D:
            handle_ctrl_d(mysh);
            break;
        case CTRL_L:
            handle_ctrl_l(mysh);
            break;
        case CTRL_A:
            handle_ctrl_a(mysh);
            break;
        case CTRL_W:
            handle_ctrl_w(mysh);
            break;
        case CTRL_Y:
            handle_ctrl_y(mysh);
            break;
        default:
            process_input2(mysh);
            break;
    }
}

int get_stdin(mysh_t *mysh)
{
    signal(SIGINT, handle_ctrlc);
    terminal_line(mysh);
    reset_termios(mysh);
    while (true) {
        mysh->termios_data->ch = getchar();
        process_input(mysh);
        if (mysh->termios_data->ch == '\n')
            break;
    }
    return 0;
}
