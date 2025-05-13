/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** handle terminal signals
*/

#include "my.h"

void handle_ctrlc(int sigid)
{
    sigid = WTERMSIG(sigid);
    if (sigid == SIGINT)
        return;
}

int is_coredump(mysh_t *mysh, int sigid, char *str)
{
    if (__WCOREDUMP(sigid)) {
        str = realloc(str, strlen(str) + strlen(" (core dumped)\n") + 1);
        strcpy(str + (strlen(str) - 1), " (core dumped)\n");
        mini_printstderr("%s", str);
        return mysh->ret_value;
    }
    if (str)
        mini_printstderr("%s", str);
    return mysh->ret_value;
}

void set_signal(mysh_t *mysh, int sigid, char **str)
{
    switch WTERMSIG(sigid) {
        case SIGTERM:
            *str = strdup("terminated\n");
            mysh->ret_value = 143;
            break;
        case SIGKILL:
            *str = strdup("Killed.\n");
            mysh->ret_value = 137;
            break;
        case SIGSEGV:
            *str = strdup("Segmentation fault\n");
            mysh->ret_value = 139;
            break;
        case SIGFPE:
            *str = strdup("Floating exception\n");
            mysh->ret_value = 136;
            break;
    }
}

int signal_handler(mysh_t *mysh, int sigid)
{
    char *str = NULL;

    if (sigid >= 1)
        mysh->ret_value = 1;
    set_signal(mysh, sigid, &str);
    return is_coredump(mysh, sigid, str);
}
