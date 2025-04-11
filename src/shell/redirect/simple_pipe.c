/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** simple_pipe
*/

#include "my.h"
#include "lib.h"

static int execute_with_context(executioncontext_t *context)
{
    dup2(context->in_fd, STDIN_FILENO);
    dup2(context->out_fd, STDOUT_FILENO);
    close(context->in_fd == STDIN_FILENO ? -1 : context->in_fd);
    close(context->out_fd == STDOUT_FILENO ? -1 : context->out_fd);
    execute_bin(context->path, context->argv, context->env);
    exit(0);
}

static int prepare_command_context(char *buffer, char **env,
    executioncontext_t *context)
{
    if (!buffer)
        return 1;
    context->argv = my_str_to_word_array(buffer);
    if (!context->argv || !context->argv[0]) {
        if (context->argv)
            cleanup_argv(context->argv);
        return 1;
    }
    context->path = concas_command(context->argv, env);
    context->env = env;
    return 0;
}

static int execute_if_valid(executioncontext_t *context, char *buffer)
{
    if (access(context->path, X_OK) == 0) {
        execute_with_context(context);
    } else {
        my_printf("%s: Command not found.\n", buffer);
        free(context->path);
        cleanup_argv(context->argv);
        return 1;
    }
    return 0;
}

int find_and_execute_command(char *buffer, char **env,
    int in_fd, int out_fd)
{
    executioncontext_t context = {0};
    int result;

    context.in_fd = in_fd;
    context.out_fd = out_fd;
    if (prepare_command_context(buffer, env, &context) != 0)
        return 1;
    result = execute_if_valid(&context, buffer);
    if (result == 0) {
        free(context.path);
        cleanup_argv(context.argv);
    }
    return result;
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
