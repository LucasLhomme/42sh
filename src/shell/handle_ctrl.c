/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_ctrl
*/

#include <unistd.h>

#include "project.h"

int check_ctrl(char c, char *line, int *pos, int *len)
{
    if (c == 12) {
        write(1, "\033[H\033[J", 6);
        *pos = 0;
        *len = 0;
        line[0] = '\0';
        print_prompt();
        return 1;
    }
    if (c == 1) {
        for (; *pos > 0; (*pos)--)
            write(1, "\033[D", 3);
        return 1;
    }
    if (c == 5) {
        for (; *pos < *len; (*pos)++)
            write(1, "\033[C", 3);
        return 1;
    }
    return 0;
}
