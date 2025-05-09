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
#include <string.h>
#include <stdio.h>
#include "project.h"

void print_history(history_t *head)
{
    if (head == NULL)
        return;
    while (head != NULL) {
        printf("%s\n", head->command);
        head = head->next;
    }
}

history_t *create_history_node(const char *line)
{
    history_t *node = malloc(sizeof(history_t));

    if (!node)
        return NULL;
    node->command = strdup(line);
    node->next = NULL;
    node->prev = NULL;
    return node;
}

history_t *add_command_to_history(history_t *head, char *command)
{
    history_t *new_node = create_history_node(command);
    history_t *temp;

    if (!new_node)
        return head;
    if (!head)
        return new_node;
    temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
    new_node->prev = temp;
    return head;
}

history_t *def_linked_list_history(FILE *history_file)
{
    history_t *head = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (!history_file)
        return NULL;
    while (1) {
        read = getline(&line, &len, history_file);
        if (read == -1)
            break;
        if (read > 0 && line[read - 1] == '\n')
            line[read - 1] = '\0';
        head = add_command_to_history(head, line);
    }
    free(line);
    return head;
}

void free_history(history_t *head)
{
    history_t *tmp = NULL;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->command);
        free(tmp);
    }
}
