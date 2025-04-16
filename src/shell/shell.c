/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** shell function
*/

#include "my.h"
#include "lib.h"

int process_input(char *buffer, char **env)
{
    int exit_status = 0;

    if (strcmp(buffer, " ") == 0 || strcmp(buffer, "\t") == 0 || !buffer)
        return 0;
    if (strcmp(buffer, "\n") != 0) {
        cleaning_buffer(buffer);
        exit_status = hand_buffer(buffer, env);
    }
    return exit_status;
}

int loop_terminal(char **env)
{
    size_t len = 0;
    ssize_t read;
    char *buffer = NULL;
    int exit_status = 0;

    while (1) {
        printf("$> ");
        read = getline(&buffer, &len, stdin);
        if (read == -1) {
            free(buffer);
            printf("exit\n");
            break;
        }
        trim_whitespace(buffer);
        if (strcmp(buffer, "exit") == 0)
            break;
        if (strcmp(buffer, "\n") != 0)
        exit_status = process_input(buffer, env);
    }
    return exit_status;
}

int loop_tty(char **env)
{
    size_t len = 0;
    ssize_t read;
    char *buffer = NULL;
    int exit_status = 0;

    while (1) {
        read = getline(&buffer, &len, stdin);
        if (read == -1) {
            free(buffer);
            break;
        }
        if (strcmp(buffer, "exit") == 0)
            break;
        if (strcmp(buffer, "\n") != 0)
        exit_status = process_input(buffer, env);
        if (exit_status != 0)
            return exit_status;
    }
    return exit_status;
}
