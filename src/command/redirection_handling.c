/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** redirection_handling.c
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "project.h"
#include "my.h"

int open_redirection_file(const char *filename, int flags)
{
    int fd = open(filename, flags, 0644);

    if (fd == -1)
        perror("open");
    return fd;
}

int apply_redirection(int fd, int std_fd, char **args, int i)
{
    if (fd == -1)
        return -1;
    dup2(fd, std_fd);
    close(fd);
    args[i] = NULL;
    return 0;
}

int find_type_redirection(char *arg, char *next_arg)
{
    int fd = 0;

    if (my_strcmp(arg, ">") == 0) {
        fd = open_redirection_file(next_arg, O_WRONLY | O_CREAT | O_TRUNC);
        return fd;
    }
    if (my_strcmp(arg, ">>") == 0) {
        fd = open_redirection_file(next_arg, O_WRONLY | O_CREAT | O_APPEND);
        return fd;
    }
    if (my_strcmp(arg, "<") == 0) {
        fd = open_redirection_file(next_arg, O_RDONLY);
        return fd;
    }
    return -2;
}

int check_redirection_syntax(char **args)
{
    int len = len_tab(args);

    if ((len == 1) && ((my_strcmp(args[0], "<") == 0) ||
        (my_strcmp(args[0], ">") == 0) || (my_strcmp(args[0], ">>") == 0))) {
        my_putstrerror("Missing name for redirect.\n");
        return 1;
    }
    if (my_strcmp(args[len], ">") == 0 || my_strcmp(args[len], ">>") == 0 ||
        my_strcmp(args[len], "<") == 0) {
        my_putstrerror("Missing name for redirect.\n");
        exit(1);
    }
    return 0;
}

static int handle_redirections(char **args)
{
    int fd = 0;

    for (int i = 0; args[i]; i++) {
        if (!args[i + 1])
            break;
        fd = find_type_redirection(args[i], args[i + 1]);
        if (fd == -2)
            continue;
        if (fd == -1)
            return -1;
        if (apply_redirection(fd, (!my_strcmp(args[i], "<")) ? STDIN_FILENO :
            STDOUT_FILENO, args, i) == -1)
            return -1;
        for (int j = i; args[j]; j++) {
            args[j] = args[j + 2];
        }
        i--;
    }
    return 0;
}

int redirection(char **args)
{
    if (check_redirection_syntax(args))
        return 1;
    return handle_redirections(args);
}
