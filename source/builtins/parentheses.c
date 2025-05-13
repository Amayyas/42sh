/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** exec of parentheses
*/

#include "my.h"

char **get_cmd_par(mysh_t *mysh, char *index)
{
    par_t *tmp = mysh->par;
    char *id = strtok(index, ")\0");
    char *tmp_id = NULL;

    if (!id)
        return NULL;
    for (; tmp; tmp = tmp->next) {
        tmp_id = my_inttostring(tmp->key);
        if (my_strcmp(id, tmp_id) == 0) {
            free(tmp_id);
            return tmp->value;
        }
        if (tmp_id)
            free(tmp_id);
    }
    return NULL;
}

// la tu bin tree (1), utilise la ll
void exec_parentheses(mysh_t *mysh, bin_tree_t *node)
{
    char **command_array = get_cmd_par(mysh, node->command[0] + 1);
    bin_tree_t *root = NULL;

    if (!command_array)
        return;
    root = create_bin_tree(command_array, 0,
        my_arraylen(command_array) - 1);
    exec_tree(mysh, root);
    free_bin_tree(root);
}
