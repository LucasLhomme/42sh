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
