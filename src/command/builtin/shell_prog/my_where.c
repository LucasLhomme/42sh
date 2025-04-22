/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle where builtin
*/

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle which built-in
*/

#include "project.h"
#include <string.h>
#include <unistd.h>

static char *get_env_path(char **shell_env)
{
    if (!shell_env)
        return NULL;
    for (int i = 0; shell_env[i]; i++) {
        if (strncmp(shell_env[i], "PATH=", 5) == 0)
            return shell_env[i] + 5;
    }
    return NULL;
}

static char *build_path(char *dir, char *command)
{
    int len_path = strlen(dir);
    int len_cmd = strlen(command);
    char *full_path = malloc(len_path + len_cmd + 2);

    if (!full_path)
        return NULL;
    strcpy(full_path, dir);
    strcat(full_path, "/");
    strcat(full_path, command);
    return full_path;
}

static char *search_in_paths(char *paths, char *command)
{
    char *token = strtok(paths, ":");
    char *full_path = NULL;

    while (token) {
        full_path = build_path(token, command);
        if (!full_path)
            break;
        if (access(full_path, X_OK) == 0)
            return full_path;
        free(full_path);
        token = strtok(NULL, ":");
    }
    return NULL;
}

char *find_executable(char *command, char **shell_env)
{
    char *paths = get_env_path(shell_env);
    char *paths_copy = NULL;
    char *full_path = NULL;

    if (!paths || !shell_env)
        return NULL;
    if (strncmp(command, "/bin/", 5) == 0)
        return strdup(command);
    paths_copy = strdup(paths);
    full_path = search_in_paths(paths_copy, command);
    free(paths_copy);
    return full_path;
}

static int validate_args(char **args)
{
    if (!args[1]) {
        printf("where: Too few arguments.\n");
        return 1;
    }
    return 0;
}

void print_paths(char *command, char **env_array)
{
    char *paths = get_env_path(env_array);
    char *paths_copy = NULL;
    char *token = NULL;
    char *full_path = NULL;

    if (!paths)
        return;
    paths_copy = strdup(paths);
    if (!paths_copy)
        return;
    token = strtok(paths_copy, ":");
    while (token) {
        full_path = build_path(token, command);
        if (full_path && access(full_path, X_OK) == 0)
            printf("%s\n", full_path);
        free(full_path);
        token = strtok(NULL, ":");
    }
    free(paths_copy);
}

void check_builtin_commands(char *command)
{
    const char *builtins[] = {"cd", "env", "exit", "setenv",
        "unsetenv", "echo", "which", "where", NULL};

    for (int i = 0; builtins[i]; i++) {
        if (strcmp(command, builtins[i]) == 0) {
            printf("%s not found\n", command);
            break;
        }
    }
}

int my_where(char **args, env_t *head, char **env, int *exit_status)
{
    char **env_array = NULL;
    int validation_result;

    (void) exit_status;
    (void) env;
    validation_result = validate_args(args);
    if (validation_result != 0)
        return validation_result;
    env_array = convert_env_to_array(head);
    if (!env_array)
        return 84;
    for (int i = 1; args[i] != NULL; i++) {
        check_builtin_commands(args[i]);
        print_paths(args[i], env_array);
    }
    free_env_array(env_array);
    return 0;
}
