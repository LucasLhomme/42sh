/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** my_unsetenv.c
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

str_and_int_t *def_unsetenv(char **args, env_t *head, char **env)
{
    str_and_int_t *bundle = malloc(sizeof(str_and_int_t));
    int len_args = len_tab(args);

    if (!head)
        head = def_linked_list(env[0], 0, env);
    if (len_args > 2)
        return NULL;
    if (len_args == 0) {
        my_putstrerror("unsetenv: Too few arguments.\n");
        return NULL;
    }
    bundle->i = my_strlen(args[1]) + 1;
    bundle->str = my_strcat(args[1], "=");
    return bundle;
}

int my_unsetenv(char **args, env_t *head, char **env, int *exit_status)
{
    env_t *temp = NULL;
    str_and_int_t *bundle = def_unsetenv(args, head, env);

    (void)exit_status;
    (void)env;
    if (!bundle)
        return 1;
    temp = head;
    head = head->next;
    while (head) {
        if (my_strncmp(bundle->str, head->line, bundle->i) == 0)
            break;
        if (head->next == NULL)
            return 1;
        temp = temp->next;
        head = head->next;
    }
    temp->next = head->next;
    free(head);
    return 0;
}
