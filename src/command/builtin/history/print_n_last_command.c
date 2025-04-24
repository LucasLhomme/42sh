/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** print_n_last_command.c
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"
#include <stdlib.h>
#include <string.h>

void print_good_command(history_t *head, int idx, int id)
{
    if (id >= idx) {
        if (head->command)
            printf("%s\n", head->command);
    }
}

int print_last_n(history_t *head, int idx)
{
    int id = 0;
    int nb_node = 0;

    if (!head)
        return 1;
    nb_node = count_node(head);
    if (idx != 0)
        idx = nb_node - idx;
    while (head) {
        print_good_command(head, idx, id);
        id++;
        head = head->next;
    }
    return 0;
}
