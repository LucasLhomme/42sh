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
    static int i = 0;

    char **line_tab = my_str_to_word_array(line);

    if (strcmp(line_tab[0], "history") == 0) {
        if (!head) {
            printf("ya quoi  la ptn\n");
            return 1;
        }
        else {
            print_history(head);
            return 1;
        }
    }
    if (i == 0) {
        head = def_linked_list_history(line);
        i++;
    }
    else {
        printf("bah alors\n");
        add_command(head, line);
    }

    return 0;
}
