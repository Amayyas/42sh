/*
** EPITECH PROJECT, 2025
** sh
** File description:
** handle ctrl keys
*/

#include "my.h"

static void up_arrow(mysh_t *mysh)
{
    if (mysh->history_cursor == NULL) {
        strcpy(mysh->saved_line, mysh->termios_data->line);
        mysh->history_cursor = mysh->history;
    } else if (mysh->history_cursor->next)
        mysh->history_cursor = mysh->history_cursor->next;
    memset(mysh->termios_data->line, 0, BUFSIZ);
    strcpy(mysh->termios_data->line, mysh->history_cursor->command);
    mysh->termios_data->len_line = strlen(mysh->history_cursor->command);
    mysh->termios_data->cursor_pos = mysh->termios_data->len_line;
    mini_printf("\r\033[2K");
    terminal_line(mysh);
    mini_printf("%s", mysh->termios_data->line);
}

static void down_arrow(mysh_t *mysh)
{
    if (mysh->history_cursor->prev) {
        mysh->history_cursor = mysh->history_cursor->prev;
        memset(mysh->termios_data->line, 0, BUFSIZ);
        strcpy(mysh->termios_data->line, mysh->history_cursor->command);
        mysh->termios_data->len_line = strlen(mysh->history_cursor->command);
        mysh->termios_data->cursor_pos = mysh->termios_data->len_line;
    } else {
        memset(mysh->termios_data->line, 0, BUFSIZ);
        strcpy(mysh->termios_data->line, mysh->saved_line);
        mysh->termios_data->len_line = strlen(mysh->saved_line);
        mysh->termios_data->cursor_pos = mysh->termios_data->len_line;
        mysh->history_cursor = NULL;
    }
    mini_printf("\r\033[2K");
    terminal_line(mysh);
    mini_printf("%s", mysh->termios_data->line);
}

void history_arrows(mysh_t *mysh, char arrow)
{
    if (arrow == ARROW_UP && mysh->history != NULL)
        up_arrow(mysh);
    else if (arrow == ARROW_DOWN && mysh->history_cursor != NULL)
        down_arrow(mysh);
}

void arrows(mysh_t *mysh, char arrow)
{
    if (arrow == ARROW_RIGHT &&
    mysh->termios_data->cursor_pos < mysh->termios_data->len_line) {
        mysh->termios_data->cursor_pos++;
        mini_printf("\033[C");
    } else if (arrow == ARROW_LEFT && mysh->termios_data->cursor_pos > 0) {
        mysh->termios_data->cursor_pos--;
        mini_printf("\033[D");
    }
}

void suppr(mysh_t *mysh)
{
    if (mysh->termios_data->cursor_pos < mysh->termios_data->len_line) {
        for (int i = mysh->termios_data->cursor_pos;
        i < mysh->termios_data->len_line - 1; i++)
            mysh->termios_data->line[i] = mysh->termios_data->line[i + 1];
        mysh->termios_data->len_line--;
        mysh->termios_data->line[mysh->termios_data->len_line] = '\0';
        mini_printf("\033[K");
        for (int i = mysh->termios_data->cursor_pos;
        i < mysh->termios_data->len_line; i++)
            mini_printf("%c", mysh->termios_data->line[i]);
        for (int i = mysh->termios_data->len_line;
        i > mysh->termios_data->cursor_pos; i--)
            mini_printf("\033[D");
    }
}

void handle_backspace(mysh_t *mysh)
{
    int chars_to_move_back = 0;

    if (mysh->termios_data->cursor_pos > 0) {
        mysh->termios_data->cursor_pos--;
        for (int i = mysh->termios_data->cursor_pos;
            i < mysh->termios_data->len_line - 1; i++)
            mysh->termios_data->line[i] = mysh->termios_data->line[i + 1];
        mysh->termios_data->len_line--;
        mysh->termios_data->line[mysh->termios_data->len_line] = '\0';
        mini_printf("\b\033[K");
        for (int i = mysh->termios_data->cursor_pos;
            i < mysh->termios_data->len_line; i++)
            mini_printf("%c", mysh->termios_data->line[i]);
        chars_to_move_back =
            mysh->termios_data->len_line - mysh->termios_data->cursor_pos;
        for (int i = 0; i < chars_to_move_back; i++)
            mini_printf("\033[D");
    }
}
