/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** command_cd
*/

#include "my.h"
#include "lib.h"

int handling_error(char *path, char *current)
{
    int exit_status = 0;

    if (chdir(path) != 0) {
        if (errno == ENOTDIR) {
            printf("%s: Not a directory.\n", path);
            exit_status = 1;
        }
        if (errno == ENOENT) {
            printf("%s: No such file or directory.\n", path);
            exit_status = 1;
        }
        if (access(path, X_OK) != 0) {
            printf("%s: Permission denied.\n", path);
            exit_status = 1;
        }
        free(current);
    }
    return exit_status;
}

void prev_cd(char *buffer)
{
    cleaning_buffer(buffer);
    chdir(buffer);
}

int change_directory(char *path, char *current, char **prev)
{
    if (strncmp(path, "cd", 2) == 0)
        return 0;
    if (strcmp(path, "-") == 0) {
        prev_cd(*prev);
        free(*prev);
        *prev = current;
        return 0;
    }
    if (handling_error(path, current) != 0) {
        return 1;
    }
    if (*prev)
        free(*prev);
    *prev = current;
    return 0;
}

static char *find_env_home(char *path, char **env)
{
    for (int i = 0; env[i]; i++) {
        if (strncmp(env[i], "HOME=", 5) == 0) {
            path = env[i] + 5;
            break;
        }
    }
    return path;
}

int my_cd(char *buffer, char **env)
{
    static char *prev = NULL;
    char *path = strtok(buffer, " ");
    char *current = getcwd(NULL, 0);

    path = strtok(NULL, " ");
    if (strtok(NULL, " ") != NULL) {
        printf("cd: Too many arguments.\n");
        free(current);
        return 1;
    }
    if (!path || strcmp(path, "") == 0 || strncmp(path, "~", 1) == 0) {
        path = find_env_home(path, env);
        if (!path) {
            free(current);
            return 0;
        }
    }
    trim_whitespace(path);
    return change_directory(path, current, &prev);
}
