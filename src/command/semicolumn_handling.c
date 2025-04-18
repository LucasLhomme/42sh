/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** semicolumn_handling.c
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "project.h"
#include "my.h"

int is_semicolumn_command(char **args)
{
    int len = len_tab(args);

    for (int i = 0; args[i] != NULL; i++) {
        if (nb_char(args[i], ';') >= 1 && len == 1) {
            return 0;
        }
        if (my_strcmp(args[i], ";") == 0)
            return 1;
    }
    return 0;
}

static pid_t child_proc(void (*child_func)(semicolumn_t *, env_t *, int *),
    semicolumn_t *commands, env_t *env, int *exit_status)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        child_func(commands, env, exit_status);
        exit(*exit_status);
    }
    return pid;
}

static void first_child_process(semicolumn_t *commands, env_t *env,
    int *exit_status)
{
    execute_command(commands->cmd1, env, exit_status);
}

static void second_child_process(semicolumn_t *commands, env_t *env,
    int *exit_status)
{
    execute_command(commands->cmd2, env, exit_status);
}

void exec_semicolumn_command(semicolumn_t *commands, env_t *env,
    int *exit_status)
{
    commands->pid1 = child_proc(first_child_process,
        commands, env, exit_status);
    commands->pid2 = child_proc(second_child_process,
        commands, env, exit_status);
    waitpid(commands->pid1, NULL, 0);
    waitpid(commands->pid2, NULL, 0);
}

static semicolumn_t *initialize_semicolumn_command(void)
{
    semicolumn_t *commands = malloc(sizeof(semicolumn_t));

    if (!commands)
        return NULL;
    commands->is_semicolumn = 0;
    commands->pid1 = 0;
    commands->pid2 = 0;
    for (int i = 0; i < 256; i++) {
        commands->cmd1[i] = NULL;
        commands->cmd2[i] = NULL;
    }
    return commands;
}

static void parse_semicolumn_arguments(char **args, semicolumn_t *commands)
{
    int i = 0;
    int j = 0;

    for (; args[i] != NULL; i++) {
        if (my_strcmp(args[i], ";") == 0) {
            commands->is_semicolumn = 1;
            commands->cmd1[i] = NULL;
            i++;
            break;
        }
        commands->cmd1[i] = args[i];
    }
    while (args[i] != NULL) {
        commands->cmd2[j] = args[i];
        j++;
        i++;
    }
    commands->cmd2[j] = NULL;
}

int semicolumn_handle(char **args, env_t *head, int *exit_status)
{
    semicolumn_t *commands = initialize_semicolumn_command();

    if (!commands)
        return 1;
    parse_semicolumn_arguments(args, commands);
    exec_semicolumn_command(commands, head, exit_status);
    free(commands);
    return 0;
}
