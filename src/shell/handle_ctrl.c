/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_ctrl
*/

#include <unistd.h>
#include "project.h"

static int handle_ctrl_l(char *line, int *pos, int *len)
{
    write(1, "\033[H\033[J", 6);
    *pos = 0;
    *len = 0;
    line[0] = '\0';
    print_prompt();
    return 1;
}

static int handle_ctrl_a(int *pos)
{
    for (; *pos > 0; (*pos)--)
        write(1, "\033[D", 3);
    return 1;
}

static int handle_ctrl_e(int *pos, int *len)
{
    for (; *pos < *len; (*pos)++)
        write(1, "\033[C", 3);
    return 1;
}

static int handle_ctrl_u(char *line, int *pos, int *len)
{
    int i;
    int old_len = *len;

    if (*pos <= 0)
        return 0;
    for (i = 0; i < *pos; i++)
        write(STDOUT_FILENO, "\b", 1);
    if (*pos < *len) {
        int remaining = *len - *pos;
        for (i = 0; i < remaining; i++)
            line[i] = line[i + *pos];
        line[i] = '\0';
        write(STDOUT_FILENO, line, remaining);
        for (i = remaining; i < old_len; i++)
            write(STDOUT_FILENO, " ", 1);
        for (i = remaining; i < old_len; i++)
            write(STDOUT_FILENO, "\b", 1);
        *len = remaining;
    } else {
        line[0] = '\0';
        for (i = 0; i < old_len; i++)
            write(STDOUT_FILENO, " ", 1);
        for (i = 0; i < old_len; i++)
            write(STDOUT_FILENO, "\b", 1);
        *len = 0;
    }
    *pos = *len;
    return 1;
}

int check_ctrl(char c, char *line, int *pos, int *len)
{
    if (c == 12)
        return handle_ctrl_l(line, pos, len);
    if (c == 1)
        return handle_ctrl_a(pos);
    if (c == 5)
        return handle_ctrl_e(pos, len);
    if (c == 21)
        return handle_ctrl_u(line, pos, len);
    return 0;
}
