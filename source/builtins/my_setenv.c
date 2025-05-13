/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** setenv recode
*/

#include "my.h"

bool is_name_valid(char *name)
{
    if (name == NULL || name[0] == '\0' || !my_isalpha(name[0])) {
        mini_printstderr("setenv: Variable name must begin with a letter.\n");
        return false;
    }
    for (int i = 1; name[i] != '\0'; i++) {
        if (!my_isalnum(name[i]) && name[i] != '_') {
            mini_printstderr("setenv: Variable name must contain ");
            mini_printstderr("alphanumeric characters.\n");
            return false;
        }
    }
    return true;
}

char *get_newline_replace(mysh_t *mysh, char *name, char *value)
{
    char *new_line = NULL;
    int len_name = my_strlen(name);
    int total_len = len_name + my_strlen(value) + 2;

    if (value[0] == TICK)
        new_line = get_cmd_value(mysh, name, value);
    else {
        new_line = malloc(sizeof(char) * total_len);
        my_strcpy(new_line, name);
        new_line[len_name] = '=';
        my_strcpy(new_line + len_name + 1, value);
    }
    return new_line;
}

void replace_envvalue(mysh_t *mysh, char *name, char *value, int index)
{
    int env_size;
    char **new_env_array;
    char *new_line = get_newline_replace(mysh, name, value);

    for (env_size = 0; mysh->env[env_size] != NULL; env_size++);
    new_env_array = malloc(sizeof(char *) * (env_size + 1));
    for (int i = 0; i < env_size; i++)
        new_env_array[i] = my_strdup(mysh->env[i]);
    free(new_env_array[index]);
    new_env_array[index] = new_line;
    new_env_array[env_size] = NULL;
    free_array(mysh->env);
    mysh->env = new_env_array;
}

void add_envvalue(mysh_t *mysh, char *name, char *value)
{
    int env_size;
    char **new_env_array;
    char *new_line = get_newline_replace(mysh, name, value);

    for (env_size = 0; mysh->env[env_size] != NULL; env_size++);
    new_env_array = malloc(sizeof(char *) * (env_size + 2));
    if (new_env_array == NULL) {
        free(new_line);
        return;
    }
    for (int i = 0; i < env_size; i++)
        new_env_array[i] = my_strdup(mysh->env[i]);
    new_env_array[env_size] = my_strdup(new_line);
    new_env_array[env_size + 1] = NULL;
    free_array(mysh->env);
    free(new_line);
    mysh->env = new_env_array;
}

void my_setenv(mysh_t *mysh, char *name, char *value)
{
    int len_name = my_strlen(name);

    if (!is_name_valid(name)) {
        mysh->ret_value = 1;
        return;
    }
    for (int i = 0; mysh->env[i] != NULL; i++) {
        if (my_strncmp(mysh->env[i], name, len_name) == 0) {
            replace_envvalue(mysh, name, value, i);
            mysh->ret_value = 0;
            return;
        }
    }
    add_envvalue(mysh, name, value);
    mysh->ret_value = 0;
}
