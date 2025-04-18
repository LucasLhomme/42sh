/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** history_handling.c
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"

int history_add(char *line)
{
    static history_t *head = NULL;
    char **line_tab = my_str_to_word_array(line);

    if (line_tab == NULL || line_tab[0] == NULL)
        return 0;
    if (strcmp(line_tab[0], "history") == 0) {
        print_history(head);
        return 1;
    }
    if (!head)
        head = def_linked_list_history(line);
    else
        head = add_command(head, line);
    return 0;
}
