/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** command_env
*/
#include "my.h"
#include "lib.h"

int print_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        my_printf("%s\n", env[i]);
    return 0;
}

int check_var(char *name)
{
    if (!name)
        return 84;
    for (int i = 0; name[i] != '\0'; i++) {
        if (!my_isalpha(name[0])) {
            my_printf("setenv: Variable name must begin with a letter.\n");
            return 1;
        }
        if (nonalphanum(name[i]) != 0) {
            my_printf
            ("setenv: Variable name must contain alphanumeric characters.\n");
            return 1;
        }
        if ((!my_isalpha(name[i]) && !my_isnum(name[i]))) {
            my_printf("setenv: Variable name must ");
            my_printf("contain only alphanumeric characters.\n");
            return 1;
        }
    }
    return 0;
}

static void free_argv(char **argv)
{
    for (int i = 0; argv[i] != NULL; i++)
        free(argv[i]);
    free(argv);
}

static int handle_no_arguments(char **env, char **argv)
{
    print_env(env);
    free_argv(argv);
    return 0;
}

static int handle_too_many_arguments(char **argv)
{
    my_printf("setenv: Too many arguments.\n");
    free_argv(argv);
    return 1;
}

static int handle_invalid_variable_name(int exit_check_var, char **argv)
{
    free_argv(argv);
    return exit_check_var;
}

static int handle_null_value(char *name, char **env, char **argv)
{
    int result = new_value_env(name, env);

    free_argv(argv);
    return result;
}

static int handle_name_and_value(char *name, char *value,
    char **env, char **argv)
{
    int result = over_value_env(name, value, env);

    free_argv(argv);
    return result;
}

int my_setenv(char *buffer, char **env)
{
    char **argv = my_str_to_word_array(buffer);
    char *name = argv[1];
    char *value = argv[2];
    int exit_check_var = check_var(name);

    if (!argv[1])
        return handle_no_arguments(env, argv);
    if (argv[1] && argv[2] && argv[3])
        return handle_too_many_arguments(argv);
    if (exit_check_var != 0)
        return handle_invalid_variable_name(exit_check_var, argv);
    if (value == NULL)
        return handle_null_value(name, env, argv);
    if (name != NULL || value != NULL)
        return handle_name_and_value(name, value, env, argv);
    free_argv(argv);
    return 0;
}

int my_env(char *buffer, char **env)
{
    char **argv = my_str_to_word_array(buffer);
    int result = 0;

    if (my_strncmp(buffer, "unsetenv", 8) == 0)
        result = my_unsetenv(argv[1], env);
    else if (my_strncmp(buffer, "env", 3) == 0)
        result = print_env(env);
    for (int i = 0; argv[i] != NULL; i++)
        free(argv[i]);
    free(argv);
    return result;
}
