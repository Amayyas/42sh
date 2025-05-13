/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** terminal line prompt
*/

#include "my.h"

void terminal_line(mysh_t *mysh)
{
    int prompt_size = 0;
    char cwd[MAX_LENGHT];

    if (isatty(0) == 0)
        return;
    getcwd(cwd, MAX_LENGHT);
    mini_printf("[");
    mini_printf("%s%s" RESET, mysh->color, cwd);
    mini_printf("]$-> ");
    prompt_size = strlen(cwd) + 6;
    mysh->prompt_len = prompt_size;
}
