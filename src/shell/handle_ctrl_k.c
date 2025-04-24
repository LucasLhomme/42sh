/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** handle_ctrl_k
*/
#include <unistd.h>

int handle_ctrl_k(char *line, int *pos, int *len)
{
    int i = 0;
    int old_len = *len;

    if (*pos >= *len)
        return 0;
    line[*pos] = '\0';
    for (i = *pos; i < old_len; i++)
        write(STDOUT_FILENO, " ", 1);
    for (i = *pos; i < old_len; i++)
        write(STDOUT_FILENO, "\b", 1);
    *len = *pos;
    return 1;
}