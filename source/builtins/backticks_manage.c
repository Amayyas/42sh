/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** init_backticks function
*/

#include "my.h"

void free_ticks(mysh_t *mysh, char **ticks_array, bin_tree_t *root)
{
    free(mysh->command);
    free(mysh->color);
    free_bin_tree(root);
    free_array(ticks_array);
    free_all_ll(mysh);
    free_array(mysh->env);
    free(mysh->termios_data);
    free(mysh->path_line);
    free(mysh->home_line);
    free(mysh);
}

void exec_ticks(mysh_t *mysh, int fd[2], char *ticks_str)
{
    bin_tree_t *root = NULL;
    char **ticks_array = NULL;

    ticks_array = my_strtoword_array(ticks_str);
    if (ticks_str)
        free(ticks_str);
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    root = create_bin_tree(ticks_array, 0, my_arraylen(ticks_array) - 1);
    exec_tree(mysh, root);
    free_ticks(mysh, ticks_array, root);
    exit(0);
}

char *get_output(FILE *file)
{
    char *line = NULL;
    size_t size = 0;
    int len = MAX_LENGHT;
    char *output = malloc(sizeof(char) * len);

    output[0] = '\0';
    while (getline(&line, &size, file) != -1) {
        if (line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        if (my_strlen(line) >= len) {
            len += my_strlen(line);
            output = realloc(output, sizeof(char) * len + 1);
        }
        my_strcat(output, line);
        my_strcat(output, " ");
    }
    output[my_strlen(output) - 1] = '\0';
    free(line);
    return output;
}

static char *change_cmd(FILE *file)
{
    if (!file) {
        perror("fdopen");
        return NULL;
    }
    return get_output(file);
}

static char *ticks(mysh_t *mysh, int i)
{
    pid_t pid = -1;
    int fd[2];
    FILE *file = NULL;
    char *output = NULL;
    char *ticks_str = NULL;

    ticks_str = my_strdup_char(mysh->command + i, TICK);
    pipe(fd);
    pid = fork();
    if (pid == 0)
        exec_ticks(mysh, fd, ticks_str);
    else if (pid > 0) {
        close(fd[1]);
        file = fdopen(fd[0], "r");
        output = change_cmd(file);
        fclose(file);
    }
    free(ticks_str);
    return output;
}

static int find_close_ticks(mysh_t *mysh)
{
    int j = 0;

    while (mysh->command[j] != TICK && mysh->command[j] != '\0')
        j++;
    j++;
    while (mysh->command[j] != TICK && mysh->command[j] != '\0')
        j++;
    return j;
}

void edit_cmd_ticks(mysh_t *mysh, char *output, int i)
{
    char *new_cmd = malloc(sizeof(char) * (my_strlen(mysh->command)
    + my_strlen(output) + 1));
    int close = 0;

    new_cmd[0] = '\0';
    my_strncpy(new_cmd, mysh->command, i);
    my_strcat(new_cmd, output);
    close = find_close_ticks(mysh);
    my_strcat(new_cmd, mysh->command + close + 1);
    free(mysh->command);
    mysh->command = my_strdup(new_cmd);
    free(new_cmd);
    free(output);
    return;
}

void set_backticks(mysh_t *mysh)
{
    int i = 0;
    char *output = NULL;

    for (; mysh->command[i]; i++) {
        if (mysh->command[i] == TICK) {
            output = ticks(mysh, i + 1);
            edit_cmd_ticks(mysh, output, i);
            break;
        }
    }
}
