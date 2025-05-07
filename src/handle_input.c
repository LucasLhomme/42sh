/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** no_name.c
*/

#include "project.h"

void free_all(char **args, char *line)
{
    free_args(args);
    free(line);
}

void handle_eof(history_t **history_main)
{
    print_history(*history_main);
    my_exit(NULL, *history_main);
}

void handle_exit_command(char **args, history_t **history_main)
{
    my_exit(args, *history_main);
    free_args(args);
    exit(0);
}

void handle_input(env_t *head, int *exit_status, char **env,
    history_t **history_main)
{
    char *line = NULL;
    char **args = NULL;

    if (isatty(STDIN_FILENO) == 1)
        print_header();
    while (1) {
        line = read_line(exit_status, *history_main);
        if (!line)
            handle_eof(history_main);
        if (line[0] == '\0') {
            free(line);
            continue;
        }
        args = is_exit_cmd(line);
        if (args)
            handle_exit_command(args, history_main);
        if (history_add(line, history_main) == 1)
            process_command(line, head, exit_status, env);
        free_all(args, line);
    }
}
