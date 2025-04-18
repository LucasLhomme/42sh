/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** my_env.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "project.h"
#include "my.h"

int my_env(char **args, env_t *head, char **env, int *last_exit_status)
{
    (void)last_exit_status;
    (void)args;
    (void)env;
    if (!head)
        return 1;
    else
        print_list(head);
    return 0;
}
