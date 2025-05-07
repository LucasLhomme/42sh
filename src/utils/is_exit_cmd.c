/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** is_exit_cmd.c
*/

#include "project.h"

char **is_exit_cmd(char *line)
{
    int size = strlen(line);
    char **args = NULL;

    if (!args)
        return NULL;
    parse_args(line, args, size);
    if (strcmp(args[0], "exit") == 0)
        return args;
    else {
        free_args(args);
        return NULL;
    }
}
