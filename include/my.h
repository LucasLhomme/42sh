/*
** EPITECH PROJECT, 2024
** Mon H
** File description:
** Header avec les fonctions
*/

#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <ctype.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

typedef int (*command_func_t)(char *, char **);

typedef struct handle_command_s {
    char *command;
    command_func_t func;
} handle_command_t;

typedef struct handle_redirect_s {
    char *command;
    command_func_t func;
} handle_redirect_t;

typedef struct context_s {
    char *path;
    char **argv;
    char **env;
    int in_fd;
    int out_fd;
} executioncontext_t;

typedef struct pipe_context_s {
    int pipefd[2];
    pid_t pid1;
    pid_t pid2;
    char *command1;
    char *command2;
    char **env;
} pipe_context_t;

#ifndef MY_H_
    #define MY_H_
char *cleaning_buffer(char *buffer);
int searching_bin(char *buffer, char **env);
int loop_terminal(char **env);
int hand_command(char *buffer, char **env);
int my_cd(char *command, char **env);
int loop_tty(char **env);
int my_env(char *buffer, char **env);
int my_setenv(char *buffer, char **env);
int new_value_env(char *name, char **env);
int over_value_env(char *name, char *value, char **env);
int my_unsetenv(char *name, char **env);
int execute_bin(char *path, char **argv, char **env);
int hand_buffer(char *buffer, char **env);
int simple_pipe(char *buffer, char **env);
char *concas_command(char **argv, char **env);
int pipe_command_setup(char *command1, char *command2, char **env);
int simple_semicolon(char *buffer, char **env);
int redirect(char *buffer, char **env);
int my_execute_program(char *buffer, char **env);
void cleanup_argv(char **argv);
void free_argv(char **argv);
char *find_env(char *path, char **env);
int handle_null_value(char *name, char **env);
int handle_invalid_variable_name(int exit_check_var, char **argv);
int handle_too_many_arguments(char **argv);
int handle_no_arguments(char **env, char **argv);
int print_env(char **env);
int find_and_execute_command(char *buffer, char **env, int in_fd, int out_fd);
int is_null_command(char *command1, char *command2);

#endif /* MY_H_ */
