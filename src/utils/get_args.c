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

static void parse_token(char *token, char **args, int *argc, int size)
{
    while (*token && *argc < size) {
        if (semicolon_handling(args, argc, &token))
            break;
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
