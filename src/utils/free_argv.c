/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** free_argv
*/
#include "my.h"
#include <stdlib.h>

void free_argv(char **argv)
{
    for (int i = 0; argv[i] != NULL; i++)
        free(argv[i]);
    free(argv);
}
