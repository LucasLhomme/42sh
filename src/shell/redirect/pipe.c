/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** pipe
*/
#include "my.h"
#include "lib.h"
#include <ctype.h>
#include <errno.h>

int simple_pipe(char *buffer, char **env)
{
    char *command1 = my_strtok(buffer, "|");
    char *command2 = my_strtok(NULL, "|");

    return pipe_command_setup(command1, command2, env);
}
