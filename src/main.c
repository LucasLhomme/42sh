/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-joseph.birck
** File description:
** main
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include "project.h"

static int is_whitespace_only(const char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] != ' ' && line[i] != '\t')
            return 0;
    }
    return 1;
}

void process_command(char *line, env_t *head, int *exit_status,
    char **env)
{
    int size = strlen(line) + 1;
    char *args[size];

    parse_args(line, args, size);
    if (is_builtin(head, args, env, exit_status) == 1)
        return;
    execute_command(args, head, exit_status);
}

void handle_input(env_t *head, int *exit_status, char **env)
{
    char *line = NULL;
    int result = 0;
    static history_t *history = NULL;

    if (isatty(STDIN_FILENO) == 1)
        print_header();
    while (1) {
        line = read_line(exit_status);
        if (!line)
            return;
        result = history_add(line, &history);
        if (line[0] == '\0') {
            free(line);
            continue;
        }
        if (result == 1)
            process_command(line, head, exit_status, env);
        free(line);
    }
}

int main(int ac, char **av, char **env)
{
    env_t *head = def_linked_list(env[0], 0, env);
    int exit_status = 0;

    (void)ac;
    (void)av;
    signal(SIGINT, handle_ctr_c);
    handle_input(head, &exit_status, env);
    free_list(head);
    return exit_status;
}
