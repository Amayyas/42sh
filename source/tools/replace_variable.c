/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** replace $... by his value
*/

#include "my.h"

char *search_in_env(mysh_t *mysh, char *var_name)
{
    char *tmp_env = NULL;

    for (int i = 0; mysh->env[i]; i++) {
        tmp_env = my_strdup_char(mysh->env[i], '=');
        if (my_strcmp(tmp_env, var_name) == 0) {
            free(tmp_env);
            tmp_env = strchr(mysh->env[i], '=');
            tmp_env++;
            return tmp_env;
        }
        if (tmp_env)
            free(tmp_env);
    }
    mini_printstderr("%s: Undefined variable.\n", var_name);
    mysh->ret_value = 1;
    return NULL;
}

char *get_variable_value(mysh_t *mysh, char *var_name)
{
    variables_t *tmp = mysh->variables;

    while (tmp) {
        if (my_strcmp(tmp->name, var_name) == 0)
            return tmp->value;
        tmp = tmp->next;
    }
    return search_in_env(mysh, var_name);
}

void replace_command(mysh_t *mysh, int i, char *var_value)
{
    char *save = NULL;

    save = my_strdup_char(mysh->command_array[i], '$');
    free(mysh->command_array[i]);
    if (save[0] == '\0') {
        mysh->command_array[i] = strdup(var_value);
    } else {
        save = realloc(save, strlen(save) + strlen(var_value) + 1);
        strcat(save, var_value);
        mysh->command_array[i] = strdup(save);
    }
    free(save);
}

int find_dollar(mysh_t *mysh, int i)
{
    char *var_name = NULL;
    char *dup = strdup(mysh->command_array[i]);

    var_name = strchr(dup, '$');
    if (var_name != NULL) {
        var_name++;
        if (var_name == NULL) {
            free(dup);
            return -1;
        }
        if (get_variable_value(mysh, var_name))
            replace_command(mysh, i, get_variable_value(mysh, var_name));
        else {
            free(dup);
            return 1;
        }
    }
    free(dup);
    return 0;
}

int replace_variable(mysh_t *mysh)
{
    static int limit_alias_loop = 0;

    if (set_alias(mysh, &limit_alias_loop) == 1)
        return 1;
    limit_alias_loop = 0;
    for (int i = 0; mysh->command_array[i]; i++) {
        if (find_dollar(mysh, i) == 1) {
            return 1;
        }
    }
    return 0;
}
