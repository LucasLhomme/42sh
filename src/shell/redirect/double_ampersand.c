/*
** EPITECH PROJECT, 2025
** handle_ampersand
** File description:
** execute multiple commands but stop at the first failure
*/

#include "lib.h"
#include "my.h"

int handle_double_ampersand(char *buffer, char **env)
{
    char *new_buffer = my_strtok(buffer, "&&");
    int exit_status = 0;

    for (int i = 0; new_buffer != NULL; i++) {
        if (i > 0 && exit_status != 0)
            break;
        exit_status = hand_command(new_buffer, env);
        new_buffer = my_strtok(NULL, "&&");
    }
    return exit_status;
}
