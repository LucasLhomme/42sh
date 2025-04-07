/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** simple_pipe
*/
#include "my.h"
#include "lib.h"
#include <ctype.h>
#include <errno.h>

static int execute_with_context(executioncontext_t *context)
{
    dup2(context->in_fd, STDIN_FILENO);
    dup2(context->out_fd, STDOUT_FILENO);
    close(context->in_fd == STDIN_FILENO ? -1 : context->in_fd);
    close(context->out_fd == STDOUT_FILENO ? -1 : context->out_fd);
    execute_bin(context->path, context->argv, context->env);
    exit(0);
}

static int find_and_execute_command(char *buffer, char **env,
    int in_fd, int out_fd)
{
    executioncontext_t context = {0};

    context.argv = my_str_to_word_array(buffer);
    if (!context.argv || !context.argv[0])
        return 1;
    context.path = concas_command(context.argv);
    context.env = env;
    context.in_fd = in_fd;
    context.out_fd = out_fd;
    if (access(context.path, X_OK) == 0) {
        execute_with_context(&context);
    } else {
        my_printf("%s: Command not found.\n", buffer);
        free(context.path);
        cleanup_argv(context.argv);
        return 1;
    }
    return 0;
}

int is_null_command(char *command1, char *command2)
{
    if (command1 == NULL || command2 == NULL) {
        my_printf("Invalid null command.\n");
        return 1;
    }
    if (command1[0] == '|' || command2[0] == '|') {
        my_printf("Invalid null command.\n");
        return 1;
    }
    return 0;
}

static int setup_first_pipe(int pipefd[2], char *command1, char **env)
{
    pid_t pid1 = fork();

    if (pid1 == -1) {
        perror("fork");
        return 1;
    }
    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        find_and_execute_command(command1, env, STDIN_FILENO, pipefd[1]);
        exit(1);
    }
    return pid1;
}

static int setup_second_pipe(int pipefd[2], char *command2, char **env)
{
    pid_t pid2 = fork();

    if (pid2 == -1) {
        perror("fork");
        return 1;
    }
    if (pid2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        find_and_execute_command(command2, env, pipefd[0], STDOUT_FILENO);
        exit(1);
    }
    return pid2;
}

static int create_pipe_and_validate(int pipefd[2])
{
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
    return 0;
}

static void wait_for_children(pid_t pid1, pid_t pid2)
{
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

static int handle_pid_error(pipe_context_t *context)
{
    context->pid1 = setup_first_pipe(context->pipefd,
        context->command1, context->env);
    if (context->pid1 == -1) {
        close(context->pipefd[0]);
        close(context->pipefd[1]);
        return 1;
    }
    context->pid2 = setup_second_pipe(context->pipefd,
        context->command2, context->env);
    if (context->pid2 == -1) {
        close(context->pipefd[0]);
        close(context->pipefd[1]);
        return 1;
    }
    return 0;
}

int pipe_command_setup(char *command1, char *command2, char **env)
{
    pipe_context_t context = {0};

    if (is_null_command(command1, command2) == 1)
        return 1;
    context.command1 = trim_whitespace(command1);
    context.command2 = trim_whitespace(command2);
    context.env = env;
    if (create_pipe_and_validate(context.pipefd) == -1)
        return 1;
    if (handle_pid_error(&context) == 1)
        return 1;
    close(context.pipefd[0]);
    close(context.pipefd[1]);
    wait_for_children(context.pid1, context.pid2);
    return 0;
}
