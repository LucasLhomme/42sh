/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** hand_buffer
*/

#include "my.h"
#include "lib.h"
#include <unistd.h>
#include <sys/wait.h>

int hand_buffer(char *buffer, char **env)
{
    int exit_status = 0;

    if (my_strchr(buffer, '|') != NULL) {
        exit_status = simple_pipe(buffer, env);
        if (exit_status != 0)
            return exit_status;
        return exit_status;
    }
    if (my_strchr(buffer, ';') != NULL) {
        exit_status = simple_semicolon(buffer, env);
        if (exit_status != 0)
            return exit_status;
        return exit_status;
    }
    if (my_strchr(buffer, '>') != NULL || my_strchr(buffer, '<') != NULL) {
        exit_status = redirect(buffer, env);
        if (exit_status != 0)
            return exit_status;
        return exit_status;
    }
    if (buffer[0] != '\0') {
        exit_status = hand_command(buffer, env);
        if (exit_status != 0)
            return exit_status;
        return exit_status;
    }
    return 0;
}
