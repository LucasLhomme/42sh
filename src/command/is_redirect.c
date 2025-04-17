/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** is_redirect.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "my.h"
#include "project.h"
#include <signal.h>

const command_t command[] = {
    {"|", handle_pipes},
    {";", semicolumn_handle},
    {NULL, NULL}
};

static int is_good_command(char *command, char *arg, int *last_exit_status)
{
    if (my_strcmp(arg, command) == 0) {
        return 0;
    }
    return 1;
}

int is_command(env_t *head, char **args, int *last_exit_status)
{
    int result = 0;

    if (!args || !args[0])
        return 0;
    for (int i = 0; command[i].command != NULL; i++) {
        for (int j = 0; args[j] != NULL; j++) {
            result =
                is_good_command(command[i].command, args[j], last_exit_status)
                ? command[i].function(args, head, last_exit_status) : 1;
            return result;
        }
    }
    return 0;
}
