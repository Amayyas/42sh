/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** edit_commande function (for parentheses)
*/

#include "my.h"

void edit_command_manage(mysh_t *mysh)
{
    init_parentheses(mysh);
    set_backticks(mysh);
}
