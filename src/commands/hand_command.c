/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** hand_command
*/
#include "lib.h"
#include "my.h"
#include <sys/stat.h>

const handle_command_t commands[] = {
    {"cd", my_cd},
    {"env", my_env},
    {"setenv", my_setenv},
    {"unsetenv", my_env},
    {NULL, NULL}
};

static int is_folder(char *buffer)
{
    struct stat path_stat;
    int exit_status = 0;

    if (stat(buffer, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) {
        my_printf("%s: Permission denied.\n", buffer);
        exit_status = 1;
    }
    return exit_status;
}

int my_execute_program(char *buffer, char **env)
{
    for (int i = 0; commands[i].command != NULL; i++) {
        if (my_strncmp(buffer, commands[i].command,
            my_strlen(commands[i].command)) == 0)
            return commands[i].func(buffer, env);
    }
    return searching_bin(buffer, env);
}

int execute_child_process(char **args, char **env)
{
    if (execve(args[0], args, env) == -1) {
        free_argv(args);
        exit(1);
    }
    return 0;
}

int handle_fork(char **args, char **env)
{
    int status;
    pid_t pid = fork();

    if (pid == 0) {
        execute_child_process(args, env);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    } else
        return 1;
    return 0;
}

int is_program(char *buffer, char **env)
{
    char **args = my_str_to_word_array(buffer);
    int result = 0;

    if (my_strncmp(buffer, "./", 2) == 0 || (my_strncmp(buffer, "/", 1) == 0))
        result = handle_fork(args, env);
    free_argv(args);
    return result;
}

int hand_command(char *buffer, char **env)
{
    int exit_status = 0;

    trim_whitespace(buffer);
    if (is_program(buffer, env) == 0)
        exit_status = 1;
    if (is_folder(buffer) == 1)
        exit_status = 1;
    else
        exit_status = my_execute_program(buffer, env);
    return exit_status;
}
