/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** setenv_case.c
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

env_t *home(env_t *head, pack_env_t *pack)
{
    int i = 0;
    int len = my_strlen(pack->new_value);
    int len2 = my_strlen(pack->env_value) + 2;
    char *str = malloc(sizeof(char) * (len2 + len));
    env_t *temp = head;

    if (!str)
        return head;
    my_strcpy(str, pack->env_value);
    my_strcat(str, "=");
    my_strcat(str, pack->new_value);
    str[len + len2] = '\0';
    while (temp) {
        if (i == pack->idx) {
            temp->line = my_strdup(str);
        }
        temp = temp->next;
        i++;
    }
    return head;
}

env_t *casual_add(char *str, char *new_value, env_t *head)
{
    char *temp = NULL;
    int len = my_strlen(str) + my_strlen(new_value) + 2;

    if (!str || !new_value) {
        print_error("setenv", "Invalid arguments");
        return head;
    }
    temp = malloc(len);
    if (!temp) {
        print_error("setenv", "Memory allocation failed");
        return head;
    }
    my_strcpy(temp, str);
    my_strcat(temp, "=");
    my_strcat(temp, new_value);
    head = add_node(head, temp, 0);
    return head;
}

env_t *one_arg(env_t *head, char *arg)
{
    int len = my_strlen(arg);
    char *temp = malloc(sizeof(char) * (len + 2));

    if (!temp)
        return head;
    if (!arg) {
        print_error("setenv", "Invalid arguments");
        return head;
    }
    my_strcpy(temp, arg);
    my_strcat(temp, "=");
    head = add_node(head, temp, 0);
    return head;
}
