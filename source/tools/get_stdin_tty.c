/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get stdin if the shel is non interactive
*/
#include "my.h"

static void free_everything(mysh_t *mysh)
{
    free_array(mysh->env);
    free(mysh->color);
    free(mysh->command);
    free(mysh->path_line);
    free(mysh->home_line);
    free_all_ll(mysh);
    free(mysh);
}

int get_stdin_tty(mysh_t *mysh)
{
    size_t len = 0;
    int result;
    int ret;

    result = getline(&mysh->command, &len, stdin);
    if (result == EOF) {
        ret = mysh->ret_value;
        free_everything(mysh);
        exit(ret);
    }
    if (result == 1) {
        mysh->is_empty = true;
        free(mysh->command);
    }
    return 0;
}
