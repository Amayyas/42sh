/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** return true if the variable exist, else false
*/

#include "my.h"

bool is_inenv(char **env, char *search)
{
    int len_search = my_strlen(search);

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], search, len_search) == 0) {
            return true;
        }
    }
    return false;
}
