/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** print_error
*/
#include "my.h"

void my_putstrerror(const char *str)
{
    if (!str)
        return;
    write(2, str, my_strlen(str));
}

void print_error(const char *cmd, const char *message)
{
    if (cmd) {
        my_putstrerror(cmd);
        my_putstrerror(": ");
    }
    my_putstrerror(message);
    my_putstrerror("\n");
}

void print_error_reverse(const char *cmd, const char *message, int status)
{
    int len = my_strlen(cmd);
    char *cmd_printable = malloc(sizeof(char) * len);

    my_putstrerror(message);
    if (cmd) {
        if (status == 1) {
            cmd_printable = remove_first_char(cmd);
            my_putstrerror(cmd_printable);
            my_putstrerror(".\n");
        } else
            my_putstrerror(cmd);
    }
}
