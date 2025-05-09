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

int check_capacity(handle_ctrl_t ctrl)
{
    if (ensure_capacity(&ctrl) == -1) {
        if (ctrl.line)
            free(ctrl.line);
        return 84;
    }
    return 0;
}

handle_ctrl_t init_control(char *line, handle_ctrl_t ctrl, int pos, int len)
{
    ctrl.line = line;
    ctrl.line_ptr = &line;
    ctrl.pos = &pos;
    ctrl.len = &len;
    return ctrl;
}

int free_line(int status, char *line)
{
    if (status == -2) {
        if (line)
            free(line);
        return 84;
    }
    return 0;
}
