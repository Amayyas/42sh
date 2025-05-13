/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** init_parentheses function
*/

#include "my.h"

par_t *create_par(char *value, unsigned int index)
{
    par_t *par = NULL;

    if (!value)
        return NULL;
    par = malloc(sizeof(par_t));
    par->key = index;
    par->value = my_strtoword_array(value);
    par->next = NULL;
    return par;
}

void add_par_end(mysh_t *mysh, char *value, unsigned int index)
{
    par_t *new_par = create_par(value, index);
    par_t *tmp = mysh->par;

    if (!new_par)
        return;
    if (!tmp) {
        mysh->par = new_par;
        return;
    }
    for (; tmp->next; tmp = tmp->next);
    tmp->next = new_par;
}

int find_close_par(mysh_t *mysh, int i)
{
    int j = i;

    while (mysh->command[j] != CLOSE_PAR && mysh->command[j] != '\0')
        j++;
    return j;
}

void edit_cmd_par(mysh_t *mysh, int index, char *new_cmd, int i)
{
    char *nb = my_inttostring(index);

    new_cmd[i + 1] = '\0';
    my_strcat(new_cmd, nb);
    my_strcat(new_cmd, mysh->command + find_close_par(mysh, i));
    free(nb);
    free(mysh->command);
    mysh->command = my_strdup(new_cmd);
}

void init_parentheses(mysh_t *mysh)
{
    int i = 0;
    static unsigned int index = 0;
    char *new_cmd = malloc(sizeof(char) * my_strlen(mysh->command) + 1);
    char *par_str = NULL;

    for (; mysh->command[i]; i++) {
        new_cmd[i] = mysh->command[i];
        if (mysh->command[i] == OPEN_PAR) {
            par_str = my_strdup_char(mysh->command + i + 1, CLOSE_PAR);
            add_par_end(mysh, par_str, index);
            edit_cmd_par(mysh, index, new_cmd, i);
            index += 1;
            break;
        }
    }
    if (par_str)
        free(par_str);
    free(new_cmd);
}
