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
#include <stdlib.h>
#include <string.h>

char *get_history_file_path(void)
{
    char *home = getenv("HOME");
    char *path = NULL;
    size_t len = 0;

    if (!home)
        return NULL;
    len = strlen(home) + strlen("/.history") + 1;
    path = malloc(len);
    if (!path)
        return NULL;
    snprintf(path, len, "%s/.history", home);
    return path;
}

history_t *make_history_linked_list(FILE *history_file, history_t *head)
{
    if (!head)
        head = def_linked_list_history(history_file);
    return head;
}

int handle_history_command(char **tab, history_t **head)
{
    int len = len_args(tab);

    if (len == 1 && strcmp(tab[0], "history") == 0)
        return print_last_n(*head, 0);
    if (len > 1 && strcmp(tab[0], "history") == 0
        && strcmp(tab[1], "clear") == 0)
        return history_clear(head);
    if (len > 1 && strcmp(tab[0], "history") == 0 && is_num(tab[1]) == 0)
        return print_last_n(*head, atoi(tab[1]));
    return 1;
}

int history_handle(char *str, history_t **head)
{
    char **tab = NULL;
    int result = 0;
    char *tmp = str;

    if (!str)
        return 0;
    tmp += strspn(tmp, " \t");
    if (*tmp == '\0')
        return 0;
    tab = my_str_to_word_array(str);
    result = handle_history_command(tab, head);
    free_word_array(tab);
    return result;
}

int history_add(char *line, history_t **history)
{
    size_t len = strlen(line);
    char *history_path = get_history_file_path();
    FILE *history_file = NULL;

    if (!*history) {
        history_file = history_path ? fopen(history_path, "r") : NULL;
        *history = make_history_linked_list(history_file, *history);
        if (history_file)
            fclose(history_file);
    }
    history_file = history_path ? fopen(history_path, "a") : NULL;
    if (history_file != NULL) {
        fwrite(line, sizeof(char), len, history_file);
        fwrite("\n", sizeof(char), 1, history_file);
        fclose(history_file);
    }
    *history = add_command_to_history(*history, line);
    free(history_path);
    return history_handle(line, history);
}
