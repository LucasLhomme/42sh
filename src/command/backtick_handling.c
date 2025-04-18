/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** backtick_handling.c
*/

#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int is_backtick(char **args, int idx)
{
    char c = 0;

    for (; args[idx] != NULL; idx++) {
        c = get_last_char(args[idx]);
        if (args[idx][0] == '`' && c == '`') {
            return idx;
        }
    }
    return 0;
}

static char *extract_command(const char *start, const char *end)
{
    size_t len = end - start - 1;

    return strndup(start + 1, len);
}

static char *execute_backtick(const char *command)
{
    FILE *fp = popen(command, "r");
    char *result = NULL;
    size_t size = 0;
    ssize_t read = 0;

    if (!fp)
        return NULL;
    read = getdelim(&result, &size, '\0', fp);
    pclose(fp);
    if (read <= 0) {
        free(result);
        return NULL;
    }
    result[strcspn(result, "\n")] = '\0';
    return result;
}

static char *build_new_argument(const char *arg, const char *start,
    const char *end, const char *result)
{
    size_t prefix_len = start - arg;
    size_t suffix_len = strlen(end + 1);
    size_t total_len = prefix_len + strlen(result) + suffix_len + 1;
    char *new_arg = malloc(total_len);

    if (!new_arg)
        return NULL;
    strncpy(new_arg, arg, prefix_len);
    new_arg[prefix_len] = '\0';
    strcat(new_arg, result);
    strcat(new_arg, end + 1);
    return new_arg;
}

char *handle_backtick(const char *arg)
{
    const char *start = strchr(arg, '`');
    const char *end = strrchr(arg, '`');
    char *command = NULL;
    char *result = NULL;
    char *new_arg = NULL;

    if (!start || !end || start == end)
        return strdup(arg);
    command = extract_command(start, end);
    if (!command)
        return strdup(arg);
    result = execute_backtick(command);
    free(command);
    if (!result)
        return strdup(arg);
    new_arg = build_new_argument(arg, start, end, result);
    free(result);
    return new_arg ? new_arg : strdup(arg);
}

void free_args(char **args)
{
    if (!args)
        return;
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}

int backtick_handle(char **args, int *last_exit_status)
{
    char *new_arg = NULL;

    (void)last_exit_status;
    for (int i = 0; args[i] != NULL; i++) {
        if (strchr(args[i], '`')) {
            new_arg = handle_backtick(args[i]);
            args[i] = new_arg;
        }
    }
    return 0;
}
