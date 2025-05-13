/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** change directory
*/

#include "my.h"

void go_to_filepath(mysh_t *mysh, char *filepath, bool *is_error)
{
    if (chdir(filepath) == -1) {
        mini_printstderr("%s: %s.\n", filepath, strerror(errno));
        mysh->ret_value = 1;
        *is_error = true;
    }
}

void handle_home(mysh_t *mysh, char *home, bool *is_error)
{
    if (chdir(home) == -1) {
        mini_printstderr("cd: Can't change to home directory.\n");
        mysh->ret_value = 1;
        *is_error = true;
    }
}

void handle_oldpwd(mysh_t *mysh, char *oldpwd, bool *change_env, bool *is_err)
{
    if (oldpwd == NULL) {
        mini_printstderr(": No such file or directory.\n");
        mysh->ret_value = 1;
        *change_env = true;
        *is_err = true;
    } else {
        chdir(oldpwd);
    }
}

void update_env(mysh_t *mysh, char *pwd, char *oldpwd)
{
    my_setenv(mysh, "PWD", pwd);
    my_setenv(mysh, "OLDPWD", oldpwd);
    mysh->ret_value = 1;
}

void my_cd(mysh_t *mysh, char *filepath)
{
    bool is_error = false;
    bool change_env = false;
    char pwd[MAX_LENGHT];
    char oldpwd[MAX_LENGHT];
    char *oldpwd_path = env_parser(mysh, "OLDPWD");

    getcwd(oldpwd, MAX_LENGHT);
    if (filepath == NULL || my_strcmp(filepath, "~") == 0)
        handle_home(mysh, mysh->home_line, &is_error);
    else if (my_strcmp(filepath, "-") == 0)
        handle_oldpwd(mysh, oldpwd_path, &change_env, &is_error);
    else
        go_to_filepath(mysh, filepath, &is_error);
    getcwd(pwd, MAX_LENGHT);
    if (!change_env)
        update_env(mysh, pwd, oldpwd);
    if (!is_error)
        mysh->ret_value = 0;
    free(oldpwd_path);
}
