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
#include <sys/types.h>
#include <sys/wait.h>
#include "my.h"
#include "project.h"

const command_t command[] = {
    {"|", handle_pipes},
    {";", handle_semicolon},
    {"&&", handle_double_ampersand},
    {"||", handle_double_pipe},
    {NULL, NULL}
};

static int match_special_command(const char *arg)
{
    for (int i = 0; command[i].command != NULL; i++) {
        if (my_strcmp(arg, command[i].command) == 0)
            return i;
    }
    return -1;
}

int is_command(env_t *head, char **args, int *exit_status)
{
    int index = 0;

    if (!args || !args[0])
        return 0;
    for (int j = 0; args[j] != NULL; j++) {
        index = match_special_command(args[j]);
        if (index != -1) {
            command[index].function(args, head, exit_status);
            return 1;
        }
    }
    return 0;
}
