/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is history command
*/

#include "my.h"

bool myisdigits(const char *str)
{
    if (str == NULL || *str == '\0')
        return false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

bool history_errors(mysh_t *mysh, bin_tree_t *node)
{
    if (node->command[1] != NULL && node->command[1][0] == '-') {
        mini_printstderr("Usage: history [-chrSLMT] [# number of events].\n");
        mysh->ret_value = 1;
        return true;
    }
    if (node->command[1] != NULL && !myisdigits(node->command[1])) {
        mini_printstderr("history: Badly formed number.\n");
        mysh->ret_value = 1;
        return true;
    }
    return false;
}

int get_linked_size(history_t *history)
{
    int size = 0;
    history_t *temp = history;

    while (temp != NULL) {
        size++;
        temp = temp->next;
    }
    return size;
}

bool n_last_history(mysh_t *mysh, bin_tree_t *node, history_t *temp)
{
    int num = 0;
    int history_size = get_linked_size(mysh->history);
    int skip = 0;

    if (node->command[1] != NULL && myisdigits(node->command[1])) {
        num = atoi(node->command[1]);
        temp = mysh->history;
        while (temp && temp->next)
            temp = temp->next;
        skip = history_size > num ? history_size - num : 0;
        for (int i = 0; i < skip; i++)
            temp = temp->prev;
        while (temp) {
            printf("    %d  %s   %s\n", temp->id, temp->date, temp->command);
            temp = temp->prev;
        }
        return true;
    }
    return false;
}

bool is_history(mysh_t *mysh, bin_tree_t *node)
{
    history_t *temp = NULL;

    if (my_strcmp(node->command[0], "history") == 0) {
        temp = mysh->history;
        if (history_errors(mysh, node))
            return true;
        if (n_last_history(mysh, node, temp))
            return true;
        while (temp && temp->next)
            temp = temp->next;
        while (temp) {
            printf("    %d  %s   %s\n", temp->id, temp->date, temp->command);
            temp = temp->prev;
        }
        mysh->ret_value = 0;
        return true;
    }
    return false;
}
