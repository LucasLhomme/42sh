/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** no_name.c
*/

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my.h"
#include "project.h"

int ensure_capacity(handle_ctrl_t *ctrl)
{
    char *new_line = NULL;

    if (*(ctrl->pos) + 1 >= ctrl->capacity) {
        ctrl->capacity *= 2;
        new_line = realloc(*(ctrl->line_ptr), ctrl->capacity);
        if (!new_line)
            return -1;
        *(ctrl->line_ptr) = new_line;
        ctrl->line = *(ctrl->line_ptr);
    }
    return 0;
}

static int reallocate_if_needed(handle_ctrl_t *ctrl)
{
    char *new_line = NULL;

    if (*ctrl->len + 1 >= ctrl->capacity) {
        ctrl->capacity *= 2;
        new_line = realloc(*ctrl->line_ptr, ctrl->capacity);
        if (!new_line)
            return -1;
        *ctrl->line_ptr = new_line;
        ctrl->line = *ctrl->line_ptr;
    }
    return 0;
}

static void shift_characters(handle_ctrl_t *ctrl)
{
    if (*ctrl->pos < *ctrl->len) {
        memmove(&ctrl->line[*ctrl->pos + 1], &ctrl->line[*ctrl->pos],
                *ctrl->len - *ctrl->pos);
    }
}

static void insert_at_position(handle_ctrl_t *ctrl)
{
    ctrl->line[*ctrl->pos] = ctrl->c;
    (*ctrl->len)++;
    (*ctrl->pos)++;
}

static void display_after_insert(handle_ctrl_t *ctrl)
{
    if (*ctrl->pos < *ctrl->len) {
        write(1, &ctrl->line[*ctrl->pos - 1], *ctrl->len - *ctrl->pos + 1);
        write_char(ctrl->pos, ctrl->len);
    } else {
        write(1, &ctrl->c, 1);
    }
}

void insert_char(handle_ctrl_t ctrl)
{
    if (reallocate_if_needed(&ctrl) == -1)
        return;
    shift_characters(&ctrl);
    insert_at_position(&ctrl);
    display_after_insert(&ctrl);
}
