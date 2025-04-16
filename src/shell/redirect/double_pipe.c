/*
** EPITECH PROJECT, 2025
** double_pipe.c
** File description:
** if one function fails an other success
*/

#include "my.h"
#include "lib.h"

int handle_double_pipe(char *buffer, char **env)
{
    char *new_buffer = my_strtok(buffer, "||");
    int exit_status = 0;

    for (int i = 0; new_buffer != NULL; i++) {
        if (i > 0 && exit_status == 0)
            break;
        exit_status = hand_command(new_buffer, env);
        new_buffer = my_strtok(NULL, "||");
    }
    return exit_status;
}
