/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-joseph.birck
** File description:
** get_env
*/

#include "my.h"
#include "project.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char **convert_env_to_array(env_t *head)
{
    int count = 0;
    env_t *tmp = head;
    char **env_array = NULL;

    while (tmp) {
        count++;
        tmp = tmp->next;
    }
    env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array)
        return NULL;
    tmp = head;
    for (int i = 0; i < count; i++) {
        env_array[i] = my_strdup(tmp->line);
        tmp = tmp->next;
    }
    env_array[count] = NULL;
    return env_array;
}

void free_env_array(char **env_array)
{
    for (int i = 0; env_array[i]; i++)
        free(env_array[i]);
    free(env_array);
}
