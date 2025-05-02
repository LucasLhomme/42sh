/*
** EPITECH PROJECT, 2025
** double_pipe.c
** File description:
** if one function fails an other success
*/

#include "my.h"

static void execute_until_pipe(double_pipe_t *pipe_args,
    separator_index_t *index, int i)
{
    index->end = i;
    execute_segment(pipe_args->args,
        pipe_args->head, pipe_args->exit_status, index);
}

static int should_stop_execution(int exit_status)
{
    return exit_status == 0;
}

static void handle_remaining(double_pipe_t *pipe_args,
    separator_index_t *index)
{
    index->end = -1;
    execute_last_command(pipe_args->args,
        pipe_args->head, pipe_args->exit_status, index);
}

int handle_double_pipe(char **args, env_t *head, int *exit_status)
{
    double_pipe_t pipe_args = {args, head, exit_status};
    separator_index_t index = {0};

    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "||") != 0)
            continue;
        execute_until_pipe(&pipe_args, &index, i);
        if (should_stop_execution(*exit_status))
            return 0;
        index.start = i + 1;
    }
    handle_remaining(&pipe_args, &index);
    return 0;
}
