/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_ctrl
*/

#include <unistd.h>
#include "project.h"

int check_ctrl(handle_ctrl_t *handle_ctrl, int *exit_status,
    history_t *history, env_t *head)
{
    if (handle_ctrl->c == 12)
        *exit_status = handle_ctrl_l(handle_ctrl->line,
    handle_ctrl->pos, handle_ctrl->len);
    if (handle_ctrl->c == 1)
        *exit_status = handle_ctrl_a(handle_ctrl->pos);
    if (handle_ctrl->c == 5)
        *exit_status = handle_ctrl_e(handle_ctrl->pos, handle_ctrl->len);
    if (handle_ctrl->c == 21)
        *exit_status = handle_ctrl_u(handle_ctrl->line, handle_ctrl->pos,
    handle_ctrl->len);
    if (handle_ctrl->c == 11)
        *exit_status = handle_ctrl_k(handle_ctrl->line, handle_ctrl->pos,
            handle_ctrl->len);
    if (handle_ctrl->c == 23)
        return handle_ctrl_w(handle_ctrl);
    if (handle_ctrl->c == 4)
        return -2;
    return *exit_status;
}
