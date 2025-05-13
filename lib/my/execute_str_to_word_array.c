/*
** EPITECH PROJECT, 2025
** my_strtoword_array
** File description:
** my_strtoword_array
*/

#include "my.h"

static char *extract_special_token(char *str, int *i)
{
    char *token;

    if (*i + 1 < my_strlen(str) && str[*i] == str[*i + 1] &&
    (str[*i] == '&' || str[*i] == '>' || str[*i] == '<' || str[*i] == '|')) {
        token = malloc(sizeof(char) * 3);
        if (token == NULL)
            return NULL;
        token[0] = str[*i];
        token[1] = str[*i];
        token[2] = '\0';
        *i += 2;
    } else {
        token = malloc(sizeof(char) * 2);
        if (token == NULL)
            return NULL;
        token[0] = str[*i];
        token[1] = '\0';
        (*i)++;
    }
    return token;
}

static int calculate_quoted_length(char *str, int i, char quote_type)
{
    int len = 1;
    bool escaped = false;

    i++;
    while (str[i] && (str[i] != quote_type || escaped)) {
        if (str[i] == '\\' && !escaped)
            escaped = true;
        else
            escaped = false;
        i++;
        len++;
    }
    if (str[i] == quote_type) {
        len++;
    }
    return len;
}

static void copy_quoted_content(char *token, char *str,
    int *i, char quote_type)
{
    int j = 0;
    bool escaped = false;

    (*i)++;
    while (str[*i] && (str[*i] != quote_type || escaped)) {
        if (str[*i] == '\\' && !escaped) {
            escaped = true;
            (*i)++;
            continue;
        }
        token[j] = str[*i];
        j++;
        (*i)++;
        escaped = false;
    }
    if (str[*i] == quote_type)
        (*i)++;
    token[j] = '\0';
}

static char *extract_quoted_word(char *str, int *i)
{
    char quote_type = str[*i];
    int len = calculate_quoted_length(str, *i, quote_type);
    char *token = malloc(sizeof(char) * (len + 1));

    if (token == NULL)
        return NULL;
    copy_quoted_content(token, str, i, quote_type);
    return token;
}

static int calculate_word_length(char *str, int start)
{
    int len = 0;
    int esc = 0;
    int i = start;

    while (str[i]) {
        if (str[i] == '\\' && !esc) {
            esc = 1;
            i++;
            len++;
            continue;
        }
        if ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
            special_char(str[i]) || str[i] == '"' || str[i] == '\'') && !esc)
            break;
        esc = 0;
        i++;
        len++;
    }
    return len;
}

static void copy_word_content(char *token, char *str, int *i, int len)
{
    int j = 0;
    int escape = 0;

    while (j < len) {
        if (str[*i] == '\\' && !escape) {
            escape = 1;
            (*i)++;
            continue;
        }
        token[j] = str[*i];
        j++;
        (*i)++;
        escape = 0;
    }
    token[j] = '\0';
}

static char *extract_word(char *str, int *i)
{
    int len = calculate_word_length(str, *i);
    char *token;

    if (len == 0)
        return NULL;
    token = malloc(sizeof(char) * (len + 1));
    if (token == NULL)
        return NULL;
    copy_word_content(token, str, i, len);
    return token;
}

void skip_whitespace(char *str, int *i)
{
    while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
        (*i)++;
}

char *get_next_token(char *str, int *i)
{
    char *token = NULL;

    if (str[*i] == '"' || str[*i] == '\'')
        token = extract_quoted_word(str, i);
    else if (special_char(str[*i]))
        token = extract_special_token(str, i);
    else
        token = extract_word(str, i);
    return token;
}
