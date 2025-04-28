/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** handle_ctrl_e
*/
#include <unistd.h>

int handle_ctrl_e(int *pos, int *len)
{
    for (; *pos < *len; (*pos)++)
        write(1, "\033[C", 3);
    return 1;
}
