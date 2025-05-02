/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** history_clear.c
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"
#include <stdlib.h>
#include <string.h>

int history_clear(history_t **head)
{
    char *history_path = get_history_file_path();
    FILE *history_file;
    history_t *tmp;

    if (!head)
        return 1;
    while (*head) {
        tmp = (*head)->next;
        free((*head)->command);
        free(*head);
        *head = tmp;
    }
    if (history_path) {
        history_file = fopen(history_path, "w");
        if (history_file)
            fclose(history_file);
        free(history_path);
    }
    return 0;
}
