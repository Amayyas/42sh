/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** every functions about freeing a ll are here
*/

#include "my.h"


void free_ll_variables(variables_t *variables)
{
    variables_t *tmp = NULL;

    if (variables == NULL)
        return;
    while (variables) {
        tmp = variables;
        variables = variables->next;
        if (tmp->name)
            free(tmp->name);
        if (tmp->value)
            free(tmp->value);
        free(tmp);
    }
}

void free_ll_alias(alias_t *alias)
{
    alias_t *tmp = NULL;

    if (alias == NULL)
        return;
    while (alias) {
        tmp = alias;
        alias = alias->next;
        if (tmp->key)
            free(tmp->key);
        if (tmp->value)
            free(tmp->value);
        free(tmp);
    }
}

void free_ll_par(par_t *par)
{
    par_t *tmp = NULL;

    if (par == NULL)
        return;
    while (par) {
        tmp = par;
        par = par->next;
        if (tmp->value)
            free_array(tmp->value);
        free(tmp);
    }
}

void free_ll_ticks(ticks_t *ticks)
{
    ticks_t *tmp = NULL;

    if (ticks == NULL)
        return;
    while (ticks) {
        tmp = ticks;
        ticks = ticks->next;
        if (tmp->value)
            free_array(tmp->value);
        free(tmp);
    }
}

void free_ll_history(history_t *history)
{
    history_t *temp = history;
    history_t *next = NULL;

    while (temp) {
        next = temp->next;
        if (temp->command)
            free(temp->command);
        if (temp->date)
            free(temp->date);
        free(temp);
        temp = next;
    }
}
