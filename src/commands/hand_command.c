/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** hand_command
*/
#include "lib.h"
#include "my.h"

const handle_command_t commands[] = {
    {"cd", my_cd},
    {"env", my_env},
    {"setenv", my_setenv},
    {"unsetenv", my_env},
    {NULL, NULL}
};

int hand_command(char *buffer, char **env)
{
    for (int i = 0; commands[i].command != NULL; i++) {
        if (my_strncmp(buffer, commands[i].command,
            my_strlen(commands[i].command)) == 0)
            return commands[i].func(buffer, env);
    }
    return searching_bin(buffer, env);
}
