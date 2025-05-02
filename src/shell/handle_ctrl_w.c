/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-21-42sh-lucas.lhomme
** File description:
** handle_ctrl_w
*/
#include "project.h"
#include <unistd.h>

static int find_word_start(handle_ctrl_t *ctrl, int *delete_count)
{
    int i = *(ctrl->pos);
    
    if (*(ctrl->pos) <= 0)
        return 1;
    for (; i > 0 && isspace(ctrl->line[i - 1]); i--, (*delete_count)++);
    for (; i > 0 && (isalnum(ctrl->line[i - 1]) ||
    ctrl->line[i - 1] == '_'); i--, (*delete_count)++);
    
    if (*delete_count == 0)
        return 1;
    return i;
}

static void move_cursor_back(int delete_count)
{
    for (int j = 0; j < delete_count; j++)
        write(STDOUT_FILENO, "\b", 1);
}

static void update_line_buffer(handle_ctrl_t *ctrl, int start_pos, int old_len, int delete_count)
{
    for (int j = start_pos; j < old_len; j++)
        ctrl->line[j] = ctrl->line[j + delete_count];
    *(ctrl->len) = old_len - delete_count;
    *(ctrl->pos) = start_pos;
}

static void display_updated_line(handle_ctrl_t *ctrl, int start_pos, int delete_count)
{
    int j = 0;
    
    write(STDOUT_FILENO, ctrl->line + start_pos, *(ctrl->len) - start_pos);
    
    for (j = 0; j < delete_count; j++)
        write(STDOUT_FILENO, " ", 1);
    for (j = 0; j < delete_count + (*(ctrl->len) - start_pos); j++)
        write(STDOUT_FILENO, "\b", 1);
}

int handle_ctrl_w(handle_ctrl_t *ctrl)
{
    int old_len = *(ctrl->len);
    int delete_count = 0;
    int start_pos;
    
    start_pos = find_word_start(ctrl, &delete_count);
    if (start_pos == -1)
        return 0;
    move_cursor_back(delete_count);
    update_line_buffer(ctrl, start_pos, old_len, delete_count);
    display_updated_line(ctrl, start_pos, delete_count);
    
    return 1;
}
