/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** handle_env
*/

#include "lib.h"
#include "my.h"

int print_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        printf("%s\n", env[i]);
    return 0;
}

int handle_no_arguments(char **env, char **argv)
{
    print_env(env);
    free_argv(argv);
    return 0;
}

int handle_too_many_arguments(char **argv)
{
    printf("setenv: Too many arguments.\n");
    free_argv(argv);
    return 1;
}

int handle_invalid_variable_name(int exit_check_var, char **argv)
{
    free_argv(argv);
    return exit_check_var;
}

int handle_null_value(char *name, char **env)
{
    char *new_entry = NULL;
    int result = 0;

    for (int i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], name, strlen(name)) == 0 &&
        env[i][strlen(name)] == '=') {
            new_entry = malloc(strlen(name) + 2);
            strcpy(new_entry, name);
            strcat(new_entry, "=");
            env[i] = new_entry;
            return 0;
        }
    }
    result = new_value_env(name, env);
    return result;
}
