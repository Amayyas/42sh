/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** is setcolor function call
*/

#include "my.h"

bool setcolor_error3(char *argument, mysh_t *mysh)
{
    if (my_strcmp(argument, "CYAN") == 0) {
        free(mysh->color);
        mysh->color = my_strdup(CYAN);
        return true;
    }
    if (my_strcmp(argument, "RESET") == 0) {
        free(mysh->color);
        mysh->color = my_strdup(RESET);
        return true;
    }
    return false;
}

bool setcolor_error2(char *argument, mysh_t *mysh)
{
    if (my_strcmp(argument, "BLUE") == 0) {
        free(mysh->color);
        mysh->color = my_strdup(BLUE);
        return true;
    }
    if (my_strcmp(argument, "MAGENTA") == 0) {
        free(mysh->color);
        mysh->color = my_strdup(MAGENTA);
        return true;
    }
    if (setcolor_error3(argument, mysh))
        return true;
    return false;
}

bool setcolor_error(char *argument, mysh_t *mysh)
{
    if (my_strcmp(argument, "RED") == 0) {
        free(mysh->color);
        mysh->color = my_strdup(RED);
        return true;
    }
    if (my_strcmp(argument, "GREEN") == 0) {
        free(mysh->color);
        mysh->color = my_strdup(GREEN);
        return true;
    }
    if (my_strcmp(argument, "YELLOW") == 0) {
        free(mysh->color);
        mysh->color = my_strdup(YELLOW);
        return true;
    }
    if (setcolor_error2(argument, mysh))
        return true;
    return false;
}

void print_setcolorusage(void)
{
    mini_printf("USAGE:\n\tsetcolor [COLOR]\n");
    mini_printf("COLOR:\n\tRED\n\tGREEN\n\tYELLOW\n");
    mini_printf("\tBLUE\n\tMAGENTA\n\tCYAN\n\tRESET\n");
}

bool is_setcolor(mysh_t *mysh, bin_tree_t *node)
{
    if (my_strcmp(node->command[0], "setcolor") == 0) {
        if (node->command[1] == NULL
        || my_strcmp(node->command[1], "-h") == 0) {
            print_setcolorusage();
            mysh->ret_value = 0;
            return true;
        }
        if (node->command[2] != NULL) {
            mini_printstderr("setcolor: To much argument in function call\n");
            mysh->ret_value = 1;
            return true;
        }
        if (!setcolor_error(node->command[1], mysh)) {
            mini_printstderr("setcolor: color unavailable\n");
            mysh->ret_value = 1;
            return true;
        }
        return true;
    }
    return false;
}
