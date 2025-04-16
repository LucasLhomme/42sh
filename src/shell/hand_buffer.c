/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** hand_buffer
*/

#include "my.h"
#include "lib.h"

const handle_redirect_t redirect_table[] = {
    {"||", handle_double_pipe},
    {"|", simple_pipe},
    {";", simple_semicolon},
    {">", redirect},
    {"<", redirect},
    {"&&", handle_double_ampersand},
    {NULL, NULL}
};

int hand_buffer(char *buffer, char **env)
{
    for (int i = 0; redirect_table[i].command != NULL; i++) {
        if (my_strstr(buffer, redirect_table[i].command) != NULL)
            return redirect_table[i].func(buffer, env);
    }
    return hand_command(buffer, env);
}
