/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** is exit function call
*/

#include "my.h"

static void exit_free(mysh_t *mysh)
{
    free(mysh->color);
    free(mysh->path_line);
    free(mysh->home_line);
    free(mysh->termios_data);
    free_all(mysh);
}

static void print_goodbye(void)
{
    printf("\n-----------------------------------------\n");
    printf("|            Goodbye!                   |\n");
    printf("| Thank you for using the 42sh shell.   |\n");
    printf("|                                       |\n");
    printf("| Made by:                              |\n");
    printf("|   - Aouadene Amayyas                  |\n");
    printf("|   - Aberkane Mathys EL GOAT           |\n");
    printf("|   - COMBE--BRACCIALE Nielsen          |\n");
    printf("|                                       |\n");
    printf("| From the Epitech school.              |\n");
    printf("| See readme for more details.          |\n");
    printf("-----------------------------------------\n\n");
}

bool is_exit(mysh_t *mysh, bin_tree_t *node)
{
    int return_value = 0;

    if (my_strcmp(node->command[0], "exit") == 0) {
        if (node->command[1] != NULL
        && (node->command[2] != NULL || !my_isdigit(node->command[1]))) {
            mini_printstderr("exit: Expression Syntax.\n");
            mysh->ret_value = 1;
            return true;
        }
        if (node->command[1] != NULL && my_isdigit(node->command[1]))
            return_value = my_atoi(node->command[1]);
        if (isatty(0) == 1)
            print_goodbye();
        exit_free(mysh);
        exit(return_value);
    }
    return false;
}
