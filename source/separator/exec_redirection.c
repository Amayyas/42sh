/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** exec redirection handler
*/

#include "my.h"

static void free_redirection(mysh_t *mysh)
{
    free(mysh->color);
    free(mysh->path_line);
    free(mysh->home_line);
    free(mysh->termios_data);
    free_all(mysh);
}

int check_right_node(mysh_t *mysh, bin_tree_t *node)
{
    if (!node->right) {
        mini_printstderr("Missing name for redirect.\n");
        mysh->ret_value = 1;
        return 1;
    }
    return 0;
}

static void check_error_redirection(mysh_t *mysh, pid_t pid, int fd)
{
    int status;

    waitpid(pid, &status, 0);
    if (status >= 1)
        mysh->ret_value = 1;
    close(fd);
}

void error_cant_open(bin_tree_t *node)
{
    if (access(node->right->command[0], F_OK) != 0) {
        mini_printstderr("%s: No such file or directory.\n",
            node->right->command[0]);
        exit(1);
    }
    mini_printstderr("%s: Permission denied.\n",
        node->right->command[0]);
    exit(1);
}

void append_output_redirection(mysh_t *mysh, bin_tree_t *node)
{
    int fd;
    pid_t pid;
    int ret = 0;

    if (check_right_node(mysh, node) == 1)
        return;
    fd = open(node->right->command[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1)
        error_cant_open(node);
    pid = fork();
    if (pid == -1)
        exit(-1);
    if (pid == 0) {
        dup2(fd, 1);
        ret = exec_tree(mysh, node->left);
        free_redirection(mysh);
        exit(ret);
    } else
        check_error_redirection(mysh, pid, fd);
}

void output_redirection(mysh_t *mysh, bin_tree_t *node)
{
    int fd;
    pid_t pid;
    int ret = 0;

    if (check_right_node(mysh, node) == 1)
        return;
    fd = open(node->right->command[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
        error_cant_open(node);
    pid = fork();
    if (pid == -1)
        exit(84);
    if (pid == 0) {
        dup2(fd, 1);
        ret = exec_tree(mysh, node->left);
        free_redirection(mysh);
        exit(ret);
    } else
        check_error_redirection(mysh, pid, fd);
}

static void input_redirection(mysh_t *mysh, bin_tree_t *node)
{
    int fd;
    pid_t pid;
    int ret = 0;

    fd = open(node->right->command[0], O_RDONLY);
    if (fd == -1)
        error_cant_open(node);
    pid = fork();
    if (pid == -1)
        exit(84);
    if (pid == 0) {
        dup2(fd, 0);
        ret = exec_tree(mysh, node->left);
        free_redirection(mysh);
        exit(ret);
    } else
        check_error_redirection(mysh, pid, fd);
}

static int handling_error_redirection(bin_tree_t *node)
{
    if (node->right == NULL) {
        mini_printstderr("Missing name for redirect.\n");
        return 84;
    }
    if (node->left == NULL) {
        mini_printstderr("Invalid null command.\n");
        return 84;
    }
    return 0;
}

void exec_redirection(mysh_t *mysh, bin_tree_t *node)
{
    if (handling_error_redirection(node) == 84) {
        mysh->ret_value = 1;
        return;
    }
    if (my_strcmp(node->redirection, ">") == 0)
        output_redirection(mysh, node);
    if (my_strcmp(node->redirection, "<") == 0)
        input_redirection(mysh, node);
    if (my_strcmp(node->redirection, ">>") == 0)
        append_output_redirection(mysh, node);
    if (my_strcmp(node->redirection, "<<") == 0)
        here_document(mysh, node);
}
