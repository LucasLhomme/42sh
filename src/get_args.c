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
#include "my.h"
#include "project.h"

void parse_args(char *line, char **args, int size)
{
    int argc = 0;
    char *token = strtok(line, " \t");

    while (token && argc < size) {
        args[argc] = token;
        argc++;
        token = strtok(NULL, " \t");
    }
    args[argc] = NULL;
}

char *read_line(void)
{
    char *line = NULL;
    size_t len = 0;

    if (isatty(STDIN_FILENO) == 1)
        if (print_prompt() == 84)
            write(1, "$> ", 3);
    if (getline(&line, &len, stdin) == -1) {
        free(line);
        return (NULL);
    }
    line[my_strcspn(line, "\n")] = '\0';
    return (line);
}
