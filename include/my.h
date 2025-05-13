/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my.h
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <signal.h>
#include <wait.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
#include "termios_interface.h"

#ifndef MY_H
    #define MY_H
    #define MAX_LENGHT 1024
    #define RED     "\x1b[31m"
    #define GREEN   "\x1b[32m"
    #define YELLOW  "\x1b[33m"
    #define BLUE    "\x1b[34m"
    #define MAGENTA "\x1b[35m"
    #define CYAN    "\x1b[36m"
    #define RESET   "\x1b[0m"
    #define OPEN_PAR '('
    #define CLOSE_PAR ')'
    #define TICK '`'

    //node type
typedef enum node_type {
    COMMAND = 0,
    SEMICOLON = 1,
    PIPE = 2,
    REDIRECTION = 3,
    OR = 4,
    AND = 5
} node_type_t;

typedef struct variables {
    char *name;
    char *value;
    struct variables *next;
} variables_t;

typedef struct alias {
    char *key;
    char *value;
    struct alias *next;
} alias_t;

typedef struct par {
    int key;
    char **value;
    struct par *next;
} par_t;

typedef struct ticks {
    int key;
    char **value;
    struct ticks *next;
} ticks_t;

typedef struct history {
    char *command;
    int id;
    char *date;
    struct history *next;
    struct history *prev;
} history_t;

typedef struct binary_tree {
    enum node_type type;
    char **command;
    char *redirection;
    struct binary_tree *left;
    struct binary_tree *right;
} bin_tree_t;

typedef struct mysh {
    char *command;
    char **command_array;
    char **env;
    bool is_empty;
    int ret_value;
    char *path_line;
    char *home_line;
    char *color;
    variables_t *variables;
    alias_t *alias;
    par_t *par;
    ticks_t *ticks;
    history_t *history;
    history_t *history_cursor;
    char saved_line[BUFSIZ];
    bin_tree_t *root;
    termios_data_t *termios_data;
    int prompt_len;
} mysh_t;

/// termios
void handle_ctrl_y(mysh_t *mysh);
void handle_ctrl_w(mysh_t *mysh);
void handle_ctrl_a(mysh_t *mysh);
void handle_ctrl_d(mysh_t *mysh);
void handle_ctrl_l(mysh_t *mysh);
void arrows(mysh_t *mysh, char arrow);
void history_arrows(mysh_t *mysh, char arrow);
void suppr(mysh_t *mysh);
void handle_backspace(mysh_t *mysh);
void reset_termios(mysh_t *mysh);
/// lib
variables_t *add_node_start(variables_t *variables, char *name, char *value);
int replace_globbins(mysh_t *mysh);
bool compare_str(void *str1, void *str2);
alias_t *tri_fusion(alias_t *head,
    bool(*sort_func)(void *value1, void *value2));
void free_all_ll(mysh_t *mysh);
void free_ll_history(history_t *history);
void free_ll_ticks(ticks_t *ticks);
void free_ll_par(par_t *par);
void free_ll_alias(alias_t *alias);
void free_ll_variables(variables_t *variables);
char *array_to_str(char **array);
char *get_cmd_value(mysh_t *mysh, char *name, char *value);
void set_backticks(mysh_t *mysh);
void init_parentheses(mysh_t *mysh);
void exec_parentheses(mysh_t *mysh, bin_tree_t *node);
char *my_inttostring(int num);
void edit_command_manage(mysh_t *mysh);
char *my_strdup_char(char *str, char c);
int set_alias(mysh_t *mysh, int *limit);
int is_alias(mysh_t *mysh, bin_tree_t *node);
void print_alias(alias_t *alias);
void add_alias(mysh_t *mysh, char *key, char *value);
int len_tab(char **array);
bool is_history(mysh_t *mysh, bin_tree_t *node);
void add_to_history(mysh_t *mysh);
int replace_variable(mysh_t *mysh);
int or_redirection(mysh_t *mysh, bin_tree_t *node);
int and_redirection(mysh_t *mysh, bin_tree_t *node);
int get_stdin_tty(mysh_t *mysh);
void terminal_line(mysh_t *mysh);
int my_set(mysh_t *mysh, char *command);
bool is_set(mysh_t *mysh, bin_tree_t *node);
int get_type(char *str);
bool myisdigits(const char *str);
bool my_isalpha(char c);
bool my_isalnum(char c);
bool is_cd(mysh_t *mysh, bin_tree_t *node);
bool is_env(mysh_t *mysh, bin_tree_t *node);
bool my_isdigit(char *str);
int mini_printstderr(const char *format, ...);
bool is_exit(mysh_t *mysh, bin_tree_t *node);
bool is_setenv(mysh_t *mysh, bin_tree_t *node);
int my_atoi(const char *str);
bool is_unsetenv(mysh_t *mysh, bin_tree_t *node);
void here_document(mysh_t *mysh, bin_tree_t *node);
void free_all(mysh_t *mysh);
int file_exists(char *path);
int get_stdin(mysh_t *mysh);
void handle_ctrlc(int sigid);
int my_arraylen(char **array);
void free_array(char **array);
bool is_setcolor(mysh_t *mysh, bin_tree_t *node);
bool is_builtins(mysh_t *mysh, bin_tree_t *node);
int my_strlen(char const *str);
char *my_strncpy(char *dest, char *src, int n);
void my_print_env(mysh_t *mysh);
char **my_arraydup(char **array);
char *my_strdup(const char *src);
void handle_home_env(mysh_t *mysh);
void handle_path_env(mysh_t *mysh);
bool is_separator(bin_tree_t *node);
void free_all_command(mysh_t *mysh);
void free_bin_tree(bin_tree_t *node);
int special_char(char c);
int count_tokens(char *str);
void skip_whitespace(char *str, int *i);
char *get_next_token(char *str, int *i);
int fill_array(char **array, char *str, int max_tokens);
char **my_strtoword_array(char *str);
int mini_printf(const char *format, ...);
void my_cd(mysh_t *mysh, char *filepath);
bool is_inenv(char **env, char *search);
void my_unsetenv(mysh_t *mysh, char *name);
int signal_handler(mysh_t *mysh, int sigid);
char *my_strcat(char *dest, char const *src);
char *my_strcpy(char *dest, char const *src);
char *env_parser(mysh_t *mysh, char *search);
int my_strcmp(char const *s1, char const *s2);
void exec_pipe(mysh_t *mysh, bin_tree_t *node);
int exec_tree(mysh_t *mysh, bin_tree_t *node);
int new_process(bin_tree_t *node, mysh_t *mysh);
int execute_command(bin_tree_t *node, mysh_t *mysh);
void exec_redirection(mysh_t *mysh, bin_tree_t *node);
void my_setenv(mysh_t *mysh, char *name, char *value);
int my_strncmp(char const *s1, char const *s2, int n);
void print_tree(bin_tree_t *node, int depth, const char *side);
bin_tree_t *create_bin_tree(char **command_array, int start, int end);
char *handle_bang_command(mysh_t *mysh, char *cmd);
char *find_command_by_prefix(mysh_t *mysh, const char *prefix);
char *find_command_by_number(mysh_t *mysh, int num);

#endif /* MY_H */
