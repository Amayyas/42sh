/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** handle env variable
*/

#include "my.h"

void handle_home_env(mysh_t *mysh)
{
    char *new_home_line = env_parser(mysh, "HOME");

    if (new_home_line != NULL) {
        if (mysh->home_line)
            free(mysh->home_line);
        mysh->home_line = my_strdup(new_home_line);
    }
    free(new_home_line);
}

void handle_path_env(mysh_t *mysh)
{
    char *new_path_line = env_parser(mysh, "PATH");
    char *nb = my_inttostring(mysh->ret_value);

    mysh->variables = add_node_start(mysh->variables, "?", nb);
    free(nb);
    if (new_path_line == NULL && !is_inenv(mysh->env, "PATH"))
        return;
    if (mysh->path_line)
        free(mysh->path_line);
    mysh->path_line = my_strdup(new_path_line);
    free(new_path_line);
    handle_home_env(mysh);
}
