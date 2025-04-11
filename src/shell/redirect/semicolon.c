/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** semicolon
*/

#include "my.h"
#include "lib.h"

int simple_semicolon(char *buffer, char **env)
{
    char *new_buffer = my_strtok(buffer, ";");
    int exit_status = 0;

    for (int i = 0; new_buffer != NULL; i++) {
        exit_status = hand_command(new_buffer, env);
        new_buffer = my_strtok(NULL, ";");
    }
    return exit_status;
}
