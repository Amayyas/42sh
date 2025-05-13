/*
** EPITECH PROJECT, 2025
** B-PSU-200-MPL-2-1-42sh-nielsen.combe-bracciale
** File description:
** count_tokens
*/

#include "my.h"

int special_char(char c)
{
    return (c == '|' || c == '>' || c == '<' || c == ';' || c == '&');
}

static int handle_special_chars(char *str, int i, int *count)
{
    if (i + 1 < my_strlen(str) && str[i] == str[i + 1] &&
    (str[i] == '&' || str[i] == '>' || str[i] == '<' || str[i] == '|')) {
        (*count)++;
        return 1;
    } else {
        (*count)++;
        return 0;
    }
}

static int skip_quoted_section(char *str, int i, char quote_type)
{
    int start = i;
    bool escaped = false;

    i++;
    while (str[i] && (str[i] != quote_type || escaped)) {
        if (str[i] == '\\' && !escaped)
            escaped = true;
        else
            escaped = false;
        i++;
    }
    if (str[i] == quote_type)
        i++;
    return i - start - 1;
}

static int handle_quoted_token(char *str, int i, int *in_word, int *count)
{
    if (!*in_word) {
        (*count)++;
        *in_word = 1;
    }
    return skip_quoted_section(str, i, str[i]);
}

static int handle_word_start(int *in_word, int *count)
{
    if (*in_word == 0) {
        (*count)++;
        *in_word = 1;
    }
    return 0;
}

int count_tokens(char *str)
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '"' || str[i] == '\'') {
            i += handle_quoted_token(str, i, &in_word, &count);
            continue;
        }
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
            in_word = 0;
            continue;
        }
        if (special_char(str[i])) {
            i += handle_special_chars(str, i, &count);
            in_word = 0;
            continue;
        }
        handle_word_start(&in_word, &count);
    }
    return count;
}
