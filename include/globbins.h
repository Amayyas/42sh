/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbins header file
*/

#include <glob.h>

#ifndef GLOBBINS_H
    #define GLOBBINS_H
    #define STAR '*'
    #define Q_MARK '?'
    #define OPEN_BRACKET '['
    #define CLOSE_BRACKET ']'
    #define OPEN_GROUP '{'
    #define CLOSE_GROUP '}'
    #define TILDE '~'

typedef struct globbins {
    char glob;
} globbins_t;

#endif /* !GLOBBINS_H */
