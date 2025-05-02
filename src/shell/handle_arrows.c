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

void handle_vertical_arrows(char seq[2], char *line, int *pos, int *len)
{
    char *new_command = NULL;

    if (seq[0] != '[')
        return;
    if (seq[1] == 'A' || seq[1] == 'B') {
        new_command = history_navigation(seq);
        if (new_command) {
            memset(line, 0, 1024);
            strcpy(line, new_command);
            *len = strlen(new_command);
            *pos = *len;
        }
    }
}
