/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** no_name.c
*/

#include "project.h"

static void handle_exit(char *line, input_t *ctx)
{
    char **args = is_exit_cmd(line);

    if (!args)
        return;
    for (int i = 0; args[i] != NULL; i++)
        printf("arg : %s\n", args[i]);
    free(line);
    my_exit(args, *ctx->history, ctx->env_list);
}

static int handle_line(char *line, input_t *ctx)
{
    int result = 0;

    if (line[0] == '\0') {
        free(line);
        return 0;
    }
    handle_exit(line, ctx);
    result = history_add(line, ctx->history);
    if (result == 1)
        process_command(line, ctx->env_list, ctx->exit_status, ctx->env);
    free(line);
    return 1;
}

void handle_input(env_t *head, int *exit_status, char **env,
    history_t **history_main)
{
    char *line = NULL;
    input_t ctx = {
        .env_list = head,
        .exit_status = exit_status,
        .env = env,
        .history = history_main
    };

    if (isatty(STDIN_FILENO) == 1)
        print_header();
    while (1) {
        line = read_line(exit_status, *history_main, head);
        if (!line) {
            print_history(*history_main);
            my_exit(NULL, *history_main, head);
            return;
        }
        handle_line(line, &ctx);
    }
}
