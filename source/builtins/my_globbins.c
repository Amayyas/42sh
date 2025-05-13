/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbins handle
*/

#include "my.h"
#include "globbins.h"

const globbins_t globbins[] = {
    {STAR},
    {Q_MARK},
    {OPEN_BRACKET},
    {CLOSE_BRACKET},
    {OPEN_GROUP},
    {CLOSE_GROUP},
    {TILDE},
    {'0'}
};

void glob_error(mysh_t *mysh, int ret)
{
    switch (ret) {
        case GLOB_NOMATCH:
            fprintf(stderr, "%s: No match.\n", mysh->command_array[0]);
            break;
        case GLOB_NOSPACE:
            fprintf(stderr, "42sh: glob: Out of memory\n");
            break;
        case GLOB_ABORTED:
            fprintf(stderr, "42sh: glob: Read error\n");
            break;
        default:
            fprintf(stderr, "%s: event not found.\n",
                mysh->command_array[0]);
            break;
    }
    mysh->ret_value = 1;
}

static void apply_glob_results(mysh_t *mysh, int index,
    int orig_count, glob_t *results)
{
    int glob_count = results->gl_pathc;
    int total_count = orig_count + glob_count - 1;

    mysh->command_array =
        realloc(mysh->command_array, sizeof(char *) * (total_count + 1));
    for (int i = orig_count - 1; i > index; i--)
        mysh->command_array[i + glob_count - 1] = mysh->command_array[i];
    for (int j = 0; j < glob_count; j++)
        mysh->command_array[index + j] = strdup(results->gl_pathv[j]);
    mysh->command_array[total_count] = NULL;
    mysh->ret_value = 0;
}

void handle_globbins(mysh_t *mysh, int index)
{
    glob_t results;
    int orig_count = 0;
    int ret = 0;

    while (mysh->command_array[orig_count] != NULL)
        orig_count++;
    ret = glob(mysh->command_array[index], GLOB_TILDE_CHECK, NULL, &results);
    if (ret == 0)
        apply_glob_results(mysh, index, orig_count, &results);
    else
        glob_error(mysh, ret);
    globfree(&results);
}

bool search_glob(mysh_t *mysh, int i, int index)
{
    for (int j = 0; globbins[j].glob != '0'; j++) {
        if (mysh->command_array[index][i] == globbins[j].glob) {
            handle_globbins(mysh, index);
            return true;
        }
    }
    return false;
}

int replace_globbins(mysh_t *mysh)
{
    bool skip = false;

    mysh->ret_value = 0;
    for (int index = 0; mysh->command_array[index] != NULL; index++) {
        for (int i = 0; mysh->command_array[index][i] != '\0' && !skip; i++)
            skip = search_glob(mysh, i, index);
    }
    if (mysh->ret_value == 1)
        return 84;
    return 0;
}
