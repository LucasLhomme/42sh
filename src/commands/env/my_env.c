/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** my_env
*/
#include "my.h"
#include "lib.h"

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
