/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** get_env.c
*/

#include "../../include/my.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char *get_env(const char *var, env_t *head)
{
    int len = my_strlen(var);

    for (env_t *tmp = head; tmp != NULL; tmp = tmp->next) {
        if (my_strncmp(tmp->line, var, len) == 0 && tmp->line[len] == '=') {
            return tmp->line + len + 1;
        }
    }
    return NULL;
}
