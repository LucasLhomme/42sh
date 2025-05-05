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

void handle_vertical_arrows(char seq[2], handle_ctrl_t *ctrl)
{
    char *new_command = NULL;

    if (seq[0] != '[')
        return;
    if (seq[1] == 'A' || seq[1] == 'B') {
        new_command = history_navigation(seq);
        if (new_command) {
            size_t needed = strlen(new_command) + 1;

            // Réallocation si nécessaire
            if (needed > ctrl->capacity) {
                while (needed > ctrl->capacity)
                    ctrl->capacity *= 2;
                char *new_line = realloc(*ctrl->line_ptr, ctrl->capacity);
                if (!new_line)
                    return; // handle error
                *ctrl->line_ptr = new_line;
                ctrl->line = *ctrl->line_ptr;
            }

            memset(ctrl->line, 0, ctrl->capacity);
            strcpy(ctrl->line, new_command);
            *ctrl->len = strlen(new_command);
            *ctrl->pos = *ctrl->len;
        }
    }
}
