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

static void handle_arrow_keys(char seq[2], int *pos, int len)
{
    if (seq[0] == '[') {
        if (seq[1] == 'D' && *pos > 0) {
            (*pos)--;
            write(1, "\033[D", 3);
        }
        if (seq[1] == 'C' && *pos < len) {
            (*pos)++;
            write(1, "\033[C", 3);
        }
        if (seq[0] == '[' && (seq[1] == 'A' || seq[1] == 'B')) {
            history_navigation(seq);
        }
    }
}

static void handle_backspace(char *line, int *pos, int *len)
{
    if (*pos > 0) {
        memmove(&line[*pos - 1], &line[*pos], *len - *pos);
        (*len)--;
        (*pos)--;
        write(1, "\b", 1);
        write(1, &line[*pos], *len - *pos);
        write(1, " ", 1);
        for (int i = 0; i < *len - *pos + 1; i++)
            write(1, "\b", 1);
    }
}

void insert_char(char *line, char c, int *pos, int *len)
{
    if (*len < 1023) {
        if (*pos < *len)
            memmove(&line[*pos + 1], &line[*pos], *len - *pos);
        line[*pos] = c;
        (*len)++;
        (*pos)++;
        if (*pos < *len) {
            write(1, &line[*pos - 1], *len - *pos + 1);
            write_char(pos, len);
        } else
            write(1, &c, 1);
    }
}

static int init_line(char **line, struct termios *oldt)
{
    *line = malloc(1024);
    if (!*line)
        return -1;
    memset(*line, 0, 1024);
    set_raw_mode(oldt);
    if (isatty(STDIN_FILENO))
        print_prompt();
    return 0;
}

static int handle_escape(char seq[2], int *pos, int len)
{
    if (read(STDIN_FILENO, &seq[0], 1) != 1)
        return -1;
    if (read(STDIN_FILENO, &seq[1], 1) != 1)
        return -1;
    handle_arrow_keys(seq, pos, len);
    return 1;
}

static int check_character(char c, char *line, int *pos, int *len)
{
    char seq[2];

    if (c == '\n') {
        write(1, "\n", 1);
        return 0;
    }
    if (c == '\033')
        return handle_escape(seq, pos, *len);
    if (c == KEY_BACKSPACE || c == '\b') {
        handle_backspace(line, pos, len);
        return 1;
    }
    if (c >= 32 && c <= 126) {
        insert_char(line, c, pos, len);
        return 1;
    }
    return -1;
}

static int read_character(char *line, int *pos, int *len)
{
    char c = 0;
    int status = 0;

    if (read(STDIN_FILENO, &c, 1) != 1)
        return -1;
    status = check_character(c, line, pos, len);
    if (status == -1)
        status = check_ctrl(c, line, pos, len);
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

char *read_line(void)
{
    static struct termios oldt;
    char *line = NULL;
    int pos = 0;
    int len = 0;
    int status = 1;

    if (init_line(&line, &oldt) == -1)
        return NULL;
    while (status > 0)
        status = read_character(line, &pos, &len);
    return finalize_line(line, len, status, &oldt);
}
