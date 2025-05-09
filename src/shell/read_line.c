/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** read_line.c
*/

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my.h"
#include "project.h"

static void set_raw_mode(struct termios *old)
{
    struct termios newt;

    tcgetattr(STDIN_FILENO, old);
    newt = *old;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

static void handle_arrow_keys(char seq[2], handle_ctrl_t ctrl)
{
    handle_horizontal_arrows(seq, ctrl.pos, ctrl.len);
    handle_vertical_arrows(seq, &ctrl);
}

static void handle_backspace(handle_ctrl_t ctrl)
{
    if (*ctrl.pos > 0) {
        memmove(&ctrl.line[*ctrl.pos - 1],
            &ctrl.line[*ctrl.pos], *ctrl.len - *ctrl.pos);
        (*ctrl.len)--;
        (*ctrl.pos)--;
        write(1, "\b", 1);
        write(1, &ctrl.line[*ctrl.pos], *ctrl.len - *ctrl.pos);
        write(1, " ", 1);
        for (int i = 0; i < *ctrl.len - *ctrl.pos + 1; i++)
            write(1, "\b", 1);
    }
}

static int init_line(char **line, struct termios *oldt)
{
    *line = NULL;
    set_raw_mode(oldt);
    if (isatty(STDIN_FILENO))
        print_prompt();
    return 0;
}

static int handle_escape(char seq[2], handle_ctrl_t ctrl)
{
    if (read(STDIN_FILENO, &seq[0], 1) != 1)
        return -1;
    if (read(STDIN_FILENO, &seq[1], 1) != 1)
        return -1;
    handle_arrow_keys(seq, ctrl);
    return 1;
}

static int check_character(handle_ctrl_t ctrl)
{
    char seq[2];

    if (ctrl.c == '\n') {
        write(1, "\n", 1);
        return 0;
    }
    if (ctrl.c == '\033')
        return handle_escape(seq, ctrl);
    if (ctrl.c == KEY_BACKSPACE || ctrl.c == '\b') {
        handle_backspace(ctrl);
        return 1;
    }
    if (ctrl.c >= 32 && ctrl.c <= 126) {
        insert_char(ctrl);
        return 1;
    }
    return -1;
}

static int read_character(handle_ctrl_t ctrl, int *exit_status,
    history_t *history, env_t *head)
{
    int status = 0;

    if (read(STDIN_FILENO, &ctrl.c, 1) != 1)
        return -1;
    status = check_character(ctrl);
    if (status == -1)
        status = check_ctrl(&ctrl, exit_status, history, head);
    return status;
}

static char *finalize_line(char *line, int len, int status,
    struct termios *oldt)
{
    tcsetattr(STDIN_FILENO, TCSANOW, oldt);
    if (len == 0 && status == -1) {
        free(line);
        return NULL;
    }
    line[len] = '\0';
    return line;
}

static int prepare_reading(char **line, struct termios *oldt,
    handle_ctrl_t *ctrl)
{
    if (init_line(line, oldt) == -1)
        return -1;
    ctrl->capacity = 64;
    *line = malloc(ctrl->capacity);
    if (!*line)
        return -1;
    memset(*line, 0, ctrl->capacity);
    return 0;
}

char *read_line(int *exit_status, history_t *history, env_t *head)
{
    static struct termios oldt;
    handle_ctrl_t ctrl;
    char *line = NULL;
    int pos = 0;
    int len = 0;
    int status = 1;

    if (prepare_reading(&line, &oldt, &ctrl) == -1) {
        free(line);
        return NULL;
    }
    ctrl.line = line;
    ctrl.line_ptr = &line;
    ctrl.pos = &pos;
    ctrl.len = &len;
    while (status > 0) {
        if (ensure_capacity(&ctrl) == -1) {
            free(ctrl.line);
            return NULL;
        }
        status = read_character(ctrl, exit_status, history, head);
        if (status == -2) {
            free(line);
            return NULL;
        }
    }
    return finalize_line(line, len, status, &oldt);
}
