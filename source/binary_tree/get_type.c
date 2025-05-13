/*
** EPITECH PROJECT, 2025
** get type
** File description:
** get the type of an str (if its a separator or a command)
*/

#include "my.h"

int get_node_type(char *str)
{
    if (my_strcmp(str, "|") == 0)
        return PIPE;
    if (my_strcmp(str, ";") == 0)
        return SEMICOLON;
    if (my_strcmp(str, "&&") == 0)
        return AND;
    if (my_strcmp(str, "||") == 0)
        return OR;
    if (my_strcmp(str, ">") == 0 || my_strcmp(str, "<") == 0 ||
        my_strcmp(str, ">>") == 0 || my_strcmp(str, "<<") == 0)
        return REDIRECTION;
    return COMMAND;
}

/// @brief return the type of the str (separator or command)
/// @param str str to check
/// @return "|" PIPE == 2, ";" SEMICOLON == 1, ">" REDIRECTION == 3,
/// @return "<" REDIRECTION == 3, ">>" REDIRECTION == 3,
/// @return "<<" REDIRECTION == 3, COMMAND == 0
/// @return "&&" AND == 5, "||" OR == 4
int get_type(char *str)
{
    int start = 0;
    int end_index = my_strlen(str) - 1;

    while (str[start] == ' ')
        start++;
    while (end_index > start && str[end_index] == ' ') {
        str[end_index] = '\0';
        end_index--;
    }
    str += start;
    return get_node_type(str);
}
