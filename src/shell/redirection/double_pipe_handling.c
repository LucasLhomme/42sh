/*
** EPITECH PROJECT, 2025
** double_pipe.c
** File description:
** if one function fails an other success
*/

#include "my.h"

int handle_double_pipe(char **args, env_t *head, int *exit_status)
{
    separator_index_t index = {0};

    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "||") == 0) {
            index.end = i;
            execute_segment(args, head, exit_status, &index);
            index.start = i + 1;
        }
    }
    if (*exit_status != 0) {
        index.end = -1;
        execute_last_command(args, head, exit_status, &index);
    }
    return 0;
}
