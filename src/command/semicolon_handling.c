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

void free_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

static int execute_cmd(char **args, semicolon_t cmd_index,
    env_t *env, int *last_exit_status)
{
    int cmd_len = cmd_index.end - cmd_index.start;
    char **cmd = NULL;

    if (cmd_len <= 0)
        return 0;
    cmd = malloc(sizeof(char *) * (cmd_len + 1));
    if (!cmd)
        return 84;
    for (int j = 0; j < cmd_len; j++)
        cmd[j] = my_strdup(args[cmd_index.start + j]);
    cmd[cmd_len] = NULL;
    execute_command(cmd, env, last_exit_status);
    free_array(cmd);
    return 0;
}

int handle_semicolon(char **args, env_t *env, int *last_exit_status)
{
    semicolon_t cmd_index = {0};
    int is_semicolon = 0;
    int is_last_arg = 0;

    for (int i = 0; args[i] != NULL; i++) {
        is_semicolon = my_strcmp(args[i], ";") == 0;
        is_last_arg = args[i + 1] == NULL;
        if (!is_semicolon && !is_last_arg)
            continue;
        cmd_index.end = is_semicolon ? i : i + 1;
        if (execute_cmd(args, cmd_index, env, last_exit_status) == 84)
            return 84;
        cmd_index.start = i + 1;
    }
    return *last_exit_status;
}
