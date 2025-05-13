/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** if the command is in /usr/bin
*/

#include "my.h"

int file_exists(char *path)
{
    return access(path, X_OK) == 0;
}
