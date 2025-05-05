/*
** EPITECH PROJECT, 2024
** B-CPE-110-LIL-1-1-organized-joseph.birck
** File description:
** file.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "my.h"
#include "project.h"
#include <signal.h>

static char *construct_full_path(const char *dir, const char *command)
{
    char full_path[256];

    my_strcpy(full_path, dir);
    my_strcat(full_path, "/");
    my_strcat(full_path, command);
    return strdup(full_path);
}

char *find_path(char *command, env_t *head)
{
    char *path = get_env("PATH", head);
    char *paths = NULL;
    char *dir = NULL;
    char *full_path = NULL;

    if (!path)
        return NULL;
    paths = strdup(path);
    dir = strtok(paths, ":");
    while (dir) {
        full_path = construct_full_path(dir, command);
        if (full_path && access(full_path, X_OK) == 0) {
            free(paths);
            return full_path;
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }
    free(paths);
    return NULL;
}

char *resolve_command_path(char **args, env_t *head)
{
    if (!args[0])
        exit(0);
    if (my_strchr(args[0], '/') != NULL) {
        if (access(args[0], X_OK) == 0)
            return args[0];
        return NULL;
    }
    if (!head)
        return NULL;
    return find_path(args[0], head);
}

static int execute_child_process(char *cmd_path, char **args, env_t *head)
{
    if (execve(cmd_path, args, convert_env_to_array(head)) == -1){
        my_putstrerror(args[0]);
        my_putstrerror(": Exec format error. Binary file not executable.\n");
        kill(getpid(), SIGKILL);
        exit(1);
    }
    print_error(cmd_path, strerror(errno));
    exit(2);
}

static void free_if_necessary(char *cmd_path, char *original_cmd)
{
    if (cmd_path != original_cmd) {
        free(cmd_path);
    }
}

static void handle_parent_process(pid_t pid, int *exit_status,
    char *cmd_path, char *original_cmd)
{
    int status;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        *exit_status = WEXITSTATUS(status);
    }
    free_if_necessary(cmd_path, original_cmd);
}

int handle_execution_failure(char *cmd_path, char *cmd, int *exit_status)
{
    if ((my_strcmp(cmd, ">") == 0) || (my_strcmp(cmd, ">>") == 0) ||
        (my_strcmp(cmd, "<") == 0)) {
        my_putstrerror("Missing name for redirect.\n");
        *exit_status = 1;
    } else {
        *exit_status = 1;
        print_error(cmd, "Command not found.");
    }
    free_if_necessary(cmd_path, cmd);
    return *exit_status;
}

pid_t create_child_process(char *cmd_path, char **args, env_t *head)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        free_if_necessary(cmd_path, args[0]);
        return -1;
    }
    if (pid == 0) {
        if (redirection(args) == 1) {
            exit(1);
        }
        execute_child_process(cmd_path, args, head);
    }
    return pid;
}

void execute_command(char **args, env_t *head, int *exit_status)
{
    char *cmd_path = NULL;
    pid_t pid = {0};

    if (is_command(head, args, exit_status) == 1)
        return;
    if (is_backtick(args, 0) != 0)
        backtick_handle(args, exit_status);
    cmd_path = resolve_command_path(args, head);
    if (!cmd_path) {
        handle_execution_failure(cmd_path, args[0], exit_status);
        return;
    }
    pid = create_child_process(cmd_path, args, head);
    if (pid > 0)
        handle_parent_process(pid, exit_status, cmd_path, args[0]);
}
