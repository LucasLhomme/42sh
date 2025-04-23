/*
** EPITECH PROJECT, 2025
** handle_ampersand
** File description:
** execute multiple commands but stop at the first failure
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "project.h"
#include "my.h"

static void execute_last_command(char **args,
    env_t *head, int *exit_status, separator_index_t *index)
{
    for (int i = index->start; args[i] != NULL; i++) {
        if (args[i] && my_strcmp(args[i], "") != 0) {
            execute_command(&args[index->start], head, exit_status);
            break;
        }
    }
}

int handle_double_ampersand(char **args, env_t *head, int *exit_status)
{
    separator_index_t index = {0};

    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "&&") == 0) {
            index.end = i;
            execute_segment(args, head, exit_status, &index);
            index.start = i + 1;
        }
    }
    if (*exit_status == 0) {
        index.end = -1;
        execute_last_command(args, head, exit_status, &index);
    }
    return 0;
}
