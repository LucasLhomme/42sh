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
#include "my.h"
#include "project.h"

void process_command(char *line, env_t *head, int *last_exit_status,
    char **env)
{
    int nb_space = nb_char(line, ' ');
    int nb_tab = nb_char(line, '\t');
    int size = nb_tab + nb_space + 1;
    char *args[size];

    parse_args(line, args, size);
    if (is_builtin(head, args, env, last_exit_status) == 1)
        return;
    execute_command(args, head, last_exit_status);
}

void handle_input(env_t *head, int *last_exit_status, char **env)
{
    char *line = NULL;
    int result = 0;

    while (1) {
        line = read_line();
        if (!line) {
            return;
        }
        result = history_add(line);
        if (line[0] == '\0') {
            free(line);
            continue;
        }
        if (result == 0)
            process_command(line, head, last_exit_status, env);
        free(line);
    }
}

int main(int ac, char **av, char **env)
{
    env_t *head = def_linked_list(env[0], 0, env);
    int last_exit_status = 0;

    (void)ac;
    (void)av;
    signal(SIGINT, handle_ctr_c);
    handle_input(head, &last_exit_status, env);
    free_list(head);
    return last_exit_status;
}
