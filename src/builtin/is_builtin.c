/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** is_builtin.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "my.h"
#include "project.h"

const builtin_t builtin[] = {
    {"cd", my_cd},
    {"env", my_env},
    {"exit", my_exit},
    {"setenv", my_setenv},
    {"unsetenv", my_unsetenv},
    {"echo", my_echo},
    {"which", my_which},
    {"where", my_where},
    {NULL, NULL}
};

int is_builtin(env_t *head, char **args, char **env, int *exit_status)
{
    for (int i = 0; builtin[i].command != NULL; i++) {
        if (my_strstr(args[0], builtin[i].command) != NULL) {
            builtin[i].function(env, head, args, exit_status);
            return 1;
        }
    }
    return 0;
}
