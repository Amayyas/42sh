/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** main minishell
*/

#include "my.h"
#include "termios_interface.h"

static void print_welcome(void)
{
    system("toilet -f mono12 -F metal '42sh'");
    printf("-----------------------------------------\n");
    printf("| Welcome to the 42sh shell.\t\t|\n");
    printf("| Type 'exit' to leave the shell.\t|\n|\t\t\t\t\t|\n");
    printf("| Made by:\t\t\t\t|\n");
    printf("|   - Aouadene Amayyas\t\t\t|\n");
    printf("|   - Aberkane Mathys GOAT\t\t|\n");
    printf("|   - COMBE--BRACCIALE Nielsen\t\t|\n|\t\t\t\t\t|\n");
    printf("| From the Epitech school.\t\t|\n");
    printf("| See readme for more details.\t\t|\n");
    printf("-----------------------------------------\n\n");
}

static void init_struct_bis(mysh_t *mysh)
{
    mysh->termios_data = malloc(sizeof(termios_data_t));
    mysh->termios_data->ch = '\0';
    mysh->termios_data->cursor_pos = 0;
    mysh->termios_data->len_line = 0;
    mysh->termios_data->line[0] = '\0';
    mysh->history = NULL;
    mysh->history_cursor = NULL;
    memset(mysh->saved_line, 0, BUFSIZ);
    return;
}

int init_struct(mysh_t *mysh, char **env)
{
    if (isatty(0) == 1)
        print_welcome();
    mysh->command = NULL;
    mysh->command_array = NULL;
    mysh->env = my_arraydup(env);
    mysh->ret_value = 0;
    mysh->path_line = my_strdup("/usr/bin");
    mysh->home_line = NULL;
    mysh->color = my_strdup(RESET);
    mysh->variables = NULL;
    mysh->alias = NULL;
    mysh->par = NULL;
    mysh->ticks = NULL;
    mysh->root = NULL;
    init_struct_bis(mysh);
    return 0;
}

void error_handling(int argc, char **argv)
{
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0) {
        mini_printf("Usage:\t./mysh to launch the terminal.\n");
        exit(0);
    }
    if (argc != 1) {
        mini_printstderr("No argument to start the shell\n");
        exit(84);
    }
}

void exec_interface(mysh_t *mysh)
{
    if (isatty(0) == 1) {
        enable_raw_mode();
        get_stdin(mysh);
        disable_raw_mode();
    } else
        get_stdin_tty(mysh);
}

static void process_bang_command(mysh_t *mysh)
{
    char *original_cmd = NULL;
    char *new_cmd = NULL;

    if (mysh->command[0] != '!')
        return;
    original_cmd = my_strdup(mysh->command);
    new_cmd = handle_bang_command(mysh, original_cmd);
    if (new_cmd == NULL) {
        free(original_cmd);
        return;
    }
    if (new_cmd != original_cmd) {
        free(mysh->command);
        mysh->command = new_cmd;
    }
    free(original_cmd);
}

static int process_command(mysh_t *mysh)
{
    if (mysh->command[0] != '\0')
        add_to_history(mysh);
    edit_command_manage(mysh);
    mysh->command_array = my_strtoword_array(mysh->command);
    if (replace_variable(mysh) == 1)
        return 1;
    if (replace_globbins(mysh) == 84)
        return 1;
    mysh->root = create_bin_tree(mysh->command_array, 0,
        my_arraylen(mysh->command_array) - 1);
    mysh->ret_value = 0;
    exec_tree(mysh, mysh->root);
    return 0;
}

void execute_shell(mysh_t *mysh)
{
    history_t *save = mysh->history;

    handle_path_env(mysh);
    mysh->is_empty = false;
    exec_interface(mysh);
    mysh->history = save;
    if (mysh->is_empty == true)
        return;
    process_bang_command(mysh);
    if (process_command(mysh) == 1) {
        free_array(mysh->command_array);
        if (mysh->command != NULL)
            free(mysh->command);
        mysh->command = NULL;
        return;
    }
    free_all_command(mysh);
}

int main(int argc, char **argv, char **env)
{
    mysh_t *mysh;

    error_handling(argc, argv);
    mysh = malloc(sizeof(mysh_t));
    init_struct(mysh, env);
    while (true) {
        execute_shell(mysh);
    }
    return 0;
}
