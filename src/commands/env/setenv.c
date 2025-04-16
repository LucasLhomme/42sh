/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** setenv
*/

#include "lib.h"
#include "my.h"

int over_value_env(char *name, char *value, char **env)
{
    char *new_value = malloc(my_strlen(name) + strlen(value) + 3);
    int i = 0;

    if (new_value == NULL)
        return 1;
    strcpy(new_value, name);
    strcat(new_value, "=");
    strcat(new_value, value);
    for (; env[i]; i++) {
        if (strncmp(env[i], name, strlen(name)) == 0) {
            env[i] = new_value;
        }
    }
    env[i] = new_value;
    env[i + 1] = NULL;
    return 0;
}

int new_value_env(char *name, char **env)
{
    char *new_value = malloc(strlen(name) + 2);
    int i = 0;

    if (!name || new_value == NULL)
        return 84;
    strcpy(new_value, name);
    strcat(new_value, "=");
    for (; env[i]; i++) {
        if (strncmp(env[i], name, strlen(name)) == 0) {
            env[i] = new_value;
        }
    }
    env[i] = new_value;
    env[i + 1] = NULL;
    return 0;
}
