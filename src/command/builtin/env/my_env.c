/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** my_env.c
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "project.h"

int my_env(char **args, env_t *head, char **env, int *exit_status)
{
    (void)exit_status;
    (void)args;
    (void)env;
    if (!head)
        return 1;
    else
        print_list(head);
    return 0;
}
