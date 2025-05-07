/*
** EPITECH PROJECT, 2025
** structure_classic
** File description:
** project
*/

#ifndef PROJECT_H
    #define PROJECT_H
    #include <stdarg.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <time.h>
    #include <dirent.h>
    #include <ctype.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <string.h>
    #include <unistd.h>
    #include "struct_word_array.h"


// define keys

    #define KEY_LEFT 0x445B1B
    #define KEY_RIGHT 0x435B1B
    #define KEY_UP 0x415B1B
    #define KEY_DOWN 0x425B1B
    #define KEY_BACKSPACE 127
    #define KEY_DEL 0x7E335B1B

// Struct

typedef struct str_and_int_s {
    char *str;
    int i;
} str_and_int_t;

typedef struct pack_env_s {
    char *line;
    int idx;
    char *new_value;
    char *env_value;
} pack_env_t;

typedef struct env {
    char *line;
    int is_add;
    struct env *next;
} env_t;

typedef struct history_s {
    char *command;
    struct history_s *next;
    struct history_s *prev;
} history_t;

typedef struct builtin_s {
    char *command;
    int (*function)(char **args, env_t *head, char **env, int *exit_status);
} builtin_t;

typedef struct command_s {
    char *command;
    int (*function)(char **args, env_t *head, int *exit_status);
} command_t;

typedef struct pipe_command {
    char **cmd1;
    char **cmd2;
    int is_pipe;
    pid_t pid1;
    pid_t pid2;
    int fd[2];
} pipe_command_t;

typedef struct separator_s {
    int end;
    int start;
} separator_index_t;

typedef struct {
    char **args;
    env_t *head;
    int *exit_status;
} double_pipe_t;

typedef struct {
    char *line;
    char **line_ptr;
    int *pos;
    int *len;
    char c;
    int capacity;
} handle_ctrl_t;


// Builtin funtion

int is_builtin(env_t *head, char **args, char **env, int *last_exit_value);

int my_cd(char **args, env_t *head, char **env, int *exit_status);

int my_env(char **args, env_t *head, char **env, int *exit_status);

int my_exit(char **args, history_t *history);

int my_unsetenv(char **args, env_t *head, char **env, int *exit_status);

int my_setenv(char **args, env_t *head, char **env, int *exit_status);

env_t *home(env_t *head, pack_env_t *pack);

env_t *casual_add(char *str, char *new_value, env_t *head);

env_t *one_arg(env_t *head, char *arg);

int my_echo(char **args, env_t *head, char **env, int *exit_status);

int my_which(char **args, env_t *head, char **env, int *exit_status);

int my_where(char **args, env_t *head, char **env, int *exit_status);

// Linked list

env_t *def_linked_list(char *line, int status, char **env);

env_t *add_node(env_t *head, char *line, int status);

void print_list(env_t *head);

void free_list(env_t *head);

void free_env_array(char **env_array);

char **convert_env_to_array(env_t *head);

history_t *def_linked_list_history(FILE *history_file);

history_t *add_command_to_history(history_t *head, char *command);

void print_history(history_t *head);

void free_history(history_t *head);

// Exec function

int exec_pipe_command(pipe_command_t *commands, env_t *env, int *exit_status);

void execute_segment(char **args,
    env_t *head, int *exit_status, separator_index_t *index);

void execute_last_command(char **args,
    env_t *head, int *exit_status, separator_index_t *index);

int handle_double_ampersand(char **args, env_t *head, int *exit_status);

int handle_double_pipe(char **args, env_t *head, int *exit_status);

void execute_command(char **args, env_t *head, int *exit_status);

int handle_semicolon(char **args, env_t *head, int *exit_status);

int handle_pipes(char **args, env_t *head, int *exit_status);

int redirection(char **args);

int is_command(env_t *head, char **args, int *exit_status);

int is_backtick(char **args, int idx);

int backtick_handle(char **args, int *exit_status);


// Error

void my_putstrerror(const char *str);

void print_error(const char *cmd, const char *message);

void handle_ctr_c(int sig);


// Get args

void print_header(void);

int print_prompt(void);

void handle_horizontal_arrows(char seq[2], int *pos, int *len);

void handle_vertical_arrows(char seq[2], handle_ctrl_t *ctrl);

void parse_args(char *line, char **args, int size);

void free_args(char **args);

char *read_line(int *exit_status, history_t *history);

void insert_char(handle_ctrl_t ctrl);

int ensure_capacity(handle_ctrl_t *ctrl);

void handle_input(env_t *head, int *exit_status, char **env,
    history_t **history_main);

// History

int history_add(char *line, history_t **history);

int print_last_n(history_t *head, int idx);

int history_clear(history_t **head);

char *get_history_file_path(void);

char *history_navigation(char seq[2]);

history_t *make_history_linked_list(FILE *history_file, history_t *head);

//handle ctrl

int handle_ctrl_a(int *pos);

int handle_ctrl_e(int *pos, int *len);

int handle_ctrl_k(char *line, int *pos, int *len);

int handle_ctrl_l(char *line, int *pos, int *len);

int handle_ctrl_u(char *line, int *pos, int *len);

int handle_ctrl_w(handle_ctrl_t *ctrl);

//utils

void write_char(int *pos, int *len);

char *remove_first_char(const char *str);

void parse_args(char *line, char **args, int size);

void handle_ctr_c(int sig);

void print_error_reverse(const char *cmd, const char *message, int status);

void print_error(const char *cmd, const char *message);

void my_putstrerror(const char *str);

int count_node(history_t *head);

void free_word_array(char **array);

char **is_exit_cmd(char *line);

// Special inputs

int check_ctrl(handle_ctrl_t *handle_ctrl, int *exit_status,
    history_t *history);

#endif
