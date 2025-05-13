/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** exec with pipe
*/

#include "my.h"

int handle_child(mysh_t *mysh, bin_tree_t *node, int pipefd[2])
{
    int ret = 0;

    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    exec_tree(mysh, node->left);
    ret = mysh->ret_value;
    free(mysh->color);
    free(mysh->path_line);
    free(mysh->home_line);
    free(mysh->termios_data);
    free_all(mysh);
    return ret;
}

int handle_child2(mysh_t *mysh, bin_tree_t *node, int pipefd[2])
{
    int ret = 0;

    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    exec_tree(mysh, node->right);
    ret = mysh->ret_value;
    free(mysh->color);
    free(mysh->path_line);
    free(mysh->home_line);
    free(mysh->termios_data);
    free_all(mysh);
    return ret;
}

void handle_error(char *str)
{
    perror(str);
    exit(84);
}

static int handling_error_pipe(bin_tree_t *node, mysh_t *mysh)
{
    if (node->left == NULL || node->right == NULL) {
        mini_printstderr("Invalid null command.\n");
        mysh->ret_value = 1;
        return 1;
    }
    return 0;
}

void close_pipes_and_wait(mysh_t *mysh, int pipefd[2], pid_t pid1, pid_t pid2)
{
    int status1;
    int status2;

    close(pipefd[0]);
    close(pipefd[1]);
    if (waitpid(pid1, &status1, 0) == -1)
        handle_error("waitpid");
    if (waitpid(pid2, &status2, 0) == -1)
        handle_error("waitpid");
    signal_handler(mysh, status1);
    signal_handler(mysh, status2);
}

static pid_t create_fork(void)
{
    pid_t pid = fork();

    if (pid == -1)
        handle_error("fork");
    return pid;
}

void exec_pipe(mysh_t *mysh, bin_tree_t *node)
{
    int pipefd[2];
    pid_t pid1;
    pid_t pid2;

    if (handling_error_pipe(node, mysh) == 1)
        return;
    if (pipe(pipefd) == -1)
        handle_error("pipe");
    pid1 = create_fork();
    if (pid1 == 0)
        exit(handle_child(mysh, node, pipefd));
    pid2 = create_fork();
    if (pid2 == 0)
        exit(handle_child2(mysh, node, pipefd));
    close_pipes_and_wait(mysh, pipefd, pid1, pid2);
}
