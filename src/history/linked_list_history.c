/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** linked_list_history.c
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

history_t *add_command(history_t *head, char *command)
{
    static int idx = 0;
    history_t *node = malloc(sizeof(history_t));
    history_t *temp;

    if (node == NULL)
        return NULL;
    node->command = strdup(command);
    if (!node->command)
        return NULL;
    node->idx = idx;
    node->next = NULL;
    if (!head)
        return node;
    temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = node;
    idx++;
    return head;
}

void print_history(history_t *head)
{
    if (head == NULL)
        return;
    while (head != NULL) {
        printf("%s\n", head->command);
        head = head->next;
    }
}

history_t *def_linked_list_history(char *command)
{
    history_t *head = NULL;

    if (command == NULL) {
        return head;
    }
    head = add_command(head, command);
    return head;
}

void free_history(history_t *head)
{
    history_t *temp;

    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
