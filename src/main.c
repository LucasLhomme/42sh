/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** main
*/

#include "lib.h"
#include "my.h"
#include <string.h>

int handle_child_process(char **env)
{
    if (isatty(STDIN_FILENO) == 1)
        return loop_terminal(env);
    else
        return loop_tty(env);
}

void print_signal_message(int status)
{
    char *signal_message = strsignal(WTERMSIG(status));

    if (signal_message != NULL)
        write(STDERR_FILENO, signal_message, my_strlen(signal_message));
    else
        write(STDERR_FILENO, "Unknown signal", 14);
    if (WCOREDUMP(status))
        write(STDERR_FILENO, " (core dumped)", 14);
    write(STDERR_FILENO, "\n", 1);
}

int handle_parent_process(pid_t id)
{
    int status = 0;
    int exit_status = 0;

    if (waitpid(id, &status, 0) == -1) {
        perror("waitpid failed");
        return EXIT_FAILURE;
    }
    if (WIFEXITED(status))
        exit_status = WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        print_signal_message(status);
        exit_status = 128 + WTERMSIG(status);
        return exit_status;
    }
    return exit_status;
}

pid_t initialize_fork(void)
{
    pid_t id = fork();

    if (id == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    return id;
}

int main(int ac, char **argv, char **env)
{
    pid_t id = initialize_fork();
    char **new_env = env;

    if (argv == NULL || ac < 1)
        return 84;
    if (id == 0)
        exit(handle_child_process(new_env));
    else
        return handle_parent_process(id);
}
