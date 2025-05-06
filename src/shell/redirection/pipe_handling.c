/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** pipe_handling.c
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "project.h"
#include "my.h"

int is_piped_command(char **args, int *exit_status)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (nb_char(args[i], '|') >= 2) {
            my_putstrerror("Invalid null command.\n");
            *exit_status = 1;
            return 1;
        }
        if (my_strcmp(args[i], "|") == 0)
            return 1;
    }
    return 0;
}

static pid_t child_proc(void (*child_func)(pipe_command_t *, env_t *, int *),
    pipe_command_t *commands, env_t *env, int *exit_status)
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

static void first_child_process(pipe_command_t *commands, env_t *env,
    int *exit_status)
{
    dup2(commands->fd[1], STDOUT_FILENO);
    close(commands->fd[0]);
    close(commands->fd[1]);
    execute_command(commands->cmd1, env, exit_status);
}

static void second_child_process(pipe_command_t *commands, env_t *env,
    int *exit_status)
{
    dup2(commands->fd[0], STDIN_FILENO);
    close(commands->fd[1]);
    close(commands->fd[0]);
    execute_command(commands->cmd2, env, exit_status);
}

int exec_pipe_command(pipe_command_t *commands, env_t *env, int *exit_status)
{
    if (!commands || !commands->is_pipe)
        return 1;
    if (pipe(commands->fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    commands->pid1 = child_proc(first_child_process,
        commands, env, exit_status);
    commands->pid2 = child_proc(second_child_process,
        commands, env, exit_status);
    close(commands->fd[0]);
    close(commands->fd[1]);
    waitpid(commands->pid1, NULL, 0);
    waitpid(commands->pid2, NULL, 0);
    return 0;
}

static int *get_size_cmd(char **args)
{
    int *cmd = malloc(sizeof(int) * 2);
    int cmd1_size = 0;
    int cmd2_size = 0;
    int i = 0;

    for (; args[i] != NULL && strcmp(args[i], "|") != 0; i++)
        cmd1_size++;
    if (args[i] != NULL)
        i++;
    for (int j = i; args[j] != NULL; j++)
        cmd2_size++;
    cmd[0] = cmd1_size;
    cmd[1] = cmd2_size + 1;
    return cmd;
}

static pipe_command_t *initialize_pipe_command(char **args)
{
    pipe_command_t *commands = malloc(sizeof(pipe_command_t));
    int cmd = len_tab(args);

    if (!commands || !cmd)
        return NULL;
    commands->is_pipe = 0;
    commands->pid1 = 0;
    commands->pid2 = 0;
    commands->fd[0] = -1;
    commands->fd[1] = -1;
    commands->cmd1 = calloc(cmd + 1, sizeof(char *));
    commands->cmd2 = calloc(cmd + 1, sizeof(char *));
    if (!commands->cmd1 || !commands->cmd2)
        return NULL;
    return commands;
}

static void parse_pipe_arguments(char **args, pipe_command_t *commands)
{
    int i = 0;
    int j = 0;

    for (; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "|") == 0) {
            commands->is_pipe = 1;
            commands->cmd1[i] = NULL;
            i++;
            break;
        }
        commands->cmd1[i] = strdup(args[i]);
    }
    commands->cmd1[i] = NULL;
    while (args[i] != NULL) {
        commands->cmd2[j] = strdup(args[i]);
        j++;
        i++;
    }
    commands->cmd2[j] = NULL;
}

int handle_pipes(char **args, env_t *head, int *exit_status)
{
    pipe_command_t *commands = initialize_pipe_command(args);

    if (!commands || (args[0] && my_strcmp(args[0], "|") == 0)) {
        print_error(NULL, "Invalid null command.");
        *exit_status = 1;
        if (commands)
            free(commands);
        return 1;
    }
    parse_pipe_arguments(args, commands);
    exec_pipe_command(commands, head, exit_status);
    for (int i = 0; commands->cmd1[i]; i++)
        free(commands->cmd1[i]);
    for (int i = 0; commands->cmd2[i]; i++)
        free(commands->cmd2[i]);
    free(commands->cmd1);
    free(commands->cmd2);
    free(commands);
    return 0;
}
