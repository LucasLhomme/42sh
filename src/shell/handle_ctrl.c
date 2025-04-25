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
    if (c == 12)
        return handle_ctrl_l(line, pos, len);
    if (c == 1)
        return handle_ctrl_a(pos);
    if (c == 5)
        return handle_ctrl_e(pos, len);
    if (c == 21)
        return handle_ctrl_u(line, pos, len);
    if (c == 11)
        return handle_ctrl_k(line, pos, len);
    // if (c == 23)
    //     return handle_ctrl_w(line, pos, len);
    if (c == 4) {
        printf("exit\n");
        exit(1);
    }
    return 0;
}
