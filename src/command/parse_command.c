/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-joseph.birck
** File description:
** parse_command.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "project.h"

int count_words(const char *str)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == '\t')
            continue;
        else
            count++;
    }
    return count;
}

char **parse_commmand(const char *str)
{
    int words = count_words(str);
    char **args = malloc(sizeof(char *) * words + 1);
    char *command = my_strdup(str);
    char *token;
    int i = 0;

    if (!args || !command)
        return NULL;
    token = strtok(command, " \t");
    while (token) {
        args[i] = my_strdup(token);
        token = strtok(NULL, " \t");
    }
    args[i] = NULL;
    free(command);
    return args;
}
