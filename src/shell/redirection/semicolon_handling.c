/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** semicolumn_handling.c
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "project.h"
#include "my.h"

static int handle_no_semicolon(char **args, int *nb_args, char *token)
{
    if (!token)
        return 1;
    args[*nb_args] = token;
    (*nb_args)++;
    return 1;
}

static void handle_semicolon_case(char **args,
    int *nb_args, char **current_token, char *semicolon)
{
    if (semicolon == *current_token) {
        args[*nb_args] = ";";
        (*nb_args)++;
        (*current_token)++;
    } else {
        *semicolon = '\0';
        args[*nb_args] = *current_token;
        (*nb_args)++;
        args[*nb_args] = ";";
        (*nb_args)++;
        *current_token = semicolon + 1;
    }
}

int semicolon_handling(char **args, int *nb_args, char **current_token)
{
    char *token = NULL;
    char *semicolon = NULL;

    token = *current_token;
    semicolon = strchr(token, ';');
    if (!semicolon)
        return handle_no_semicolon(args, nb_args, token);
    handle_semicolon_case(args, nb_args, current_token, semicolon);
    return 0;
}

static void execute_segment(char **args,
    env_t *head, int *exit_status, separator_index_t *index)
{
    for (int i = index->start; i < index->end; i++) {
        if (args[i] && my_strcmp(args[i], "") != 0) {
            args[index->end] = NULL;
            execute_command(&args[index->start], head, exit_status);
            break;
        }
    }
}

int handle_semicolon(char **args, env_t *head, int *exit_status)
{
    separator_index_t index = {0};

    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], ";") == 0) {
            index.end = i;
            execute_segment(args, head, exit_status, &index);
            index.start = i + 1;
        }
    }
    index.end = -1;
    for (int i = index.start; args[i] != NULL; i++) {
        if (args[i] && my_strcmp(args[i], "") != 0) {
            execute_command(&args[index.start], head, exit_status);
            break;
        }
    }
    return 0;
}
