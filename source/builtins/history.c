/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** command history
*/

#include "my.h"

char *get_date(void)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char *date = malloc(6);

    if (date == NULL)
        return NULL;
    strftime(date, 6, "%H:%M", tm);
    return date;
}

void add_to_history(mysh_t *mysh)
{
    history_t *new_node = malloc(sizeof(history_t));

    if (new_node == NULL)
        return;
    new_node->command = strdup(mysh->command);
    new_node->id = (mysh->history == NULL) ? 1 : mysh->history->id + 1;
    new_node->date = get_date();
    new_node->next = mysh->history;
    new_node->prev = NULL;
    if (mysh->history != NULL)
        mysh->history->prev = new_node;
    mysh->history = new_node;
}
