/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** my_exit.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "project.h"
#include "my.h"

static int exit_loop(char *arg)
{
    for (int i = 0; arg[i]; i++) {
        if (arg[i] < '0' || arg[i] > '9') {
            print_error("exit", "numeric argument required");
            return 1;
        }
    }
    return 0;
}

int my_exit(char **args, history_t *history)
{
    int status = 0;

    if (args != NULL && args[0] != NULL && args[1] != NULL) {
        if (exit_loop(args[1])) {
            my_printf("exit\n");
            exit(84);
        }
        status = my_atoi(args[1]);
    }
    if (history)
        free_history(history);
    my_printf("exit\n");
    exit(status);
}
