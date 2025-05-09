/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** handle_arrows.c
*/

#include "my.h"

void handle_horizontal_arrows(char seq[2], int *pos, int *len)
{
    if (seq[0] != '[')
        return;
    if (seq[1] == 'D' && *pos > 0) {
        (*pos)--;
        write(1, "\033[D", 3);
    }
    if (seq[1] == 'C' && *pos < *len) {
        (*pos)++;
        write(1, "\033[C", 3);
    }
}

static int is_vertical_arrow(char seq[2])
{
    return (seq[0] == '[' && (seq[1] == 'A' || seq[1] == 'B'));
}

static int ensure_line_capacity(handle_ctrl_t *ctrl, size_t needed)
{
    char *new_line = NULL;

    if (needed <= (size_t)ctrl->capacity)
        return 1;
    while (needed > (size_t)ctrl->capacity)
        ctrl->capacity *= 2;
    new_line = realloc(*ctrl->line_ptr, ctrl->capacity);
    if (!new_line)
        return 0;
    *ctrl->line_ptr = new_line;
    ctrl->line = new_line;
    return 1;
}

static void load_command_into_line(handle_ctrl_t *ctrl, const char *command)
{
    memset(ctrl->line, 0, ctrl->capacity);
    strcpy(ctrl->line, command);
    *ctrl->len = strlen(command);
    *ctrl->pos = *ctrl->len;
}

void handle_vertical_arrows(char seq[2], handle_ctrl_t *ctrl)
{
    size_t needed = 0;
    char *new_command = NULL;

    if (!is_vertical_arrow(seq))
        return;
    new_command = history_navigation(seq);
    if (!new_command)
        return;
    needed = strlen(new_command) + 1;
    if (!ensure_line_capacity(ctrl, needed))
        return;
    load_command_into_line(ctrl, new_command);
}
