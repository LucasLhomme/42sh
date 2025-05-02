/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** execute_seg
*/
#include "my.h"

void execute_segment(char **args,
    env_t *head, int *exit_status, separator_index_t *index)
{
    for (int i = index->start; i < index->end; i++) {
        if (args[i] && my_strcmp(args[i], "") != 0) {
            args[index->end] = NULL;
            execute_command(&args[index->start], head, exit_status);
            break;
        }
    }
}
