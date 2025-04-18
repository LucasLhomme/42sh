/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle echo command
*/

#include "my.h"
#include "project.h"

int my_echo(char **args, env_t *head, char **env, int *last_exit_status)
{
    (void)env;
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "echo") == 0 && strcmp(args[i + 1], "$?") == 0) {
            printf("%d\n", last_exit_status[0]);
            return 0;
        }
        if (strcmp(args[i], "echo") == 0) {
            execute_command(args, head, last_exit_status);
            return 0;
        }
    }
    return 1;
}
