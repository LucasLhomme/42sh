/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** searching_bin
*/

#include "lib.h"
#include "my.h"

static int is_valid_home_path(char *path)
{
    return path[0] != '\0';
}

char *find_env(char *path, char **env)
{
    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], "HOME=", 5) == 0) {
            path = env[i] + 5;
            break;
        }
    }
    if (path != NULL && !is_valid_home_path(path))
        return NULL;
    return path;
}

static int handle_command_not_found(char **argv, char *path)
{
    if (path != NULL)
        free(path);
    if (argv != NULL && argv[0] != NULL)
        my_printf("%s: Command not found.\n", argv[0]);
    free_argv(argv);
    return 1;
}

static char *expand_tilde(char *arg, char **env)
{
    char *home_path;
    char *new_path;

    if (arg[0] != '~')
        return arg;
    home_path = find_env(NULL, env);
    if (home_path == NULL)
        return arg;
    new_path = malloc(my_strlen(home_path) + my_strlen(arg) + 1);
    if (new_path == NULL)
        return arg;
    my_strcpy(new_path, home_path);
    my_strcat(new_path, arg + 1);
    free(arg);
    return new_path;
}

static int execute_command(char *path, char **argv, char **env)
{
    if (access(path, X_OK) == 0)
        return execute_bin(path, argv, env);
    return handle_command_not_found(argv, path);
}

static int handle_empty_or_null_argv(char *buffer, char **argv)
{
    if (argv == NULL || argv[0] == NULL) {
        if (argv != NULL) {
            free_argv(argv);
            return 1;
        }
        my_printf("%s: Command not found.\n", buffer);
        return 1;
    }
    return 0;
}

static int handle_directory_case(char **argv)
{
    struct stat st;

    if (argv[0] != NULL && argv[0][0] != '\0') {
        if (stat(argv[0], &st) == 0 && S_ISDIR(st.st_mode)) {
            my_printf("%s: Is a directory.\n", argv[0]);
            free_argv(argv);
            return 1;
        }
    }
    return 0;
}

static int handle_null_path(char **argv, char *path)
{
    if (path == NULL) {
        my_printf("%s: Command not found.\n", argv[0]);
        free_argv(argv);
        return 1;
    }
    return 0;
}

int searching_bin(char *buffer, char **env)
{
    char **argv = my_str_to_word_array(buffer);
    char *path = NULL;

    if (find_env(NULL, env) == NULL) {
        free_argv(argv);
        return 1;
    }
    if (argv != NULL && argv[0] != NULL && my_strncmp(argv[0], "/", 1) == 0)
        return 0;
    if (handle_empty_or_null_argv(buffer, argv))
        return 1;
    argv[0] = expand_tilde(argv[0], env);
    if (handle_directory_case(argv))
        return 1;
    path = concas_command(argv, env);
    if (handle_null_path(argv, path))
        return 1;
    return execute_command(path, argv, env);
}
