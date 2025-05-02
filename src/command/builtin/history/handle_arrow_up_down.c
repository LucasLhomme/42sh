/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** handle_arrow_up_down.c
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"
#include <stdlib.h>
#include <string.h>

static history_t *load_history(void)
{
    static history_t *history_start = NULL;
    static int loaded = 0;
    char *path = 0;
    FILE *file = NULL;

    if (!loaded) {
        path = get_history_file_path();
        file = fopen(path, "r");
        free(path);
        if (file) {
            history_start = make_history_linked_list(file, NULL);
            fclose(file);
        }
        loaded = 1;
    }
    return history_start;
}

static history_t *navigate_history(char direction, history_t *current)
{
    if (direction == 'A' && current && current->prev)
        return current->prev;
    if (direction == 'B' && current && current->next)
        return current->next;
    return current;
}

static void display_current_command(const char *command)
{
    if (!command)
        return;
    write(1, "\33[2K\r", 5);
    print_prompt();
    write(1, command, strlen(command));
    fflush(stdout);
}

char *history_navigation(char seq[2])
{
    static history_t *current = NULL;
    history_t *history_start = load_history();

    if (!history_start || !seq || (seq[1] != 'A' && seq[1] != 'B'))
        return NULL;
    if (!current)
        current = history_start;
    current = navigate_history(seq[1], current);
    if (current && current->command) {
        display_current_command(current->command);
        return current->command;
    }
    return NULL;
}
