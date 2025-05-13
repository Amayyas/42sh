/*
** EPITECH PROJECT, 2025
** minishell 1
** File description:
** create a new process
*/

#include "my.h"

void find_command(bin_tree_t *node, mysh_t *mysh)
{
    char *path_line_dup = my_strdup(mysh->path_line);
    char *bin_path = strtok(path_line_dup, ":");
    char full_path[MAX_LENGHT];

    while (bin_path != NULL) {
        my_strcpy(full_path, bin_path);
        my_strcat(full_path, "/");
        my_strcat(full_path, node->command[0]);
        if (file_exists(full_path)) {
            node->command[0] = my_strdup(full_path);
            free(path_line_dup);
            return;
        }
        bin_path = strtok(NULL, ":");
    }
    free(path_line_dup);
}

void fail_execve(mysh_t *mysh, bin_tree_t *node)
{
    mysh->ret_value = 1;
    mini_printstderr("%s", node->command[0]);
    if (errno == 8)
        mini_printstderr(": Exec format error. Binary file not executable.\n");
    else if (file_exists(mysh->command_array[0]) != 0)
        mini_printstderr(": Permission denied.\n");
    else
        mini_printstderr(": Command not found.\n");
    free(mysh->path_line);
    free(mysh->home_line);
    free(mysh->color);
    free(mysh->termios_data);
    free_all(mysh);
    exit(1);
}

int new_process(bin_tree_t *node, mysh_t *mysh)
{
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        find_command(node, mysh);
        execve(node->command[0], node->command, mysh->env);
        fail_execve(mysh, node);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        return signal_handler(mysh, status);
    } else {
        perror("fork");
        exit(1);
    }
    return 0;
}
