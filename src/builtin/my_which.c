/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle which built-in
*/

#include "project.h"
#include "my.h"

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

static char *find_executable(char *command, char **shell_env)
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

static int which_validate(char **args, env_t *head, char ***env_array)
{
    if (!args[1]) {
        printf("which: Too few arguments.\n");
        return 1;
    }
    *env_array = convert_env_to_array(head);
    if (!*env_array) {
        printf("%s: Command not found.", args[1]);
        return 84;
    }
    return 0;
}

void use_useless(int *exit_status, char **env)
{
    (void) exit_status;
    (void) env;
}

int my_which(char **args, env_t *head, char **env, int *exit_status)
{
    char *path = NULL;
    int result = 0;
    char **env_array = NULL;
    int valid_result = which_validate(args, head, &env_array);

    use_useless(exit_status, env);
    if (valid_result != 0)
        return valid_result;
    for (int i = 1; args[i] != NULL; i++) {
        path = find_executable(args[i], env_array);
        if (path) {
            printf("%s\n", path);
            free(path);
        } else {
            printf("%s: Command not found.\n", args[i]);
            result = 1;
        }
    }
    free_env_array(env_array);
    return result;
}
