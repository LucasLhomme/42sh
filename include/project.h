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
    #include "struct_word_array.h"

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

typedef struct builtin_s {
    char *command;
    int (*function)(char **args, env_t *head, char **env, int *last_exit_status);
} builtin_t;

typedef struct command_s {
    char *command;
    int (*function)(char **args, env_t *head, int *last_exit_status);
} command_t;

typedef struct pipe_command {
    char *cmd1[256];
    char *cmd2[256];
    int is_pipe;
    pid_t pid1;
    pid_t pid2;
    int fd[2];
} pipe_command_t;

typedef struct semicolumn_s {
    char *cmd1[256];
    char *cmd2[256];
    pid_t pid1;
    pid_t pid2;
    int is_semicolumn;
} semicolumn_t;


// Builtin funtion

int is_builtin(env_t *head, char **args, char **env, int *last_exit_value);

int my_cd(char **args, env_t *head, char **env, int *last_exit_status);

int my_env(char **args, env_t *head, char **env, int *last_exit_status);

int my_exit(char **args, env_t *head, char **env, int *last_exit_statusv);

int my_unsetenv(char **args, env_t *head, char **env, int *last_exit_status);

int my_setenv(char **args, env_t *head, char **env, int *last_exit_status);

env_t *home(env_t *head, pack_env_t *pack);

env_t *casual_add(char *str, char *new_value, env_t *head);

env_t *one_arg(env_t *head, char *arg);

int my_echo(char **args, env_t *head, char **env, int *last_exit_status);


// Linked list

env_t *def_linked_list(char *line, int status, char **env);

env_t *add_node(env_t *head, char *line, int status);

void print_list(env_t *head);

void free_list(env_t *head);

void free_env_array(char **env_array);

char **convert_env_to_array(env_t *head);


// Exec function

int exec_pipe_command(pipe_command_t *commands, env_t *env, int *exit_status);

int is_piped_command(char **args, int *last_exit_status);

int is_semicolumn_command(char **args);

void execute_command(char **args, env_t *head, int *last_exit_status);

int semicolumn_handle(char **args, env_t *head, int *last_exit_status);

int handle_pipes(char **args, env_t *head, int *last_exit_status);

int redirection(char **args);

int is_command(env_t *head, char **args, int *last_exit_status);

int is_backtick(char **args, int idx);

int backtick_handle(char **args, int *last_exit_status);


// Error

void my_putstrerror(const char *str);

void print_error(const char *cmd, const char *message);

void handle_ctr_c(int sig);


// Get args

int print_prompt(void);

char *read_line(void);

void parse_args(char *line, char **args, int size);

void free_args(char **args);

#endif
