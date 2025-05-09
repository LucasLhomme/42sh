/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** handle_ctr_c
*/
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "project.h"

void handle_ctr_c(int sig)
{
    if (sig == SIGINT) {
        printf("\n");
        print_prompt();
    }
}

void initialize_ctrl(handle_ctrl_t *ctrl, char *line,
    int *pos, int *len)
{
    ctrl->line = line;
    ctrl->line_ptr = &line;
    ctrl->pos = pos;
    ctrl->len = len;
}

int handle_ctrl_d(int status, char *line,
    history_t *history, env_t *head)
{
    if (status == -2) {
        free(line);
        my_exit(NULL, history, head);
        return 1;
    }
    return 0;
}

int process_input_loop(handle_ctrl_t *ctrl, int *exit_status,
    history_t *history, env_t *head)
{
    int status = 1;

    while (status > 0) {
        if (ensure_capacity(ctrl) == -1) {
            free(ctrl->line);
            return -1;
        }
        status = read_character(*ctrl, exit_status);
        if (status == -2 &&
            handle_ctrl_d(status, ctrl->line, history, head))
            return -1;
    }
    return status;
}
