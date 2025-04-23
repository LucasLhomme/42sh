/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** semicolumn_handling.c
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "project.h"
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

int handle_semicolon(char **args, env_t *head, int *exit_status)
{
    separator_index_t index = {0};

    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], ";") == 0) {
            index.end = i;
            execute_segment(args, head, exit_status, &index);
            index.start = i + 1;
        }
    }
    index.end = -1;
    for (int i = index.start; args[i] != NULL; i++) {
        if (args[i] && my_strcmp(args[i], "") != 0) {
            execute_command(&args[index.start], head, exit_status);
            break;
        }
    }
    return 0;
}
