/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle ! commands for history
*/

#include "my.h"

char *find_command_by_prefix(mysh_t *mysh, const char *prefix)
{
    history_t *temp = mysh->history;

    if (!prefix || !temp)
        return NULL;
    while (temp) {
        if (strncmp(temp->command, prefix, strlen(prefix)) == 0)
            return my_strdup(temp->command);
        temp = temp->next;
    }
    return NULL;
}

char *find_command_by_number(mysh_t *mysh, int num)
{
    history_t *temp = mysh->history;

    while (temp) {
        if (temp->id == num)
            return my_strdup(temp->command);
        temp = temp->next;
    }
    return NULL;
}

char *handle_bang_command(mysh_t *mysh, char *cmd)
{
    char *new_cmd = NULL;

    if (cmd[0] != '!')
        return cmd;
    if (myisdigits(cmd + 1)) {
        new_cmd = find_command_by_number(mysh, atoi(cmd + 1));
    } else {
        new_cmd = find_command_by_prefix(mysh, cmd + 1);
    }
    if (!new_cmd) {
        mini_printstderr("%s: Event not found.\n", cmd);
        mysh->ret_value = 1;
        return NULL;
    }
    mini_printf("%s\n", new_cmd);
    return new_cmd;
}
