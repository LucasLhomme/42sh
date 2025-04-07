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
    char *new_value = malloc(my_strlen(name) + my_strlen(value) + 3);
    int i = 0;

    if (new_value == NULL)
        return 1;
    my_strcpy(new_value, name);
    my_strcat(new_value, "=");
    my_strcat(new_value, value);
    for (; env[i]; i++) {
        if (my_strncmp(env[i], name, my_strlen(name)) == 0) {
            env[i] = new_value;
        }
    }
    env[i] = new_value;
    env[i + 1] = NULL;
    return 0;
}

int new_value_env(char *name, char **env)
{
    char *new_value = malloc(my_strlen(name) + 2);
    int i = 0;

    if (!name)
        return 84;
    my_strcpy(new_value, name);
    my_strcat(new_value, "=");
    for (; env[i]; i++) {
        if (my_strncmp(env[i], name, my_strlen(name)) == 0) {
            env[i] = new_value;
        }
    }
    env[i] = new_value;
    env[i + 1] = NULL;
    return 0;
}
