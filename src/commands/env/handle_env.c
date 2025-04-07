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
        my_printf("%s\n", env[i]);
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
    my_printf("setenv: Too many arguments.\n");
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
        if (my_strncmp(env[i], name, my_strlen(name)) == 0 &&
        env[i][my_strlen(name)] == '=') {
            new_entry = malloc(my_strlen(name) + 2);
            my_strcpy(new_entry, name);
            my_strcat(new_entry, "=");
            env[i] = new_entry;
            return 0;
        }
    }
    result = new_value_env(name, env);
    return result;
}
