/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** pipe
*/

#include "my.h"
#include "lib.h"

int simple_pipe(char *buffer, char **env)
{
    char *command1 = strtok(buffer, "|");
    char *command2 = strtok(NULL, "|");

    return pipe_command_setup(command1, command2, env);
}
