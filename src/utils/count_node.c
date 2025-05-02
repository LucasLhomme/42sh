/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** count_node.c
*/

#include "my.h"

int count_node(history_t *head)
{
    int count = 0;

    while (head) {
        head = head->next;
        count++;
    }
    return count;
}
