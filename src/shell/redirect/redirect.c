/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** redirect
*/

#include "lib.h"
#include "my.h"
#include <fcntl.h>
#include <sys/types.h>

static int handle_redirect_error(char *command, char *file)
{
    if (command == NULL || command[0] == '\0') {
        printf("Invalid null command.\n");
        return 1;
    }
    if (file == NULL || file[0] == '\0') {
        printf("Missing name for redirect.\n");
        return 1;
    }
    return 0;
}

static int execute_command_with_redirect(char *command, char **env, int fd,
    int std_fd)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        close(fd);
        return 1;
    }
    if (pid == 0) {
        dup2(fd, std_fd);
        close(fd);
        if (hand_command(command, env) == -1) {
            printf("%s: Command not found.\n", command);
            exit(1);
        }
        exit(0);
    } else {
        close(fd);
        waitpid(pid, NULL, 0);
    }
    return 0;
}

static int handle_output_redirect(char *command, char *file, char **env,
    int append)
{
    int fd = 0;

    if (!file) {
        printf("Missing name for redirect.\n");
        return 1;
    }
    if (append)
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (handle_redirect_error(command, file))
        return 1;
    return execute_command_with_redirect(command, env, fd, STDOUT_FILENO);
}

static int handle_input_redirect(char *command, char *file, char **env)
{
    int fd = open(file, O_RDONLY);
    int result = execute_command_with_redirect(command, env, fd, STDIN_FILENO);

    if (handle_redirect_error(command, file))
        return 1;
    if (fd == -1) {
        printf("%s: No such file or directory\n", file);
        return 1;
    }
    return result;
}

static int handle_double_output_redirect(char *buffer, char **env)
{
    char *command = trim_whitespace(my_strtok(buffer, ">>"));
    char *file = trim_whitespace(my_strtok(NULL, ">>"));

    return handle_output_redirect(command, file, env, 1);
}

static int handle_single_output_redirect(char *buffer, char **env)
{
    char *command = trim_whitespace(my_strtok(buffer, ">"));
    char *file = trim_whitespace(my_strtok(NULL, ">"));

    return handle_output_redirect(command, file, env, 0);
}

static int handle_single_input_redirect(char *buffer, char **env)
{
    char *command = trim_whitespace(my_strtok(buffer, "<"));
    char *file = trim_whitespace(my_strtok(NULL, "<"));

    if (!file) {
        printf("Missing name for redirect.\n");
        return 1;
    }
    return handle_input_redirect(command, file, env);
}

int redirect(char *buffer, char **env)
{
    if (strstr(buffer, ">>"))
        return handle_double_output_redirect(buffer, env);
    if (strstr(buffer, ">"))
        return handle_single_output_redirect(buffer, env);
    if (strstr(buffer, "<"))
        return handle_single_input_redirect(buffer, env);
    return 1;
}
