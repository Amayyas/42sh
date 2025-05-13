/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** backticks function
*/

#include "my.h"

static char **get_cmd_ticks(mysh_t *mysh, char *index)
{
    ticks_t *tmp = mysh->ticks;
    char *id = strtok(index, "`\0");
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

static void child(mysh_t *mysh, char *value)
{
    char **command_array = get_cmd_ticks(mysh, value + 1);

    if (!command_array)
        return;
}

int total_len(char **array)
{
    int len = 0;

    for (int i = 0; array[i]; i++) {
        for (int j = 0; array[i][j]; j++)
            len++;
        len++;
    }
    return len;
}

char *create_new_line(char **array, char *name)
{
    int len = total_len(array);
    char *new_line = my_strdup(name);
    int i = 0;

    new_line = realloc(new_line, len + (my_strlen(name) + 2));
    my_strcat(new_line, "=");
    i = my_strlen(new_line);
    for (int j = 0; array[j]; j++) {
        for (int k = 0; array[j][k]; k++) {
            new_line[i] = array[j][k];
            i++;
        }
        if (array[j + 1]) {
            new_line[i] = ' ';
            i++;
        }
    }
    new_line[i] = '\0';
    return new_line;
}

char **get_array_output(FILE *file)
{
    char *line = NULL;
    size_t size = 0;
    int i = 0;
    int len = 2;
    char **buffer = malloc(sizeof(char *) * len);

    buffer[0] = '\0';
    while (getline(&line, &size, file) != -1) {
        if (line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        if (i >= len - 1) {
            len += 1;
            buffer = realloc(buffer, sizeof(char *) * len);
        }
        buffer[i] = my_strdup(line);
        i++;
    }
    buffer[i] = NULL;
    free(line);
    return buffer;
}

static char *parent(FILE *file, char *name)
{
    char *new_line = NULL;
    char **buffer = NULL;

    if (!file) {
        perror("fdopen");
        return NULL;
    }
    buffer = get_array_output(file);
    new_line = create_new_line(buffer, name);
    free_array(buffer);
    return new_line;
}

// q? si execve exit alors comment les free marche ?
char *get_cmd_value(mysh_t *mysh, char *name, char *value)
{
    pid_t pid = -1;
    int fd[2];
    FILE *file = NULL;
    char *output = NULL;

    pipe(fd);
    pid = fork();
    if (pid == 0) {
        child(mysh, value);
    } else if (pid > 0) {
        output = parent(file, name);
        fclose(file);
        return output;
    }
    return NULL;
}
