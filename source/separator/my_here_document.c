/*
** EPITECH PROJECT, 2025
** >>
** File description:
** remake the here document
*/

#include "my.h"

static void free_heredoc(mysh_t *mysh)
{
    free(mysh->color);
    free(mysh->path_line);
    free(mysh->home_line);
    free(mysh->termios_data);
    free_all(mysh);
}

static char *concatenate_strings(char *buffer, char *buff)
{
    char *command = malloc(sizeof(char)
    * (my_strlen(buffer) + my_strlen(buff) + 2));

    command[0] = '\0';
    my_strcat(command, buffer);
    my_strcat(command, buff);
    my_strcat(command, "\n");
    return command;
}

static bool process_buffer(char **buffer, char *buff, const char *delimiter)
{
    char *command = NULL;

    if (my_strcmp(buff, delimiter) == 0)
        return false;
    else {
        command = concatenate_strings(*buffer, buff);
        free(*buffer);
        *buffer = command;
        return true;
    }
}

static bool getline_verif(int ret, bool *is_open)
{
    if (ret == 1)
        return true;
    if (ret == -1) {
        *is_open = false;
        return true;
    }
    return false;
}

char *heredoc_command(char *delimiter)
{
    bool is_open = true;
    char *buff = NULL;
    size_t buff_size = 0;
    int ret = 0;
    char *buffer = malloc(sizeof(char) * 1);

    buffer[0] = '\0';
    while (is_open) {
        mini_printf("? ");
        ret = getline(&buff, &buff_size, stdin);
        if (getline_verif(ret, &is_open))
            continue;
        buff[my_strlen(buff) - 1] = '\0';
        is_open = process_buffer(&buffer, buff, delimiter);
    }
    free(buff);
    return buffer;
}

static void close_and_wait(int fd[2], pid_t pid, char *command)
{
    close(fd[0]);
    write(fd[1], command, my_strlen(command));
    close(fd[1]);
    waitpid(pid, NULL, 0);
    free(command);
}

void here_document(mysh_t *mysh, bin_tree_t *node)
{
    char *command = heredoc_command(node->right->command[0]);
    int fd[2];
    pid_t pid;

    pipe(fd);
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        exec_tree(mysh, node->left);
        free(command);
        free_heredoc(mysh);
        close(fd[0]);
        exit(EXIT_SUCCESS);
    } else
        close_and_wait(fd, pid, command);
}
