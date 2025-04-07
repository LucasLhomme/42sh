/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** clean_argv
*/
#include <stddef.h>
#include <stdlib.h>

void cleanup_argv(char **argv)
{
    if (argv) {
        for (int i = 0; argv[i] != NULL; i++)
            free(argv[i]);
        free(argv);
    }
}
