/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** free everything
*/

#include "my.h"

/// @brief free the totality of an array
void free_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++) {
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
    array = NULL;
}

/// @brief free the command array and the command str
void free_all_command(mysh_t *mysh)
{
    free(mysh->command);
    if (mysh->command_array) {
        for (int i = 0; mysh->command_array[i] != NULL; i++)
            free(mysh->command_array[i]);
        free(mysh->command_array);
    }
    if (mysh->root)
        free_bin_tree(mysh->root);
}

void free_all_ll(mysh_t *mysh)
{
    if (mysh->variables)
        free_ll_variables(mysh->variables);
    if (mysh->alias)
        free_ll_alias(mysh->alias);
    if (mysh->par)
        free_ll_par(mysh->par);
    if (mysh->ticks)
        free_ll_ticks(mysh->ticks);
    if (mysh->history)
        free_ll_history(mysh->history);
}

/// @brief free env, path, command array&str, the struct
void free_all(mysh_t *mysh)
{
    free_all_ll(mysh);
    free_array(mysh->env);
    free_all_command(mysh);
    free(mysh);
}
