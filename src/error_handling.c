/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-joseph.birck
** File description:
** error_handling
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include "my.h"
#include "project.h"

void handle_ctr_c(int sig)
{
    if (sig == SIGINT) {
        printf("\n");
        print_prompt();
    }
}

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

char *remove_first_char(const char *str)
{
    int len = my_strlen(str);
    char *src = malloc(sizeof(char) * len);
    int y = 0;

    for (int i = 1; str[i] != '\0'; i++) {
        src[y] = str[i];
        y++;
    }
    src[y] = '\0';
    return src;
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
