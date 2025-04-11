/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** unsetenv
*/

#include "lib.h"
#include "my.h"

int verify_buffer(char *path, char **current)
{
    if (!path || my_strcmp(path, "") == 0) {
        my_printf("unsetenv: Too few arguments.");
        free(*current);
        *current = NULL;
        return 1;
    }
    return 0;
}

int check_name(char *name)
{
    if (!name) {
        my_printf("unsetenv: Too few arguments.\n");
        return 1;
    }
    return 0;
}

static int count_env_vars(char **env)
{
    int count = 0;

    if (env == NULL)
        return 0;
    while (env[count] != NULL)
        count++;
    return count;
}

static void copy_env_vars(char **env, char **new_env, char *name, int *j)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], name, my_strlen(name)) != 0 ||
        env[i][my_strlen(name)] != '=') {
            new_env[*j] = env[i];
            (*j)++;
        }
    }
    new_env[*j] = NULL;
}

int my_unsetenv(char *name, char **env)
{
    int j = 0;
    int env_len = count_env_vars(env);
    char **new_env = NULL;

    if (check_name(name))
        return 1;
    new_env = malloc(sizeof(char *) * (env_len + 1));
    if (new_env == NULL)
        return 1;
    copy_env_vars(env, new_env, name, &j);
    for (int i = 0; i < j; i++)
        env[i] = new_env[i];
    env[j] = NULL;
    free(new_env);
    return 0;
}
