/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** get_args.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
#include "project.h"

static char *extract_command(char **str)
{
    char *start = *str;
    size_t len = 0;
    char *word = NULL;

    while (**str && strncmp(*str, "&&", 2) != 0 &&
       strncmp(*str, "||", 2) != 0 && **str != ';')
    (*str)++;
    len = *str - start;
    word = strndup(start, len);
    return word;
}

static int spot_double_ampersand(char **token, char **args, int *argc)
{
    char *sep = NULL;

    if (strncmp(*token, "&&", 2) == 0) {
        sep = strdup("&&");
        args[*argc] = sep;
        (*argc)++;
        *token += 2;
        return 1;
    }
    return 0;
}

static int spot_double_pipe(char **token, char **args, int *argc)
{
    char *sep = NULL;

    if (strncmp(*token, "||", 2) == 0) {
        sep = strdup("||");
        args[*argc] = sep;
        (*argc)++;
        *token += 2;
        return 1;
    }
    return 0;
}

static int spot_semicolon(char **token, char **args, int *argc)
{
    char *sep = NULL;

    if (**token == ';') {
        sep = strdup(";");
        args[*argc] = sep;
        (*argc)++;
        (*token)++;
        return 1;
    }
    return 0;
}

static void spot_command(char **token, char **args, int *argc)
{
    char *word = extract_command(token);

    if (word && *word) {
        args[*argc] = word;
        (*argc)++;
    }
}

static void parse_token(char *token, char **args, int *argc, int size)
{
    while (*token && *argc < size) {
        if (spot_double_pipe(&token, args, argc))
            continue;
        if (spot_double_ampersand(&token, args, argc))
            continue;
        if (spot_semicolon(&token, args, argc))
            continue;
        spot_command(&token, args, argc);
        if (!strncmp(token, "&&", 2) || *token == ';')
            continue;
    }
}

void parse_args(char *line, char **args, int size)
{
    int argc = 0;
    char *token = strtok(line, " \t");

    while (token && argc < size) {
        parse_token(token, args, &argc, size);
        token = strtok(NULL, " \t");
    }
    args[argc] = NULL;
}
