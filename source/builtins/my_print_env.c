/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** print all the env
*/

#include "my.h"

void my_print_env(mysh_t *mysh)
{
    for (int i = 0; mysh->env[i] != NULL; i++) {
        mini_printf("%s\n", mysh->env[i]);
    }
    return;
}
