/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** command_env
*/

#include "my.h"
#include "lib.h"

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

int update_env_var(char *name, char *value, char **env, int index)
{
    char *new_entry = malloc(my_strlen(name) + my_strlen(value) + 2);

    if (new_entry == NULL)
        return 84;
    my_strcpy(new_entry, name);
    my_strcat(new_entry, "=");
    my_strcat(new_entry, value);
    free(env[index]);
    env[index] = new_entry;
    return 0;
}

int handle_name_and_value(char *name, char *value, char **env)
{
    int name_len = my_strlen(name);

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], name, name_len) == 0 &&
            env[i][name_len] == '=') {
            return update_env_var(name, value, env, i);
        }
    }
    return over_value_env(name, value, env);
}

int process_setenv_args(char **argv, char **env)
{
    char *name = argv[1];
    char *value = argv[2];
    int exit_check_var = check_var(name);

    if (exit_check_var != 0)
        return handle_invalid_variable_name(exit_check_var, argv);
    if (value == NULL)
        return handle_null_value(name, env);
    return handle_name_and_value(name, value, env);
}

int my_setenv(char *buffer, char **env)
{
    char **argv = my_str_to_word_array(buffer);
    int result = 84;

    if (!argv) {
        free_argv(argv);
        return 84;
    }
    if (!argv[1])
        result = handle_no_arguments(env, argv);
    else if (argv[1] && argv[2] && argv[3])
        result = handle_too_many_arguments(argv);
    else
        result = process_setenv_args(argv, env);
    if (result != 0 && result != 1)
        free_argv(argv);
    return result;
}
