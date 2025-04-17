/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-joseph.birck
** File description:
** env.c
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

env_t *add_node(env_t *head, char *line, int status)
{
    env_t *node = malloc(sizeof(env_t));
    env_t *temp;

    if (node == NULL)
        return NULL;
    node->line = line;
    node->is_add = status;
    node->next = NULL;
    if (!head)
        return node;
    temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = node;
    return head;
}

void print_list(env_t *head)
{
    if (head == NULL)
        return;
    while (head != NULL) {
        my_printf("%s\n", head->line);
        head = head->next;
    }
}

env_t *def_linked_list(char *line, int status, char **env)
{
    env_t *head = NULL;

    if (env[0] == NULL) {
        return head;
    }
    head = add_node(head, line, status);
    for (int i = 1; env[i] != NULL; i++) {
        head = add_node(head, env[i], status);
    }
    return head;
}

void free_list(env_t *head)
{
    env_t *temp;

    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
